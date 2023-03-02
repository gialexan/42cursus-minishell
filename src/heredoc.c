/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:00:51 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/02 15:03:47 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>


/*
* Prototipagem inicial da função heredoc.
*
* To do:
* Salvar o fd em algum lugar para usar no na hr de executar
* Os textos esritos no here_doc devem expandir se forem variáveis de expansão.
*
*/

void	here_doc(char *delimiter)
{
	int fd;
	char *input;
	
	fd = open ("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while (TRUE)
	{
		input = readline("> ");
		if (!ft_strcmp(input, delimiter))
			break ;
		ft_putendl_fd(input, fd);
		free(input);
	}
	free(input);
	close(fd);
}