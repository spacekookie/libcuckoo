#include "hashing.h"

#include <cuckoo.h>
#include <string.h>


int cc_hashing_murmur(unsigned long *hash_val, char *string, size_t table_size)
{
#define C1 0xcc9e2d51
#define C2 0x1b873593
#define N 0xe6546b64
#define M 5
#define C3 0x85ebca6b
#define C4 0xc2b2ae35
#define R1 15
#define R2 13
#define R3 16
#define R4 13
#define ROTL32(v, shift) ( ((v) << (shift)) | ( (v) >> (32 - (shift))) )

    unsigned int key_len = (unsigned int) strlen(string);
    int l = (int) key_len / 4;
    uint32_t seed = 0xAF172FE;
    int i = 0;

    uint32_t h = seed, k = 0;
    uint8_t *d = (uint8_t *) string;
    const uint32_t *chunks = (const uint32_t *)(d + l * 4);
    const uint8_t *tail = (const uint8_t *)(d + l * 4);

    for (i = -l; i != 0; ++i) {
        k = chunks[i];
        k *= C1;
        k = ROTL32(k, R1);
        k *= C2;
        h ^= k;
        h = ROTL32(k, R2);
        h = h * M + N;
    }

    k = 0;
    switch(key_len & 3) {
        case 3:
            k ^= (tail[2] << 16);
        case 2:
            k ^= (tail[1] << 8);
        case 1:
            k ^= tail[0];
            k *= C1;
            k = ROTL32(k, R1);
            k *= C2;
            h ^= k;
        default: break;
    }

    /* Finalised hash */
    h ^= key_len;
    h ^= (h >> R3);
    h *= C3;
    h ^= (h >> R4);
    h *= C4;
    h ^= (h >> R3);

    /* Apply range limit */
    h %= table_size;

    *hash_val = h;
    return CUCKOO_SUCCESS;
}


int cc_hashing_numeric(unsigned long *hash_val, char *string, size_t table_size)
{

    return CUCKOO_HASHING_FAILED;
}


int cc_hashing_jenkins(unsigned long *hash_val, char *string, size_t table_size)
{

    return CUCKOO_HASHING_FAILED;
}


int cc_hashing_bernstein(unsigned long *hash_val, char *string, size_t table_size)
{

    return CUCKOO_HASHING_FAILED;
}
