/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:07:01 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/04 14:05:29 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	init_prompt(t_msh *msh)
{
	msh->prompt = "\e[0;34mmsh -> \e[0m";
	return (0);
}

int	check_exit(t_msh msh)
{
	if (ft_strncmp(msh.line, "exit", 4) == 0)
		return (0);
	return (1);
}

void signal_handler(int signal_num)
{
	printf("Received signal: %d\n", signal_num);
}

int	main(int argc, char **argv, char **old_env)
{
	t_msh	msh;

	(void)argc;
	(void)argv;
	(void)old_env;
	msh.env = init_env(old_env);
	init_history();
	// signal(SIGINT, signal_handler);
	while (1)
	{
		init_prompt(&msh);
		msh.line = readline(msh.prompt);
		msh.paths = get_paths(msh.env.tab);
		parse_line(&msh);
		parse_fd_data(&msh);
		if (msh.cmd_nbr)
			commands(&msh);
		custom_add_history(msh.line);
		free_things(msh);
		if (!check_exit(msh))
		{
			exit(1);
			free_env(msh);
		}
			// break ;
		free(msh.line);
	}
	free_env(msh);
}
