/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:17:53 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/06 23:33:41 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_redirect
{
	int			fd;
	t_bool		boolean;
	const char *message;
	const char *filename;
}	t_redirect;

typedef struct s_execute
{
	t_redir	*input;
	t_redir *error;
	t_redir *output;
}	t_execute;

#endif