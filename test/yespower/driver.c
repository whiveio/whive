/* Standalone tests of the production Whive header-hash wrapper. */
#include "yespower.h"
#include "sysendian.h"
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

enum { THREAD_COUNT = 4, HASH_REPETITIONS = 4 };

static void print_hash(const char *name, const unsigned char input[80])
{
    unsigned char output[32];
    yespower_binary_t expected;
    const yespower_params_t old = {YESPOWER_0_5, 4096, 16,
        (const uint8_t *)"Client Key", 10};
    const yespower_params_t current = {YESPOWER_0_9, 2048, 32, NULL, 0};
    const yespower_params_t *params = le32dec(input + 68) > 1530403200 ? &current : &old;
    assert(yespower_hash((const char *)input, (char *)output) == 0);
    assert(yespower_tls(input, 80, params, &expected) == 0);
    assert(memcmp(output, expected.uc, 32) == 0);
    printf("%s ", name);
    for (size_t i = 0; i < sizeof(output); ++i) printf("%02x", output[i]);
    putchar('\n');
}

static unsigned char thread_input[80];
static unsigned char thread_expected[32];

static void *thread_hash(void *unused)
{
    (void)unused;
    for (int i = 0; i < HASH_REPETITIONS; ++i) {
        unsigned char output[32];
        assert(yespower_hash((const char *)thread_input, (char *)output) == 0);
        assert(memcmp(output, thread_expected, 32) == 0);
    }
    return NULL;
}

int main(void)
{
    unsigned char header[80];
    for (size_t i = 0; i < sizeof(header); ++i) header[i] = (unsigned char)(i * 3);
    print_hash("fixture", header);
    le32enc(header + 68, 1530403199); print_hash("before", header);
    le32enc(header + 68, 1530403200); print_hash("boundary", header);
    le32enc(header + 68, 1530403201); print_hash("after", header);

    /* Header byte order and genesis values from src/chainparams.cpp. */
    const unsigned char merkle[32] = {
        0xab,0x4c,0x83,0xb8,0xe4,0x5c,0x5b,0xdb,
        0x44,0x23,0x2f,0x17,0xea,0x6a,0xf5,0xc0,
        0x2e,0xe0,0x40,0x97,0x14,0xc1,0xe0,0x9b,
        0xd8,0xed,0x12,0x09,0xb7,0x4c,0x04,0xb8};
    memset(header, 0, sizeof(header));
    le32enc(header, 1); memcpy(header + 36, merkle, sizeof(merkle));
    le32enc(header + 68, 1580658322); le32enc(header + 72, 0x1f00ffff);
    le32enc(header + 76, 63992); print_hash("genesis", header);
    le32enc(header + 68, 1580662895); le32enc(header + 72, 0x207fffff);
    le32enc(header + 76, 2); print_hash("regtest-genesis", header);

    /* Varied public synthetic headers, including nonce/version extremes. */
    uint32_t state = 0x12345678;
    for (unsigned int n = 0; n < 16; ++n) {
        for (size_t i = 0; i < sizeof(header); ++i) {
            state = state * 1664525U + 1013904223U;
            header[i] = state >> 24;
        }
        le32enc(header + 68, n & 1 ? 1530403201 : 1530403200);
        le32enc(header, n & 2 ? 0xffffffffU : 0);
        le32enc(header + 76, n & 4 ? 0xffffffffU : 0);
        char label[32]; snprintf(label, sizeof(label), "synthetic-%u", n);
        print_hash(label, header);
    }

    yespower_params_t invalid[] = {
        {0, 2048, 32, NULL, 0}, {YESPOWER_0_9, 1000, 32, NULL, 0},
        {YESPOWER_0_9, 2049, 32, NULL, 0}, {YESPOWER_0_9, 2048, 7, NULL, 0},
        {YESPOWER_0_9, 2048, 33, NULL, 0}, {YESPOWER_0_9, 2048, 32, NULL, 1}
    };
    for (size_t i = 0; i < sizeof(invalid) / sizeof(invalid[0]); ++i) {
        yespower_binary_t output;
        errno = 0;
        assert(yespower_tls(header, 80, &invalid[i], &output) == -1);
        assert(errno == EINVAL);
    }

    memcpy(thread_input, header, sizeof(header));
    assert(yespower_hash((const char *)header, (char *)thread_expected) == 0);
    pthread_t threads[THREAD_COUNT];
    for (size_t i = 0; i < THREAD_COUNT; ++i) assert(pthread_create(&threads[i], NULL, thread_hash, NULL) == 0);
    for (size_t i = 0; i < THREAD_COUNT; ++i) assert(pthread_join(threads[i], NULL) == 0);
    puts("invalid-parameters-and-concurrency PASS");
    printf("metrics {\"invalid_parameter_cases\":%zu,\"concurrent_threads\":%zu,"
           "\"repeated_hashes_per_thread\":%d}\n", sizeof(invalid) / sizeof(invalid[0]),
           sizeof(threads) / sizeof(threads[0]), HASH_REPETITIONS);
    return 0;
}
