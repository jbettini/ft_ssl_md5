#ifndef SSL_H
# define SSL_H
#include "../libft/libft.h"

typedef struct s_cmd
{
    char    *cmd;
    bool    p;
    bool    q;
    bool    r;
    t_list  *s;
    t_list  *files;
}				t_cmd;

void    free_safe(void *ptr);
t_cmd   *cmd_parse(char **args);
void    help();
void    cmd_free(t_cmd *args);
void    ft_putbool(bool b);
void    cmd_print(t_cmd *args);

#endif
