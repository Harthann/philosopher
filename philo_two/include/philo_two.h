/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 11:08:45 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/11 10:31:41 by nieyraud         ###   ########.fr       */
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

typedef struct		s_status
{
	int				simu_state;
	struct timeval	*last_meal;
	int				philo_count;
	int				fork_count;
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
	int				count_meal;
	struct timeval	timestamp;
	t_status		*status;
	char			state;
	sem_t			*semafork;
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
pthread_mutex_t		*init_mutex_table(int length, char **fork_table);
t_philo				*init_philosopher(char **av, int ac);
int					check_validity(t_philo *list);

void				fork_inc(sem_t *semafork, int *fork_count);
void				fork_dec(sem_t *semafork, int *fork_count, t_philo *philo);

void				take_a_fork(t_philo *philo);
int					philosopher_eating(t_philo *philo);
int					philosopher_sleeping(t_philo *philo);
int					philosopher_thinking(t_philo *philo);
int					check_meal_count(t_status status);
int					is_alive(t_philo *philo);

#endif
