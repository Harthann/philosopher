/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 11:08:45 by nieyraud          #+#    #+#             */
/*   Updated: 2020/09/30 10:22:16 by nieyraud         ###   ########.fr       */
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

pthread_mutex_t *g_printing;

typedef struct		s_status
{
	int				simu_state;
	int				philo_count;
}					t_status;

/*
** tts = time to sleep;
** ttd = time to die;
** tte = time to eat;
** state : 0 = think, 1 = eat, 2 = sleep, 3 = dead, 4 = pending
** fork = 0 : fork unlock	fork = 1 : fork lock
*/


typedef struct		s_philo
{
	long			ttd;
	long			tte;
	long			tts;
	int				number;
	struct timeval	timestamp;
	t_status		*status;
	pthread_mutex_t	*mutex_left;
	pthread_mutex_t	*mutex_right;
	int				count_meal;
	struct timeval	last_meal;
	char			state;
}					t_philo;

int					ft_atoi(char *str);
void				ft_putnbr(long nb);
char				*ft_ultoa(long int n);
char				*ft_ultox(unsigned long int n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(char *str);
int					ft_count_length(long int n);

long				compare_time(struct timeval	tp, struct timeval start_t);
void				print_state(long timestamp, int number, char *str);
void				ft_free(t_philo *list);

void				create_philosopher(t_philo *philo, int number,
									char **av, t_status *status);
pthread_mutex_t		*init_mutex_table(int length);
t_philo				*init_philosopher(char **av, int ac);
int					check_validity(t_philo *list);

void				take_a_fork(t_philo *philo);
int					philosopher_eating(t_philo *philo);
int					philosopher_sleeping(t_philo *philo);
int					philosopher_thinking(t_philo *philo);
int					is_alive(t_philo *philo);
void				my_sleep(t_philo *philo);

#endif
