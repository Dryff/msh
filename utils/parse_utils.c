/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:07:58 by cgelin            #+#    #+#             */
/*   Updated: 2023/02/02 10:30:34 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	is_white_space(char c)
{
	if ((c <= 13 && c >= 9) || c == ' ')
		return (1);
	return (0);
}

int	is_delimiter(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	get_size(char *s, int i)
{
	int size;

	size = 0;
	while (s[i] && !is_delimiter(s[i++]))
		size++;
	return (size);
}
