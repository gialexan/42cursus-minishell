/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/22 09:43:55 by gialexan         ###   ########.fr       */
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

char *get_key(char *str)
{
    char	*sign;
	size_t	key_length;

	sign = ft_strchr(str, '=');
    if (!sign)
        return NULL;
    key_length = sign - str;
    if (key_length == 0)
        return NULL;
    return (ft_substr(str, 0, key_length));
}

t_bool	export_error(char *str)
{
	msh_error("export", str, 0);
	return (FALSE);
}

t_bool valid_string(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '_' && !ft_isalnum(str[i + 1]))
		return (FALSE);
	else if (str[i] != '_' && !ft_isalpha(str[i]))
		return (export_error(str));
	while (str[++i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]) && str[i] != '=')
			return (export_error(str));
		if (str[i] == '=')
			return (TRUE);
	}
	return (TRUE);
}

void	exec_unset(char *str)
{
	delete_envp(str, get_envp(), NULL);
}

void	exec_export(char *str)
{
	char	*key;
	char	*tmp;
	t_list	*node;
	int		lenght;
	t_bool	string;
	
	key = str;
	tmp = get_key(str);
	if (tmp)
		key = tmp;
	string = valid_string(str);
	node = search_envp(key, *get_envp());
	if (node && string)
	{
		lenght = ft_strlen(str);
		if (ft_strncmp(str, node->content, lenght))
		{
			update_envp(str, node);
			free(key);
		}
	}
	else if (string)
		insert_envp(str, get_envp());
}

int main(int argc, char **argv, char **envp)  // '"'  $PWD
{
	t_data		data;
    t_list		*token = NULL;
	t_cmd		*parser = NULL;
    t_scanner	scanner;

	(void)argv;
	(void)envp;

	init_envment(envp, get_envp());

	char *str = "te@st";
	printf("%d\n", valid_string(str));

	// t_list *tmp = search_envp("test", *get_envp());
	// printf("%s\n", (char *)tmp->content);

	// str = "test=viao";
	// exec_export(str);

	// tmp = search_envp("test", *get_envp());
	// printf("%s\n", (char *)tmp->content);

	// str = "test";
	// exec_unset(str);

	// tmp = search_envp("test", *get_envp());
	// printf("%p\n", tmp);

	// ft_lstclear(get_envp(), free);

    // char command[] = "\'test";
    // scanner = init_scanner(command);
    // token = lexical_analysis(&scanner, token);
	// parser = syntax_analysis(token);
	// data.readpipe = FALSE; //Arrumar lugar melhor para isso.
	// execute_command(parser, &data);
}
