/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcountchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:39:49 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/17 12:42:33 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strcountchr(const char *s, int c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == (char)c)
			count++;
		s++;
	}
	if (*s == (char)c)
		count++;
	return (count);
}
