/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:15:20 by yootaki           #+#    #+#             */
/*   Updated: 2021/05/09 13:44:14 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int chr, size_t len)
{
	size_t			i;
	unsigned char	c;
	unsigned char	*ptr;

	c = (unsigned char)chr;
	ptr = (unsigned char *)str;
	i = 0;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (str);
}
