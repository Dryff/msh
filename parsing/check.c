/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:37:28 by colas             #+#    #+#             */
/*   Updated: 2023/02/23 10:56:09 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	check_param(t_msh *msh, char *param)
{
	char	*pathing;
	char	*slashed;
	int		i;

	if (param == NULL)
		return (ft_err_printf("msh: permission denied:\n"), 2);
	i = 0;
	while (msh->paths[i])
	{
		slashed = ft_strjoin(msh->paths[i], "/");
		pathing = ft_strjoin(slashed, param);
		free(slashed);
		if (access(pathing, F_OK) == 0)
			return (free(pathing), 0);
		free(pathing);
		i++;
	}
	return (1);
}

void	check_input(t_msh *msh)
{
	if (msh->fildes.input == 1)
		msh->fildes.infd = open(msh->fildes.in_name, O_RDONLY);
	if (msh->fildes.infd == -1)
	{
		if (access(msh->fildes.in_name, F_OK) == 0)
			ft_err_printf("msh: permission denied: %s\n", \
			msh->fildes.in_name);
		else
			ft_err_printf("msh: no such file or directory: %s\n", \
			msh->fildes.in_name);
		return ;
	}
}

void	check_output(t_msh *msh)
{
	if (msh->fildes.output == 1)
		msh->fildes.outfd = open(msh->fildes.out_name, \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (msh->fildes.output == 2)
		msh->fildes.outfd = open(msh->fildes.out_name, \
		O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (msh->fildes.outfd == -1)
	{
		ft_err_printf("msh: permission denied: %s\n", msh->fildes.out_name);
		return ;
	}
}

int	check_hub(t_msh *msh)
{
	check_input(msh);
	check_output(msh);
	return (1);
}
