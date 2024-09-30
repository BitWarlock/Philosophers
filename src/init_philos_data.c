/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:19:49 by mrezki            #+#    #+#             */
/*   Updated: 2024/09/28 22:19:50 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static t_philo	*t_philo_array(int size)
{
	t_philo	*arr;

	arr = malloc(sizeof(t_philo) * size);
	if (!arr)
		return (NULL);
	return (arr);
}

static t_mutex	*mutex_array(int size)
{
	t_mutex	*arr;

	arr = malloc(sizeof(pthread_mutex_t) * size);
	if (!arr)
		return (NULL);
	return (arr);
}

static int	init_mutexes(t_agora *dining_table, int num_philos)
{
	int		i;

	i = 0;
	dining_table->forks = malloc(sizeof(t_mutex) * num_philos);
	if (!dining_table->forks)
		return (0);
	if (pthread_mutex_init(&dining_table->print, NULL)
		|| pthread_mutex_init(&dining_table->waiter, NULL)
		|| pthread_mutex_init(&dining_table->end, NULL)
		|| pthread_mutex_init(&dining_table->meals, NULL))
		return (0);
	while (i < num_philos)
	{
		if (pthread_mutex_init(&dining_table->forks[i].fork, NULL))
			return (0);
		dining_table->forks[i].taken = 0;
		i++;
	}
	return (1);
}

static int	init_philos_data(t_agora *dining_table)
{
	int	i;

	i = 0;
	while (i < dining_table->num_philos)
	{
		dining_table->philo[i].id = i;
		dining_table->philo[i].data = dining_table;
		dining_table->philo[i].last_meal = get_time_in_mc();
		dining_table->philo[i].start_time = get_time_in_ms();
		dining_table->philo[i].meals_eaten = 0;
		dining_table->philo[i].is_full = 0;
		dining_table->philo[i].fork = &dining_table->forks[i].fork;
		if (dining_table->philo[i].last_meal < 0
			|| dining_table->philo[i].start_time < 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_dining_table(t_agora *dining_table)
{
	int	i;
	int	num_philos;

	i = 0;
	num_philos = dining_table->num_philos;
	dining_table->philo = t_philo_array(num_philos);
	dining_table->forks = mutex_array(num_philos);
	if (!dining_table->forks
		|| !dining_table->philo)
		return (perror("malloc"), 0);
	if (!dining_table->philo || !dining_table->forks)
		return (perror("malloc"), 0);
	if (!init_mutexes(dining_table, num_philos))
		return (perror("mutex"), 0);
	if (!init_philos_data(dining_table))
		return (perror("gettimeofday"), 0);
	return (1);
}
