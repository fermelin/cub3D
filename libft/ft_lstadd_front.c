/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 14:43:49 by fermelin          #+#    #+#             */
/*   Updated: 2020/05/23 17:15:59 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list *tmp;

	if (!lst)
		return ;
	if (!(*lst))
		(*lst) = new;
	else
	{
		tmp = (*lst);
		(*lst) = new;
		(*lst)->next = tmp;
	}
}
