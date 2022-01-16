/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vne_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <bmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 01:25:45 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/15 19:45:05 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char	**add_env(char **env, char *var)
{
	int		i;
	int		n;
	char	**vne;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(var, env[i], ft_strchr(var, '=') - var))
			break ;
	if (env[i])
	{
		free(env[i]);
		env[i] = var;
		return (env);
	}
	n = i;
	while (env[n])
		n++;
	vne = malloc(sizeof(char *) * ++n + 1);
	vne[n] = NULL;
	vne[--n] = var;
	while (--n >= 0)
		vne[n] = env[n];
	free(env);
	return (vne);
}

char	**remove_env(char **env, char *var)
{
	int		i;
	int		n;
	char	**vne;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(var, env[i], ft_strlen(var)))
			break ;
	if (!env[i])
		return (env);
	n = i;
	while (env[n])
		n++;
	vne = malloc(sizeof(char *) * n);
	vne[--n] = NULL;
	while (--n >= 0)
	{
		if (n < i)
			vne[n] = env[n];
		else
			vne[n] = env[n + 1];
	}
	free(env);
	return (vne);
}

int		ft_unset(t_cmd *cmd)
{
	int	n;
	int	i;
	char	*var;

	n = 0;
	while (cmd->args[++n])
	{
		i = -1;
		var = cmd->args[n];
		while (var[++i])
			if (!ft_isalnum((int)var[i]) && var[i] != '_')
				break ;
		if (var[i])
			join_write(STDERR_FILENO, "unset: identifiant non valable :", var);
		else
			g_msh_env = remove_env(g_msh_env, var);
	}
	return (0);
}

int		ft_export(t_cmd *cmd)
{
	int	n;
	int	i;
	char	*var;

	n = 0;
	while (cmd->args[++n])
	{
		i = -1;
		var = cmd->args[n];
		while (var[++i])
			if (var[i] == '=' || (!ft_isalnum((int)var[i]) && var[i] != '_'))
				break ;
		if (var[i] != '=')
			join_write(STDERR_FILENO, "export: identifiant non valable :", var);
		else if (var[i])
			g_msh_env = add_env(g_msh_env, var);
	}
	return (0);
}

int		ft_env()
{
	int	i;
	char **vne;
	i = -1;
	vne = g_msh_env;
	while (vne[++i])
	{
		write(STDOUT_FILENO, vne[i], ft_strlen(vne[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
