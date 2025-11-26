#!/bin/bash
# Get RegTest genesis hash and merkle root for 200 COIN reward

echo "Starting whived in regtest mode to get genesis hashes..."
echo ""

# Create a temporary regtest directory
REGTEST_DIR="/tmp/whive_regtest_genesis_test"
rm -rf "$REGTEST_DIR"
mkdir -p "$REGTEST_DIR"

# Start whived in regtest mode with debug output
/Users/munje/Devops/whive/build/bin/whived -regtest -datadir="$REGTEST_DIR" -daemon -debug=1

# Wait for it to start and then stop
sleep 5

# Stop it
/Users/munje/Devops/whive/build/bin/whive-cli -regtest -datadir="$REGTEST_DIR" stop 2>/dev/null

sleep 2

# Get the genesis block info
echo "Getting genesis block (block 0)..."
GENESIS_INFO=$(/Users/munje/Devops/whive/build/bin/whive-cli -regtest -datadir="$REGTEST_DIR" getblock $(/Users/munje/Devops/whive/build/bin/whive-cli -regtest -datadir="$REGTEST_DIR" getblockhash 0) 2>/dev/null)

if [ $? -eq 0 ]; then
    echo "$GENESIS_INFO"
    echo ""
    echo "Extract these values for chainparams.cpp:"
    echo "  genesis hash: $(echo "$GENESIS_INFO" | grep '"hash"' | head -1 | cut -d'"' -f4)"
    echo "  merkle root: $(echo "$GENESIS_INFO" | grep '"merkleroot"' | cut -d'"' -f4)"
else
    echo "Failed to get genesis info. Checking debug.log..."
    cat "$REGTEST_DIR/regtest/debug.log" | grep -i "genesis\|error" | tail -20
fi

# Cleanup
rm -rf "$REGTEST_DIR"
