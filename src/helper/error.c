/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:27:43 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/05 12:04:46 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

void	msh_error(char *name, char *msg, int error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (msg == NULL && error == 0)
	{
		perror(name);
		return ;
	}
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	else if (error)
		ft_putendl_fd(strerror(error), STDERR_FILENO);
}

int	export_error(char *str)
{
	char *err_msg;

	err_msg = "`arg': not a valid identifier";
	err_msg = ft_strreplace(err_msg, "arg", str);
	msh_error("export", err_msg, 0);
	free(err_msg);
	return (EXIT_FAILURE);
}

// static void	cd_error(char *path)
// {
// 	if (!path)
// 		msh_error("cd", NULL, 2);
// 	else
// 		msh_error("cd", NULL, 2);
// }