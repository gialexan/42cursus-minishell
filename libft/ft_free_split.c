/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:05:07 by gialexan          #+#    #+#             */
/*   Updated: 2022/11/10 15:45:29 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(void **str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_free((void *)&str[i]);
	ft_free((void *)&str);
	str = NULL;
}
