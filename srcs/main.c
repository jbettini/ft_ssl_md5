#include "ssl.h"

int main(int ac, char **av) {
    if (ac < 2)
    fprintf(stderr, "usage: ft_ssl command [flags] [file/string]");
    else {
        t_cmd   *cmd = cmd_parse(&av[1]);
    }
}