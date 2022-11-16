/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 23:22:57 by ffiliz            #+#    #+#             */
/*   Updated: 2021/11/19 14:31:34 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**alloc_words(char const *s, char c, char ***tab)
{
	size_t	idx;
	size_t	nb_words;

	nb_words = 0;
	idx = 0;

	while(s[idx])
	{
		while(s[idx] && s[idx] == c)
			idx++;
		if(s[idx])
			nb_words++;
		while(s[idx] && s[idx] != c)
			idx++;
	}
	*tab = malloc(sizeof(char *) * (nb_words + 1));
	return(*tab);
}

char	**free_split_error(char ***tab)
{
	int	freedx;

	if(*tab)
	{
		freedx = 0;
		while((*tab)[freedx])
			free((*tab)[freedx++]);
		free(*tab);
		*tab = (char **)NULL;
	}
	return (*tab);
}

char	**alloc_each_word(char const *s, char c, char ***tab)
{
	int widx;
	int wlen;
	int sidx;

	sidx = 0;
	widx = 0;
	while(s[sidx])
	{
		while(s[sidx] && s[sidx] == c)
			sidx++;
		wlen = 0;
		while(s[sidx] && s[sidx] != c)
		{
			sidx++;
			wlen++;
		}
		if (wlen)
		{
			(*tab)[widx] = (char*)malloc(sizeof(char) * (wlen + 1));
			if (!(*tab)[widx++])
				return (free_split_error(tab));
		}
	}
	return (*tab);
}

void	copy_words(char const *s, char c, char **tab)
{
		int widx;
	int wlen;
	int sidx;

	sidx = 0;
	widx = 0;
	while(s[sidx])
	{
		while(s[sidx] && s[sidx] == c)
			sidx++;
		wlen = 0;
		while(s[sidx] && s[sidx] != c)
			tab[widx][wlen++] = s[sidx++];
		tab[widx++][wlen] = '\0';
	}
	tab[widx] = (char *)NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	if (!alloc_words(s, c, &tab))
		return (NULL);
	if (!alloc_each_word(s, c, &tab))
		return (NULL);
	copy_words(s, c, tab);
	return (tab);
}
/*
int main(int ac, char **av)
{
	char **tab = ft_split(av[1], av[2][0]);
	size_t i = -1;
	while(tab[++i])
		printf("\nWord = %ld\n %s \n", i, tab[i]);
}*/
