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

    uint32_t k = 0;
    uint32_t h = seed;
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
    int c;
    unsigned int hash = 0xEC4FE9;

    do {
        c = *string++;
        hash ^= ((hash << 5) + hash >> 3) + c;
    }while(c);

    *hash_val = hash % table_size;
    return CUCKOO_SUCCESS;
}


/* Code taken (and modified) from lookup3.c, by Bob Jenkins, May 2006, Public Domain.*/
int cc_hashing_jenkins(unsigned long *hash_val, char *string, size_t table_size)
{

/* For now we assume we always run on little endian hardware */
#define HASH_LITTLE_ENDIAN 1

/* Hash utility macros */
#define rot(x, k) (((x) << (k)) | ((x) >> (32 - (k))))
#define mix(a,b,c) \
{ \
  a -= c;  a ^= rot(c, 4);   c += b; \
  b -= a;  b ^= rot(a, 6);   a += c; \
  c -= b;  c ^= rot(b, 8);   b += a; \
  a -= c;  a ^= rot(c, 16);  c += b; \
  b -= a;  b ^= rot(a, 19);  a += c; \
  c -= b;  c ^= rot(b, 4);   b += a; \
}
#define finalise(a,b,c) \
{ \
  c ^= b; c -= rot(b, 14); \
  a ^= c; a -= rot(c, 11); \
  b ^= a; b -= rot(a, 25); \
  c ^= b; c -= rot(b, 16); \
  a ^= c; a -= rot(c, 4);  \
  b ^= a; b -= rot(a, 14); \
  c ^= b; c -= rot(b, 24); \
}

    uint32_t a, b, c;
    union { const void *ptr; size_t i; } u;
    size_t length = strlen(string);
    const uint32_t initval = 42;

    /* Set up the internal state */
    a = b = c = 0xdeadbeef + ((uint32_t) length) + initval;

    u.ptr = string;
    if (HASH_LITTLE_ENDIAN && ((u.i & 0x3) == 0)) {
        const uint32_t *k = (const uint32_t *) string;
        const uint8_t  *k8;

        while (length > 12) {
            a += k[0];
            b += k[1];
            c += k[2];
            mix(a,b,c);
            length -= 12;
            k += 3;
        }

        switch(length) {
            case 12: c+=k[2];           b+=k[1]; a+=k[0]; break;
            case 11: c+=k[2]&0xffffff;  b+=k[1]; a+=k[0]; break;
            case 10: c+=k[2]&0xffff;    b+=k[1]; a+=k[0]; break;
            case  9: c+=k[2]&0xff;      b+=k[1]; a+=k[0]; break;
            case  8: b+=k[1];           a+=k[0];          break;
            case  7: b+=k[1]&0xffffff;  a+=k[0];          break;
            case  6: b+=k[1]&0xffff;    a+=k[0];          break;
            case  5: b+=k[1]&0xff;      a+=k[0];          break;
            case  4: a+=k[0];                             break;
            case  3: a+=k[0]&0xffffff;                    break;
            case  2: a+=k[0]&0xffff;                      break;
            case  1: a+=k[0]&0xff;                        break;
            case  0: return c;
        }

    } else if (HASH_LITTLE_ENDIAN && ((u.i & 0x1) == 0)) {
        const uint16_t *k = (const uint16_t *) string;
        const uint8_t  *k8;

        /* All but last block: aligned reads and different mixing */
        while (length > 12) {
            a += k[0] + (((uint32_t)k[1])<<16);
            b += k[2] + (((uint32_t)k[3])<<16);
            c += k[4] + (((uint32_t)k[5])<<16);
            mix(a,b,c);
            length -= 12;
            k += 6;
        }

        /* handle the last (probably partial) block */
        k8 = (const uint8_t *) k;
        switch(length) {
            case 12:  c+=k[4]+(((uint32_t)k[5])<<16);
                b+=k[2]+(((uint32_t)k[3])<<16);
                a+=k[0]+(((uint32_t)k[1])<<16);
                break;
            case 11:  c+=((uint32_t)k8[10])<<16;
            case 10:  c+=k[4];
                b+=k[2]+(((uint32_t)k[3])<<16);
                a+=k[0]+(((uint32_t)k[1])<<16);
                break;
            case 9 :  c+=k8[8];
            case 8 :  b+=k[2]+(((uint32_t)k[3])<<16);
                a+=k[0]+(((uint32_t)k[1])<<16);
                break;
            case 7 :  b+=((uint32_t)k8[6])<<16;
            case 6 :  b+=k[2];
                a+=k[0]+(((uint32_t)k[1])<<16);
                break;
            case 5 :  b+=k8[4];
            case 4 :  a+=k[0]+(((uint32_t)k[1])<<16);
                break;
            case 3 :  a+=((uint32_t)k8[2])<<16;
            case 2 :  a+=k[0];
                break;
            case 1 :  a+=k8[0];
                break;
            case 0 :  return c;
        }

    } else {

        /* need to read the key one byte at a time */
        const uint8_t *k = (const uint8_t *) string;

        /* all but the last block: affect some 32 bits of (a,b,c) */
        while (length > 12) {
            a += k[0];
            a += ((uint32_t)k[1])<<8;
            a += ((uint32_t)k[2])<<16;
            a += ((uint32_t)k[3])<<24;
            b += k[4];
            b += ((uint32_t)k[5])<<8;
            b += ((uint32_t)k[6])<<16;
            b += ((uint32_t)k[7])<<24;
            c += k[8];
            c += ((uint32_t)k[9])<<8;
            c += ((uint32_t)k[10])<<16;
            c += ((uint32_t)k[11])<<24;
            mix(a,b,c);
            length -= 12;
            k += 12;
        }

        /* last block: affect all 32 bits of (c) */
        switch(length) {
            case 12: c += ((uint32_t) k[11]) << 24;
            case 11: c += ((uint32_t) k[10]) << 16;
            case 10: c += ((uint32_t) k[9]) << 8;
            case  9: c += k[8];
            case  8: b += ((uint32_t) k[7]) << 24;
            case  7: b += ((uint32_t) k[6]) << 16;
            case  6: b += ((uint32_t) k[5]) << 8;
            case  5: b += k[4];
            case  4: a += ((uint32_t) k[3]) << 24;
            case  3: a += ((uint32_t) k[2]) << 16;
            case  2: a += ((uint32_t) k[1]) << 8;
            case  1: a += k[0]; break;
            case  0:  return c;
        }
    }

    /* Finalise the hash and return the in-range value */
    finalise(a,b,c);
    *hash_val = c % table_size;
    return CUCKOO_SUCCESS;
}


int cc_hashing_bernstein(unsigned long *hash_val, char *string, size_t table_size)
{

    return CUCKOO_HASHING_FAILED;
}
