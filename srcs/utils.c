#include "ssl.h"

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