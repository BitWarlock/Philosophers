/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:19:46 by mrezki            #+#    #+#             */
/*   Updated: 2024/09/28 22:19:46 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	put_forks(t_philo *philo)
{
	int		right;
	int		left;

	right = philo->id;
	left = (philo->id + 1) % philo->data->num_philos;
	pthread_mutex_unlock(&philo->data->forks[left].fork);
	pthread_mutex_unlock(&philo->data->forks[right].fork);
}

static int	sleep_one(t_philo *philo)
{
	usleep_(philo->data->time_die, philo);
	philo->data->end_dinner = 1;
	pthread_mutex_unlock(philo->fork);
	return (1);
}

static int	request_forks(t_philo *philo)
{
	int		right;
	int		left;

	if (philo->id %2 == 0)
	{
		right = philo->id;
		left = (philo->id + 1) % philo->data->num_philos;
	}
	else
	{
		left = philo->id;
		right = (philo->id + 1) % philo->data->num_philos;
	}
	pthread_mutex_lock(&philo->data->forks[left].fork);
	print_philo_action(philo, FORK);
	if (philo->data->num_philos == 1)
		sleep_one(philo);
	if (!dinner_ongoing(philo))
		return (1);
	pthread_mutex_lock(&philo->data->forks[right].fork);
	philo->last_meal = get_time_in_mc();
	print_philo_action(philo, FORK);
	return (1);
}

static void	take_forks(t_philo *philo)
{
	/*if (philo->id % 2 != 0 && philo->meals_eaten == 0)*/
	/*	usleep_(50, philo);*/
	while (!request_forks(philo) && dinner_ongoing(philo))
		usleep_(50, philo);
}

void	eat(t_philo *philo)
{
	if (!dinner_ongoing(philo)
		|| philo->is_full)
		return ;
	take_forks(philo);
	print_philo_action(philo, EAT);
	usleep_(philo->data->time_eat, philo);
	philo->meals_eaten++;
	put_forks(philo);
}
