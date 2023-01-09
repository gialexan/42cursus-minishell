/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/01/09 19:39:53 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"



char	advance(t_scanner *scan)
{
	scan->index++;
	return (scan->start[scan->index - 1]);
}

int	main(void)
{
	t_scanner scanner;

	char *cmdline = ">>def";
	
	scanner.index = 0;
	scanner.start = cmdline;
	
	while(cmdline[scanner.index])
	{
		char c = advance(&scanner);
		printf("%c\n", c);
	}
}











// int	main(void)
// {
// 	t_scanner scanner;
// 	t_token tk;
// 	int i;

// 	char *cmdline = ">>def";
	
// 	i = 1;
// 	scanner.iter.start = cmdline;
// 	scanner.iter.index = 0;
// 	if (cmdline[i] == '>')
// 	{
// 		scanner.tk_next.token = TK_GREAT;
// 		scanner.tk_next.lexema = cmdline;
// 		scanner.tk_next.size = i;
// 		dprintf(1, "Token: %d - Lexema: ", scanner.tk_next.token);
// 		write(1, scanner.tk_next.lexema, scanner.tk_next.size);
// 		write(1, "\n", 1);
// 	}
// }