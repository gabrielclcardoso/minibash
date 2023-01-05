/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:10:05 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/05 18:04:33 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	build_lst_cmd(t_cmd_lst **lst_cmd, char *line);
static void	initialize_ids(t_cmd_lst *lst_cmd);
static int	parse_cmds(t_cmd_lst *lst_cmd, t_var_lst *env_lst);

t_cmd_lst	*parse_input(char *line, t_var_lst *env_lst)
{
	t_cmd_lst	*lst_cmd;

	lst_cmd = NULL;
	build_lst_cmd(&lst_cmd, line);
	if (!parse_cmds(lst_cmd, env_lst))
	{
		ft_cmdclear(&lst_cmd);
		return (NULL);
	}
	return (lst_cmd);
}

static void	build_lst_cmd(t_cmd_lst **lst_cmd, char *line)
{
	char	**all_cmds;
	char	**temp;

	all_cmds = ft_split_quotes(line, '|');
	temp = all_cmds;
	while (*temp)
		ft_cmdadd_back(lst_cmd, ft_cmd_new(*temp++));
	free(all_cmds);
	initialize_ids(*lst_cmd);
}

static void	initialize_ids(t_cmd_lst *lst_cmd)
{
	int	counter;

	counter = 0;
	while (lst_cmd)
	{
		lst_cmd->id = counter++;
		lst_cmd = lst_cmd->next;
	}
}

static int	parse_cmds(t_cmd_lst *lst_cmd, t_var_lst *env_lst)
{
	while (lst_cmd)
	{
		if (whitespace_checker(lst_cmd->line))
		{
			print_syntax_error(lst_cmd, "");
			return (0);
		}
		if (!interpret_redirects(lst_cmd, lst_cmd->line))
			return (0);
		lst_cmd->args = ft_split_quotes(lst_cmd->line, ' ');
		interpret_vars(lst_cmd->args, env_lst);
		cleanup(lst_cmd->args);
		lst_cmd = lst_cmd->next;
	}
	return (1);
}
