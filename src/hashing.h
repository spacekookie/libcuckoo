#ifndef LIBCUCKOO_HASHING_H
#define LIBCUCKOO_HASHING_H

#include <stddef.h>

/**
 * Hash a string with murmor (used as first table hash function)
 *
 * @param hash_val
 * @param string
 * @param table_size
 * @return
 */
int cc_hashing_murmur(unsigned long *hash_val, char *string, size_t table_size);

/**
 * Hash a string XOR numerically (used as second table hash function)
 *
 * @param hash_val
 * @param string
 * @param table_size
 * @return
 */
int cc_hashing_numeric(unsigned long *hash_val, char *string, size_t table_size);

/**
 * Hash a string with jenkins (used as third table hash function)
 *
 * @param hash_val
 * @param string
 * @param table_size
 * @return
 */
int cc_hashing_jenkins(unsigned long *hash_val, char *string, size_t table_size);

/**
 * Hash a string with jenkins (used as fourth table hash function)
 *
 * @param hash_val
 * @param string
 * @param table_size
 * @return
 */
int cc_hashing_bernstein(unsigned long *hash_val, char *string, size_t table_size);


#endif //LIBCUCKOO_HASHING_H
