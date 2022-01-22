/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:53:56 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/21 05:26:52 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define _DEFAULT_SOURCE
# include <sys/types.h>
# include <signal.h>
# include "../minishell.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// CHECK
int		ft_whitespace(char c);
int		is_pipe(char c);
int		quote_check(char c, int in_quote);
// INIT
char	**copy_env(char **env);
void	init_command(t_cmd *cmd, char ***env);
// PARSE
char	*get_word(char *str, int *len, int arg, char ***env);
void	get_pipe(char *line, int *i, t_cmd *act);
int		take_command(char *line, int *i, t_cmd *act, char ***env);
t_cmd	*get_line(char *line, char ***env);
int		read_line(char ***env);
// REDIRECTIONS
int		is_redirect(char c);
void	clean_redir(t_cmd *act);
int		wich_redirect(char *line, int *i);
t_redir	*create_redirect(char *line, int *i, int type);
void	get_redirect(char *line, int *i, t_cmd *act);
// SIGNALS
void	handle_sig(int sig);
// ENV
char	*replace_with_env(char *word, int *i, char ***env);
char	*get_env_variable(char *word, char ***env);
char	*find_env(char *nail, char **env);
// TEST
void	show_red(t_cmd *tokens);
void	show_tokens(t_cmd *tokens);
// UTILS
void	ft_putchar(char c);
void	ft_putstr(char *str);
int		calcul_arg(char *line, int i);
char	*ft_substr(char *s, int start, int len);

#endif
