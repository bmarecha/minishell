/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 02:05:24 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/15 18:02:10 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**copy_env(char **env)
{
	int		i;
	int		shlvl;
	char	*shl;
	char	**vne;

	i = 0;
	while (env[i])
		i++;
	vne = malloc(sizeof(char *) * (i + 1));
	vne[i] = NULL;
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6))
			vne[i] = ft_strdup(env[i]);
		else
		{
			shlvl = atoi(env[i] + 6);
			shl = ft_itoa(++shlvl);
			vne[i] = ft_strjoin("SHLVL=", shl);
			free(shl);
		}
	}
	return (vne);
}

void	init_command(t_cmd *cmd)
{
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->pipe = 3;
	cmd->i_red = NULL;
	cmd->o_red = NULL;
}
