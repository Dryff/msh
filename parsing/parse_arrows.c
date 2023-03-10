/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:52:35 by colas             #+#    #+#             */
/*   Updated: 2023/03/05 18:54:10 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	get_cmd_is_before_arrow(t_msh *msh, int i)
{
	while (msh->line[i] && !is_alpha(msh->line[i]))
		i--;
	while (i >= 0 && msh->line[i] != '|')
		i--;
	i++;
	return (i);
}

int	get_cmd_is_after_arrow(t_msh *msh, int i)
{
	while (msh->line[i] && msh->line[i] != '>' && msh->line[i] != '<')
		i++;
	while (msh->line[i] && (msh->line[i] == '>' || msh->line[i] == '<'))
		i++;
	while (msh->line[i] && (is_white_space(msh->line[i])))
		i++;
	while (msh->line[i] && is_alpha(msh->line[i]))
		i++;
	while (msh->line[i] && (is_white_space(msh->line[i])))
		i++;
	return (i);
}

int	is_name_before_arrow(t_msh *msh, int i)
{
	while (msh->line[i] && msh->line[i] != '>' && msh->line[i] != '<')
	{
		if (!is_white_space(msh->line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	get_size_until_arrow(t_msh *msh, int i)
{
	while (msh->line[i] && msh->line[i] != '<' && msh->line[i] != '>')
		i++;
	return (i);
}

int	is_between_quotes(t_msh *msh, int k)
{
	int j;
	char quote;
	int count;
	int i;

	j = k;
	printf("i = %d\n", j);
	while (j >= 0)
	{
		if ((msh->line[j] == '"' || msh->line[j] == '\'') && (j == 0 || is_white_space(msh->line[j - 1])))
		{
			quote = msh->line[j];
			i = j;
			count = 0;
			while (i >= 0)
			{
				if (msh->line[i] == quote)
					count++;
				i--;
			}
			printf("count = %d\n", count);
			if (count % 2 == 1)
				return (1);
		}
		j--;
	}
	return (0);
}

int	is_redirect(t_msh *msh, int k)
{
	while (msh->line[k] && msh->line[k] != '|')
	{
		if (msh->line[k] == '<' || msh->line[k] == '>')
		{
			if (!is_between_quotes(msh, k))
				return (k);
			else
				return (-1);
		}
		k++;
	}
	return (-1);
}

int	check_fd(t_msh *msh, int i, int j)
{
	int k;

	msh->cmd[j].here_doc = 0;
	k = is_redirect(msh, i);
	printf("k = %d\n", k);
	if (k == -1)
		return (0);
	if (msh->line[k] && msh->line[k + 1] && msh->line[k] == '<' && msh->line[k + 1] == '<')
		msh->cmd[j].here_doc = 1;
	return (1);
}