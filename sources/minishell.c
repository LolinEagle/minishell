/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:25:45 by frrusso           #+#    #+#             */
/*   Updated: 2022/06/06 10:09:00 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// 0 in not a builtins
// 1 is a builtins
// 2 exit
int	ft_builtins(char **line, char **envp)
{
	if (ft_is_str(line[0], "echo"))
		return (ft_echo(line));
	if (ft_is_str(line[0], "cd"))
		return (ft_cd(line, envp));
	if (ft_is_str(line[0], "pwd"))
		return (ft_pwd());
	if (ft_is_str(line[0], "export"))
		return (ft_export(line, envp));
	if (ft_is_str(line[0], "unset"))
		return (ft_unset(line, envp));
	if (ft_is_str(line[0], "env"))
		return (ft_env(envp));
	if (ft_is_str(line[0], "exit"))
		return (ft_exit());
	return (0);
}

char	**create_token_exec(char *cmd)
{
	char	**new_token_exec;

	new_token_exec = (char **)malloc(sizeof(char *) * 2);
	if (!new_token_exec)
		return (FAILURE);
	new_token_exec[0] = cmd;
	new_token_exec[1] = NULL;
	return (new_token_exec);
}

int	minishell(char *line, char **envp)
{
	int		i;
	int		in;
	char	**cmd;
	char	**token;

	cmd = ft_split(line, ';');
	if (!cmd)
		return (0);
	in = 0;
	token = NULL;
	i = -1;
	while (cmd[++i] && in != 2)
	{
		ft_free_split(token);
		token = lexer(cmd[i]);
		if (!token)
			break ;
		in = ft_builtins(token, envp);
		if (in > 0)
			continue ;
		ft_exec(envp, cmd[i], create_token_exec(cmd[i]));
	}
	ft_free_split(token);
	ft_free_split(cmd);
	return (in);
}
