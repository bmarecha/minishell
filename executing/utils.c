/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <bmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:08:40 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/09 21:58:15 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char ***split)
{
	int	i;

	i = -1;
	while ((*split)[++i])
		free((*split)[i]);
	free(*split);
}

void	join_write(int fd, char *str1, char *str2)
{
	write(fd, str1, ft_strlen(str1));
	write(fd, str2, ft_strlen(str2));
	write(fd, "\n", 1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
