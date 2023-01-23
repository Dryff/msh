/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:13:34 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/23 11:45:52 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!needle[0])
		return ((char *)haystack);
	if (!len)
		return (NULL);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j])
		{
			if (needle[j + 1] == '\0')
			{
				if (j + i > len - 1)
					return (0);
				return ((char *)&haystack[i]);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_strstr(const char *str, const char *to_find)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	printf("%c", str[i + j + 1]);
	if ((!str || !to_find))
		return (0);
	if (to_find[0] == 0)
		return (0);
	while (str[i])
	{
		while (to_find[j])
		{
			if (str[i + j] != to_find[j])
				break ;
			j++;
			if (!to_find[j] && (str[i + j + 1] == ' ' || str[i + j + 1] == '=')){
				return (1);
			}
		}
		j = 0;
		i++;
	}
	return (0);
}