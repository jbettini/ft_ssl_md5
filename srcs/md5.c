#include "ssl.h"


char    *md5(char *data_to_hash) {
    int data_len = ft_strlen(data_to_hash);
    int blocks_num = (data_len + 8) / 64 + 1;
    char **blocks_tab = malloc(sizeof(char *) * (blocks_num + 1));
    // printf("len : %d | malloced : %d\n", data_len, blocks);
    for (int i = 0; i < blocks_num; i++)
        blocks_tab[i] = malloc(sizeof(char) * 64 + 1);
    blocks_tab[blocks_num] = NULL;

    printf("%s", read_data(open("srcs/main.c", 0)));
}