/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 21:12:05 by tblaudez          #+#    #+#             */
/*   Updated: 2018/08/20 19:41:52 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_putendl(int signo)
{
	(void)signo;
	ft_putchar_fd('\n', 0);
}

t_env	*get_list_minishell(void)
{
	static t_env	*list = NULL;

	if (!list)
		list = create_list_node();
	return (list);
}

void	edit_env(char *s1, char *s2)
{
	const char	*tmp[] = {s1, s2, NULL};

	set_env((char**)tmp);
}

void	display_prompt_msg(int signo)
{
	char	path[PATH_MAX];
	char	*wd;

	if (signo)
		ft_putendl_fd("\b\b  ", 0);
	getcwd(path, PATH_MAX);
	wd = ft_strrchr(path, '/');
	if (!ft_strequ(path, "/"))
		wd += 1;
	ft_fprintf(0, "{yellow}->{eoc} {bold}{blue}%s{eoc} ", wd);
}
