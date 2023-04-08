/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:56:40 by dardo-na          #+#    #+#             */
/*   Updated: 2023/04/08 11:01:02 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	cut_str(char *str)
{
	while (*str != '\0')
	{
		*str = *(str + 1);
		str++;
	}
}

t_bool	str_starts_with(char *str, char *start)
{
	char	*test;

	if (str == NULL || start == NULL)
		return (FALSE);
	test = ft_strnstr(str, start, ft_strlen(start));
	if (test != NULL)
		return (TRUE);
	return (FALSE);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*new_string;

	new_string = ft_strjoin(s1, s2);
	free(s1);
	s1 = NULL;
	return (new_string);
}

// t_bool	str_is_equal(char *s1, char *s2)
// {
// 	if (s1 == s2)
// 		return (TRUE);
// 	if (s1 == NULL || s2 == NULL)
// 		return (FALSE);
// 	while (*s1 || *s2)
// 		if (*s1++ != *s2++)
// 			return (FALSE);
// 	return (TRUE);
// }
