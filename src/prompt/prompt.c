/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:40:12 by dardo-na          #+#    #+#             */
/*   Updated: 2023/04/07 23:15:08 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static void	build_path(char *path)
{
	char	*home;
	int		length;

	getcwd(path, PATH_MAX);
	home = getenv(HOME_K);
	if (home == NULL)
		return ;
	if (!str_starts_with(path, home))
		return ;
	length = ft_strlen(home) - 1;
	while (length--)
		cut_str(path);
	path[0] = '~';
}

static char	*find_username(void)
{
	char	*username;

	username = getenv(USERNAME_K);
	if (username == NULL)
		username = getenv(USER_K);
	if (username == NULL)
		username = "???";
	return (username);
}

static char	*build_parse(void)
{
	char	path[PATH_MAX];
	char	*parse;
	char	*username;

	build_path(path);
	username = find_username();
	parse = ft_strdup(GB);
	if (username != NULL)
		parse = ft_strjoin_free(parse, username);
	parse = ft_strjoin_free(parse, WB ":" BB);
	parse = ft_strjoin_free(parse, path);
	parse = ft_strjoin_free(parse, RC "$ ");
	return (parse);
}

char	*prompt(void)
{
	char	*line;
	char	*parse;

	parse = build_parse();
	line = readline(parse);
	if (line == NULL)
		return (NULL);
	if (!str_is_equal(line, EMP_STR))
		add_history(line);
	free(parse);
	parse = NULL;
	return (line);
}
