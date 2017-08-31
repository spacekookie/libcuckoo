# libcuckoo
Queued cuckoo hashing dictionary as described by Y. Arbitman, M. Naor, and G. Segev

## Performance

There will be some benchmark results later. This is a dump of what happens when you insert the entire alphabet (as keys) into a three-table cuckoo map. Not too bad...

```
=== Inserting 'a' ===
[ ,  ,  ,  ,  ,  , a,  ,  ,  ,  , ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'b' ===
[ ,  ,  ,  ,  ,  , a,  ,  ,  , b, ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'c' ===
[ ,  ,  ,  ,  ,  , a, c,  ,  , b, ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'd' ===
[ ,  ,  ,  ,  ,  , d, c,  ,  , b, ]
[ ,  , a,  ,  ,  ,  ,  ,  ,  ,  , ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'e' ===
[ ,  ,  ,  ,  ,  , e, c,  ,  , b, ]
[ , d, a,  ,  ,  ,  ,  ,  ,  ,  , ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'f' ===
[ ,  ,  ,  ,  ,  , e, c,  , f, b, ]
[ , d, a,  ,  ,  ,  ,  ,  ,  ,  , ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'g' ===
[ ,  ,  ,  ,  ,  , e, c,  , g, b, ]
[ , d, a,  ,  , f,  ,  ,  ,  ,  , ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'h' ===
[ ,  ,  ,  , h,  , e, c,  , g, b, ]
[ , d, a,  ,  , f,  ,  ,  ,  ,  , ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'i' ===
[ ,  ,  ,  , h,  , i, c,  , g, b, ]
[e, d, a,  ,  , f,  ,  ,  ,  ,  , ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'j' ===
[ ,  ,  ,  , h,  , i, c,  , g, j, ]
[e, d, a,  , b, f,  ,  ,  ,  ,  , ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'k' ===
[ ,  ,  ,  , k,  , i, c,  , g, j, ]
[e, d, a,  , h, f,  ,  ,  ,  ,  , ]
[ ,  ,  , b,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'l' ===
[ ,  ,  ,  , k, l, i, c,  , g, j, ]
[e, d, a,  , h, f,  ,  ,  ,  ,  , ]
[ ,  ,  , b,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'm' ===
[ ,  , m,  , k, l, i, c,  , g, j, ]
[e, d, a,  , h, f,  ,  ,  ,  ,  , ]
[ ,  ,  , b,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'n' ===
[ ,  , n,  , k, l, i, c,  , g, j, ]
[e, d, a,  , h, f,  ,  , m,  ,  , ]
[ ,  ,  , b,  ,  ,  ,  ,  ,  ,  , ]

=== Inserting 'o' ===
[ ,  , n,  , k, l, i, c,  , g, o, ]
[e, d, a,  , h, j,  ,  , m,  ,  , ]
[ ,  ,  , b, f,  ,  ,  ,  ,  ,  , ]

=== Inserting 'p' ===
[ ,  , n,  , k, l, i, c, p, g, o, ]
[e, d, a,  , h, j,  ,  , m,  ,  , ]
[ ,  ,  , b, f,  ,  ,  ,  ,  ,  , ]

=== Inserting 'q' ===
[ ,  , n,  , k, l, i, c, q, g, o, ]
[e, d, a,  , h, j,  ,  , p,  ,  , ]
[ ,  ,  , b, f,  ,  ,  , m,  ,  , ]

=== Inserting 'r' ===
[ ,  , n,  , k, l, i, c, q, g, r, ]
[e, d, a,  , h, j, o,  , p,  ,  , ]
[ ,  ,  , b, f,  ,  ,  , m,  ,  , ]

=== Inserting 's' ===
[ ,  , n,  , s, l, i, c, q, g, r, ]
[e, d, a,  , h, j, o,  , p, k,  , ]
[ ,  ,  , b, f,  ,  ,  , m,  ,  , ]

=== Inserting 't' ===
[ ,  , n,  , s, l, i, t, q, g, r, ]
[e, d, a,  , h, j, c,  , p, k,  , ]
[ ,  ,  , b, f,  , o,  , m,  ,  , ]

=== Inserting 'u' ===
[ ,  , n,  , s, l, i, t, q, u, r, ]
[g, d, a,  , h, j, c,  , p, k,  , ]
[ , e,  , b, f,  , o,  , m,  ,  , ]

=== Inserting 'v' ===
[ ,  , n,  , s, v, i, t, q, u, r, ]
[g, d, a,  , h, j, c, l, p, k,  , ]
[ , e,  , b, f,  , o,  , m,  ,  , ]

=== Inserting 'w' ===
[ ,  , n, w, s, v, i, t, q, u, r, ]
[g, d, a,  , h, j, c, l, p, k,  , ]
[ , e,  , b, f,  , o,  , m,  ,  , ]

=== Inserting 'x' ===
[ ,  , n, w, s, x, i, t, q, u, r, ]
[v, d, a,  , h, j, c, l, p, k,  , ]
[g, e,  , b, f,  , o,  , m,  ,  , ]

=== Inserting 'y' ===
[ ,  , n, w, s, x, y, t, q, u, r, ]
[v, d, a,  , h, j, c, l, p, k, i, ]
[g, e,  , b, f,  , o,  , m,  ,  , ]

=== Inserting 'z' ===
[ ,  , n, w, s, x, y, t, z, u, r, ]
[v, d, a,  , h, j, c, q, p, k, i, ]
[g, e,  , b, f,  , o, l, m,  ,  , ]
```