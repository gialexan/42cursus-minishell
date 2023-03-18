/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/18 08:11:15 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------TESTES---------------------------------------------------------------//
/*
 *				<---------------------Lexical Analysis Testes---------------------->
 * teste:
 * 1 = "<<<>>>	|>|<<    |>>'ola42'\"ola42\"    ola42     "
 * 2 = "< infile ls -l -a -b -cd > outfile | < outfile"
 * 3 = "< ls -l -a -b -cd > 'test'"
 *
 *              <---------------------Syntax Analysis Testes----------------------->
 * No error:
 *	1 = < infile, 2 = ls > outfile, 3 = ls > outfile | cat infile, 4 = << infile >> outfile, 5 = ls wc-l
 * Error:
 *	1 = ls ||| wc -l, 2 = ls |, 3 = ls >, 4 = <, 5 = |, 6 = <<infile>>>, 7 = <<<infile, 8 = ls | >, 9 = ls > |
 *
 * [<<] [EOF] [test1] [ls] [<] [test] [cat] [<<] [EOF] [-l] [<<] [EOF1] [>>] [test] [>] [test]
 *
 *              <---------------------Coisas Aleatórios----------------------->
 * run_cmdlst vai estar dentro da execute_command:
 * ls <<EOF -l > outfile < infile
 * cat > ./outfiles/outfiles1 < missing
 * cat > outfile < missing
 * "<< EOF test1  ls < test  cat <<EOF -l << EOF1 >> test > test"
 * echo "Olá, 42 São Paulo!" > /tmp/heredoc.txt
*/

/* TO DO
 *
 * Criar o executor de comando;
 * Pegar o exception dos file abertos;
 * Criar expansor de arquivos;
 * Criar expansor geral $pwd, $user
 *
 * Criar search_envp = ok;
 * Criar delete_envp = ok;
 * Criar insert_envp = ok;
 * 
*/

/* 
void	init_exec(t_data *data)
{
	data->fd[STDIN_FILENO] = STDIN_FILENO;
	data->fd[STDOUT_FILENO] = STDOUT_FILENO;
	data->retcode = 0;
	data->error = FALSE;
}

void	execute_command(t_cmd *cmd, t_data *data)
{
	t_list	*tmp;

	if (!cmd)
		return ;
	init_exec(data);
	tmp = exec_redirect(cmd->token, data, NULL);
	ft_lstclear(&tmp, free);
	execute_command(cmd->next, data);
	free(cmd);
}
*/

/* t_list *search_envp(char *search, t_list *envp)
{
	int lenght;

	if (!envp)
		return (NULL);
	else if (!ft_strncmp(search, envp->content, 1))
	{
		lenght = ft_strlen(search);
		if (!ft_strncmp(search, envp->content, lenght))
			return (envp);
	}
	return (search_envp(search, envp->next));
}

t_bool	delete_envp(char *delete, t_list **envp, t_list *prev)
{
	t_list	*tmp;
	int		lenght;

	if (!*envp)
		return (FALSE);
	tmp = *envp;
	if (!ft_strncmp(delete, tmp->content, 1))
	{
		lenght = ft_strlen(delete);
		if (!ft_strncmp(delete, tmp->content, lenght))
		{
			if (!prev)
				*envp = (*envp)->next;
			else if (prev && *envp)
				prev->next = (*envp)->next;
			free(tmp);
			tmp = NULL;
			return (TRUE);
		}
	}
	return (delete_envp(delete, &(*envp)->next, *envp));	
}

t_bool	insert_envp(char *insert, t_list **envp)
{
	if (!insert)
		return (FALSE);
	ft_lstadd_back(envp, ft_lstnew(insert));
	return (TRUE);
}

t_bool	update_envp(char *key, char *new, t_list **envp)
{
	t_list *update;

	update = search_envp(key, *envp);
	if (!update)
		return FALSE;
	free(update->content);
	update->content = new;
	return (TRUE);
}
 */

char *get_key(char *envp)
{
    char *sign;
	size_t key_length;

	sign = ft_strchr(envp, '=');
    if (!sign)
        return NULL;
    key_length = sign - envp;
    if (key_length == 0)
        return NULL;
    return ft_substr(envp, 0, key_length);
}

int main(int argc, char **argv, char **envp)
{
	t_data		data;
    t_list		*token = NULL;
	t_cmd		*parser = NULL;
    t_scanner	scanner;

	(void)argv;
	(void)envp;

	///init_envment(envp, get_envp());

	char *str = "cavalinho_test1_test2=cavalomanço=test2_test1";
	char *test = get_key(str);
	if (test)
		printf("%s\n", test);
	else
		printf("%p\n", test);
	// if (result)
	// 	len = ft_strlen(result);
	//int len = strlen(result);
	//printf("%s", ft_substr(str, 0, len));
    // char command[] = "< infile ls | ls > outfile -a";

    // scanner = init_scanner(command);
    // token = lexical_analysis(&scanner, token);
	// parser = syntax_analysis(token);
	// data.readpipe = FALSE; //Arrumar lugar melhor para isso.
	// execute_command(parser, &data);
}
