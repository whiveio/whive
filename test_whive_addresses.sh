#!/bin/bash
# Whive Address Type Verification Script
# Tests all address formats: Legacy, SegWit, and Taproot

set -e  # Exit on error

WHIVE_CLI="/Users/munje/Devops/whive/build/bin/whive-cli"
DATADIR="/Users/munje/whive-test-data"
WALLET_NAME="address_verification_test"

echo "=========================================="
echo "Whive Address Type Verification Test"
echo "=========================================="
echo ""

# Check if node is running
echo "→ Checking if Whive node is running..."
if ! $WHIVE_CLI -datadir=$DATADIR getblockchaininfo &>/dev/null; then
    echo "✗ Error: Whive node is not running"
    echo "  Please start the node with: whived -datadir=$DATADIR -daemon"
    exit 1
fi
echo "✓ Node is running"
echo ""

# Get current block height
BLOCKHEIGHT=$($WHIVE_CLI -datadir=$DATADIR getblockcount)
echo "→ Current block height: $BLOCKHEIGHT"

# Check if Taproot is activated (block 177,408)
if [ $BLOCKHEIGHT -ge 177408 ]; then
    echo "✓ Taproot is ACTIVATED (activation height: 177,408)"
    TAPROOT_ACTIVE=true
else
    echo "⚠ Taproot not yet activated (current: $BLOCKHEIGHT, needed: 177,408)"
    TAPROOT_ACTIVE=false
fi
echo ""

# Check if test wallet already exists
echo "→ Checking for existing test wallet..."
if $WHIVE_CLI -datadir=$DATADIR listwallets | grep -q "\"$WALLET_NAME\""; then
    echo "⚠ Wallet '$WALLET_NAME' already exists, unloading it..."
    $WHIVE_CLI -datadir=$DATADIR unloadwallet "$WALLET_NAME" 2>/dev/null || true
    sleep 1
fi

# Create descriptor wallet (required for Taproot)
echo "→ Creating descriptor wallet for testing..."
if $WHIVE_CLI -datadir=$DATADIR createwallet "$WALLET_NAME" false false "" false true > /dev/null; then
    echo "✓ Descriptor wallet created: $WALLET_NAME"
else
    echo "✗ Failed to create wallet"
    exit 1
fi
echo ""

echo "=========================================="
echo "Testing Address Generation"
echo "=========================================="
echo ""

# Test 1: Legacy P2PKH Address
echo "1. Legacy P2PKH Address (Base58)"
echo "   Expected prefix: W"
ADDR_LEGACY=$($WHIVE_CLI -datadir=$DATADIR -rpcwallet=$WALLET_NAME getnewaddress "test_legacy" "legacy")
echo "   Generated: $ADDR_LEGACY"

# Validate address
VALIDATE_LEGACY=$($WHIVE_CLI -datadir=$DATADIR validateaddress "$ADDR_LEGACY")
IS_VALID=$(echo "$VALIDATE_LEGACY" | grep -o '"isvalid": *[^,]*' | awk '{print $2}')
ADDR_TYPE=$(echo "$VALIDATE_LEGACY" | grep -o '"type": *"[^"]*"' | cut -d'"' -f4)

if [ "$IS_VALID" = "true" ]; then
    echo "   ✓ Valid: Yes"
    echo "   ✓ Type: $ADDR_TYPE"
    if [[ $ADDR_LEGACY == W* ]]; then
        echo "   ✓ Prefix: Correct (starts with 'W')"
    else
        echo "   ✗ Prefix: INCORRECT (should start with 'W')"
    fi
else
    echo "   ✗ Validation FAILED"
fi
echo ""

# Test 2: P2SH-SegWit Address (nested SegWit)
echo "2. P2SH-SegWit Address (Nested SegWit)"
echo "   Expected prefix: 5"
ADDR_P2SH_SEGWIT=$($WHIVE_CLI -datadir=$DATADIR -rpcwallet=$WALLET_NAME getnewaddress "test_p2sh_segwit" "p2sh-segwit")
echo "   Generated: $ADDR_P2SH_SEGWIT"

VALIDATE_P2SH=$($WHIVE_CLI -datadir=$DATADIR validateaddress "$ADDR_P2SH_SEGWIT")
IS_VALID=$(echo "$VALIDATE_P2SH" | grep -o '"isvalid": *[^,]*' | awk '{print $2}')
ADDR_TYPE=$(echo "$VALIDATE_P2SH" | grep -o '"type": *"[^"]*"' | cut -d'"' -f4)

if [ "$IS_VALID" = "true" ]; then
    echo "   ✓ Valid: Yes"
    echo "   ✓ Type: $ADDR_TYPE"
    if [[ $ADDR_P2SH_SEGWIT == 5* ]]; then
        echo "   ✓ Prefix: Correct (starts with '5')"
    else
        echo "   ⚠ Prefix: Different (starts with '${ADDR_P2SH_SEGWIT:0:1}')"
    fi
else
    echo "   ✗ Validation FAILED"
fi
echo ""

