/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:01 by agouet            #+#    #+#             */
/*   Updated: 2022/05/25 10:21:16 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// recup le chemin dune commande
// paths a free
char	**get_paths(char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = envp[i] + 5;
	paths = ft_split(path, ':');
	return (paths);
}

void	ft_free_pa(char **paths, char *path_cmd, char **token)
{
	if (paths)
		free(paths);
	if (path_cmd)
		free(path_cmd);
	if (token)
		free(token);
}

void	ft_child(char **paths, char *path_cmd, char **token, char **envp)
{
	pid_t	child;
	int		wstatus;

	child = fork();
	if (child < 0)
		return ;
	if (!child)
	{
		execve(path_cmd, token, envp);
		ft_free_pa(paths, path_cmd, token);
		exit(EXIT_FAILURE);
	}
	wait(&wstatus);
}

// execute une seule commande pour le moment token[0]
// access = 0 => check si une commande existe
// si exceve > 0 => n a pas marchee
void	ft_exec(char **envp, char **token)
{
	int		i;
	char	**paths;
	char	*path_cmd;

	paths = get_paths(envp);
	path_cmd = NULL;
	i = -1;
	while (paths[++i])
	{
		path_cmd = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin_free(path_cmd, token[0]);
		if (access(path_cmd, F_OK) == 0)
		{
			ft_child(paths, path_cmd, token, envp);
			break ;
		}
	}
	ft_free_pa(paths, path_cmd, token);
}
