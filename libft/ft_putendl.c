/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:30:25 by jbettini          #+#    #+#             */
/*   Updated: 2021/11/04 20:31:32 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	ft_putendl_void(void *s)
{
	ft_putstr((char *)s);
	ft_putchar('\n');
}

void	ft_putendl(char const *s)
{
	ft_putstr(s);
	ft_putchar('\n');
}

void	ft_putsendl(char **s)
{
	for (int i = 0; s[i]; i++) {
		ft_putstr(s[i]);
		ft_putchar('\n');
	}
}
