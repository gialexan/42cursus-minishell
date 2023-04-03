/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:16 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/03 18:18:01 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

static char	*variable_expansion(char *str, char *key);
static char	*word_splitting(t_scanner *scanner, char *result);

t_list	*expandlst(t_list *token, t_list *head)
{
	t_list	*tmp;
	char	*aux;

	if (!token)
		return head;
	tmp = advanced(&token);
	tmp->content = pathname_expansion(tmp->content, 0, 0);
	if (!strncmp(tmp->content, "", 1))
		ft_lstdelone(tmp, free);
	else
		ft_lstadd_back(&head, tmp);
	return (expandlst(token, head));
}

char	*expandchr(char *word)
{
	char		*result;
	t_scanner	scanner;

	scanner = init_scanner(word);
	result = word_splitting(&scanner, result);
	return (result);
}

//mudar para irativo talvez.
char	*pathname_expansion(char *path, int i, int init)
{
	if (ft_chrcmp(path[i], '\0'))
		return (path);
	else if (ft_chrcmp(path[i], '$'))
	{
		init = i++;
		if (ft_chrcmp(path[i], '?'))
			return (ft_strdup("1"));
		else if (ft_isalpha(path[i]) || ft_chrcmp(path[i], '_'))
		{
			while (path[i] && (ft_isalnum(path[i]) || ft_chrcmp(path[i],'_')))
				i++;
			path = variable_expansion(path, ft_substr(path, init, i - init));
		}
	}
	return (pathname_expansion(path, i + 1, init));
}

static char	*word_splitting(t_scanner *scanner, char *result)
{
	char	*sliced;
	char	*expanded;
	char	*unquoted;

	if (scanner->current >= ft_strlen(scanner->cmd))
		return (result);
	scanner->start = scanner->current;
	if (ft_chrcmp(scanner->cmd[scanner->current], '\'') ||
		ft_chrcmp(scanner->cmd[scanner->current], '"'))
		sliced = slice_quotes(scanner);
	else
		sliced = slice_word(scanner);
	expanded = pathname_expansion(sliced, 0, 0);
	unquoted = unquote(expanded);
	result = concatenate(result, unquoted);
	free(expanded);
	free(unquoted);
	return (word_splitting(scanner, result));
}

static char	*variable_expansion(char *str, char *key)
{
	char	*tmp;
	t_list	*envp;

	envp = search_envp(key + 1, *get_envp());
	if (!envp)
	{
		if (ft_chrcmp(str[0], '"'))
			tmp = ft_strdup(str);
		else
			tmp = ft_strdup("");
	}
	else
		tmp = ft_strreplace(str, key, ft_strchr(envp->content, '=') + 1);
	free(key);
	free(str);
	return (tmp);
}
