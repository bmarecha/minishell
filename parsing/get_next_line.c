/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:40:31 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/06 17:50:54 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		nouvelleligne(char *str)
{
	int				i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

static char		*pnl(char *line, char **str)
{
	char	*tmp;
	int		i;

	if (!(ft_strchr(*str, '\n')))
	{
		if (!(line = ft_strdup(*str)))
			return (NULL);
		free(*str);
		*str = NULL;
	}
	else
	{
		i = nouvelleligne(*str);
		if (!(line = ft_substr(*str, 0, i)))
			return (NULL);
		tmp = *str;
		if (!(*str = ft_strdup(tmp + i + 1)))
			return (NULL);
		free(tmp);
	}
	return (line);
}

int				get_next_line(int fd, char **line)
{
	char			*tmp;
	static char		*str = NULL;
	int				n;

	if (BUFFER_SIZE <= 0)
		return (-1);
	if (fd < 0 || !line || (!(tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1)))))
		return (-1);
	while (!(ft_strchr(str, '\n')) && (n = read(fd, tmp, BUFFER_SIZE)))
	{
		if (n == -1)
		{
			free(tmp);
			return (-1);
		}
		tmp[n] = '\0';
		if (!(str = ft_strjoin(str, tmp)))
			return (-1);
	}
	free(tmp);
	if (!(*line = pnl(*line, &str)))
		return (-1);
	return ((!str && !n) ? 0 : 1);
}
