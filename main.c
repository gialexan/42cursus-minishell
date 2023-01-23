/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/01/23 19:44:40 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"


int	main(void)
{
	t_scanner scan;

	char *cmdline = "<||||<<|||||||>";
	t_token token;

	int i = -1;
	
	char *tmp1;
	tmp1 = malloc(10 * sizeof(char));

	scan.start = 0;
	scan.curr = -1;
	while (cmdline[++scan.curr] != '\0')
	{
		tmp1 = malloc(10 * sizeof(char));
		scan.start = scan.curr;
		if (cmdline[scan.curr] == '<')
		{
			scan.curr++;
			if (cmdline[scan.curr] == '<')
			{
				scan.curr++;
				strncat(tmp1, cmdline + scan.start, scan.curr - scan.start);
				printf("%s\n", tmp1);
			}
			//strncat(tmp1, cmdline + scan.start, scan.curr - scan.start);
		}
		if (cmdline[scan.curr] == '>')
		{
			scan.curr++;
			strncat(tmp1, cmdline + scan.start, scan.curr - scan.start);
			printf("%s\n", tmp1);
		}
		free(tmp1);
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