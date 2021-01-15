/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:59:36 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/15 15:11:26 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_strcpy(char *dest, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	add_numb(char *str, long nb)
{
	int		i;
	long	tmp;

	tmp = nb;
	i = 0;
	while (tmp > 9)
	{
		tmp /= 10;
		i++;
	}
	while (i)
	{
		str[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	str[i] = nb % 10 + '0';
}

void	print_state(struct timeval timestamp, int number, char *str)
{
	char			to_print[100];
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	sem_wait(g_semaprint);
	memset(to_print, 0, 100);
	add_numb(to_print, compare_time(tp, timestamp));
	to_print[ft_strlen(to_print)] = ' ';
	add_numb(to_print + ft_strlen(to_print), number);
	to_print[ft_strlen(to_print)] = ' ';
	ft_strcpy(to_print + ft_strlen(to_print), str);
	write(1, to_print, ft_strlen(to_print));
	if (ft_strcmp(str, " died\n"))
		sem_post(g_semaprint);
}
