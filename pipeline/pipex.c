/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:51:03 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/05/20 00:01:02 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipex(t_ms *ms)
{
	int	i;
	int stin;

	parse_env(ms);
	i = -1;
	while (i < ms->parser.pipes_qtn)
	{
		if (i >= 0)
		{
			stin = dup(STDIN_FILENO);
			dup42(ms->cmds.fd[0], STDIN_FILENO);
		}
		if (pipe(ms->cmds.fd) == -1)
			ft_exit(ms);
		build_cmd_table(ms);
		if (is_builtin(ms))
			exec_builtin(ms);
		else
			create_process_and_exec_cmd(ms, i);
		reset_cmd_table(ms);
		i++;
	}
	dup2(stin, STDIN_FILENO);
	end_pipeline(ms);
}
