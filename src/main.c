/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/20 19:16:22 by gialexan         ###   ########.fr       */
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
 * Criar msg de erro export
 * criar o unset
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

char *get_key(char *envp)
{
    char	*sign;
	size_t	key_length;

	sign = ft_strchr(envp, '=');
    if (!sign)
        return NULL;
    key_length = sign - envp;
    if (key_length == 0)
        return NULL;
    return (ft_substr(envp, 0, key_length));
}

t_bool valid_string(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (FALSE); //msg erro
	while (str[++i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (FALSE); //msg
	}
	return (TRUE);
}

void	export(char *str)
{
	int		len;
	char	*key;
	char	*tmp;
	t_list	*node;
	t_bool	string;
	
	key = str;
	tmp = get_key(str);
	if (tmp)
		key = tmp;
	string = valid_string(key);
	node = search_envp(key, *get_envp());
	if (node && string)
	{
		len = ft_strlen(str);
		if (ft_strncmp(str, node->content, len))
		{
			update_envp(str, node);
			free(key);
		}
	}
	else if (string)
		insert_envp(str, get_envp());
}

int main(int argc, char **argv, char **envp)
{
	t_data		data;
    t_list		*token = NULL;
	t_cmd		*parser = NULL;
    t_scanner	scanner;

	(void)argv;
	(void)envp;

	// init_envment(envp, get_envp());

	// char *str = "test";
	// export(str);

	// t_list *tmp = search_envp("test", *get_envp());
	// printf("%s\n", (char *)tmp->content);

	// str = "test=viao";
	// export(str);

	// tmp = search_envp("test", *get_envp());
	// printf("%s\n", (char *)tmp->content);

	// str = "test=carro";
	// export(str);

	// tmp = search_envp("test", *get_envp());
	// printf("%s\n", (char *)tmp->content);

	// ft_lstclear(get_envp(), free);

    // char command[] = "< infile ls | ls > outfile -a";
    // scanner = init_scanner(command);
    // token = lexical_analysis(&scanner, token);
	// parser = syntax_analysis(token);
	// data.readpipe = FALSE; //Arrumar lugar melhor para isso.
	// execute_command(parser, &data);
}
