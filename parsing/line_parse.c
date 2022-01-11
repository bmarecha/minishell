/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:17:36 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/11 17:31:23 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int	whitespace(char c)
{
	if (c == ' ' || c == '	')
	{
		return (1);
	}
	return (0);
}

int	is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);	
}
int	is_pipe(char c)
{
	if (c == '|' || c == ';')
		return (1);
	return (0);
}

char	*get_word(char *str, int *len)
{
	int		in_quote;
	int		start;

	in_quote = 0;
	start = *len;
	while ((!whitespace(str[*len]) || in_quote != 0) && (!is_pipe(str[*len]) || !is_redirect(str[*len]) || in_quote != 0) && str[*len])
	{
		if (str[*len] == '\'')
		{
			if (in_quote == 1)
				in_quote = 0;
			else if (in_quote == 0)
				in_quote = 1;
		}
		if (str[*len] == '\"')
		{
			if (in_quote == 2)
				in_quote = 0;
			else if (in_quote == 0)
				in_quote = 2;
		}
		*len = *len + 1;
	}
	if (in_quote != 0)
		return (NULL);
	return (ft_substr(str, start, *len - start));
}

int		wich_redirect(char *line, int *i)
{
	if (line[*i] == '<' && line[*i + 1] != '<')
	{
		*i = *i + 1;
		return (1);
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		*i = *i + 2;
		return (2);
	}
	if (line[*i] == '>' && line[*i + 1] != '>')
	{
		*i = *i + 1;
		return (3);
	}
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		*i = *i + 2;
		return (4);
	}
	return (0);
}

t_redir	*create_redirect(char *line, int *i, int type)
{
	t_redir		*redir;

	redir = malloc(sizeof(t_redir));
	if (type == 1 || type == 4)
		*i = *i + 1;
	if (type == 2 || type == 3)
		*i = *i + 1;
	redir->file = get_word(line, i);
	redir->type = type;
	return (redir);
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

void	get_redirect(char *line, int *i, t_cmd *act)
{
	int		redirect;

	redirect = wich_redirect(line, i);
	if (redirect == 1)
		act->i_red = create_redirect(line, i, 1);
	else if (redirect == 2)
		act->i_red = create_redirect(line, i, 2);
	else if (redirect == 3)
		act->o_red = create_redirect(line, i, 4);
	else if (redirect == 4)
		act->o_red = create_redirect(line, i, 3);
	while (whitespace(line[*i]))
		*i = *i + 1;
	if (is_redirect(line[*i]))
	{
		if (act->i_red)
		{
			free(act->i_red->file);
			free(act->i_red);
			act->i_red = NULL;
		}
		if (act->o_red)
		{
			free(act->o_red->file);
			free(act->o_red);
			act->o_red = NULL;
		}
		get_redirect(line, i, act);
	}
}

int	calcul_arg(char *line, int i)
{
	int		arg;
	int		in_quote;
	int		in_word;

	arg = 0;
	in_quote = 0;
	in_word = 0;
	while (line[i] && (!is_pipe(line[i]) || in_quote != 0) && (!is_redirect(line[i]) || in_quote != 0))
	{
		if (line[i] == '\'')
		{
			if (in_quote == 1)
				in_quote = 0;
			else if (in_quote == 0)
				in_quote = 1;
		}
		if (line[i] == '\"')
		{
			if (in_quote == 2)
				in_quote = 0;
			else if (in_quote == 0)
				in_quote = 2;
		}
		if (!whitespace(line[i]) && !in_word)
			in_word = 1;
		if (whitespace(line[i]) && in_word && !in_quote)
		{
			in_word = 0;
			arg++;
		}
		i++;
	}
	if (in_word == 1)
		arg++;
	return (arg);
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

void	init_command(t_cmd *cmd, char ***env)
{
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->pipe = 3;
	cmd->i_red = NULL;
	cmd->o_red = NULL;
	cmd->env = env;
}

t_cmd	*get_line(char *line, char ***env)
{
	t_cmd	*act;
	t_cmd	*new;
	t_cmd	*tokens;
	int		i;

	i = 0;
	act = malloc(sizeof(t_cmd));
	tokens = act;
	init_command(act, env);
	while (line[i])
	{
		while (whitespace(line[i]))
			i++;
		take_command(line, &i, act);
		if (line[i])
		{
			new = malloc(sizeof(t_cmd));
			init_command(new, env);
			new->prev = act;
			act->next = new;
			act = new;
		}
	}
	return (tokens);
}

void	show_tokens(t_cmd *tokens)
{
	int		i;

	i = 0;
	while (tokens != NULL)
	{
		ft_putstr("___________________\n");
		ft_putstr("name: ");
		ft_putstr(tokens->name);
		ft_putstr("\n");
		while (tokens->args[i] != NULL)
		{
			ft_putstr("argv: ");
			ft_putstr(tokens->args[i]);
			ft_putstr("\n");
			i++;
		}
		ft_putstr("pipe: ");
		ft_putchar(tokens->pipe + 48);
		ft_putstr("\n");
		if (tokens->i_red)
		{
			ft_putstr("file: ");
			ft_putstr(tokens->i_red->file);
			ft_putstr("\n");
			ft_putstr("type: ");
			ft_putchar(tokens->i_red->type + 48);
			ft_putstr("\n");
		}
		if (tokens->o_red)
		{
			ft_putstr("file: ");
			ft_putstr(tokens->o_red->file);
			ft_putstr("\n");
			ft_putstr("type: ");
			ft_putchar(tokens->o_red->type + 48);
			ft_putstr("\n");
		}
		ft_putstr("___________________\n");
		i = 0;
		tokens = tokens->next;
	}
}

int	read_line(char ***env)
{
	char *line;
	t_cmd *tokens;

	line = NULL;
	tokens = NULL;
	ft_putstr("prompt: ");
	while (get_next_line(0, &line) > 0)
	{
		tokens = get_line(line, env);
		show_tokens(tokens);
		start_chain(tokens);
		ft_putstr("prompt: ");
		free(line);
	}
	ft_putstr("exit");
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	read_line(&env);
	return (0);
}
