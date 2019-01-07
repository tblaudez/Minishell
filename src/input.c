/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:40:41 by tblaudez          #+#    #+#             */
/*   Updated: 2018/09/04 10:35:09 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_input(char *input)
{
	char	var_name[NAME_MAX];
	int		i;

	input = ft_strreplace_all(input, '~', fetch_list_content("HOME"));
	ft_bzero(var_name, NAME_MAX);
	while ((i = ft_charsrc(input, '$') + 1) >= 1)
	{
		while (input[i] && !ft_isspace(input[i]) && !ft_strchr("/;:", input[i]))
		{
			ft_strncat(var_name, input + i, 1);
			ft_strcpy(input + i, input + i + 1);
		}
		input = ft_strreplace(input, '$', fetch_list_content(var_name));
	}
	return (input);
}

int		choose_function(char *str)
{
	char	**input;

	if (!(input = ft_strsplit(str, ' ')))
		return (1);
	if (ft_strequ(input[0], "exit"))
	{
		ft_strarray_del(input);
		return (0);
	}
	else if (ft_strequ(input[0], "cd"))
		change_directory(input + 1);
	else if (ft_strequ(input[0], "env"))
		display_env();
	else if (ft_strequ(input[0], "setenv"))
		set_env(input + 1);
	else if (ft_strequ(input[0], "unsetenv"))
		unset_env(input + 1);
	else if (ft_strequ(input[0], "echo"))
		ft_echo(input + 1);
	else
		execute_binary(input);
	ft_strarray_del(input);
	return (1);
}

int		check_input(char *str)
{
	char	**cmd;
	int		i;

	if (!(*str))
	{
		ft_strdel(&str);
		ft_putchar_fd('\n', 0);
		return (1);
	}
	str = parse_input(ft_strtrim(ft_strtrimchar(str, '\"')));
	cmd = ft_strsplit(str, ';');
	ft_strdel(&str);
	i = -1;
	while (cmd && cmd[++i])
	{
		if (!choose_function(cmd[i]))
			return (0);
	}
	ft_strarray_del(cmd);
	return (1);
}
