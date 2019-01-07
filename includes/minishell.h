/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 21:40:36 by tblaudez          #+#    #+#             */
/*   Updated: 2018/09/25 16:47:44 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include "libft.h"

typedef struct		s_env
{
	char			*var_name;
	char			*content;
	struct s_env	*next;
}					t_env;

void				execute_binary(char **input);

int					check_input(char *str);
int					choose_function(char *str);
char				*parse_input(char *input);

void				ft_echo(char **input);
void				set_env(char **input);
void				unset_env(char **input);
void				change_directory(char **input);
void				display_env(void);

t_env				*create_list_node(void);
void				create_env_list(int ac, char **av, char **envp);
char				*fetch_list_content(char *var_name);
void				free_list(void);
void				delete_first_node(void);

t_env				*get_list_minishell(void);
void				sig_putendl(int signo);
void				edit_env(char *s1, char *s2);
void				display_prompt_msg(int signo);

#endif
