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

static void	put_forks(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_unlock(&philo->data
		->forks[first_fork].fork);
	pthread_mutex_unlock(&philo->data
		->forks[second_fork].fork);
}

static int	sleep_one(t_philo *philo)
{
	usleep_(philo->data->time_die, philo);
	philo->data->end_dinner = 1;
	pthread_mutex_unlock(philo->fork);
	return (1);
}

static int	request_forks(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->data->forks[first_fork].fork);
	print_philo_action(philo, FORK);
	if (philo->data->num_philos == 1)
		sleep_one(philo);
	if (!dinner_ongoing(philo))
		return (pthread_mutex_unlock(
				&philo->data->forks[first_fork].fork), 1);
	pthread_mutex_lock(&philo->data->forks[second_fork].fork);
	philo->last_meal = get_time_in_mc();
	print_philo_action(philo, FORK);
	return (1);
}

static void	take_forks(t_philo *philo, int first, int second)
{
	pthread_mutex_lock(&philo->data->meals);
	usleep_(philo->data->num_philos, philo);
	pthread_mutex_unlock(&philo->data->meals);
	while (!request_forks(philo, first, second)
		&& dinner_ongoing(philo))
		usleep_(100, philo);
}

void	eat(t_philo *philo)
{
	int		second;
	int		first;

	if (!dinner_ongoing(philo)
		|| philo->is_full)
		return ;
	forks_priority(&first, &second,
		philo->id, philo->data->num_philos);
	take_forks(philo, first, second);
	print_philo_action(philo, EAT);
	usleep_(philo->data->time_eat, philo);
	philo->meals_eaten++;
	put_forks(philo, first, second);
}
