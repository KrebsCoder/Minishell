/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:34:24 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/05/13 00:32:29 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_ms *ms)
{
	printf("\n");
	free_matrix(ms->lexer.tokens);
	free(ms->cmds.file_path);
	free(ms->prompt.special);
	ft_lstclear(ms->list, free);
	ft_free(ms);
	exit(1);
}
