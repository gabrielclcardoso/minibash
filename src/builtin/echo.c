/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:49:26 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/27 02:26:02 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
int check_heredoc(t_cmd_lst *cmd);
int execute_heredoc(t_cmd_lst *cmd);

int echo(t_cmd_lst *cmd, t_cmd_info *data)
{
	int status;

	if (!check_heredoc(cmd))
		return (0);
	cmd->pid = fork();
	if (!cmd->pid)
	{
		int content_index;
		int trailing_newline;

		content_index = -1;
		trailing_newline = 1;
		if (!cmd->args[1])
		{
			ft_putstr_fd("\n", cmd->output);
			exit(0);
		}
		else if (!ft_strncmp(cmd->args[1], "-n", 2) && ft_strlen(cmd->args[1]) == 2)
		{
			content_index = 2;
			trailing_newline = 0;
		}
		else
			content_index = 1;
		while (cmd->args[content_index])
		{
			ft_putstr_fd(cmd->args[content_index], cmd->output);
			if (cmd->args[content_index + 1])
				write(cmd->output, " ", 1);
			content_index++;
		}
		if (trailing_newline)
			write(cmd->output, "\n", 1);
		exit(0);
	}
	// closing all my writing pipes
	if (cmd->id < (data->qty - 1))
		close(data->pipes[cmd->id][1]);
	waitpid(cmd->pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
	return (1);
}

int check_heredoc(t_cmd_lst *cmd)
{
	if (cmd->delimiter)
		if (!execute_heredoc(cmd))
			return (0);
	return (1);
}

int execute_heredoc(t_cmd_lst *cmd)
{
	int status;
	int heredoc_pid;

	heredoc_pid = fork();
	if (!heredoc_pid)
	{
		restore_sigint();
		get_heredoc_input(cmd);
		exit(0);
	}
	waitpid(heredoc_pid, &status, 0);
	if (!WIFEXITED(status))
		return (0);
	return (1);
}
