/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/01/09 14:44:42 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

int	main(void)
{
	printf("%d\n", TK_EOF);
	printf("%d\n", TK_WORD);
	printf("%d\n", TK_PIPE);
	printf("%d\n", TK_LESS);
	printf("%d\n", TK_GREAT);
	printf("%d\n", TK_DLESS);
	printf("%d\n", TK_DGREAT);
}
