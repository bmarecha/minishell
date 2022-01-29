/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:53:10 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/29 18:56:28 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	heredoc_fill_file(char *read, char *delimiter, int fd)
{
	static int	line;

	line++;
	read = readline("> ");
	while (read)
	{
		if (ft_strncmp(read, delimiter,
				ft_strlen(read) + ft_strlen(delimiter) + 2) != 0)
		{
			line++;
			write(fd, read, ft_strlen(read));
			write(fd, "\n", 1);
		}
		else
			break ;
		free(read);
		read = readline(">");
	}
	if (read == NULL)
	{
		ft_putstr_fd("minishell: warning: here-document at line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `eof')\n", 2);
	}
	if (read)
		free(read);
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
