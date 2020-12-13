/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:01:29 by oelazzou          #+#    #+#             */
/*   Updated: 2019/04/09 18:54:22 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_there(char *s, char c)
{
	if (s)
	{
		while (*s)
		{
			if (*s == c)
				return (1);
			s++;
		}
		if (c == '\0' && *s == '\0')
			return (1);
		return (0);
	}
	return (0);
}