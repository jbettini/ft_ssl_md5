#include "ssl.h"

t_cmd *cmd_get() {
    t_cmd *p = malloc(sizeof(t_cmd));

    p->cmd = NULL;
    p->s = NULL;
    p->files = NULL;
    p->p = false;
    p->q = false;
    p->r = false;
    return p;
}

bool    cmd_exit_on_multiple_option(t_cmd *args, char *option) {
    ft_putstr(args->cmd);
    ft_putstr(": Multiple digest or unknown options: ");
    ft_putstr(option);
    ft_putstr(" and ");
    ft_putendl(option);
    cmd_free(args);
    exit(1);
    return false;
}

void    help_on_error(char *bad_cmd) {
    ft_putstr("ft_ssl: Error: \'");
    ft_putstr(bad_cmd);
    ft_putendl("\' is an invalid command.\n");
    help();
    exit(1);
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

t_cmd   *cmd_parse(char **args) {
    t_cmd   *ret =  cmd_get();

    if (ft_strequ(args[0], "md5"))
        ret->cmd = ft_strdup(args[0]);
    else
        help_on_error(args[0]);
    
    int i = 0;

    while (args[++i]) {
        if (ft_strequ(args[i], "-p")) {
            ret->p = ret->p ? cmd_exit_on_multiple_option(ret, "-p") : true;
        } else if (ft_strequ(args[i], "-q")) {
            ret->q = ret->q ? cmd_exit_on_multiple_option(ret, "-q") : true;
        } else if (ft_strequ(args[i], "-r")) {
            ret->r = ret->r ? cmd_exit_on_multiple_option(ret, "-r") : true;
        } else if (ft_strequ(args[i], "-s")) {
            if (!args[++i]) {
                ft_putstr("ft_ssl: Error: -s flags Cannot take a Null String.\n");
                cmd_free(ret);
                exit(1);
            }  
            ft_lstadd_back(&ret->s, ft_lstnew(ft_strdup(args[i])));
        } else
            break ;
    }
    if (args[i]) {
        while(args[i])
            ft_lstadd_back(&ret->files, ft_lstnew(ft_strdup(args[i++])));
    }
    cmd_print(ret);
    return ret;
}

void    cmd_free(t_cmd *args) {
    if (args->cmd) {
        free_safe(args->cmd);
    }
    if (args->s) {
        ft_lstclear(&args->s, free_safe);
    }
    if (args->s) {
        free_safe(args);
    }
}