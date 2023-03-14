/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:14:40 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/14 16:31:46 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *search_envp(char *search, t_list *envp)
{
	int lenght;

	if (!envp)
		return (NULL);
	else if (!ft_strncmp(search, envp->content, 1))
	{
		lenght = ft_strlen(search);
		if (!ft_strncmp(search, envp->content, lenght))
			return (envp->content);
	}
	return (search_envp(search, envp->next));
}
