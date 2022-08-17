/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:25:11 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/17 14:01:40 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_free1(char ***envp, int ret)
{
	ft_split_free(*envp);
	exit(ret);
}

void	ft_child_free2(char ***token, char ***envp, t_list *l_token, int ret)
{
	ft_split_free(*token);
	ft_split_free(*envp);
	ft_lstclear2(&l_token);
	exit(ret);
}

void	ft_child_free3(char ***token, char ***envp, t_pipe *pipex, int ret)
{
	if (pipex->l_start)
		ft_lstclear2(&pipex->l_start);
	ft_split_free(*token);
	ft_split_free(*envp);
	exit(ret);
}
