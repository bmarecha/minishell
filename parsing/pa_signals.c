/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 03:18:22 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/28 23:23:48 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	manage_sig(int interactive, struct sigaction *s1, struct sigaction *s2)
{
	if (interactive)
	{
		s2->sa_handler = SIG_IGN;
		sigaction(SIGINT, s1, NULL);
		sigaction(SIGQUIT, s2, NULL);
	}
	if (!interactive)
	{
		s2->sa_handler = &handle_sig_two;
		sigaction(SIGINT, s2, NULL);
		sigaction(SIGQUIT, s2, NULL);
	}
}

void	handle_sig(int sig)
{
	if (sig == SIGQUIT)
	{
		g_return = 131;
		return ;
	}
	g_return = 130;
	ft_putstr_fd("\n", 0);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sig_two(int sig)
{
	if (sig == SIGQUIT)
	{
		g_return = 131;
		ft_putstr_fd("Quit (core dumped)\n", 2);
		return ;
	}
	g_return = 130;
	ft_putstr_fd("\n", 0);
	rl_on_new_line();
	rl_replace_line("", 0);
}
