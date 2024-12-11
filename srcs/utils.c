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