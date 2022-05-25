/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:14:21 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/25 10:21:20 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_msg(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	return (FAILURE);
}

int	ft_is_exit(char *line)
{
	int		i;
	char	*exit;

	if (ft_strlen(line) != 4)
		return (0);
	exit = "exit";
	i = 0;
	while (exit[i] && line[i] == exit[i])
		i++;
	if (!exit[i] && !line[i])
	{
		free(line);
		return (1);
	}
	return (0);
}

void	ft_new_prompt(int signum)
{
	if (signum == SIGINT)
	{
		ft_msg("\b\b  \n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
		ft_msg("\b\b  \b\b", 1);
}

int	check_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (ft_msg("Error: path not found\n", 2));
	return (SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	char	**token;
	char	*line;

	(void)av;
	if (!check_env(envp))
		return (1);
	if (ac != 1)
		return (ft_msg("Usage : ./minishell\n", 1));
	signal(SIGINT, ft_new_prompt);
	signal(SIGQUIT, ft_new_prompt);
	line = readline("minishell> ");
	while (line != NULL)
	{
		add_history (line);
		if (ft_is_exit(line))
			break ;
		minishell(line, envp);
		token = lexer(line);
		ft_exec(envp, token);
		free(line);
		line = readline("minishell> ");
	}
	rl_clear_history();
	return (ft_msg("\n", 1));
}
