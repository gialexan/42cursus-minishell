/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:04:59 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/09 15:30:31 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

static t_bool	empty_quotes(const char *str);

char	*slice_word(t_scanner *scanner)
{
	char	c;

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
	char	close;

	close = advance(scanner);
	c = advance(scanner);
	while (c != close && c != 0)
		c = advance(scanner);
	return (ft_substr(scanner->cmd, scanner->start,
			scanner->current - scanner->start));
}

char	*unquote(const char *str)
{
	if (!str)
		return (NULL);
	if (empty_quotes(str))
		return (ft_strdup(""));
	else if (str[0] == '\'')
		return (ft_strtrim(str, "'"));
	else if (str[0] == '"')
		return (ft_strtrim(str, "\""));
	return (ft_strdup(str));
}

char	*concatenate(char *oldstr, const char *append)
{
	char	*tmpstr;
	char	*newstr;

	tmpstr = oldstr;
	newstr = ft_strjoin(tmpstr, append);
	free(tmpstr);
	return (newstr);
}

static t_bool	empty_quotes(const char *str)
{
	if (str[0] == '\'' && str[1] == '\'')
		return (TRUE);
	else if (str[0] == '"' && str[1] == '"')
		return (TRUE);
	return (FALSE);
}
