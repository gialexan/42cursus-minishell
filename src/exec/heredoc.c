/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:00:51 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/07 19:06:55 by gialexan         ###   ########.fr       */
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

void	exec_heredoc(char *delimiter)
{
	int fd;
	char *input;

	fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
