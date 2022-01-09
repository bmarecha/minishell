/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:40:56 by aaapatou          #+#    #+#             */
/*   Updated: 2020/02/20 17:40:59 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dst;

	i = 0;
	if (!s)
	{
		if (!(dst = (char *)malloc(sizeof(char) * 1)))
			return (NULL);
		dst[i] = '\0';
		return (dst);
	}
	if (!(dst = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	if (!s)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	if (c == '\0')
		return (str + i);
	return (NULL);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	int		n;
	char	*str;

	if (!s)
		return (0);
	n = (int)start;
	i = 0;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len && s[i] && n < ft_strlen(s))
	{
		str[i] = s[n];
		n++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		k;

	i = 0;
	if (!s1)
		return (str = ft_strdup(s2));
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	free(s1);
	k = 0;
	while (s2[k] != '\0')
	{
		str[i] = s2[k];
		i++;
		k++;
	}
	str[i] = '\0';
	return (str);
}
