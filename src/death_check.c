/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:19:42 by mrezki            #+#    #+#             */
/*   Updated: 2024/09/28 22:19:43 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	philo_died(t_philo *philo)
{
	long long	time_after_meal;
	int			is_dead;

	pthread_mutex_lock(&philo->data->end);
	time_after_meal = get_time_in_mc() - philo->last_meal;
	is_dead = (time_after_meal >= philo->data->time_die);
	if (is_dead)
		philo->data->end_dinner = 1;
	pthread_mutex_unlock(&philo->data->end);
	if (is_dead)
		return (1);
	return (0);
}

int	dinner_ongoing(t_philo *philo)
{
	int	ongoing;

	pthread_mutex_lock(&philo->data->end);
	ongoing = !philo->data->end_dinner
		&& !philo->data->philos_fed;
	pthread_mutex_unlock(&philo->data->end);
	return (ongoing);
}

static int	are_philos_alive(t_agora *dining_table)
{
	int	i;

	i = -1;
	while (++i < dining_table->num_philos
		&& dinner_ongoing(dining_table->philo))
	{
		meals_count(dining_table, i);
		if (philo_died(&dining_table->philo[i]))
		{
			print_philo_action(&dining_table->philo[i], DIE);
			return (0);
		}
	}
	return (dinner_ongoing(dining_table->philo));
}

static void	*death_monitor(void *arg)
{
	int		i;
	t_agora	*dining_table;

	dining_table = (t_agora *)arg;
	while (1)
	{
		i = -1;
		pthread_mutex_lock(&dining_table->waiter);
		limited_meals_check(dining_table);
		if (!are_philos_alive(dining_table))
			return (pthread_mutex_unlock(
					&dining_table->waiter), NULL);
		pthread_mutex_unlock(&dining_table->waiter);
		usleep_(50, NULL);
	}
	return (NULL);
}

void	death_check(t_agora *dining_table)
{
	pthread_t	death_th;

	pthread_create(&death_th, NULL, death_monitor, dining_table);
	pthread_detach(death_th);
}
