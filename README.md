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

=== Inserting 'A' ===
[ ,  , n, w, s, x, A, t, z, u, r, ]
[v, d, a,  , y, j, c, q, p, k, i, ]
[g, e,  , b, f,  , o, l, m,  , h, ]

=== Inserting 'B' ===
[ ,  , n, w, s, l, A, t, B, u, r, ]
[v, d, a, x, y, j, c, q, p, k, z, ]
[g, e,  , b, f,  , o, i, m,  , h, ]

=== Inserting 'C' ===
[ ,  , n, w, s, C, A, t, B, u, b, ]
[v, d, a, x, y, j, c, l, p, r, z, ]
[g, e,  , q, f,  , o, i, m, k, h, ]

=== Inserting 'D' ===
[ ,  , m,  , h, x, e, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r, ]
[ , d, a, B,  ,  , A, D,  ,  , z, v,  ,  ,  , b, s,  ,  ,  ,  , t, ]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  , ]

=== Inserting 'E' ===
[ ,  , m, E, h, x, e, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r, ]
[ , d, a, B,  ,  , A, D,  ,  , z, v,  ,  ,  , b, s,  ,  ,  ,  , t, ]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  , ]

=== Inserting 'F' ===
[ ,  , m, E, F, x, e, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r, ]
[ , d, a, B, h,  , A, D,  ,  , z, v,  ,  ,  , b, s,  ,  ,  ,  , t, ]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  , ]

=== Inserting 'G' ===
[ ,  , m, E, F, x, G, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r, ]
[e, d, a, B, h,  , A, D,  ,  , z, v,  ,  ,  , b, s,  ,  ,  ,  , t, ]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  , ]

=== Inserting 'H' ===
[ ,  , m, E, F, x, H, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r, ]
[e, d, a, B, h,  , A, D,  ,  , z, v,  ,  ,  , b, s, G,  ,  ,  , t, ]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  , ]

=== Inserting 'I' ===
[ ,  , I, E, F, x, H, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r, ]
[e, d, a, B, h,  , A, D,  ,  , z, v,  ,  ,  , b, s, G,  , m,  , t, ]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  , ]

=== Inserting 'J' ===
[ ,  , J, E, F, x, H, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r, ]
[e, d, a, B, h, I, A, D,  ,  , z, v,  ,  ,  , b, s, G,  , m,  , t, ]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  , ]

=== Inserting 'K' ===
[ ,  , J, E, F, x, H, c, p, f, o,  ,  , n, w, k, K, y,  , q, g, r, ]
[e, d, a, B, h, I, A, D,  ,  , z, v,  ,  ,  , b, s, G, l, m,  , t, ]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  , ]

=== Inserting 'L' ===
[ ,  , J, L, F, x, H, c, p, f, o,  ,  , n, w, k, K, i,  , q, g, r, ]
[e, d, a, B, h, I, A, D,  ,  , z, v,  ,  ,  , y, s, G, E, m,  , t, ]
[ ,  ,  ,  ,  ,  ,  , l,  ,  ,  ,  ,  ,  , b,  ,  ,  , C,  , j,  , ]

=== Inserting 'M' ===
[ ,  , J, M, F, x, H, c, p, f, j,  ,  , n, w, k, K, i,  , q, g, r, ]
[e, d, a, B, h, I, o, D,  ,  , L, v,  ,  ,  , y, s, G, E, m,  , t, ]
[ ,  ,  ,  ,  ,  ,  , l,  ,  ,  ,  ,  ,  , b,  ,  ,  , C,  , z, A, ]

=== Inserting 'N' ===
[ ,  , J, M, F, x, H, c, p, f, N,  ,  , n, w, k, K, i,  , q, g, r, ]
[e, d, a, B, h, I, o, D,  ,  , L, v,  ,  ,  , y, j, G, E, m,  , t, ]
[ ,  ,  ,  ,  ,  ,  , l,  ,  ,  ,  ,  , s, b,  ,  ,  , C,  , z, A, ]

=== Inserting 'O' ===
[ ,  , J, M, F, x, H, c, p, f, N,  ,  , n, w, k, l, O,  , q, g, r, ]
[e, d, a, B, h, I, o, K,  ,  , L, v,  ,  ,  , y, j, G, E, m,  , i, ]
[D,  ,  ,  ,  ,  ,  , t,  ,  ,  ,  ,  , s, b,  ,  ,  , C,  , z, A, ]

=== Inserting 'P' ===
[ ,  , J, M, F, x, H, c, p, f, N,  ,  , n, w, k, l, O,  , q, P, r, ]
[e, d, a, B, h, I, o, K,  ,  , L, g,  ,  ,  , y, j, G, E, m,  , i, ]
[D,  ,  ,  ,  ,  ,  , t,  ,  ,  ,  ,  , s, b,  , v,  , C,  , z, A, ]

