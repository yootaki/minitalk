/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 21:45:44 by yootaki           #+#    #+#             */
/*   Updated: 2021/04/24 11:50:50 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int ch, size_t n)
{
	size_t			i;
	unsigned char	*ans;
	unsigned char	*str;

	str = (unsigned char *)buf;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)ch)
		{
			ans = &str[i];
			return (ans);
		}
		i++;
	}
	return (NULL);
}
