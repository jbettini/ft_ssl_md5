#include "ssl.h"
#define PAGE_SIZE 4096

char    *read_data(int fd) {
    char    *ret = NULL;
    char    buffer[PAGE_SIZE];

    if (fd < 0) {
        fprintf(stderr, "Error: Invalid file descriptor\n");
        exit(1);
    }
    int bytes_read = 0;
    while ((bytes_read = read(fd, buffer, PAGE_SIZE))) {
        if (bytes_read < 0){
            fprintf(stderr, "Error: Read Faillure\n");
            free(ret);
            exit(1);
        }
        buffer[bytes_read] = 0;
        ret = ft_strjoin_gnl(ret, buffer);
    }
    return ret;
}

void help() {
    ft_putendl("Commands:\nmd5\nsha256\n");
    ft_putendl("Flags:\n-p -q -r -s");
}

void    free_safe(void *ptr) {
    if (ptr == NULL) {
        ft_putstr("Error: try to free a null pointer\n");
        exit(1);
    }
    free(ptr);
}

void    ft_putbool(bool b) {
    b ? ft_putendl("true"): ft_putendl("false");
}

void putbytes(uint8_t *octet, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (octet[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}


void    cmd_print(t_cmd *args) {
    ft_putstr("---------------\n");
    ft_putendl(args->cmd);
    ft_putstr("-p : ");
    ft_putbool(args->p);
    ft_putstr("-q : ");
    ft_putbool(args->q);
    ft_putstr("-r : ");
    ft_putbool(args->r);
    ft_putstr("-s : \n");
    ft_lstiter(args->s, ft_putendl_void);
    ft_putstr("files : \n");
    ft_lstiter(args->files, ft_putendl_void);
    ft_putstr("---------------\n");
}