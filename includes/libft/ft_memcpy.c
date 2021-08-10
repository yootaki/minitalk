/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 22:44:01 by yootaki           #+#    #+#             */
/*   Updated: 2021/05/09 13:18:04 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *buf1, const void *buf2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (buf1 == buf2)
		return (buf1);
	str1 = (unsigned char *)buf1;
	str2 = (unsigned char *)buf2;
	i = 0;
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (buf1);
}