=== Inserting 'Q' ===
[ ,  , J, M, F, x, Q, c, p, f, N,  ,  , n, w, k, l, O,  , q, P, r, ]
[e, d, a, B, h, I, o, K,  ,  , L, g, H,  ,  , y, j, G, E, m,  , i, ]
[D,  ,  ,  ,  ,  ,  , t,  ,  ,  ,  ,  , s, b,  , v,  , C,  , z, A, ]

=== Inserting 'R' ===
[ ,  , J, M, F, x, Q, c, p, f, N,  ,  , n, w, k, l, R,  , q, P, r, ]
[e, d, a, B, h, I, O, K,  ,  , L, g, H,  ,  , y, j, G, E, m,  , i, ]
[D,  ,  ,  ,  ,  ,  , t,  ,  ,  ,  ,  , s, b,  , v, o, C,  , z, A, ]

=== Inserting 'S' ===
[ ,  , J, M, F, x, Q, c, p, f, N,  ,  , n, w, k, l, S,  , q, P, r, ]
[e, d, a, B, h, I, O, K,  ,  , L, g, H,  ,  , R, j, G, E, m,  , i, ]
[D,  ,  ,  ,  ,  ,  , t,  ,  ,  , y,  , s, b,  , v, o, C,  , z, A, ]

=== Inserting 'T' ===
[ ,  , J, M, F, x, Q, t, p, f, N,  ,  , n, w, k, l, S,  , T, P, r, ]
[e, d, a, B, h, I, c, K,  ,  , L, g, H,  ,  , R, j, G, q, m,  , i, ]
[D,  ,  , O,  ,  ,  , E,  ,  ,  , y,  , s, b,  , v, o, C,  , z, A, ]

=== Inserting 'U' ===
[ ,  , J, M, F, x, Q, t, p, f, N,  ,  , n, w, k, l, y,  , T, U, r, ]
[e, d, a, P, h, I, c, K, S,  , L, g, H,  ,  , R, j, G, q, m,  , i, ]
[D,  ,  , O,  ,  ,  , E,  ,  ,  , B,  , s, b,  , v, o, C,  , z, A, ]

=== Inserting 'V' ===
[V,  , J, M, F, x, Q, t, p, f, N,  ,  , n, w, k, l, y,  , T, U, r, ]
[e, d, a, P, h, I, c, K, S,  , L, g, H,  ,  , R, j, G, q, m,  , i, ]
[D,  ,  , O,  ,  ,  , E,  ,  ,  , B,  , s, b,  , v, o, C,  , z, A, ]

=== Inserting 'W' ===
[V,  , J, M, F, x, Q, t, p, f, N, W,  , n, w, k, l, y,  , T, U, r, ]
[e, d, a, P, h, I, c, K, S,  , L, g, H,  ,  , R, j, G, q, m,  , i, ]
[D,  ,  , O,  ,  ,  , E,  ,  ,  , B,  , s, b,  , v, o, C,  , z, A, ]

=== Inserting 'X' ===
[V,  , J, M, F, x, X, t, p, f, b, W,  , n, w, k, l, y,  , T, U, r, ]
[e, d, a, P, h, I, c, K, S,  , L, g, H,  ,  , R, j, G, Q, m, N, i, ]
[D,  ,  , O,  ,  ,  , E,  ,  ,  , B,  , s, q,  , v, o, C,  , z, A, ]

=== Inserting 'Y' ===
[Y,  , J, M, F, x, X, t, p, f, b, W,  , n, w, k, l, y,  , T, U, r, ]
[e, d, a, V, h, I, c, K, S,  , L, g, H,  ,  , R, j, G, Q, m, N, i, ]
[D, P,  , O,  ,  ,  , E,  ,  ,  , B,  , s, q,  , v, o, C,  , z, A, ]

=== Inserting 'Z' ===
[V,  , m, M,  , x, G, c,  , f,  ,  ,  , n, w,  ,  , y,  , z, g, r, Y,  , I,  , h,  , A, t, p,  , o, W,  ,  ,  , s, C, i,  , q, P,  , ]
[ , d, a, B,  ,  , O,  ,  , k,  ,  , H,  ,  , b,  ,  , E,  , U,  , J, F,  ,  ,  ,  ,  , D, S,  , L, v,  , T,  ,  , j,  , Q,  , N,  , ]
[ ,  ,  ,  ,  ,  ,  , l,  ,  ,  , X,  ,  , Z,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , K,  ,  ,  , e,  ,  ,  ,  ,  ,  ,  ,  ,  , ]

```