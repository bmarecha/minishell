/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <bmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:50:08 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/11 17:32:32 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include "../minishell.h"

int		ft_strcmp(const char *s1, const char *s2);
int		built_in_exe(t_cmd *cmd);
char	*get_real_cmd(t_cmd *cmd);
void	free_split(char ***split);
void	join_write(int fd, char *str1, char *str2);

#endif
