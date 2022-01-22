/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 05:20:31 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/21 05:26:42 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*find_env(char *nail, char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		while (env[i][j] == nail[j])
			j++;
		if (env[i][j] == '=')
			return (ft_substr(env[i], j + 1, ft_strlen(env[i]) - j));
		i++;
		j = 0;
	}
	return (NULL);
}

int	replace_with_env(char *word, int i, char ***env)
{
	char	*new;
	char	*var;
	char	*temp;
	int		start;
	int		j;

	j = 0;
	new = ft_substr(word, 0, i);
	var = calloc(ft_strlen(word) + 1, sizeof(char));
	start = i;
	i++;
	while (!ft_whitespace(word[i]) && word[i] && word[i] != '$')
	{
		var[j] = word[i];
		j++;
		i++;
	}
	temp = find_env(var, *env);
	start = start + ft_strlen(temp);
	ft_strjoin(new, temp);
	free(temp);
	temp = ft_substr(word, i, 500);
	ft_strjoin(new, temp);
	free(word);
	free(var);
	word = new;
	return (start);
}

char	*get_env_variable(char *word, char ***env)
{
	int		i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
			i = replace_with_env(word, i, env);
		i++;
	}
	return (word);
}
