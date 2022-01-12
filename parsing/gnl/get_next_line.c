/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:51:20 by bmarecha          #+#    #+#             */
/*   Updated: 2020/07/10 15:41:24 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	is_end_of_file(char **memfd, int gnl_value)
{
	if (!gnl_value)
	{
		free(*memfd);
		*memfd = 0;
	}
}

int	loop_till_eol(int fd, char **memory)
{
	int		readv;
	char	*temp;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (-42);
	readv = 1;
	while (!gnl_strrchr(memory[fd], '\n'))
	{
		readv = read(fd, temp, BUFFER_SIZE);
		if (readv <= 0)
		{
			free(temp);
			return (readv);
		}
		temp[readv] = '\0';
		memory[fd] = ft_stradd(memory[fd], temp);
	}
	free(temp);
	return (readv);
}

int	get_next_line(int fd, char **line)
{
	static char		*memory[126];
	int				res;
	int				readv;

	if (!line || BUFFER_SIZE <= 0 || fd < 0)
		return (-1);
	if (!(memory[fd]))
	{
		memory[fd] = malloc(1);
		if (!memory[fd])
			return (-1);
		*memory[fd] = 0;
	}
	readv = loop_till_eol(fd, memory);
	if (readv == -42)
		return (-1);
	res = gnl_strrchr(memory[fd], '\n');
	*line = ft_cpyto(memory[fd], '\n');
	memory[fd] = ft_resetto(memory[fd], '\n');
	if (readv == -1)
		return (-1);
	is_end_of_file(&memory[fd], res);
	return (res);
}
