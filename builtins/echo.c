/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrebs-l <lkrebs-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:08:19 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/06/06 23:59:51 by lkrebs-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*join_strings(char **echo);
static void	print_echo(t_ms *ms, int i);
static void	handle_exit_code(t_ms *ms, int i);

void	echo(t_ms *ms)
{
	int		has_nl;
	int		i;

	has_nl = 1;
	i = 1;
	if (!ms->cmds.command[1])
	{
		printf("\n");
		return ;
	}
	if (!ft_strncmp(ms->cmds.command[1], "$?", ft_strlen(ms->cmds.command[1])))
		handle_exit_code(ms, 1);
	else if (!ft_strncmp(ms->cmds.command[2], "$?", \
		ft_strlen(ms->cmds.command[2])))
		handle_exit_code(ms, 2);
	if (!ft_strncmp(ms->cmds.command[1], "-n", ft_strlen(ms->cmds.command[1])))
	{
		has_nl = 0;
		i = 2;
	}
	print_echo(ms, i);
	if (has_nl)
		printf("\n");
}

static void	handle_exit_code(t_ms *ms, int i)
{
	char	*aux;

	free(ms->cmds.command[i]);
	aux = ft_itoa(ms->cmds.exit_status);
	ms->cmds.command[i] = ft_strdup(aux);
	free(aux);
}

static void	print_echo(t_ms *ms, int i)
{
	char	**echo;
	char	*str;

	while (ms->cmds.command[i])
	{
		echo = ft_split(ms->cmds.command[i], ' ');
		str = join_strings(echo);
		printf("%s", str);
		free(str);
		free_matrix(echo);
		i++;
	}
}

static char	*join_strings(char **echo)
{
	char	*aux;
	char	*str;
	int		i;

	i = -1;
	while (echo[++i])
	{
		str = ft_strdup(echo[i]);
		free(echo[i]);
		aux = ft_strjoin(str, " ");
		echo[i] = ft_strdup(aux);
		free(aux);
		free(str);
	}
	i = -1;
	str = ft_strdup("");
	while (echo[++i])
	{
		aux = ft_strjoin(str, echo[i]);
		free(str);
		str = ft_strdup(aux);
		free(aux);
	}
	return (str);
}
