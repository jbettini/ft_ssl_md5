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
    fprintf(stderr, "%s :Multiple digest or unknown options: %s ans %s\n", args->cmd, option, option);
    cmd_free(args);
    exit(1);
    return false;
}

void    help_on_error(char *bad_cmd) {
    fprintf(stderr, "ft_ssl: Error: \'%s\' is an invalid command.\n", bad_cmd);
    help();
    exit(1);
}

t_cmd   *cmd_parse(char **args) {
    int i = 0;
    t_cmd   *ret =  cmd_get();
    if (ft_strequ(args[0], "md5"))
        ret->cmd = ft_strdup(args[0]);
    else
        help_on_error(args[0]);
    while (args[++i]) {
        if (ft_strequ(args[i], "-p")) {
            ret->p = ret->p ? cmd_exit_on_multiple_option(ret, "-p") : true;
        } else if (ft_strequ(args[i], "-q")) {
            ret->q = ret->q ? cmd_exit_on_multiple_option(ret, "-q") : true;
        } else if (ft_strequ(args[i], "-r")) {
            ret->r = ret->r ? cmd_exit_on_multiple_option(ret, "-r") : true;
        } else if (ft_strequ(args[i], "-s")) {
            if (!args[++i]) {
                fprintf(stderr, "ft_ssl: Error: -s flags Cannot take a Null String.\n");
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
    // cmd_print(ret);
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