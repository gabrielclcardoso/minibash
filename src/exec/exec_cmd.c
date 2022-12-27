/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/27 01:36:08 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_cmds(t_cmd_info *data, t_var_lst **env_lst)
{
	t_cmd_lst	*cmd;

	cmd = data->lst_cmd;
	while(cmd)
	{
		if (is_builtin(cmd->args[0]))
		{
			if (!exec_builtin_cmd(cmd, data, env_lst))
			{
				g_exit_status = 1;
				break;
			}
		}
		else
		{
			if (!exec_bin_cmd(cmd, data, *env_lst))
			{
				g_exit_status = 1;
				break;
			}
		}
		cmd = cmd->next;
	}
}
