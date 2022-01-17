/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:17:36 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/17 14:54:04 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_word(char *str, int *len)
{
	int		in_quote;
	int		start;

	in_quote = 0;
	start = *len;
	while ((!whitespace(str[*len]) || in_quote != 0) && (!is_pipe(str[*len])
			|| !is_redirect(str[*len]) || in_quote != 0) && str[*len])
	{
		in_quote = quote_check(str[*len], in_quote);
		*len = *len + 1;
	}
	if (in_quote != 0)
		return (NULL);
	return (ft_substr(str, start, *len - start));
}

void	get_pipe(char *line, int *i, t_cmd *act)
{
	if (act->prev != NULL)
	{
		if (act->prev->pipe == 1 || act->prev->pipe == 2)
			act->pipe = 0;
	}
	if (!line[*i])
		return ;
	if (line[*i] == ';')
	{
		*i = *i + 1;
		return ;
	}
	if (line[*i] == '|')
	{
		*i = *i + 1;
		if (act->pipe == 0)
			act->pipe = 2;
		else
			act->pipe = 1;
		return ;
	}
}

int	take_command(char *line, int *i, t_cmd *act)
{
	int		arg;

	arg = 0;
	act->name = get_word(line, i);
	while (whitespace(line[*i]))
		*i = *i + 1;
	act->args = malloc(sizeof(char *) * calcul_arg(line, *i) + 2);
	act->args[0] = act->name;
	arg++;
	while (!is_pipe(line[*i]) && !is_redirect(line[*i]) && line[*i])
	{
		act->args[arg] = get_word(line, i);
		arg++;
		while (whitespace(line[*i]))
			*i = *i + 1;
	}
	act->args[arg] = NULL;
	if (is_redirect(line[*i]))
		get_redirect(line, i, act);
	while (whitespace(line[*i]))
		*i = *i + 1;
	if (is_pipe(line[*i]) || line[*i] == 0)
		get_pipe(line, i, act);
	return (1);
}

t_cmd	*get_line(char *line)
{
	t_cmd	*act;
	t_cmd	*new;
	t_cmd	*tokens;
	int		i;

	i = 0;
	act = malloc(sizeof(t_cmd));
	tokens = act;
	init_command(act);
	while (line[i])
	{
		while (whitespace(line[i]))
			i++;
		take_command(line, &i, act);
		if (line[i])
		{
			new = malloc(sizeof(t_cmd));
			init_command(new);
			new->prev = act;
			act->next = new;
			act = new;
		}
	}
	return (tokens);
}

int	read_line(void)
{
	char	*line;
	t_cmd	*tokens;

	line = NULL;
	tokens = NULL;
	ft_putstr("prompt: ");
	while (get_next_line(0, &line) > 0)
	{
		tokens = get_line(line);
		show_tokens(tokens);
		start_chain(tokens);
		ft_putstr("prompt: ");
		free(line);
	}
	return (0);
}

t_glob	g_glob = {.env = NULL, .signal = 0};

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_glob.env = copy_env(env);
	read_line();
	return (0);
}
