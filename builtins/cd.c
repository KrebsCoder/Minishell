/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:13:41 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/05/24 23:16:32 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_pwd_and_oldpwd(t_ms *ms, char *current_pwd);

int	cd(t_ms *ms)
{
	char	*current_pwd;
	char	*aux1;
	char	*aux2;
	char	*path;
	int		return_chdir;

	path = NULL;
	if (!ms->cmds.command[1])
		path = ft_strdup(getenv("HOME"));
	else if (ms->cmds.command[1]
		&& (!ft_strncmp(ms->cmds.command[1], "~", ft_strlen(ms->cmds.command[1]))
		|| !ft_strncmp(ms->cmds.command[1], "~/", ft_strlen(ms->cmds.command[1]))))
		path = ft_strdup(getenv("HOME"));
	else if (ms->cmds.command[1] && !ft_strncmp(ms->cmds.command[1], "~/", 2))
	{
		aux1 = ft_strdup(ms->cmds.command[1]);
		aux2 = ft_strtrim(aux1, "~");
		path = ft_strjoin(getenv("HOME"), aux2);
		free(aux1);
		free(aux2);
	}
	else if (ms->cmds.command[1])
		path = ft_strdup(ms->cmds.command[1]);
	if (path)
		return_chdir = chdir(path);
	current_pwd = ft_calloc(256, sizeof(char));
	current_pwd = getcwd(current_pwd, 256);
	update_pwd_and_oldpwd(ms, current_pwd);
	free(path);
	return (return_chdir);
}

static void	update_pwd_and_oldpwd(t_ms *ms, char *current_pwd)
{
	t_list	*node;
	int		has_oldpwd;

	node = *(ms->list);
	has_oldpwd = 0;
	while (node->next != NULL)
	{
		if (!ft_strncmp(node->content, "PWD=", 4))
		{
			free(node->content);
			node->content = ft_strjoin("PWD=", current_pwd);
		}
		else if (!ft_strncmp(node->content, "OLDPWD=", 7))
		{
			free(node->content);
			node->content = ft_strjoin("OLDPWD=", ms->prompt.cwd);
			has_oldpwd = 1;
		}
		node = node->next;
		if (node->next == NULL && !ft_strncmp(node->content, "OLDPWD=", 7))
		{
			free(node->content);
			node->content = ft_strjoin("OLDPWD=", ms->prompt.cwd);
			has_oldpwd = 1;
		}
	}
	if (has_oldpwd == 0)
	{
		node = ft_lstnew(ft_strjoin("OLDPWD=", ms->prompt.cwd));
		ft_lstadd_back(ms->list, node);
	}
	free(current_pwd);
}
