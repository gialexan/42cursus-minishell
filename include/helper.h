/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:17:20 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/03 12:29:57 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H
# define HELPER_H

# include "parser.h"
# include "execute.h"

/***************************************************************************\
 * HELPER/PATH.C
\***************************************************************************/

void	init_arraypath(void);
void    clear_arraypath(void);

/***************************************************************************\
 * HELPER/INTERFACE.C
\***************************************************************************/

t_data	*get_data(void);
t_list	**get_envp(void);
char	***get_path(void);

/***************************************************************************\
 * HELPER/ERROR.C
\***************************************************************************/

void	msh_error(char *name, char *msg, int error);

/***************************************************************************\
 * HELPER/CLEANER.C
\***************************************************************************/

void	clear_dlst(t_cmd *lst, void (*del)(void *));

/***************************************************************************\
 * HELPER/PRINT.C
\***************************************************************************/

void	print_cmd(t_cmd *cmd);
void	declare_x(t_list *envp);
void	print_redir(t_list *token);
void	print_stack(t_list *lst, int type);

/***************************************************************************\
 * HELPER/ENVIRONMENT.C
\***************************************************************************/

t_bool	update_envp(char *update, t_list *envp);
t_list *search_envp(char *search, t_list *envp);
t_bool	insert_envp(char *insert, t_list **envp);
void	init_envment(char **envpment, t_list **envp);
t_bool	delete_envp(char *dell, t_list **envp, t_list *prev);

/***************************************************************************\
 * EXPANSION/EXPANSION.C
\***************************************************************************/

char	*unquote(char *str);
char	*expandchr(char *word);
t_bool	empty_quotes(char *str);
t_list	*expandlst(t_list *token, t_list *head);
char	*slice_word(t_scanner *scanner);
char	*slice_quotes(t_scanner *scanner);
char    *concatenate(char *str, char *append);
char	*pathname_expansion(char *path, int i, int init);

#endif