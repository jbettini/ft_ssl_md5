#ifndef SSL_H
# define SSL_H
#include "../libft/libft.h"

#define AND &
#define OR |
#define XOR ^
#define NOT ~
#define LSHIFT <<
#define RSHIFT >>

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
void    execute_cmd(t_cmd *cmd);
char    *sha256(char *data_to_hash);
char    *md5(char *data_to_hash);
void    putbytes(__uint8_t octet);

#endif
