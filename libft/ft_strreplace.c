/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:24:17 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/29 18:08:14 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int  word_count(char *str, char *word)
{
	int i;
	int count;
	int wordlen;

	i = 0;
	count = 0;
	wordlen = ft_strlen(word);
	while (str[i])
	{
		if (ft_strnstr(&str[i], word, ft_strlen(&str[i])) == &str[i])
		{
			count++;
			i += wordlen - 1;
		}
		i++;
	}
	return (count);
}


char    *ft_strreplace(char *str, char *oldw, char *neww)
{
	int i;
	char *result;
    int newwlen = ft_strlen(neww);
    int oldwlen = ft_strlen(oldw);

	result = malloc(ft_strlen(str) + word_count(str, oldw)
			* (newwlen - oldwlen) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (*str)
	{
    	if (ft_strnstr(str, oldw, ft_strlen(str)) == str)
		{
			ft_strlcpy(&result[i], neww, newwlen + 1);
        	i += newwlen;
       		str += oldwlen;
    	}
    	else
        	result[i++] = *str++;
    }
    result[i] = '\0';
    return (result);
}