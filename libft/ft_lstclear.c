/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:25:12 by ffiliz            #+#    #+#             */
/*   Updated: 2021/11/08 21:59:26 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	tmp = *lst;
	if (lst)
	{
		if (*lst)
		{
			while (tmp)
			{
				tmp = tmp->next;
				del((*lst)->content);
				free(*lst);
				*lst = tmp;
			}
		}
	}
}
