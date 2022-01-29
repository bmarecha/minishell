/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:53:10 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/29 23:01:30 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	search_sig(char *str, int sig)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == sig)
			return (1);
		i++;
	}
	return (0);
}

int	heredoc_fill_file(char *read, char *delimiter, int fd)
{
	static int	s_line;

	signal(SIGINT, handle_sig_heredoc);
	s_line++;
	read = readline("> ");
	while (read)
	{
		if (ft_strncmp(read, delimiter,
				ft_strlen(read) + ft_strlen(delimiter) + 2) != 0)
		{
			s_line++;
			write(fd, read, ft_strlen(read));
			write(fd, "\n", 1);
		}
		else
			break ;
		free(read);
		read = readline("> ");
	}
	if (read == NULL)
	{
		ft_putstr_fd("minishell: warning: here-document at line ", 2);
		ft_putnbr_fd(s_line, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putstr_fd("')\n", 2);
	}
	if (read)
		free(read);
	return (0);
}

char	*get_heredoc(char *line, int *i, t_cmd *act)
{
	char	*delimiter;
	char	*read;
	char	*file;
	char	*temp;
	int		fd;
	int		fail;

	read = NULL;
	signal(SIGINT, SIG_IGN);
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
	if (!fork() && heredoc_fill_file(read, delimiter, fd) == 0)
		exit(1);
	waitpid(-1, &fail, 0);
	if (WEXITSTATUS(fail) > 0)
	{
		unlink(temp);
		free(temp);
		temp = NULL;
		if (WEXITSTATUS(fail) == 3)
		{
			act = get_first_cmd(act);
			act->fail = 1;
		}
	}
	close(fd);
	free(delimiter);
	return (temp);
}
