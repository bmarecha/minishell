static char	*find_path(char *cmd, char **paths)
{
	int		i;
	char	*path;
	char	*cmd2;

	i = -1;
	cmd2 = ft_strjoin("/", cmd);
	free(cmd);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], cmd2);
		if (!access(path, R_OK))
		{
			free_split(&paths);
			free(cmd2);
			return (path);
		}
		if (path)
			free(path);
	}
	join_write(2, "Command Not found : ", cmd2 + 1);
	free_split(&paths);
	free(cmd2);
	return (NULL);
}

static char	*split_cmd(t_cmd *cmd)
{
	char	**split;
	char	**paths;
	char	*path;

	split = ft_split(cmd->name, " ");
	if ((!split || !split[0]) && write(2, full, ft_strlen(full)))
	{
		write(2, "Command name missing.\n", 18);
		return (NULL);
	}
	cmd->args = split;
	if (!access(split[0], R_OK))
		return (split[0]);
	path = getenv("PATH");
	printf("PATH value : %s\n", path);
	paths = ft_split(path, ":");
	if (!paths)
		return (NULL);
	return (find_path(split[0], paths));
}
