#include "ssl.h"

__uint32_t K[64] = {
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

__uint32_t a0 = 0x67452301;
__uint32_t b0 = 0xefcdab89;
__uint32_t c0 = 0x98badcfe;
__uint32_t d0 = 0x10325476;

char    *md5_cpy_blocks(char *dest, char *src, size_t len)
{
	size_t	i;

    i = 0;
	if (src) {
	    while (i < len && src[i]) {
	    	dest[i] = src[i];
            i++;
        }
    }
    while (i < len) {
        dest[i] = 0;
        i++;
    }
    dest[i] = 0;
	return (dest);
}



// TODO add len before
char    **md5_get_blocks(char *data_to_hash) {
    bool            fill_bit = false;
    __uint64_t      data_len = ft_strlen(data_to_hash);
    int             blocks_size = (data_len + 8) / 64 + 1;
    char            **blocks_tab = malloc(sizeof(char *) * (blocks_size + 1));
    
    // Todo Improve and maybe handle correctly fill bit
    for (int i = 0; i < blocks_size; i++) {
        blocks_tab[i] = malloc(sizeof(char) * 64 + 1);
        int offset = i * 64;
        if (offset <= data_len)
            md5_cpy_blocks(blocks_tab[i], &data_to_hash[offset], 64);
        else
            md5_cpy_blocks(blocks_tab[i], NULL, 64);
        int cpy_size = ft_strlen(blocks_tab[i]);
        if (cpy_size < 64 && !fill_bit) {
            blocks_tab[i][cpy_size] = 0x80;
            fill_bit = true;
        }
    }
    blocks_tab[blocks_size] = NULL;
    for (int i = 7; i >= 0; i--)
        blocks_tab[blocks_size - 1][64 - i] = ((data_len) >> (8 * i)) & 0xff;
    return blocks_tab;
}



char    *md5(char *data_to_hash) {
    char **blocks = md5_get_blocks(data_to_hash);


    // ft_putsendl(blocks);
    exit(1);
}



