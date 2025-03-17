/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_constructors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:36:50 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/17 12:02:27 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/*
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*exec_cmd(void)
{
	t_exec	*cmd;
	
	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = CMD;
	return ((t_cmd *)cmd);
}

t_cmd	*red_cmd(t_cmd *sub_cmd, char *file, char *e_file, int mode, int fd, t_token_type type)
{
	t_red	*cmd;
	
	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = type;
	cmd->r_cmd = sub_cmd;
	cmd->file = file;
	cmd->e_file = e_file;
	cmd->fd_mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}
*/