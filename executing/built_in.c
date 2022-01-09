/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <bmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 12:56:32 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/10 00:53:57 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0] || !cmd->args[1])
	{
		write(STDERR_FILENO, "Missing an argument.", );
		return (-1);
	}
	if (!chdir(cmd->args[1]))
		return (0);
	if (errno == EACCES || errno == EFAULT)
		write(STDERR_FILENO, "Access denied.\n", 15);
	if (errno == ELOOP || errno == ENAMETOOLONG)
		write(STDERR_FILENO, "Path too long or too much symbolic links.\n", 42);
	if (errno == ENOENT || errno == ENOTDIR)
		write(STDERR_FILENO,
			"The directory specified in path does not exist.\n", 48);
	if (errno == ENOMEM)
		write(STDERR_FILENO, "Insufficient kernel memory was available.\n", 42);
	return (-1);
}

int	ft_pwd(t_cmd *cmd)
{
	char	*res;

	res = getcwd(NULL, 0);
	if (res == NULL)
	{
		if (errno == ENOENT)
			write(STDERR_FILENO,
				"The current working directory has been unlinked.\n", 49);
		if (errno == ENOMEM)
			write(STDERR_FILENO, "Out of memory.\n", 15);
		if (errno == EACCES)
			write(STDERR_FILENO,
				"Permission to read or search path denied.\n", 42);
		return (-1);
	}
	write(STDOUT_FILENO, res, ft_strlen(res));
	write(STDOUT_FILENO, "\n", 1);
	free(res);
	return (0);
}

int	built_in_exe(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->name, "pwd"))
		return (ft_pwd(cmd));
	if (!ft_strcmp(cmd->name, "cd"))
		return (0);
	if (!ft_strcmp(cmd->name, "echo"))
		return (0);
	if (!ft_strcmp(cmd->name, "unset"))
		return (0);//ft_unset(cmd);
	if (!ft_strcmp(cmd->name, "exit"))
		return (0);
	if (!ft_strcmp(cmd->name, "env"))
		return (0);
	if (!ft_strcmp(cmd->name, "export"))
		return (0);
	return (-1);
}
