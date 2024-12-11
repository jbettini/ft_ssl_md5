/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:42:38 by jbettini          #+#    #+#             */
/*   Updated: 2024/12/11 08:46:19 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"



int main(int ac, char **av) {
    if (ac < 2)
        ft_putendl("usage: ft_ssl command [flags] [file/string]");
    else {
        t_cmd   *cmd = cmd_parse(&av[1]);
    }
}