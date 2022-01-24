/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 00:53:16 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/24 05:20:57 by aaapatou         ###   ########.fr       */
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

void	heredoc_fill_file(char *read, char *delimiter, int fd)
{
	read = readline(">");
	while (read)
	{
		if (ft_strncmp(read, delimiter, ft_strlen(read) + ft_strlen(delimiter) + 2) != 0)
		{
			write(fd, read, ft_strlen(read));
			write(fd, "\n", 1);
		}
		else
			break ;
		free(read);
		read = readline(">");
	}
}

char	*get_heredoc(char *line, int *i, t_cmd *act)
{
	char	*delimiter;
	char	*read;
	char	*file;
	char	*temp;
	int		fd;

	read = NULL;
	delimiter = get_word(line, i, act);
	temp = ft_strjoin(".heredoc_", delimiter);
	fd = open(temp, O_RDWR | O_CREAT | O_EXCL, 00666);
	while (fd == -1)
	{
		file = temp;
		temp = ft_strjoin(temp, "x");
		free(file);
		fd = open(temp, O_RDWR | O_CREAT | O_EXCL, 00666);
	}
	heredoc_fill_file(read, delimiter, fd);
	close(fd);
	free(delimiter);
	return (temp);
}

t_redir	*create_redirect(char *line, int *i, int type, t_cmd *act)
{
	t_redir		*redir;

	redir = malloc(sizeof(t_redir) * 1);
	while (whitespace(line[*i]))
		*i = *i + 1;
	if (type == 2)
		redir->file = get_heredoc(line, i, act);
	else
		redir->file = get_word(line, i, act);
	redir->type = type;
	return (redir);
}

void	get_redirect(char *line, int *i, t_cmd *act)
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
}
