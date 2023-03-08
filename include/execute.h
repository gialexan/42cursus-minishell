/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:17:53 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/08 14:45:47 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <helper.h>

typedef struct s_redirect
{
	int		fd;
	t_bool	boolean;
}	t_redirect;

typedef struct s_execute
{
	int			fd[2];
	t_redirect	*input;
	t_redirect *error;
	t_redirect *output;
}	t_execute;

t_token *exec_redirect(t_token *token, t_token *head);

#endif