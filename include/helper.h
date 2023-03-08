/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:17:20 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/08 11:02:26 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H
# define HELPER_H

#include <parser.h>


//linkedlist.c
void	lstadd_back(t_token **lst, t_token *new);
void	lstdelone(t_token *lst, void (*del)(void*));

//cleaner.c
void	lstclear(t_token *lst, void (*del)(void *));
void	clear_dlst(t_cmd *lst, t_token *token, void (*del)(void *));

//print.c
void	print(t_token *token);
void	print_cmd(t_cmd *cmd);
void	print_stack(t_token *token, int type);
#endif