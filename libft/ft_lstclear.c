/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 16:46:51 by fermelin          #+#    #+#             */
/*   Updated: 2020/05/23 19:24:48 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *tmp;

	while ((*lst))
	{
		tmp = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		(*lst) = tmp;
	}
	lst = NULL;
}
