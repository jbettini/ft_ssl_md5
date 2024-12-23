#include "ssl.h"

enum type {
    STDIN,
    STRING
};

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

void    handle_flags(t_cmd *cmd, char *flag) {
    if (ft_strequ(flag, "-p") && !cmd->p)
        cmd->p = true;
    else if (ft_strequ(flag, "-q") && !cmd->q)
        cmd->q = true;
    else if (ft_strequ(flag, "-r") && !cmd->r)
        cmd->r = true;
    else 
        cmd_exit_on_multiple_option(cmd, flag);
}

t_cmd   *cmd_parse(char **args) {
    int i = 0;
    t_cmd   *ret =  cmd_get();
    // TODO add SHA256
    if (ft_strequ(args[0], "md5"))
        ret->cmd = ft_strdup(args[0]);
    else
        help_on_error(args[0]);
    while (args[++i]) {
        if (ft_strequ(args[i], "-p") ||  ft_strequ(args[i], "-q") || ft_strequ(args[i], "-r"))
            handle_flags(ret, args[i]);
        else if (ft_strequ(args[i], "-s")) {
            if (!args[++i]) {
                fprintf(stderr, "ft_ssl: Error: -s flags Cannot take a Null String.\n");
                cmd_free(ret);
                exit(1);
            }  
            ft_lstadd_back(&ret->s, ft_lstnew(ft_strdup(args[i])));
        } else
            break ;
    }
    while(args[i])
        ft_lstadd_back(&ret->files, ft_lstnew(ft_strdup(args[i++])));
    return ret;
}

void    cmd_free(t_cmd *args) {
    if (args->cmd) {
        free_safe(args->cmd);
    }
    if (args->s) {
        ft_lstclear(&args->s, free_safe);
    }
    if (args->files) {
        ft_lstclear(&args->s, free_safe);
    }
    if (args->s) {
        free_safe(args);
    }
    free_safe(args);
}

void    prompt(char *hash, t_cmd *cmd, char *name, int type) 
{
    char *formated_name = NULL;
    size_t  len = ft_strlen(name) + 1;
    if (type == STRING) {
        formated_name = ft_calloc(sizeof(char), type == STRING ? len + 2 : len);
        sprintf(formated_name, "\"%s\"", name);
    }
    else {
        formated_name = ft_strdup(name);
    }
    if (cmd->q){
        if (type == STDIN)
            printf("%s\n", formated_name);
        printf("%s\n", hash);
    }
    else if (cmd->r) {
        printf("%s %s\n", hash, formated_name);
    } else {
        printf("MD5 (%s) = %s\n", formated_name, hash);
    }
    free_safe(formated_name);
}

void    execute_cmd(t_cmd *cmd) {
    char *(*hash_fun)(char *, size_t);
    if (ft_strequ(cmd->cmd, "md5"))
        hash_fun = &md5;
    else if (ft_strequ(cmd->cmd, "sha256"))
        hash_fun = &sha256;
    t_list *files = cmd->files;
    t_list *strs = cmd->s;
    // TODO handle stdin -p
    // if (cmd->p || (!strs && !files)) {
    // }
    while (strs) {
        char *hash = hash_fun(strs->content, ft_strlen(strs->content));
        prompt(hash, cmd, strs->content ,STRING);
        free(hash);
        strs = strs->next;
    };
}