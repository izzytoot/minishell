/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   60_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:34 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/08 16:02:45 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
iterar tokens todos
verificar se primeiro is builtin ou env cmd
se for ver qual is e exec
*/

#include "../../inc/minishell.h"

void	exec_single_cmd(t_minishell **msh, t_tree_node *node)
{
	t_tree_node	*cmd_node;
	
	if (node)
		cmd_node = node;
	else
		cmd_node = (*msh)->tree_root;
	if (cmd_node->type == BT_CMD)
	{
		if (ft_strcmp(cmd_node->cmd, "echo") == 0)
			ft_echo(&cmd_node);
		else if (ft_strcmp(cmd_node->cmd, "cd") == 0)
			ft_cd(msh, &cmd_node);
		else if (ft_strcmp(cmd_node->cmd, "pwd") == 0)
			print_work_dir();
		//else if (cmd_node->cmd =="export")
		//	ft_export(&(*msh));
		//else if (cmd_node->cmd == "unset")
		//	ft_unset(&(*msh));
		else if (ft_strcmp(cmd_node->cmd, "env") == 0)
			print_env(msh, &cmd_node);
		//else if (cmd_node->cmd =="exit")
		//	ft_exit(&(*msh));
	}
	else if (cmd_node->type == ENV_CMD)
		create_child_process(&(*msh), cmd_node);
}

void	create_child_process(t_minishell **msh, t_tree_node *node)
{
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed"); //change accordingly
		return ;
	}
	if (pid == 0) // not parent
	{
		if(node->type == ENV_CMD)
			exec_env_cmd(&(*msh), node);
		// if (node->type == PIPE)
			// 	exec_redir(&(*msh), node);
		// if (type_is_redir(&node->type))
		// 	exec_redir(&(*msh), node);
		exit(0); // to correct
	}
	else
		waitpid(pid, &status, 0); //wait for child
}

void	exec_env_cmd(t_minishell **msh, t_tree_node *node)
{
	char 	**envp;
	char 	**args;
	char	*env_path;
	char	*path;
	
	if (!node || !node->cmd)
	{
		ft_putstr_fd(ERR_CNOTFOUND, STDERR_FILENO);
		exit (127); //check
	}
	env_path = get_path((*msh)->envp_list);
	args = node->cmd_content;
	envp = (*msh)->envp;
	path = check_env_cmd(node->cmd, env_path, -1);
	execve(path, args, envp);
	free(envp);
	exit(1);
}


void	exec_tree(t_minishell **msh, t_tree_node *node)
{
	int	fd[2]; // fd[0]: read, fd[1]: write
	pid_t	pid;

	if (node->type == PIPE)
	{
		pipe(fd);
		
		pid = fork();
		if (pid == 0) //child process (left)
		{
			close(fd[0]); // close read end
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			exec_tree(msh, node->left);
			exit(0);
		}
		pid = fork();
		if (pid == 0) //child process (right)
		{
			close(fd[1]); // close write end
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			exec_tree(msh, node->right);
			exit(0);
		}
		close(fd[0]);
		close(fd[1]);
		wait(NULL); //??
		wait(NULL); //??
	}
	else if (type_is_redir(&node->type))
	{
		int	file_fd;
		
		file_fd = 0;
		if (node->type == REDIR_IN)
			file_fd = open(node->file, O_RDONLY);
		else if (node->type == REDIR_OUT)
			file_fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (node->type == REDIR_APP)
			file_fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file_fd < 0)
		{
			perror("open"); //check errors
			exit(1);
		}
		dup2(file_fd, node->fd);
		close(file_fd);
		exec_tree(msh, node->left);
	}
	else if (type_is_cmd(&node->type))
		exec_single_cmd(msh, node);
}
