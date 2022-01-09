/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:53:56 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/08 02:48:14 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSING_H
# define PARSING_H

#include "get_next_line.h"
#include <signal.h>

//type of redir : 1 == '<', 2 == '<<', 3 == '>>', 4 == '>'

typedef struct s_redir
{
	char	*file;
	int		type;
}				t_redir;

/*
** pipe : 0 == entree, 1 == sortie, 2 == sortie et entree, 3 == aucun des deux
** next et/ou prev sont mis a NULL dans les cas correspondants
*/

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	
	char			*name;
	char			**argv;
	int				pipe;

	t_redir			*i_red;
	t_redir			*o_red;
}					t_cmd;

int		get_next_line(int fd, char **line);

#endif