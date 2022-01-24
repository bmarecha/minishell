/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 04:54:34 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/24 05:26:21 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_prompt(char **env)
{
	char	*prompt;
	char	*temp;
	char	*pwd;
	char	*ok;

	prompt = NULL;
	prompt = ft_strdup("");
	temp = find_env("USER", env);
	ok = ft_strjoin(prompt, temp);
	free(prompt);
	prompt = ft_strjoin(ok, ":");
	free(ok);
	pwd = getcwd(NULL, 0);
	ok = ft_strjoin(prompt, pwd);
	free(prompt);
	prompt = ft_strjoin(ok, "$ ");
	free(ok);
	free(temp);
	free(pwd);
	return (prompt);
}

char	*reading(char *line, char ***env)
{
	char	*prompt;

	prompt = get_prompt(*env);
	line = readline(prompt);
	add_history(line);
	free(prompt);
	return (line);
}

void	start_command(char *line, int *i, t_cmd *act, int *arg)
{
	while (is_redirect(line[*i]))
	{
		get_redirect(line, i, act);
		while (whitespace(line[*i]))
			*i = *i + 1;
	}
	act->name = get_word(line, i, act);
	while (whitespace(line[*i]))
		*i = *i + 1;
	act->args = calloc(calcul_arg(line, *i) + 3, sizeof(char *));
	act->args[0] = act->name;
	act->arg = 1;
	*arg = *arg + 1;
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
