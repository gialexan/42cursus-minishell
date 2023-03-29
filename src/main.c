/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/29 11:56:07 by gialexan         ###   ########.fr       */
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
	ft_lstclear(&tmp, free);
	execute_command(cmd->next, data);
	free(cmd);
}
*/

/*
 * Se for só as " é só expandir e fim de papo.
 * Se for só as ' precisa fazer parser de 2 em 2.
 * Se for misturado " e ' é só chorar.
 * Saber se todas estão abertas e fechadas? Contar " e ' depois separadas depois resto da divisão por 2
*/

static	char	advance(t_scanner *scanner)
{
	scanner->current++;
	return (scanner->cmd[scanner->current - 1]);
}

static	t_bool ft_chrcmp(char c1, char c2)
{
	return (c1 == c2);
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
	char c;
	char end;
	char *sliced;

	end = advance(scanner);
	c = advance(scanner);
	while (c != end && c != 0)
		c = advance(scanner);
	return (ft_substr(scanner->cmd, scanner->start,
		scanner->current - scanner->start));
}

t_bool	empty_quotes(char *str)
{
	char	init;

	if (str[0] == '\'' || str[0] == '"')
		init = str[0];
	else
		return (FALSE);
	if (str[1] == init && str[2] == '\0')
		return (TRUE);
	return (FALSE);
}

int	count_quotes(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_chrcmp(str[i],'"') || ft_chrcmp(str[i],'\''))
			count++;
		i++;
	}
	return (count);
}

char	*unquote(char *str)
{
	char *tmp;

	if (empty_quotes(str))
		return (ft_strdup(""));
	else if (ft_chrcmp(str[0], '\''))
		return (ft_strtrim(str, "'"));
	else if (ft_chrcmp(str[0], '"'))
		return (ft_strtrim(str, "'"));
	return (ft_strdup(str));
}

int	wordcount(char *str, char *word)
{
	int i;
	int count;
	int wordlen;

	i = 0;
	count = 0;
	wordlen = ft_strlen(word);
	while (str[i])
	{
		if (ft_strnstr(&str[i], word, ft_strlen(&str[i])) == &str[i])
		{
			count++;
			i += wordlen - 1;
		}
		i++;
	}
	return (count);
}


char *ft_strreplace(char *str, char *oldw, char *neww)
{
	int i;
	char *result;
    int newwlen = ft_strlen(neww);
    int oldwlen = ft_strlen(oldw);

	result = malloc(ft_strlen(str) + wordcount(str, oldw)
			* (newwlen - oldwlen) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (*str)
	{
    	if (ft_strnstr(str, oldw, ft_strlen(str)) == str)
		{
			ft_strlcpy(&result[i], neww, newwlen + 1);
        	i += newwlen;
       		str += oldwlen;
    	}
    	else
        	result[i++] = *str++;
    }
    result[i] = '\0';
    return (result);
}

char	*expand(char *str, char *key) //dar free no str e key no final.
{
	char	*tmp;
	int		quotes;
	t_list	*envp;

	envp = search_envp(key + 1, *get_envp());
	if (!envp)
		return (ft_strdup(""));
	tmp = ft_strreplace(str, key, envp->content);
	return (tmp);
}

char	*variable_expansion(char *str)
{
	int i;
	int init;
	char *tmp;

	i = 0;
	tmp = ft_strdup(str);
	if (ft_chrcmp(str[i], '\''))
		return (tmp);
	while (str[i])
	{
		if (ft_chrcmp(str[i], '$'))
		{
			init = i++;
			if (ft_chrcmp(str[i], '?'))
				return (ft_strdup("1"));
			else if (ft_isalpha(str[i]) || ft_chrcmp(str[i], '_'))
			{
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				return (expand(tmp, ft_substr(tmp, init, i - init)));
			}
		}
		i++;
	}
	return (tmp);
}

t_list	*quotes_splitting(t_scanner *scanner, t_list *quotes)
{
	char *clear;
	char *sliced;
	char *expand;

	if (scanner->current >= ft_strlen(scanner->cmd))
		return (quotes);
	scanner->start = scanner->current;
	if (ft_chrcmp(scanner->cmd[scanner->current], '\'') ||
		ft_chrcmp(scanner->cmd[scanner->current], '"'))
		sliced = slice_quotes(scanner);
	else
		sliced = slice_word(scanner);
	expand = variable_expansion(sliced);
	//clear = unquote(sliced);
	free(sliced);
	//free(tmp);
	ft_lstadd_back(&quotes, ft_lstnew(expand));
	return (quotes_splitting(scanner, quotes));
}

void	word_splitting(void)
{
	t_scanner	scanner;
	t_list		*quotes = NULL;

	//"'ls''''''ola'oi''''bom dia   ''" -> "'ls'''''\"'ola'\"oi''''bomdia"
	char command[] = "$USER";
	//\"'''$USER'''\"
	scanner = init_scanner(command);
	quotes = quotes_splitting(&scanner, quotes);
	print_stack(quotes, 0);
}


// echo "''" '''''" $PWD "''''' "''"
int main(int argc, char **argv, char **envp)  // echo "''" ''" $PWD "'' "''"
{
	t_data		data;
    t_list		*token = NULL;
	t_cmd		*parser = NULL;
    t_scanner	scanner;

	(void)argv;
	(void)envp;

	//char *test = \"''\"gilmar\"''\";

	// char *tmp = ft_strjoin(test, c);
	// printf("%s\n", tmp);

	init_envment(envp, get_envp());

	char str[] = "\"'''$USER'''\"";
    char c[] = "$USER";
    char d[] = "Geeks";
 
    char *result = NULL;

    // oldW string
    printf("Old string: %s\n", str);
 
    printf("New String: %s\n", result);
 
    free(result);
    return 0;

	

	//ft_lstclear(get_envp(), free);

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
