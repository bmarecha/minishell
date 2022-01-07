/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <bmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 19:48:16 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/07 01:19:02 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		dupin(int i_fd, t_cmd *cmd)
{
	int fd;

	if (cmd->i_red && cmd->i_red->type == 1)
	{
		if (access(cmd->i_red->file, R_OK))
		{
			perror(cmd->i_red->file);
			return (0);
		}
		fd = open(cmd->i_red->file, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->i_red->file);
			return (0);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
		dup2(i_fd, STDIN_FILENO);
}

int		dupout(int o_fd, t_cmd *cmd)
{
	int fd;

	if (cmd->o_red && cmd->o_red->type >= 3)
	{
		if (access(cmd->o_red->file, W_OK) && errno != ENOENT)
		{
			perror(cmd->o_red->file);
			exit(-1); // And free if we can
		}
		if (cmd->o_red->type  == 3)
			fd = open(cmd->o_red->file,
				O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 00666);
		else
			fd = open(cmd->o_red->file, O_WRONLY | O_CREAT | O_TRUNC, 00666);
		if (fd == -1)
		{
			perror(cmd->o_red->file);
			return (0);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		dup2(i_fd, STDOUT_FILENO);
}

int		execute_cmd(int i_fd, t_cmd *cmd, int o_fd)
{
	cmd->name = get_real_cmd(cmd);
	if (!dupin(i_fd, cmd))
		return (-1); //Free close and exit if possible
	close(i_fd);
	if (!dupout(o_fd, cmd))
		return (-1); //Free close and exit if possible
	close(o_fd);
	if (!built_in_exe(cmd))
		execve(cmd->name, cmd->args, *(cmd->env));
}

int		forking_cmd(int i_fd, t_cmd *cmd, int o_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1) //free and exit but we still don't know how to free
		return (-1);
	else if (pid == 0)
	{
		execute_cmd(i_fd, cmd, o_fd);
		if (infd != -1)
			close(infd);
		return (0);
	}
	if (infd != -1)
		close(infd);
	return (1);
}

int		start_chain(t_cmd *cmd)
{
	int		pipefd[2];
	int		infd;
	int		status;

	infd = -1;
	if (!cmd->name)
		return (-1);
	while (cmd->next)
	{
		if (pipe(pipefd) == -1)
			perror("Can't create pipe");
		if (!forking_cmd(infd, cmd, pipefd[0]))
			break ;
		close(pipefd[0]);
		infd = pipefd[1];
		cmd = cmd->next;
	}
	while (waitpid(-1, &status, WUNTRACED) > 0)
		if (WEXITSTATUS(status))
			write(2, "Error on a child process.\n", 26);
	forking_cmd(infd, cmd, STDOUT_FILENO);
	return (0);
}