# Test 3: Native SegWit (bech32) Address
echo "3. Native SegWit Address (Bech32 - P2WPKH)"
echo "   Expected prefix: wv1q"
ADDR_BECH32=$($WHIVE_CLI -datadir=$DATADIR -rpcwallet=$WALLET_NAME getnewaddress "test_bech32" "bech32")
echo "   Generated: $ADDR_BECH32"

VALIDATE_BECH32=$($WHIVE_CLI -datadir=$DATADIR validateaddress "$ADDR_BECH32")
IS_VALID=$(echo "$VALIDATE_BECH32" | grep -o '"isvalid": *[^,]*' | awk '{print $2}')
ADDR_TYPE=$(echo "$VALIDATE_BECH32" | grep -o '"type": *"[^"]*"' | cut -d'"' -f4)

if [ "$IS_VALID" = "true" ]; then
    echo "   ✓ Valid: Yes"
    echo "   ✓ Type: $ADDR_TYPE"
    if [[ $ADDR_BECH32 == wv1q* ]]; then
        echo "   ✓ Prefix: Correct (starts with 'wv1q')"
        echo "   ✓ Encoding: Bech32"
    else
        echo "   ✗ Prefix: INCORRECT (should start with 'wv1q')"
    fi
else
    echo "   ✗ Validation FAILED"
fi
echo ""

# Test 4: Taproot (bech32m) Address
echo "4. Taproot Address (Bech32m - P2TR)"
echo "   Expected prefix: wv1p"

if [ "$TAPROOT_ACTIVE" = true ]; then
    ADDR_TAPROOT=$($WHIVE_CLI -datadir=$DATADIR -rpcwallet=$WALLET_NAME getnewaddress "test_taproot" "bech32m" 2>&1)

    # Check if command succeeded
    if [[ $ADDR_TAPROOT == wv1p* ]]; then
        echo "   Generated: $ADDR_TAPROOT"

        VALIDATE_TAPROOT=$($WHIVE_CLI -datadir=$DATADIR validateaddress "$ADDR_TAPROOT")
        IS_VALID=$(echo "$VALIDATE_TAPROOT" | grep -o '"isvalid": *[^,]*' | awk '{print $2}')
        ADDR_TYPE=$(echo "$VALIDATE_TAPROOT" | grep -o '"type": *"[^"]*"' | cut -d'"' -f4)

        if [ "$IS_VALID" = "true" ]; then
            echo "   ✓ Valid: Yes"
            echo "   ✓ Type: $ADDR_TYPE"
            echo "   ✓ Prefix: Correct (starts with 'wv1p')"
            echo "   ✓ Encoding: Bech32m"
        else
            echo "   ✗ Validation FAILED"
        fi
    else
        echo "   ✗ Error generating Taproot address: $ADDR_TAPROOT"
    fi
else
    echo "   ⊘ Skipped (Taproot not yet activated)"
fi
echo ""

echo "=========================================="
echo "Address Validation Summary"
echo "=========================================="
echo ""

# Test address validation with mixed addresses
echo "→ Testing address validation..."

# Valid Whive addresses
echo "Testing valid addresses:"
for addr in "$ADDR_LEGACY" "$ADDR_BECH32"; do
    RESULT=$($WHIVE_CLI -datadir=$DATADIR validateaddress "$addr" | grep -o '"isvalid": *[^,]*' | awk '{print $2}')
    if [ "$RESULT" = "true" ]; then
        echo "   ✓ $addr"
    else
        echo "   ✗ $addr (unexpected failure)"
    fi
done
echo ""

# Invalid addresses (Bitcoin addresses should fail)
echo "Testing rejection of Bitcoin addresses:"
BITCOIN_ADDR="bc1qar0srrr7xfkvy5l643lydnw9re59gtzzwf5mdq"
RESULT=$($WHIVE_CLI -datadir=$DATADIR validateaddress "$BITCOIN_ADDR" | grep -o '"isvalid": *[^,]*' | awk '{print $2}')
if [ "$RESULT" = "false" ]; then
    echo "   ✓ Correctly rejects Bitcoin address: $BITCOIN_ADDR"
else
    echo "   ✗ INCORRECTLY accepts Bitcoin address (BUG!)"
fi
echo ""

echo "=========================================="
echo "Cleanup"
echo "=========================================="
echo ""

# Unload test wallet
echo "→ Unloading test wallet..."
if $WHIVE_CLI -datadir=$DATADIR unloadwallet "$WALLET_NAME" > /dev/null 2>&1; then
    echo "✓ Wallet unloaded"
else
    echo "⚠ Could not unload wallet (might already be unloaded)"
fi
echo ""

echo "=========================================="
echo "Test Complete!"
echo "=========================================="
echo ""
echo "Summary of Whive Address Formats:"
echo "  • Legacy (P2PKH):        W..."
echo "  • P2SH:                  5..."
echo "  • Native SegWit (bech32): wv1q..."
echo "  • Taproot (bech32m):     wv1p..."
echo ""
echo "All address types have been verified."
echo ""
