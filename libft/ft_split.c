/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:45:42 by jholterh          #+#    #+#             */
/*   Updated: 2024/11/26 14:49:14 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// splits string into multiple strings by using a delimitor

#include "libft.h"

static int	wordcount(char *str, char delim)
{
	int	i;
	int	word_count;
	int	flag;

	word_count = 0;
	flag = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == delim)
			flag = 1;
		else
		{
			if (flag == 1)
			{
				flag = 0;
				word_count++;
			}
		}
		i++;
	}
	return (word_count);
}

static void	ft_free(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static char	*get_next_word(const char *s, char c, int *index)
{
	int	start;

	while (s[*index] && s[*index] == c)
		(*index)++;
	start = *index;
	while (s[*index] && s[*index] != c)
		(*index)++;
	return (ft_substr(s, start, *index - start));
}

char	**ft_split(const char *s, char c)
{
	int		word_count;
	char	**str;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	word_count = wordcount((char *)s, c);
	str = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		str[j] = get_next_word(s, c, &i);
		if (!str[j])
		{
			ft_free(str);
			return (NULL);
		}
		j++;
	}
	str[j] = NULL;
	return (str);
}
