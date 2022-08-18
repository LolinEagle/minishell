/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:40:53 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/18 17:47:04 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_exec(char **line, char ***envp, char **bis, t_pipe *pipex)
{
	int	ret;

	if (line[1])
		ret = chdir(line[1]);
	else
		ret = chdir(ft_get_home(*envp));
	if (ret < 0)
	{
		if (line[1] && line[1][0])
			printf("minishell: cd: %s: No such file or directory\n", line[1]);
		ft_split_free(bis);
		pipex->pipe_ret = 1;
		return (1);
	}
	return (0);
}

char	*ft_getenv(char *env, char **envp)
{
	int	i;

	if (!env)
		return (NULL);
	i = 0;
	while (envp[i] && \
	(ft_strncmp(envp[i], env, ft_strlen_equal(envp[i])) != 0))
		i++;
	if (envp[i])
		return (envp[i] + ft_strlen(env) + 1);
	return (NULL);
}
