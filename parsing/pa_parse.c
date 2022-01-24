/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:17:36 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/24 17:55:13 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_word(char *str, int *len, t_cmd *act)
{
	int		in_quote;
	int		start;
	char	*word;

	in_quote = 0;
	start = *len;
	while ((!whitespace(str[*len]) || in_quote)
		&& (!is_pipe(str[*len]) || in_quote)
		&& (!is_redirect(str[*len]) || in_quote) && str[*len])
	{
		in_quote = quote_check(str[*len], in_quote);
		*len = *len + 1;
	}
	if (in_quote != 0)
		return (NULL);
	word = ft_substr(str, start, *len - start);
	if (act->arg == 1)
		word = get_env_variable(word, act);
	word = delete_quotes(word);
	return (word);
}

int	take_command(char *line, int *i, t_cmd *act)
{
	int		arg;

	arg = 0;
	start_command(line, i, act, &arg);
	while (!is_pipe(line[*i]) && line[*i])
	{
		if (is_redirect(line[*i]))
			get_redirect(line, i, act);
		while (whitespace(line[*i]))
			*i = *i + 1;
		if (is_pipe(line[*i]) || !line[*i])
			break ;
		act->args[arg] = get_word(line, i, act);
		arg++;
		while (whitespace(line[*i]))
			*i = *i + 1;
	}
	act->args[arg] = NULL;
	while (whitespace(line[*i]))
		*i = *i + 1;
	if (is_pipe(line[*i]) || line[*i] == 0)
		get_pipe(line, i, act);
	return (1);
}

t_cmd	*get_error(char	c, t_cmd *tokens)
{
	free_all_cmd(tokens);
	if (c == '|')
		ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « | »\n", 2);
	if (c == '>')
		ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « > »\n", 2);
	if (c == '<')
		ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « < »\n", 2);
	return (NULL);
}

void	check_init(t_checkerror *error)
{
	error->i = 0;
	error->iq = 0;
	error->cp = 0;
	error->cti = 0;
	error->cto = 0;
}

t_checkerror	check_error_two(char *line, t_checkerror e)
{
	if (!ft_whitespace(line[e.i]) && (!is_redirect(line[e.i]) || e.iq) && (!is_pipe(line[e.i]) || e.iq))
		e.cto = 0;
	if (!ft_whitespace(line[e.i]) && (!is_redirect(line[e.i]) || e.iq) && (!is_pipe(line[e.i]) || e.iq))
		e.cti = 0;
	if (!ft_whitespace(line[e.i]) && (!is_pipe(line[e.i]) || e.iq) && (!is_redirect(line[e.i]) || e.iq))
		e.cp = 0;
	if (line[e.i] == '>' && !e.iq)
		e.cto++;
	if (line[e.i] == '<' && !e.iq)
		e.cti++;
	if (line[e.i] == '|' && !e.iq)
		e.cp++;
	return (e);
}

t_cmd	*show_error(t_checkerror e, t_cmd *tokens)
{
	if (e.iq != 0)
	{
		ft_putstr_fd("bash: erreur: quotes unclosed\n", 2);
		free_all_cmd(tokens);
		return (NULL);
	}
	if (e.cp != 0)
	{
		ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « | »\n", 2);
		free_all_cmd(tokens);
		return (NULL);
	}
	if (e.cto != 0)
	{
		ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « newline »\n", 2);
		free_all_cmd(tokens);
		return (NULL);
	}
	if (e.cti != 0)
	{
		ft_putstr_fd("bash: erreur de syntaxe près du symbole inattendu « newline »\n", 2);
		free_all_cmd(tokens);
		return (NULL);
	}
	return (tokens);
}

t_cmd	*check_error(char *line, t_cmd *tokens)
{
	t_checkerror e;

	check_init(&e);
	while (line[e.i])
	{
		e.iq = quote_check(line[e.i], e.iq);
		e = check_error_two(line, e);
		if (e.cti == 3 || e.cto == 3 || e.cp == 2 || (line[e.i] == '>' && (e.cti != 0 || e.cp != 0))
			|| (line[e.i] == '<' && (e.cto != 0 || e.cp != 0)) || (line[e.i] == '|' && (e.cto == 2 || e.cti != 0)))
			return (get_error(line[e.i], tokens));
		e.i++;
	}
	tokens = show_error(e, tokens);
	return (tokens);
}

t_cmd	*get_line(char *line, char ***env, int exit)
{
	t_cmd	*act;
	t_cmd	*new;
	t_cmd	*tokens;
	int		i;

	i = 0;
	act = malloc(sizeof(t_cmd));
	tokens = act;
	init_command(act, env, exit);
	while (line[i])
	{
		while (whitespace(line[i]))
			i++;
		take_command(line, &i, act);
		if (line[i])
		{
			new = malloc(sizeof(t_cmd));
			init_command(new, env, exit);
			new->prev = act;
			act->next = new;
			act = new;
		}
	}
	tokens = check_error(line, tokens);
	return (tokens);
}

int	read_line(char ***env, struct sigaction *sa1, struct sigaction *sa2)
{
	char	*line;
	t_cmd	*tokens;
	int		exit;

	exit = 0;
	line = NULL;
	manage_sig(1, sa1, sa2);
	line = reading(line, env);
	while (line != NULL)
	{
		tokens = get_line(line, env, exit);
		show_tokens(tokens);
		manage_sig(0, sa1, sa2);
		if (tokens)
			exit = start_chain(tokens);
		manage_sig(1, sa1, sa2);
		free(line);
		if (exit == 3)
			break ;
		line = reading(line, env);
	}
	rl_clear_history();
	if (!exit)
		ft_putstr("exit\n");
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char				**new_env;
	struct sigaction	sa1;
	struct sigaction	sa2;

	sa1.sa_flags = SA_RESTART;
	sa1.sa_handler = &handle_sig;
	sigemptyset(&sa1.sa_mask);
	sa2.sa_flags = SA_RESTART;
	sa2.sa_handler = SIG_IGN;
	sigemptyset(&sa2.sa_mask);
	(void)ac;
	(void)av;
	new_env = copy_env(env);
	read_line(&new_env, &sa1, &sa2);
	return (0);
}
