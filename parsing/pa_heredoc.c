#include "parsing.h"

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
