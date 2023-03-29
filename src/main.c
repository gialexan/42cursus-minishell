/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/29 20:05:45 by gialexan         ###   ########.fr       */
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
 * 4 = "<'infile''''ls'''''>outfile | echo \"'''\"''\"'\"gilmar\"'\"''\"'''\""
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
 * Criar o executor de comando;
 * Pegar o exception dos file abertos;
 * Criar expansor de arquivos;
 * Criar expansor geral $pwd, $user
*/

/*
void	init_exec(t_data *data)
{
	if (data->read - true)
		return ;
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
	exec_bultins(cmd->token, data);
	execve_cmd()
	ft_lstclear(&tmp, free);
	execute_command(cmd->next, data);
	free(cmd);
}
*/

static	char	advance(t_scanner *scanner)
{
	scanner->current++;
	return (scanner->cmd[scanner->current - 1]);
}

char	*slice_word(t_scanner *scanner)
{
	char c;

	c = advance(scanner);
	while (c != 0 && c != '\'' && c != '"')
		c = advance(scanner);
	scanner->current--;
	return (ft_substr(scanner->cmd, scanner->start,
		scanner->current - scanner->start));
}

char	*slice_quotes(t_scanner *scanner)
{
	char	c;
	char	end;
	char	*sliced;

	end = advance(scanner);
	c = advance(scanner);
	while (c != end && c != 0)
		c = advance(scanner);
	return (ft_substr(scanner->cmd, scanner->start,
		scanner->current - scanner->start));
}

t_bool	empty_quotes(char *str)
{
	if (ft_chrcmp(str[0], '\'') && ft_chrcmp(str[1], '\''))
		return (TRUE);
	else if (ft_chrcmp(str[0], '"') && ft_chrcmp(str[1], '"'))
		return (TRUE);
	return (FALSE);
}

char	*unquote(char *str)
{
	if (empty_quotes(str))
		return (ft_strdup(""));
	else if (ft_chrcmp(str[0], '\''))
		return (ft_strtrim(str, "'"));
	else if (ft_chrcmp(str[0], '"'))
		return (ft_strtrim(str, "\""));
	return (ft_strdup(str));
}

char	*variable_expansion(char *str, char *key)
{
	char	*tmp;
	t_list	*envp;

	envp = search_envp(key + 1, *get_envp());
	if (!envp)
	{
		if (ft_chrcmp(str[0], '"'))
			tmp = ft_strdup(str);
		else
			tmp = ft_strdup("");
	}
	else
	{
		tmp = ft_strchr(envp->content, '=') + 1;
		tmp = ft_strreplace(str, key, tmp);
	}
	free(key);
	free(str);
	return (tmp);
}

char	*pathname_expansion(char *path, int i, int init)
{
	if (ft_chrcmp(path[0], '\''))
		return (path);
	else if (ft_chrcmp(path[i], '\0'))
		return (path);
	else if (ft_chrcmp(path[i], '$'))
	{
		init = i++;
		if (ft_chrcmp(path[i], '?'))
			return (ft_strdup("1"));
		else if (ft_isalpha(path[i]) || ft_chrcmp(path[i], '_'))
		{
			while (path[i] && (ft_isalnum(path[i]) || ft_chrcmp(path[i],'_')))
				i++;
			path = variable_expansion(path, ft_substr(path, init, i - init));
		}
	}
	return (pathname_expansion(path, i + 1, init));
}

char *concatenate(char *str, char *append)
{
	char	*tmp;

	tmp = str;
	str = ft_strjoin(tmp, append);
	free(tmp);
	return (str);
}

char	*word_splitting(t_scanner *scanner, char *result)
{
	char	*sliced;
	char	*expanded;
	char	*unquoted;

	if (scanner->current >= ft_strlen(scanner->cmd))
		return (result);
	scanner->start = scanner->current;
	if (ft_chrcmp(scanner->cmd[scanner->current], '\'') ||
		ft_chrcmp(scanner->cmd[scanner->current], '"'))
		sliced = slice_quotes(scanner);
	else
		sliced = slice_word(scanner);
	expanded = pathname_expansion(sliced, 0, 0);
	unquoted = unquote(expanded);
	result = concatenate(result, unquoted);
	free(expanded);
	free(unquoted);
	return (word_splitting(scanner, result));
}

void	expand(void)
{
	char		*quotes = NULL;
	t_scanner	scanner;

	char command[] = "\"'$HOME'''$USER'''$PWD'\"";
	scanner = init_scanner(command);
	quotes = word_splitting(&scanner, quotes);
	printf("Saída: %s\n", quotes);
	free(quotes);
}

//\"'''$USER'''\"
// echo "''" '''''" $PWD "''''' "''"
// echo "''" ''" $PWD "'' "''"
//"'ls''''''ola'oi''''bom dia   ''" -> "'ls'''''\"'ola'\"oi''''bomdia"
int main(int argc, char **argv, char **envp)
{
	t_data		data;
    t_list		*token = NULL;
	t_cmd		*parser = NULL;
    t_scanner	scanner;

	(void)argv;
	(void)envp;

	init_envment(envp, get_envp());

	expand();

	ft_lstclear(get_envp(), free);

    return 0;

	//"<'infile''''ls'''''>outfile | echo \"'''\"''\"'\"gilmar\"'\"''\"'''\""
    //char command[] = "echo 'ls'oi''";

    //scanner = init_scanner(command);
    //token = lexical_analysis(&scanner, token);
	//print_stack(token, 0);
	//word_splitting();
	// parser = syntax_analysis(token);
	// data.readpipe = FALSE; //Arrumar lugar melhor para isso.
	// execute_command(parser, &data);
}



// char	*pathname_expansion(char *str)
// {
// 	int i;
// 	int ini;
// 	char *tmp;

// 	i = 0;
// 	tmp = ft_strdup(str);
// 	if (ft_chrcmp(str[i], '\''))
// 		return (tmp);
// 	while (str[i])
// 	{
// 		if (ft_chrcmp(str[i], '$'))
// 		{
// 			ini = i++;
// 			if (ft_chrcmp(str[i], '?'))
// 				return (ft_strdup("1"));
// 			else if (ft_isalpha(str[i]) || ft_chrcmp(str[i], '_'))
// 			{
// 				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 					i++;
// 				return (variable_expansion(tmp, ft_substr(tmp, ini, i - ini)));
// 			}
// 		}
// 		i++;
// 	}
// 	return (tmp);
// }

// t_list	*word_splitting(t_scanner *scanner, t_list *quotes)
// {
// 	char *clear;
// 	char *sliced;
// 	char *expand;

// 	if (scanner->current >= ft_strlen(scanner->cmd))
// 		return (quotes);
// 	scanner->start = scanner->current;
// 	if (ft_chrcmp(scanner->cmd[scanner->current], '\'') ||
// 		ft_chrcmp(scanner->cmd[scanner->current], '"'))
// 		sliced = slice_quotes(scanner);
// 	else
// 		sliced = slice_word(scanner);
// 	expand = pathname_expansion(sliced, 0, 0);
// 	clear = unquote(expand);
// 	//free(sliced);
// 	free(expand);
// 	ft_lstadd_back(&quotes, ft_lstnew(clear));
// 	return (word_splitting(scanner, quotes));
// }