/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:48:22 by jbettini          #+#    #+#             */
/*   Updated: 2024/12/11 08:43:53 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
