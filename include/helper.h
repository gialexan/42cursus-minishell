/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:17:20 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/04 13:50:58 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H
# define HELPER_H

# include "parser.h"
# include "execute.h"

# define EMPY ""

/***************************************************************************\
 * HELPER/PATH.C
\***************************************************************************/

void	init_arraypath(void);

/***************************************************************************\
 * HELPER/INTERFACE.C
\***************************************************************************/

t_data	*get_data(void);
t_list	**get_envp(void);
char	***get_path(void);

/***************************************************************************\
 * HELPER/ERROR.C
\***************************************************************************/

int	    export_error(char *str);
void	msh_error(char *name, char *msg, int error);

/***************************************************************************\
 * HELPER/CLEANER.C
\***************************************************************************/

void    clear_envment(void);
void    clear_arraypath(void);
void	clear_dlst(t_cmd *lst, void (*del)(void *));

/***************************************************************************\
 * HELPER/PRINT.C
\***************************************************************************/

void	print_cmd(t_cmd *cmd);
int     declare_x(t_list *envp);
void	print_redir(t_list *token);
void	print_stack(t_list *lst, int type);

/***************************************************************************\
 * HELPER/ENVIRONMENT.C
\***************************************************************************/

void	init_envment(char **envpment, t_list **envp);
t_bool	update_envp(const char *update, t_list *envp);
t_list *search_envp(const char *search, t_list *envp);
t_bool	insert_envp(const char *insert, t_list **envp);
t_bool	delete_envp(const char *dell, t_list **envp, t_list *prev);

/***************************************************************************\
 * EXPANSION/EXPANSION.C
\***************************************************************************/

char	*unquote(char *str);
char	*expand(char *word);
char	*slice_word(t_scanner *scanner);
char	*slice_quotes(t_scanner *scanner);
char    *concatenate(char *str, char *append);
char	*pathname_expansion(char *path, int i, int init);

#endif