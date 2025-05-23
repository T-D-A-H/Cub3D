/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <ctommasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:30:46 by ctommasi          #+#    #+#             */
/*   Updated: 2025/03/13 18:35:37 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	ft_free_all(char **res, size_t i)
{
	while (i > 0)
	{
		free(res[i - 1]);
		i--;
	}
	free(res);
}

static size_t	is_del(char const *dels, char c)
{
	size_t		i;

	i = 0;
	while (dels[i])
	{
		if (dels[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_word_len(char const *s, char const *dels, size_t start)
{
	size_t	len;

	len = 0;
	while (s[start + len] && !is_del(dels, s[start + len]))
		len++;
	return (len);
}

static size_t	ft_strtoklen(char const *s, char const *dels)
{
	size_t		i;
	size_t		count;
	size_t		in_word;

	i = 0;
	in_word = 0;
	count = 0;
	while (is_del(dels, s[i]))
		i++;
	while (s[i])
	{
		if (is_del(dels, s[i]))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

char	**ft_strtok(char const *s, char const *dels)
{
	char	**res;
	size_t	i;
	size_t	j;
	size_t	k;

	i = -1;
	j = 0;
	if (ft_strtoklen(s, dels) == 0)
		return (NULL);
	res = malloc((ft_strtoklen(s, dels) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (++i < ft_strtoklen(s, dels))
	{
		while (s[j] && is_del(dels, s[j]))
			j++;
		res[i] = malloc((ft_word_len(s, dels, j) + 1) * sizeof(char));
		if (!res[i])
			return (ft_free_all(res, i), NULL);
		k = 0;
		while (s[j] && !is_del(dels, s[j]))
			res[i][k++] = s[j++];
		res[i][k] = '\0';
	}
	return (res[i] = NULL, res);
}
