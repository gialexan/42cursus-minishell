/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:51:31 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/09 00:55:50 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#define TOO_MANY_ARGS "too many arguments"
#define NUMERIC_ARGS "numeric argument required"

static t_bool	check_exit_code(char *stts);
static int		get_exit_status(t_list *token);
static t_bool	handled_bad_status(char *token);

int	ft_exit(t_list *token)
{
	int		exit_status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (ft_lstsize(token) > 2)
	{
		msh_error("exit", TOO_MANY_ARGS, 0);
		return (1);
	}
	exit_status = get_exit_status(token->next);
	msh_clear();
	exit(exit_status);
}

static t_bool	check_exit_code(char *stts)
{
    int		tmp;
    char	*aux;

    if (!stts)
        return (TRUE);
    if (ft_strlen(stts) > 11)
        return (FALSE);
    tmp = ft_atoi(stts);
    aux = ft_itoa(tmp);
    if (ft_strcmp(aux, stts) != 0)
    {
        free(aux);
        return (TRUE);
    }
    free(aux);
    return (FALSE);
}

static t_bool    handled_bad_status(char *token)
{
    int		i;
    char    *msg;

    if (!token)
        return (FALSE);
    if (ft_strlen(token) > 19)
        msh_error("exit", NUMERIC_ARGS, 0);
	else
	{
		i = -1;
		while (token[++i])
		{
			if (ft_isalpha(token[i]))
			{
				msg = ft_strdup(token);
				msg = ft_strjoin_free(msg, NUMERIC_ARGS);
				msh_error("exit", msg, 0);
				free(msg);
				return (TRUE);
			}
		}
	}
    return (FALSE);
}

static int    get_exit_status(t_list *token)
{
    int    stts;

    if (!token)
        return (*get_exit_code());
    if (handled_bad_status(token->content))
        return (2);
    if (!check_exit_code(token->content))
        return(1);
    stts = ft_atoi(token->content);
    return (stts);
}