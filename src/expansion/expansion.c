/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:16 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/28 10:38:32 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"
#include "execute.h"

#define EMPY ""

static char	*get_value_exit_code(char *str);
static char	*variable_expansion(char *str, char *key);
static char	*word_splitting(t_scanner *scanner, char *result);

char	*expand(char *oldstr)
{
	char		*newstr;
	t_scanner	scanner;

	scanner = init_scanner(oldstr);
	newstr = word_splitting(&scanner, NULL);
	free(oldstr);
	return (newstr);
}

static char	*word_splitting(t_scanner *scanner, char *result)
{
	char	*sliced;
	char	*expanded;
	char	*unquoted;

	if (scanner->current >= ft_strlen(scanner->cmd))
		return (result);
	scanner->start = scanner->current;
	if (scanner->cmd[scanner->current] == '\''
		|| scanner->cmd[scanner->current] == '"')
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

char	*pathname_expansion(char *str, size_t i , size_t init)
{
	char	*key;
	char	*tmp;

	if (!str)
		return (NULL);
	if (i >= ft_strlen(str))
		return (str);
	else if (str[i] == '$')
	{
		init = i++;
		if (str[i] == '?')
			str = get_value_exit_code(str);
		else if (ft_isalpha(str[i]) || str[i] == '_')
		{
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			tmp = str;
			key = ft_substr(tmp, init, i - init);
			str = variable_expansion(tmp, key);
			free(key);
			free(tmp);
		}
	}
	return (pathname_expansion(str, i + 1, init));
}

static char	*variable_expansion(char *str, char *key)
{
	t_list	*envp;
	char	*env_value;

	if (!key || key[0] != '$' || str[0] == '\'')
		return (ft_strdup(str));
	envp = search_envp(key + 1, *get_envp());
	if (!envp)
	{
		if (str[0] == '"')
			return (ft_strdup(str));
		return (ft_strdup(""));
	}
	else
	{
		env_value = ft_strchr(envp->content, '=');
		if (!env_value)
			return (ft_strdup(""));
		else
			return (ft_strreplace(str, key, env_value + 1));
	}
}

static char	*get_value_exit_code(char *str)
{
	char	*expd_str;
	char	*exit_code;

	exit_code = ft_utoa(*get_exit_code());
	expd_str = ft_strreplace(str, "$?", exit_code);
	free(str);
	free(exit_code);
	return (expd_str);
}
