/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 11:08:45 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/15 15:09:56 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <errno.h>
# include <string.h>

/*
** Simu state : 0 = running, 1 : ended;
*/

/*
**######################################################
**######################################################
**####				PROGRAM PARAMS					####
**####				Number of philosoph				####
**####				Time to die						####
**####				Time to eat						####
**####				Time to sleep					####
**####				Number of meal (Optional)		####
**######################################################
**######################################################
*/

pthread_mutex_t	*g_printing;

typedef struct s_status
{
	int	simu_state;
	int	philo_count;
	int	started;
}	t_status;

/*
** tts = time to sleep;
** ttd = time to die;
** tte = time to eat;
*/

typedef struct s_philo
{
	long			ttd;
	long			tte;
	long			tts;
	int				number;
	pthread_mutex_t	*mutex_left;
	pthread_mutex_t	*mutex_right;
	struct timeval	last_meal;
	int				count_meal;
	struct timeval	timestamp;
	t_status		*status;
	pthread_mutex_t	action;
}					t_philo;

int				ft_atoi(char *str);
void			ft_putnbr(long nb);
char			*ft_ultoa(long int n);
char			*ft_ultox(unsigned long int n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(char *str);
int				ft_count_length(long int n);

long			compare_time(struct timeval	tp, struct timeval start_t);
void			print_state(struct timeval timestamp, int number, char *str);
void			ft_free(t_philo *list);

void			create_philosopher(t_philo *p, int n, char **a, t_status *s);
pthread_mutex_t	*init_mutex_table(int length);
t_philo			*init_philosopher(char **av, int ac);
int				check_validity(t_philo *list);

void			*philosopher_loop(void *philosopher);
void			my_sleep(long time);
void			actions(t_philo *philo);
void			*philosopher_nurse(void *philosopher);

#endif
