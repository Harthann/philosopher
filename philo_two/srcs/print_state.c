/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:36 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/09 08:41:28 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_strcpy(char *dest, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
}

void	print_state(long timestamp, int number, char *str)
{
	char	*tmp;
	char	to_print[4080];

	memset(to_print, 0, 4080);
	tmp = ft_ultoa(timestamp);
	ft_strcpy(to_print, tmp);
	to_print[ft_strlen(to_print)] = ' ';
	free(tmp);
	tmp = ft_ultoa(number);
	ft_strcpy(to_print + ft_strlen(to_print), tmp);
	to_print[ft_strlen(to_print) + 1] = ' ';
	free(tmp);
	ft_strcpy(to_print + ft_strlen(to_print), str);
	write(1, to_print, ft_strlen(to_print));
}
