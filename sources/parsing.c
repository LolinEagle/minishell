/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:08:20 by agouet            #+#    #+#             */
/*   Updated: 2022/05/25 10:16:57 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fct qui cree les "mots" en fct des espaces
// token a free
// a modifier => gerer les ; "" ''
char	**lexer(char *line)
{
	char	**token;

	token = minishell_split(line, " \t\n\v\f\r");
	if (!token)
		return (NULL);
	return (token);
}
