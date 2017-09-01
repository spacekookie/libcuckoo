# libcuckoo
Queued cuckoo hashing dictionary as described by Y. Arbitman, M. Naor, and G. Segev

## Performance

There will be some benchmark results later. This is a dump of what happens when you insert the entire alphabet (as keys) into a three-table cuckoo map. Not too bad...

```
=== Inserting 'a' ===
[ ,  ,  ,  ,  ,  , a,  ,  ,  ,  ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.030303

=== Inserting 'b' ===
[ ,  ,  ,  ,  ,  , a,  ,  ,  , b]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.060606

=== Inserting 'c' ===
[ ,  ,  ,  ,  ,  , a, c,  ,  , b]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.090909

=== Inserting 'd' ===
[ ,  ,  ,  ,  ,  , d, c,  ,  , b]
[ ,  , a,  ,  ,  ,  ,  ,  ,  ,  ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.121212

=== Inserting 'e' ===
[ ,  ,  ,  ,  ,  , e, c,  ,  , b]
[ , d, a,  ,  ,  ,  ,  ,  ,  ,  ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.151515

=== Inserting 'f' ===
[ ,  ,  ,  ,  ,  , e, c,  , f, b]
[ , d, a,  ,  ,  ,  ,  ,  ,  ,  ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.181818

=== Inserting 'g' ===
[ ,  ,  ,  ,  ,  , e, c,  , g, b]
[ , d, a,  ,  , f,  ,  ,  ,  ,  ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.212121

=== Inserting 'h' ===
[ ,  ,  ,  , h,  , e, c,  , g, b]
[ , d, a,  ,  , f,  ,  ,  ,  ,  ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.242424

=== Inserting 'i' ===
[ ,  ,  ,  , h,  , i, c,  , g, b]
[e, d, a,  ,  , f,  ,  ,  ,  ,  ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.272727

=== Inserting 'j' ===
[ ,  ,  ,  , h,  , i, c,  , g, j]
[e, d, a,  , b, f,  ,  ,  ,  ,  ]
[ ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.303030

=== Inserting 'k' ===
[ ,  ,  ,  , k,  , i, c,  , g, j]
[e, d, a,  , h, f,  ,  ,  ,  ,  ]
[ ,  ,  , b,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.333333

=== Inserting 'l' ===
[ ,  ,  ,  , k, l, i, c,  , g, j]
[e, d, a,  , h, f,  ,  ,  ,  ,  ]
[ ,  ,  , b,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.363636

=== Inserting 'm' ===
[ ,  , m,  , k, l, i, c,  , g, j]
[e, d, a,  , h, f,  ,  ,  ,  ,  ]
[ ,  ,  , b,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.393939

=== Inserting 'n' ===
[ ,  , n,  , k, l, i, c,  , g, j]
[e, d, a,  , h, f,  ,  , m,  ,  ]
[ ,  ,  , b,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.424242

=== Inserting 'o' ===
[ ,  , n,  , k, l, i, c,  , g, o]
[e, d, a,  , h, j,  ,  , m,  ,  ]
[ ,  ,  , b, f,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.454545

=== Inserting 'p' ===
[ ,  , n,  , k, l, i, c, p, g, o]
[e, d, a,  , h, j,  ,  , m,  ,  ]
[ ,  ,  , b, f,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.484848

=== Inserting 'q' ===
[ ,  , n,  , k, l, i, c, q, g, o]
[e, d, a,  , h, j,  ,  , p,  ,  ]
[ ,  ,  , b, f,  ,  ,  , m,  ,  ]

Table space utilisation: 0.515152

=== Inserting 'r' ===
[ ,  , n,  , k, l, i, c, q, g, r]
[e, d, a,  , h, j, o,  , p,  ,  ]
[ ,  ,  , b, f,  ,  ,  , m,  ,  ]

Table space utilisation: 0.545455

=== Inserting 's' ===
[ ,  , n,  , s, l, i, c, q, g, r]
[e, d, a,  , h, j, o,  , p, k,  ]
[ ,  ,  , b, f,  ,  ,  , m,  ,  ]

Table space utilisation: 0.575758

=== Inserting 't' ===
[ ,  , n,  , s, l, i, t, q, g, r]
[e, d, a,  , h, j, c,  , p, k,  ]
[ ,  ,  , b, f,  , o,  , m,  ,  ]

Table space utilisation: 0.606061

=== Inserting 'u' ===
[ ,  , n,  , s, l, i, t, q, u, r]
[g, d, a,  , h, j, c,  , p, k,  ]
[ , e,  , b, f,  , o,  , m,  ,  ]

Table space utilisation: 0.636364

=== Inserting 'v' ===
[ ,  , n,  , s, v, i, t, q, u, r]
[g, d, a,  , h, j, c, l, p, k,  ]
[ , e,  , b, f,  , o,  , m,  ,  ]

Table space utilisation: 0.666667

=== Inserting 'w' ===
[ ,  , n, w, s, v, i, t, q, u, r]
[g, d, a,  , h, j, c, l, p, k,  ]
[ , e,  , b, f,  , o,  , m,  ,  ]

Table space utilisation: 0.696970

=== Inserting 'x' ===
[ ,  , n, w, s, x, i, t, q, u, r]
[v, d, a,  , h, j, c, l, p, k,  ]
[g, e,  , b, f,  , o,  , m,  ,  ]

Table space utilisation: 0.727273

=== Inserting 'y' ===
[ ,  , n, w, s, x, y, t, q, u, r]
[v, d, a,  , h, j, c, l, p, k, i]
[g, e,  , b, f,  , o,  , m,  ,  ]

Table space utilisation: 0.757576

=== Inserting 'z' ===
[ ,  , n, w, s, x, y, t, z, u, r]
[v, d, a,  , h, j, c, q, p, k, i]
[g, e,  , b, f,  , o, l, m,  ,  ]

Table space utilisation: 0.787879

=== Inserting 'A' ===
[ ,  , n, w, s, x, A, t, z, u, r]
[v, d, a,  , y, j, c, q, p, k, i]
[g, e,  , b, f,  , o, l, m,  , h]

Table space utilisation: 0.818182

=== Inserting 'B' ===
[ ,  , n, w, s, l, A, t, B, u, r]
[v, d, a, x, y, j, c, q, p, k, z]
[g, e,  , b, f,  , o, i, m,  , h]

Table space utilisation: 0.848485

=== Inserting 'C' ===
[ ,  , n, w, s, C, A, t, B, u, b]
[v, d, a, x, y, j, c, l, p, r, z]
[g, e,  , q, f,  , o, i, m, k, h]

Table space utilisation: 0.878788

=== Inserting 'D' ===
[ ,  , m,  , h, x, e, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r]
[ , d, a, B,  ,  , A, D,  ,  , z, v,  ,  ,  , b, s,  ,  ,  ,  , t]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  ]

Table space utilisation: 0.439394

=== Inserting 'E' ===
[ ,  , m, E, h, x, e, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r]
[ , d, a, B,  ,  , A, D,  ,  , z, v,  ,  ,  , b, s,  ,  ,  ,  , t]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  ]

Table space utilisation: 0.454545

=== Inserting 'F' ===
[ ,  , m, E, F, x, e, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r]
[ , d, a, B, h,  , A, D,  ,  , z, v,  ,  ,  , b, s,  ,  ,  ,  , t]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  ]

Table space utilisation: 0.469697

=== Inserting 'G' ===
[ ,  , m, E, F, x, G, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r]
[e, d, a, B, h,  , A, D,  ,  , z, v,  ,  ,  , b, s,  ,  ,  ,  , t]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  ]

Table space utilisation: 0.484848

=== Inserting 'H' ===
[ ,  , m, E, F, x, H, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r]
[e, d, a, B, h,  , A, D,  ,  , z, v,  ,  ,  , b, s, G,  ,  ,  , t]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  ]

Table space utilisation: 0.500000

=== Inserting 'I' ===
[ ,  , I, E, F, x, H, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r]
[e, d, a, B, h,  , A, D,  ,  , z, v,  ,  ,  , b, s, G,  , m,  , t]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  ]

Table space utilisation: 0.515152

=== Inserting 'J' ===
[ ,  , J, E, F, x, H, c, p, f, o,  ,  , n, w, k, l, y,  , q, g, r]
[e, d, a, B, h, I, A, D,  ,  , z, v,  ,  ,  , b, s, G,  , m,  , t]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  ]

Table space utilisation: 0.530303

=== Inserting 'K' ===
[ ,  , J, E, F, x, H, c, p, f, o,  ,  , n, w, k, K, y,  , q, g, r]
[e, d, a, B, h, I, A, D,  ,  , z, v,  ,  ,  , b, s, G, l, m,  , t]
[ ,  ,  ,  ,  ,  ,  , i,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , C,  , j,  ]

Table space utilisation: 0.545455

=== Inserting 'L' ===
[ ,  , J, L, F, x, H, c, p, f, o,  ,  , n, w, k, K, i,  , q, g, r]
[e, d, a, B, h, I, A, D,  ,  , z, v,  ,  ,  , y, s, G, E, m,  , t]
[ ,  ,  ,  ,  ,  ,  , l,  ,  ,  ,  ,  ,  , b,  ,  ,  , C,  , j,  ]

Table space utilisation: 0.560606

=== Inserting 'M' ===
[ ,  , J, M, F, x, H, c, p, f, j,  ,  , n, w, k, K, i,  , q, g, r]
[e, d, a, B, h, I, o, D,  ,  , L, v,  ,  ,  , y, s, G, E, m,  , t]
[ ,  ,  ,  ,  ,  ,  , l,  ,  ,  ,  ,  ,  , b,  ,  ,  , C,  , z, A]

Table space utilisation: 0.575758

=== Inserting 'N' ===
[ ,  , J, M, F, x, H, c, p, f, N,  ,  , n, w, k, K, i,  , q, g, r]
[e, d, a, B, h, I, o, D,  ,  , L, v,  ,  ,  , y, j, G, E, m,  , t]
[ ,  ,  ,  ,  ,  ,  , l,  ,  ,  ,  ,  , s, b,  ,  ,  , C,  , z, A]

Table space utilisation: 0.590909

=== Inserting 'O' ===
[ ,  , J, M, F, x, H, c, p, f, N,  ,  , n, w, k, l, O,  , q, g, r]
[e, d, a, B, h, I, o, K,  ,  , L, v,  ,  ,  , y, j, G, E, m,  , i]
[D,  ,  ,  ,  ,  ,  , t,  ,  ,  ,  ,  , s, b,  ,  ,  , C,  , z, A]

Table space utilisation: 0.606061

=== Inserting 'P' ===
[ ,  , J, M, F, x, H, c, p, f, N,  ,  , n, w, k, l, O,  , q, P, r]
[e, d, a, B, h, I, o, K,  ,  , L, g,  ,  ,  , y, j, G, E, m,  , i]
[D,  ,  ,  ,  ,  ,  , t,  ,  ,  ,  ,  , s, b,  , v,  , C,  , z, A]

Table space utilisation: 0.621212

=== Inserting 'Q' ===
[ ,  , J, M, F, x, Q, c, p, f, N,  ,  , n, w, k, l, O,  , q, P, r]
[e, d, a, B, h, I, o, K,  ,  , L, g, H,  ,  , y, j, G, E, m,  , i]
[D,  ,  ,  ,  ,  ,  , t,  ,  ,  ,  ,  , s, b,  , v,  , C,  , z, A]

Table space utilisation: 0.636364

=== Inserting 'R' ===
[ ,  , J, M, F, x, Q, c, p, f, N,  ,  , n, w, k, l, R,  , q, P, r]
[e, d, a, B, h, I, O, K,  ,  , L, g, H,  ,  , y, j, G, E, m,  , i]
[D,  ,  ,  ,  ,  ,  , t,  ,  ,  ,  ,  , s, b,  , v, o, C,  , z, A]

Table space utilisation: 0.651515

=== Inserting 'S' ===
[ ,  , J, M, F, x, Q, c, p, f, N,  ,  , n, w, k, l, S,  , q, P, r]
[e, d, a, B, h, I, O, K,  ,  , L, g, H,  ,  , R, j, G, E, m,  , i]
[D,  ,  ,  ,  ,  ,  , t,  ,  ,  , y,  , s, b,  , v, o, C,  , z, A]

Table space utilisation: 0.666667

=== Inserting 'T' ===
[ ,  , J, M, F, x, Q, t, p, f, N,  ,  , n, w, k, l, S,  , T, P, r]
[e, d, a, B, h, I, c, K,  ,  , L, g, H,  ,  , R, j, G, q, m,  , i]
[D,  ,  , O,  ,  ,  , E,  ,  ,  , y,  , s, b,  , v, o, C,  , z, A]

Table space utilisation: 0.681818

=== Inserting 'U' ===
[ ,  , J, M, F, x, Q, t, p, f, N,  ,  , n, w, k, l, y,  , T, U, r]
[e, d, a, P, h, I, c, K, S,  , L, g, H,  ,  , R, j, G, q, m,  , i]
[D,  ,  , O,  ,  ,  , E,  ,  ,  , B,  , s, b,  , v, o, C,  , z, A]

Table space utilisation: 0.696970

=== Inserting 'V' ===
[V,  , J, M, F, x, Q, t, p, f, N,  ,  , n, w, k, l, y,  , T, U, r]
[e, d, a, P, h, I, c, K, S,  , L, g, H,  ,  , R, j, G, q, m,  , i]
[D,  ,  , O,  ,  ,  , E,  ,  ,  , B,  , s, b,  , v, o, C,  , z, A]

Table space utilisation: 0.712121

=== Inserting 'W' ===
[V,  , J, M, F, x, Q, t, p, f, N, W,  , n, w, k, l, y,  , T, U, r]
[e, d, a, P, h, I, c, K, S,  , L, g, H,  ,  , R, j, G, q, m,  , i]
[D,  ,  , O,  ,  ,  , E,  ,  ,  , B,  , s, b,  , v, o, C,  , z, A]

Table space utilisation: 0.727273

=== Inserting 'X' ===
[V,  , J, M, F, x, X, t, p, f, b, W,  , n, w, k, l, y,  , T, U, r]
[e, d, a, P, h, I, c, K, S,  , L, g, H,  ,  , R, j, G, Q, m, N, i]
[D,  ,  , O,  ,  ,  , E,  ,  ,  , B,  , s, q,  , v, o, C,  , z, A]

Table space utilisation: 0.742424

=== Inserting 'Y' ===
[Y,  , J, M, F, x, X, t, p, f, b, W,  , n, w, k, l, y,  , T, U, r]
[e, d, a, V, h, I, c, K, S,  , L, g, H,  ,  , R, j, G, Q, m, N, i]
[D, P,  , O,  ,  ,  , E,  ,  ,  , B,  , s, q,  , v, o, C,  , z, A]

Table space utilisation: 0.757576

=== Inserting 'Z' ===
[V,  , m, M,  , x, G, c,  , f,  ,  ,  , n, w,  ,  , y,  , z, g, r, Y,  , I,  , h,  , A, t, p,  , o, W,  ,  ,  , s, C, i,  , q, P,  ]
[ , d, a, B,  ,  , O,  ,  , k,  ,  , H,  ,  , b,  ,  , E,  , U,  , J, F,  ,  ,  ,  ,  , D, S,  , L, v,  , T,  ,  , j,  , Q,  , N,  ]
[ ,  ,  ,  ,  ,  ,  , l,  ,  ,  , X,  ,  , Z,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , K,  ,  ,  , e,  ,  ,  ,  ,  ,  ,  ,  ,  ]

Table space utilisation: 0.356061

```