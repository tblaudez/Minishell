/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 16:15:01 by tblaudez          #+#    #+#             */
/*   Updated: 2018/08/20 19:47:38 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	test_rights(char *file)
{
	if (access(file, F_OK) == -1)
		return (0);
	if (access(file, X_OK) == -1)
	{
		ft_fprintf(2, "minishell: permission denied: %s\n", file);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

static char	**list_to_array(void)
{
	int		i;
	char	**ret;
	t_env	*list;

	list = get_list_minishell();
	ret = ft_strarray_new(ft_lstlen((t_list*)list));
	i = 0;
	while (list && list->var_name)
	{
		ret[i] = ft_strjoinfree(list->var_name, "=", 0, 0);
		ret[i] = ft_strjoinfree(ret[i], list->content, 1, 0);
		i++;
		list = list->next;
	}
	return (ret);
}

static int	test_path(char **input)
{
	char	**path;
	char	file[PATH_MAX];

	signal(SIGINT, SIG_DFL);
	if (test_rights(*input))
		execve(*input, input, list_to_array());
	path = ft_strsplit(fetch_list_content("PATH"), ':');
	while (path && *path)
	{
		ft_strcpy(file, *path);
		if (file[ft_strlen(file) - 1] != '/')
			ft_strcat(file, "/");
		ft_strcat(file, *input);
		if (test_rights(file))
			execve(file, input, list_to_array());
		path++;
	}
	return (0);
}

void		execute_binary(char **input)
{
	pid_t	parent;

	parent = fork();
	signal(SIGINT, &sig_putendl);
	if (!parent && !test_path(input))
	{
		ft_fprintf(2, "minishell: command not found: %s\n", *input);
		exit(EXIT_SUCCESS);
	}
	wait(&parent);
}

int			main(int ac, char **av, char **envp)
{
	char	input[MAX_INPUT + 1];

	if (envp && *envp)
		create_env_list(ac, av, envp);
	while (42)
	{
		signal(SIGINT, display_prompt_msg);
		display_prompt_msg(0);
		input[read(0, input, MAX_INPUT)] = '\0';
		if (!check_input(ft_strdup(input)))
			break ;
	}
	free_list();
	return (0);
}
