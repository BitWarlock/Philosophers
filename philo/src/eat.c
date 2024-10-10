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
	if (pthread_mutex_unlock(&philo->data
			->forks[first_fork].fork)
		|| pthread_mutex_unlock(&philo->data
			->forks[second_fork].fork))
		return (print_error(MUTEX_U));
}

static int	sleep_one(t_philo *philo)
{
	usleep_(philo->data->time_die, philo);
	philo->data->end_dinner = 1;
	if (pthread_mutex_unlock(philo->fork))
		return (print_error(MUTEX_U), 1);
	return (1);
}

static int	request_forks(t_philo *philo, int first_fork, int second_fork)
{
	if (pthread_mutex_lock(&philo->data->forks[first_fork].fork))
		return (print_error(MUTEX_L), 1);
	print_philo_action(philo, FORK);
	if (philo->data->num_philos == 1)
		sleep_one(philo);
	if (!dinner_ongoing(philo))
		return (pthread_mutex_unlock(
				&philo->data->forks[first_fork].fork), 1);
	if (pthread_mutex_lock(&philo->data->forks[second_fork].fork))
		return (print_error(MUTEX_L), 1);
	philo->last_meal = get_time_in_mc();
	print_philo_action(philo, FORK);
	return (1);
}

static void	take_forks(t_philo *philo, int first, int second)
{
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
	if (pthread_mutex_lock(&philo->data->waiter))
		return (print_error(MUTEX_L));
	if (philo->id % 2 == 0)
		usleep_(philo->data->time_eat / 2000, philo);
	forks_priority(&first, &second,
		philo->id, philo->data->num_philos);
	if (pthread_mutex_unlock(&philo->data->waiter))
		return (print_error(MUTEX_U));
	take_forks(philo, first, second);
	print_philo_action(philo, EAT);
	usleep_(philo->data->time_eat, philo);
	philo->meals_eaten++;
	put_forks(philo, first, second);
}
