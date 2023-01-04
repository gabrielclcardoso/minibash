/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:12:19 by gcorreia          #+#    #+#             */
/*   Updated: 2023/01/04 14:18:08 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	remove_ctrl_chars(char *cmd);

void	cleanup(char **args)
{
	while (*args)
	{
		remove_quotes(*args);
		remove_ctrl_chars(*args);
		args++;
	}
}

void	remove_quotes(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == START)
			cmd = skip_variable(cmd);
		else if (*cmd == '\'' || *cmd == '\"')
			cmd = clean_quote(cmd);
		else
			cmd++;
	}
}

char	*skip_variable(char *cmd)
{
	while (*cmd && *cmd != END)
		cmd++;
	if (*cmd == END)
		cmd++;
	return (cmd);
}

char	*clean_quote(char *cmd)
{
	char	quote;

	quote = *cmd;
	remove_chunk(cmd, 0);
	while (*cmd && *cmd != quote)
		cmd++;
	if (*cmd == quote)
		remove_chunk(cmd, 0);
	return (cmd);
}

static void	remove_ctrl_chars(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == START || *cmd == END)
			remove_chunk(cmd, 0);
		else
			cmd++;
	}
}
