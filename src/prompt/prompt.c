/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:40:12 by dardo-na          #+#    #+#             */
/*   Updated: 2023/04/08 11:05:29 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static void	build_path(char *path)
{
	char	*home;
	int		length;

	getcwd(path, PATH_MAX);
	home = getenv(HOME_K);
	if (!home)
		return ;
	if (ft_strcmp(path, home) == 0)
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
	if (!username)
		username = getenv(USER_K);
	if (!username)
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
	free(parse);
	if (!line)
		return (NULL);
	if (ft_strcmp(line, EMP_STR) != 0)
		add_history(line);
	return (line);
}
