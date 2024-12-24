#include "ssl.h"
#define PAGE_SIZE 4096

t_file_data *get_file_struct() {
    t_file_data *ret = malloc(sizeof(t_file_data));
    ret->data = NULL;
    ret->data_size = 0;
    return ret;
}

void    free_file(t_file_data *to_free) {
    free_safe(to_free->data);
    free_safe(to_free);
}

t_file_data *read_data(int fd) {
    if (fd < 0) {
        fprintf(stderr, "Error: Invalid file descriptor\n");
        exit(1);
    }
    char        buffer[PAGE_SIZE + 1];
    t_file_data *ret = get_file_struct();
    int bytes_read = 0;
    while ((bytes_read = read(fd, buffer, PAGE_SIZE))) {
        // printf("Bytes Readed : %d | Total : %d\n", bytes_read, ret->data_size);
        if (bytes_read < 0){
            fprintf(stderr, "Error: Read Faillure\n");
            free_file(ret);
            exit(1);
        }
        buffer[bytes_read] = 0;
        ret->data = ft_strjoin_gnl(ret->data, buffer);
        ret->data_size += bytes_read;
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