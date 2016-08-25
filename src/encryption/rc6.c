// modified by Luigi Auriemma
/* This is an independent implementation of the encryption algorithm:   */
/*                                                                      */
/*         RC6 by Ron Rivest and RSA Labs                               */
/*                                                                      */
/* which is a candidate algorithm in the Advanced Encryption Standard   */
/* programme of the US National Institute of Standards and Technology.  */
/*                                                                      */
/* Copyright in this implementation is held by Dr B R Gladman but I     */
/* hereby give permission for its free direct or derivative use subject */
/* to acknowledgment of its origin and compliance with any conditions   */
/* that the originators of the algorithm place on its exploitation.     */
/*                                                                      */
/* Dr Brian Gladman (gladman@seven77.demon.co.uk) 14th January 1999     */

/* Timing data for RC6 (rc6.c)

128 bit key:
Key Setup:    1632 cycles
Encrypt:       270 cycles =    94.8 mbits/sec
Decrypt:       226 cycles =   113.3 mbits/sec
Mean:          248 cycles =   103.2 mbits/sec

192 bit key:
Key Setup:    1885 cycles
Encrypt:       267 cycles =    95.9 mbits/sec
Decrypt:       235 cycles =   108.9 mbits/sec
Mean:          251 cycles =   102.0 mbits/sec

256 bit key:
Key Setup:    1877 cycles
Encrypt:       270 cycles =    94.8 mbits/sec
Decrypt:       227 cycles =   112.8 mbits/sec
Mean:          249 cycles =   103.0 mbits/sec

*/

/*
#include "../std_defs.h"

static char *alg_name[] = { "rc6", "rc6.c", "rc6" };

char **cipher_name()
{
    return alg_name;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define rc6_rotl(x,r) ((x << r) | (x >> (32 - r)))
#define rc6_rotr(x,r) ((x >> r) | (x << (32 - r)))

#define rc6_f_rnd(i,a,b,c,d)                    \
        u = rc6_rotl(d * (d + d + 1), 5);       \
        t = rc6_rotl(b * (b + b + 1), 5);       \
        a = rc6_rotl(a ^ t, u) + l_key[i];      \
        c = rc6_rotl(c ^ u, t) + l_key[i + 1]

#define rc6_i_rnd(i,a,b,c,d)                    \
        u = rc6_rotl(d * (d + d + 1), 5);       \
        t = rc6_rotl(b * (b + b + 1), 5);       \
        c = rc6_rotr(c - l_key[i + 1], t) ^ u;  \
        a = rc6_rotr(a - l_key[i], u) ^ t

//uint32_t  rc6_l_key[44];  /* storage for the key schedule         */

/* initialise the key schedule from the user supplied key   */

uint32_t *rc6_set_key(uint32_t *l_key, const uint32_t in_key[], const uint32_t key_len)
{   uint32_t  i, j, k, a, b, l[8], t;

    l_key[0] = 0xb7e15163;

    for(k = 1; k < 44; ++k)
        
        l_key[k] = l_key[k - 1] + 0x9e3779b9;

    for(k = 0; k < key_len / 32; ++k)

        l[k] = in_key[k];

    t = (key_len / 32) - 1; // t = (key_len / 32);

    a = b = i = j = 0;

    for(k = 0; k < 132; ++k)
    {   a = rc6_rotl(l_key[i] + a + b, 3); b += a;
        b = rc6_rotl(l[j] + b, b);
        l_key[i] = a; l[j] = b;
        i = (i == 43 ? 0 : i + 1); // i = (i + 1) % 44;  
        j = (j == t ? 0 : j + 1);  // j = (j + 1) % t;
    }

    return l_key;
};

/* encrypt a block of text  */

void rc6_encrypt(uint32_t *l_key, const uint32_t in_blk[4], uint32_t out_blk[4])
{   uint32_t  a,b,c,d,t,u;

    a = in_blk[0]; b = in_blk[1] + l_key[0];
    c = in_blk[2]; d = in_blk[3] + l_key[1];

    rc6_f_rnd( 2,a,b,c,d); rc6_f_rnd( 4,b,c,d,a);
    rc6_f_rnd( 6,c,d,a,b); rc6_f_rnd( 8,d,a,b,c);
    rc6_f_rnd(10,a,b,c,d); rc6_f_rnd(12,b,c,d,a);
    rc6_f_rnd(14,c,d,a,b); rc6_f_rnd(16,d,a,b,c);
    rc6_f_rnd(18,a,b,c,d); rc6_f_rnd(20,b,c,d,a);
    rc6_f_rnd(22,c,d,a,b); rc6_f_rnd(24,d,a,b,c);
    rc6_f_rnd(26,a,b,c,d); rc6_f_rnd(28,b,c,d,a);
    rc6_f_rnd(30,c,d,a,b); rc6_f_rnd(32,d,a,b,c);
    rc6_f_rnd(34,a,b,c,d); rc6_f_rnd(36,b,c,d,a);
    rc6_f_rnd(38,c,d,a,b); rc6_f_rnd(40,d,a,b,c);

    out_blk[0] = a + l_key[42]; out_blk[1] = b;
    out_blk[2] = c + l_key[43]; out_blk[3] = d;
};

/* decrypt a block of text  */

void rc6_decrypt(uint32_t *l_key, const uint32_t in_blk[4], uint32_t out_blk[4])
{   uint32_t  a,b,c,d,t,u;

    d = in_blk[3]; c = in_blk[2] - l_key[43]; 
    b = in_blk[1]; a = in_blk[0] - l_key[42];

    rc6_i_rnd(40,d,a,b,c); rc6_i_rnd(38,c,d,a,b);
    rc6_i_rnd(36,b,c,d,a); rc6_i_rnd(34,a,b,c,d);
    rc6_i_rnd(32,d,a,b,c); rc6_i_rnd(30,c,d,a,b);
    rc6_i_rnd(28,b,c,d,a); rc6_i_rnd(26,a,b,c,d);
    rc6_i_rnd(24,d,a,b,c); rc6_i_rnd(22,c,d,a,b);
    rc6_i_rnd(20,b,c,d,a); rc6_i_rnd(18,a,b,c,d);
    rc6_i_rnd(16,d,a,b,c); rc6_i_rnd(14,c,d,a,b);
    rc6_i_rnd(12,b,c,d,a); rc6_i_rnd(10,a,b,c,d);
    rc6_i_rnd( 8,d,a,b,c); rc6_i_rnd( 6,c,d,a,b);
    rc6_i_rnd( 4,b,c,d,a); rc6_i_rnd( 2,a,b,c,d);

    out_blk[3] = d - l_key[1]; out_blk[2] = c; 
    out_blk[1] = b - l_key[0]; out_blk[0] = a; 
};
