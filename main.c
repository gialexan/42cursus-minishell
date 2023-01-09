/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/01/09 14:53:11 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"


int	main(void)
{
	t_token tk;
	tk.token = TK_PIPE;
	tk.lexema = "|";
	tk.size = 1;
	
	printf("id = %d <-> lexema = %s <-> size = %d\n", tk.token, tk.lexema, tk.size);
	
}
