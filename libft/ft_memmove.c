/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:11:51 by yootaki           #+#    #+#             */
/*   Updated: 2021/05/09 13:18:22 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (dest == src)
		return (dest);
	str1 = (unsigned char *)dest;
	str2 = (unsigned char *)src;
	if (str1 < str2)
		ft_memcpy(str1, str2, n);
	else if (str1 > str2)
	{
		i = n;
		while (i-- > 0)
			str1[i] = str2[i];
	}
	return (dest);
}
