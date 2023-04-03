/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:04:59 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/03 11:48:18 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

char	*slice_word(t_scanner *scanner)
{
	char c;

	c = advance(scanner);
	while (c != 0 && c != '\'' && c != '"')
		c = advance(scanner);
	scanner->current--;
	return (ft_substr(scanner->cmd, scanner->start,
		scanner->current - scanner->start));
}

char	*slice_quotes(t_scanner *scanner)
{
	char	c;
	char	end;
	char	*sliced;

	end = advance(scanner);
	c = advance(scanner);
	while (c != end && c != 0)
		c = advance(scanner);
	return (ft_substr(scanner->cmd, scanner->start,
		scanner->current - scanner->start));
}

char	*unquote(char *str)
{
	if (empty_quotes(str))
		return (ft_strdup(""));
	else if (ft_chrcmp(str[0], '\''))
		return (ft_strtrim(str, "'"));
	else if (ft_chrcmp(str[0], '"'))
		return (ft_strtrim(str, "\""));
	return (ft_strdup(str));
}

t_bool	empty_quotes(char *str)
{
	if (ft_chrcmp(str[0], '\'') && ft_chrcmp(str[1], '\''))
		return (TRUE);
	else if (ft_chrcmp(str[0], '"') && ft_chrcmp(str[1], '"'))
		return (TRUE);
	return (FALSE);
}

char *concatenate(char *str, char *append)
{
	char	*tmp;

	tmp = str;
	str = ft_strjoin(tmp, append);
	free(tmp);
	return (str);
}