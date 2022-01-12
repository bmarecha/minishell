/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 02:05:24 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/12 13:15:29 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_command(t_cmd *cmd, char ***env)
{
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->pipe = 3;
	cmd->i_red = NULL;
	cmd->o_red = NULL;
	cmd->env = env;
}
