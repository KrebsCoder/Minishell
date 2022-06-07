/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:26:20 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/06/06 22:04:53 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_ms *ms)
{
	char	*cmd;

	cmd = ms->cmds.command[0];
	if ((cmd && !extrict_strcmp(cmd, "cd"))
		|| (cmd && !extrict_strcmp(cmd, "echo"))
		|| (cmd && !extrict_strcmp(cmd, "env"))
		|| (cmd && !extrict_strcmp(cmd, "export"))
		|| (cmd && !extrict_strcmp(cmd, "pwd"))
		|| (cmd && !extrict_strcmp(cmd, "unset")))
		return (1);
	return (0);
}
