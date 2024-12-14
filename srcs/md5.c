#include "ssl.h"

char    *md5_cpy_blocks(char *dest, char *src, size_t len)
{
	size_t	i;

    i = 0;
	if (src) {
	    while (i < len && src[i]) {
	    	dest[i] = src[i];
            i++;
        }
        // if (!src[i])
        //     dest[i++] = 0x80;
    }
    while (i < len) {
        dest[i] = 0;
        i++;
    }
    dest[i] = 0;
	return (dest);
}

char    **md5_get_blocks(char *data_to_hash) {
    bool    fill_bit = false;
    int     data_len = ft_strlen(data_to_hash);
    int     blocks_size = (data_len + 8) / 64 + 1;
    char **blocks_tab = malloc(sizeof(char *) * (blocks_size + 1));
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
    return blocks_tab;
}

char    *md5(char *data_to_hash) {
    char **blocks = md5_get_blocks(data_to_hash);
    ft_putsendl(blocks);
    exit(1);
}