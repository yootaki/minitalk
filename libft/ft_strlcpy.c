/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 23:24:13 by yootaki           #+#    #+#             */
/*   Updated: 2021/05/09 22:02:41 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *string1, const char *string2, size_t size)
{
	size_t	i;
	size_t	len;

	if (string1 == NULL || string2 == NULL)
		return (0);
	len = ft_strlen(string2);
	if (size == 0)
		return (len);
	i = 0;
	while (i < size - 1 && string2[i] != '\0')
	{
		string1[i] = string2[i];
		i++;
	}
	string1[i] = '\0';
	return (len);
}
