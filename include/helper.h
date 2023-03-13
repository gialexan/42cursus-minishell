/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:17:20 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/13 19:33:33 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H
# define HELPER_H

#include <parser.h>

//error.c
void	show_error(char *msg, char *error);

// //cleaner.c
void	clear_dlst(t_cmd *lst, t_list *token, void (*del)(void *));

// //print.c
void	print_redir(t_list *token);
void	print_cmd(t_cmd *cmd);
void	print_stack(t_list *lst, int type);
#endif