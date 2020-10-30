/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 14:29:06 by fermelin          #+#    #+#             */
/*   Updated: 2020/05/24 16:44:12 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newelem;

	if (!(newelem = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	newelem->content = content;
	newelem->next = NULL;
	return (newelem);
}
