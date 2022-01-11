/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <bmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:42:41 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/11 18:21:12 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

static char	*find_path(char *cmd, char **paths)
{
	int		i;
	char	*path;
	char	*cmd2;

	i = -1;
	printf("Searching cmd path\n");
	cmd2 = ft_strjoin("/", cmd);
	printf("Cnf\n");
	free(cmd);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], cmd2);
		if (!access(path, R_OK))
		{
			printf("Command found\n");
			write(1, "Cf\n", 3);
			free_split(&paths);
			free(cmd2);
			return (path);
		}
		if (path)
			free(path);
	}
	printf("Command not found\n");
	join_write(2, "Command Not found : ", cmd2 + 1);
	write(1, "Cnf\n", 4);
	free_split(&paths);
	free(cmd2);
	return (NULL);
}

char	*get_real_cmd(t_cmd *cmd)
{
	char	**paths;
	char	*path;

	if (!cmd->name)
	{
		write(2, "Command name missing.\n", 18);
		return (NULL);
	}
	if (!access(cmd->name, R_OK))
		return (cmd->name);
	path = getenv("PATH");
	paths = ft_split(path, ":");
	if (!paths)
		return (NULL);
	return (find_path(cmd->name, paths));
}
