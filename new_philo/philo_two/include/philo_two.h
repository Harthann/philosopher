/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 11:08:45 by nieyraud          #+#    #+#             */
/*   Updated: 2021/01/15 11:24:22 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

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

sem_t	*g_semaprint;
sem_t	*g_semafork;

typedef struct s_status
{
	int				simu_state;
	int				philo_count;
	int				started;
	sem_t			*semafork;
}	t_status;

/*
** tts = time to sleep;
** ttd = time to die;
** tte = time to eat;
** state : 0 = think, 1 = eat, 2 = sleep, 3 = dead, 4 = pending
** fork = 0 : fork unlock	fork = 1 : fork lock
*/

typedef struct s_philo
{
	long			ttd;
	long			tte;
	long			tts;
	int				number;
	struct timeval	timestamp;
	t_status		*status;
	int				count_meal;
	struct timeval	last_meal;
}					t_philo;

int				ft_atoi(char *str);
void			ft_putnbr(long nb);
char			*ft_ultoa(long int n);
char			*ft_ultox(unsigned long int n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(char *str);
int				ft_count_length(long int n);
void			wait_start(t_philo philo);

long			compare_time(struct timeval	tp, struct timeval start_t);
void			print_state(struct timeval timestamp, int number, char *str);
void			ft_free(t_philo *list);

void			create_philosopher(t_philo *p, int n, char **a, t_status *s);
pthread_mutex_t	*init_mutex_table(int length);
t_philo			*init_philosopher(char **av, int ac);
int				check_validity(t_philo *list);

int				take_a_fork(t_philo *philo);
void			*philosopher_loop(void *philosopher);
void			*philosopher_nurse(void *philosopher);
void			my_sleep(long time);
void	actions(t_philo *philo);

#endif
