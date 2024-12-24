#include "ssl.h"


const uint32_t K[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

const uint32_t s[64] = {
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

char    **md5_get_blocks(char *data_to_hash, uint64_t data_len) {
    size_t      blocks_size = (data_len + 8) / 64 + 1;
    char        **blocks_tab = ft_calloc(sizeof(char *), (blocks_size + 1));
    // printf("Datalen : %lu | blocksize %zu\n", data_len, blocks_size);
    for (uint64_t i = 0; i < blocks_size; i++) {
        blocks_tab[i] = ft_calloc(sizeof(char), 64 + 1);
        uint64_t offset = i * 64;
        uint64_t rest = data_len - offset;
        if (rest >= 64){
            ft_memcpy(blocks_tab[i], (data_to_hash + offset), 64);
        }
        else {
            ft_memcpy(blocks_tab[i], (data_to_hash + offset), rest);
            blocks_tab[i][rest] = 0x80;
            for (uint64_t j = (i + 1); j < blocks_size; j++)
                blocks_tab[j] = ft_calloc(sizeof(char), 64 + 1);
            break ;
        }
    }
    
    ((uint64_t*)blocks_tab[blocks_size - 1])[7] = htole64(data_len * 8);

    return blocks_tab;
}


uint32_t leftrotate(uint32_t x, int s) {
    return (x << s) | (x >> (32 - s));
}


void print_md5(uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
    printf("FTM : %.8x%.8x%.8x%.8x\n", a, b, c, d);
}

char    *md5(char *data_to_hash, size_t data_len) {

    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xEFCDAB89;
    uint32_t c0 = 0x98BADCFE;
    uint32_t d0 = 0x10325476;

    char **blocks = md5_get_blocks(data_to_hash, data_len);

    for (int block_idx = 0; blocks[block_idx]; block_idx++) {
        uint32_t A = a0;
        uint32_t B = b0;
        uint32_t C = c0;
        uint32_t D = d0;
        
        uint32_t M[16];
        for (uint32_t i = 0; i < 16; i++) {
            M[i] = *(uint32_t *)(blocks[block_idx] + (i * 4));
        }

        for (int i = 0; i < 64; i++) {
            int F, g;
            if (i < 16) {
                F = (B AND C) OR ((NOT B) AND D);
                g = i;
            }
            else if (i < 32) {
                F = (D AND B) OR ((NOT D) AND C);
                g = (5 * i + 1) % 16;
            }
            else if (i < 48) {
                F = B XOR C XOR D;
                g = (3 * i + 5) % 16;
            }
            else {
                F = C XOR (B OR (NOT D));
                g = (7 * i) % 16;
            }
            F = (F + A + K[i] + M[g]);
            A = D;
            D = C;
            C = B;
            B = B + leftrotate(F, s[i]);
        }
        a0 += A;
        b0 += B;
        c0 += C;
        d0 += D;
    }
    ft_free_strs(blocks);
    char    *ret = ft_calloc(sizeof(char), 33);
    sprintf(ret,"%.8x%.8x%.8x%.8x", htobe32(a0), htobe32(b0), htobe32(c0), htobe32(d0));
    return ret;
}
