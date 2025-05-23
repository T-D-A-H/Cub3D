/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:37:49 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/20 13:41:27 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_arrlen(char **array)
{
	int	i;

	if (!array)
		return (-1);
	i = 0;
	while (array && array[i])
		i++;
	return (i);
}
