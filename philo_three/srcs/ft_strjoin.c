/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:39:07 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/08 11:36:12 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen((char*)s1);
	len_s2 = ft_strlen((char*)s2);
	if (!(str = (char*)malloc(len_s1 + len_s2 + 1)))
		return (0);
	ft_memcpy(str, s1, len_s1);
	ft_memcpy(str + ft_strlen((char*)s1), s2, len_s2 + 1);
	return (str);
}
