/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:16 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/29 20:47:15 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	expand(void)
{
	char		*quotes = NULL;
	t_scanner	scanner;

	char command[] = "\"'$HOME'''$USER'''$PWD'\"";
	scanner = init_scanner(command);
	quotes = word_splitting(&scanner, quotes);
	printf("Saída: %s\n", quotes);
	free(quotes);
}

char	*word_splitting(t_scanner *scanner, char *result)
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

char	*pathname_expansion(char *path, int i, int init)
{
	if (ft_chrcmp(path[0], '\''))
		return (path);
	else if (ft_chrcmp(path[i], '\0'))
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

char	*variable_expansion(char *str, char *key)
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
	{
		tmp = ft_strchr(envp->content, '=') + 1;
		tmp = ft_strreplace(str, key, tmp);
	}
	free(key);
	free(str);
	return (tmp);
}

char *concatenate(char *str, char *append)
{
	char	*tmp;

	tmp = str;
	str = ft_strjoin(tmp, append);
	free(tmp);
	return (str);
}