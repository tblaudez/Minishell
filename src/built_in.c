/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:43:12 by tblaudez          #+#    #+#             */
/*   Updated: 2018/08/08 15:43:14 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(char **input)
{
	char	tmp[PATH_MAX];

	ft_strncpy(tmp, *input, PATH_MAX);
	if (!(*input))
		ft_strncpy(tmp, fetch_list_content("HOME"), PATH_MAX);
	else if (ft_strequ(*input, "-"))
	{
		ft_strncpy(tmp, fetch_list_content("OLDPWD"), PATH_MAX);
		ft_putendl(tmp);
	}
	if (chdir(tmp) == -1)
	{
		ft_putstr_fd("cd: access denied OR no such file or directory: ", 2);
		ft_putendl_fd(*input, 2);
		return ;
	}
	getcwd(tmp, PATH_MAX);
	edit_env("OLDPWD", fetch_list_content("PWD"));
	edit_env("PWD", tmp);
}

void	display_env(void)
{
	t_env	*list;

	list = get_list_minishell();
	while (list && list->var_name)
	{
		ft_fprintf(1, "%s=%s\n", list->var_name, list->content);
		list = list->next;
	}
}

void	set_env(char **input)
{
	t_env	*list;
	t_env	*tmp;

	if (!input[0] || !input[1])
		return ;
	list = get_list_minishell();
	while (list)
	{
		if (ft_strequ(list->var_name, input[0]))
		{
			free(list->content);
			list->content = ft_strdup(input[1]);
			return ;
		}
		tmp = list;
		list = list->next;
	}
	if (tmp && tmp->var_name)
	{
		tmp->next = create_list_node();
		tmp = tmp->next;
	}
	tmp->var_name = ft_strdup(input[0]);
	tmp->content = ft_strdup(input[1]);
}

void	unset_env(char **input)
{
	t_env	*list;
	t_env	*tmp;

	list = get_list_minishell();
	while (list)
	{
		if (ft_strequ(list->var_name, input[0]))
		{
			free(list->var_name);
			free(list->content);
			if (list != get_list_minishell())
			{
				tmp->next = list->next;
				free(list);
			}
			else
				delete_first_node();
			return ;
		}
		tmp = list;
		list = list->next;
	}
}

void	ft_echo(char **input)
{
	while (*input)
	{
		ft_putstr(*input);
		ft_putchar(' ');
		input++;
	}
	ft_putchar('\n');
}
