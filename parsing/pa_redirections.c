/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 00:53:16 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/29 21:49:52 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

void	clean_redir(t_cmd *act, int redirect)
{
	if (act->i_red && (redirect == 1 || redirect == 2))
	{
		free(act->i_red->file);
		free(act->i_red);
		act->i_red = NULL;
	}
	if (act->o_red && (redirect == 3 || redirect == 4))
	{
		free(act->o_red->file);
		free(act->o_red);
		act->o_red = NULL;
	}
}

int	wich_redirect(char *line, int *i)
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

t_redir	*create_redirect(char *line, int *i, int type, t_cmd *act)
{
	t_redir		*redir;

	redir = malloc(sizeof(t_redir) * 1);
	while (whitespace(line[*i]))
		*i = *i + 1;
	redir->access = 1;
	if (type == 2)
		redir->file = get_heredoc(line, i, act);
	else
	{
		redir->file = get_word(line, i, act);
		if (access(redir->file, F_OK) == 0)
		{
			if (type == 1 && access(redir->file, R_OK) == -1)
			{
				redir->access = 0;
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(redir->file, 2);
				ft_putstr_fd(": Permission non accordée\n", 2);
			}
			else if (access(redir->file, W_OK) == -1)
			{
				redir->access = 0;
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(redir->file, 2);
				ft_putstr_fd(": Permission non accordée\n", 2);
			}
		}
		else if (type == 1)
		{
			redir->access = 0;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redir->file, 2);
			ft_putstr_fd(": Aucun fichier ou dossier de ce type\n", 2);
		}
		else if (type == 3)
			open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 00666);
		else 
			open(redir->file, O_WRONLY | O_CREAT, 00666);
	}
	redir->type = type;
	return (redir);
}

int	get_redirect(char *line, int *i, t_cmd *act)
{
	int		redirect;

	redirect = wich_redirect(line, i);
	if (act->i_red || act->o_red)
		clean_redir(act, redirect);
	if (redirect == 1)
		act->i_red = create_redirect(line, i, 1, act);
	else if (redirect == 2)
		act->i_red = create_redirect(line, i, 2, act);
	else if (redirect == 3)
		act->o_red = create_redirect(line, i, 4, act);
	else if (redirect == 4)
		act->o_red = create_redirect(line, i, 3, act);
	if (act->o_red && act->o_red->access == 0)
		return (go_to_pipe(line, i, act));
	if (act->i_red && act->i_red->access == 0)
		return (go_to_pipe(line, i, act));
	return (1);
}
