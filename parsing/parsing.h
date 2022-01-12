/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:53:56 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/12 15:08:42 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <signal.h>
# include <sys/types.h>
# include "../minishell.h"

int		get_next_line(int fd, char **line);
// CHECK
int		whitespace(char c);
int		is_pipe(char c);
int		quote_check(char c, int in_quote);
// INIT
void	init_command(t_cmd *cmd, char ***env);
// PARSE
char	*get_word(char *str, int *len);
void	get_pipe(char *line, int *i, t_cmd *act);
int		take_command(char *line, int *i, t_cmd *act);
t_cmd	*get_line(char *line, char ***env);
int		read_line(char ***env);
// REDIRECTIONS
int		is_redirect(char c);
void	clean_redir(t_cmd *act);
int		wich_redirect(char *line, int *i);
t_redir	*create_redirect(char *line, int *i, int type);
void	get_redirect(char *line, int *i, t_cmd *act);
// TEST
void	show_red(t_cmd *tokens);
void	show_tokens(t_cmd *tokens);
// UTILS
void	ft_putchar(char c);
void	ft_putstr(char *str);
int		calcul_arg(char *line, int i);
char	*ft_substr(char *s, int start, int len);

#endif
