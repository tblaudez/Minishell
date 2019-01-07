/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:39:36 by tblaudez          #+#    #+#             */
/*   Updated: 2018/08/08 15:39:50 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_list_node(void)
{
	t_env	*list;

	if (!(list = (t_env*)malloc(sizeof(t_env))))
		ft_exit("Minishell: create_list_node: malloc error.");
	list->content = NULL;
	list->var_name = NULL;
	list->next = NULL;
	return (list);
}

void	create_env_list(int ac, char **av, char **envp)
{
	t_env	*list;
	int		i;

	(void)ac;
	(void)av;
	list = get_list_minishell();
	while (*envp)
	{
		i = ft_charsrc(*envp, '=');
		list->var_name = ft_strsub(*envp, 0, i);
		list->content = ft_strdup(*envp + i + 1);
		if (*(++envp))
		{
			list->next = create_list_node();
			list = list->next;
		}
	}
}

char	*fetch_list_content(char *var_name)
{
	t_env	*list;

	list = get_list_minishell();
	while (list && !ft_strequ(list->var_name, var_name))
		list = list->next;
	return (list ? list->content : NULL);
}

void	free_list(void)
{
	t_env	*list;
	t_env	*tmp;

	list = get_list_minishell();
	while (list)
	{
		tmp = list;
		list = list->next;
		ft_strdel(&(tmp->var_name));
		ft_strdel(&(tmp->content));
		free(tmp);
	}
}

void	delete_first_node(void)
{
	t_env	*list;
	t_env	*tmp;

	list = get_list_minishell();
	if (ft_lstlen((t_list*)list) > 1)
	{
		list->var_name = list->next->var_name;
		list->content = list->next->content;
		tmp = list->next->next;
		free(list->next);
		list->next = tmp;
		return ;
	}
	list->var_name = NULL;
	list->content = NULL;
}
