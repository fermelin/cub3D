/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 11:25:23 by fermelin          #+#    #+#             */
/*   Updated: 2020/05/24 16:35:09 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	allbytes;
	char	*str;

	i = 0;
	allbytes = nmemb * size;
	if (!(str = (char*)malloc(allbytes * sizeof(char))))
		return (NULL);
	while (i < allbytes)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
