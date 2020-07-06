/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 09:39:39 by nieyraud          #+#    #+#             */
/*   Updated: 2020/07/03 09:49:45 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

pthread_mutex_t mutex;

void	*ft_test(void *tmp)
{
	int oui;

	if ((oui = pthread_mutex_lock(&mutex)) == EDEADLK)
		printf("Mutex locked with EDEALK in thread : [%d]\n", *(int*)tmp);
	else
		printf("Mutex locked returned [%d] in thread : [%d]\n", oui, *(int*)tmp);
	return (NULL);
}


int		main(void)
{
	pthread_t thread_one;
	pthread_t thread_two;
	pthread_mutex_t errchkmutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER; 
	int i;
	int j;

	pthread_mutex_init(&mutex, &errchkmutex);
	i = 1;
	j = 2;
	pthread_create(&thread_one, NULL, ft_test, &i);
	pthread_create(&thread_two, NULL, ft_test, &j);
	pthread_join(thread_one, NULL);
	pthread_join(thread_two, NULL);
	return (0);
}