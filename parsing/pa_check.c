/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 01:44:32 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/12 01:44:55 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	whitespace(char c)
{
	if (c == ' ' || c == '	')
	{
		return (1);
	}
	return (0);
}

int	is_pipe(char c)
{
	if (c == '|' || c == ';')
		return (1);
	return (0);
}

int	quote_check(char c, int in_quote)
{
	if (c == '\'')
	{
		if (in_quote == 1)
			return (0);
		else if (in_quote == 0)
			return (1);
	}
	if (c == '\"')
	{
		if (in_quote == 2)
			return (0);
		else if (in_quote == 0)
			return (2);
	}
}
