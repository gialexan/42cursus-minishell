/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/01/23 23:12:26 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

char	*ft_strdup(const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	advance(t_scanner *scanner)
{
	scanner->curr++;
	return (scanner->cmd[scanner->curr - 1]);
}

int	match(t_scanner *scanner, char expected)
{
	if (scanner->cmd[scanner->curr] != expected)
		return (FALSE);
	advance(scanner);
	return (TRUE);
}

void	init_scanner(t_scanner *scanner, const char *command)
{
	scanner->curr = 0;
	scanner->start = 0;
	scanner->cmd = command;
}

t_token		*make_token(t_scanner *scanner, t_tk_type type)
{
	t_token *token;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->lexema = ft_substr(scanner->cmd, scanner->start, scanner->curr);
	token->tk_type = type;
	return (token);
}

t_token	*scan_token(t_scanner *scanner)
{
	char	c;

	c = advance(scanner);

	if (c == '<')
	{
		if (match(scanner, '<'))
			return(make_token(scanner, TK_DLESS));
		return(make_token(scanner, TK_LESS));
	}
	return (0);
}

int	main(void)
{
	t_scanner scanner;
	const char *command = "<<"; //<||||<<|||||||>

	init_scanner(&scanner, command);
	t_token *tk = scan_token(&scanner);
	printf("%d | %s\n", tk->tk_type, tk->lexema);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;

	i = 0;
	j = strlen(s);
	if (start > j)
		return (ft_strdup(""));
	while (s[start + i] && i < len)
		i++;
	len = i + 1;
	sub = (char *) malloc((len) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len);
	return (sub);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = -1;
	if (dstsize)
	{
		while (++i < dstsize -1 && src[i])
			dst[i] = src[i];
		dst[i] = '\0';
	}
	return (strlen(src));
}

char	*ft_strdup(const char *src)
{
	int		len;
	char	*dup;

	len = strlen(src) + 1;
	dup = (char *) malloc (len * sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, src, len);
	return (dup);
}




// int	main(void)
// {
// 	t_scanner scan;

// 	char *cmdline = "<||||<<|||||||>";
// 	t_token token;

// 	int i = -1;
	
// 	char *tmp1;
// 	tmp1 = malloc(10 * sizeof(char));

// 	scan.start = 0;
// 	scan.curr = -1;
// 	while (cmdline[++scan.curr] != '\0')
// 	{
// 		tmp1 = malloc(10 * sizeof(char));
// 		scan.start = scan.curr;
// 		if (cmdline[scan.curr] == '<')
// 		{
// 			scan.curr++;
// 			if (cmdline[scan.curr] == '<')
// 			{
// 				scan.curr++;
// 				strncat(tmp1, cmdline + scan.start, scan.curr - scan.start);
// 				printf("%s\n", tmp1);
// 			}
// 		}
// 		if (cmdline[scan.curr] == '>')
// 		{
// 			scan.curr++;
// 			strncat(tmp1, cmdline + scan.start, scan.curr - scan.start);
// 			printf("%s\n", tmp1);
// 		}
// 		free(tmp1);
// 	}
// }

// t_token		build_token(t_scanner *scan, const char command)
// {
// 	if (match(scan, command[scan->curr], '<'))
// 	{
// 		if (match(scan, command[scan->curr], '<')
// 			return (make_token();
// 		return ()
// 	}
// }

