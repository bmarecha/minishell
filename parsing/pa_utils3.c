/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:33:10 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/29 23:54:40 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

t_cmd   *get_last_cmd(t_cmd *act)
{
    while (act->next)
        act = act->next;
    return (act);
}

void    show_error_heredoc(int s_line, char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(s_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
