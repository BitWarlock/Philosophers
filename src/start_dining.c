/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dining.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:20:08 by mrezki            #+#    #+#             */
/*   Updated: 2024/09/28 22:20:09 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	think(t_philo *philo)
{
	if (!dinner_ongoing(philo))
		return ;
	print_philo_action(philo, THINK);
	usleep_(philo->data->num_philos, philo);
}

static void	sleep_(t_philo *philo)
{
	if (!dinner_ongoing(philo))
		return ;
	print_philo_action(philo, SLEEP);
	usleep_(philo->data->time_sleep, philo);
}

static void	*dinner_table(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (dinner_ongoing(philo))
	{
		eat(philo);
		sleep_(philo);
		think(philo);
	}
	return (NULL);
}

static void	join_threads(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->data->num_philos)
		pthread_join(philos[i].philosopher, NULL);
}

void	start_dining(t_agora *dining_table)
{
	int			i;

	i = -1;
	dining_table->end_dinner = 0;
	while (++i < dining_table->num_philos)
		pthread_create(&dining_table->philo[i].philosopher, NULL,
			dinner_table, &dining_table->philo[i]);
	death_check(dining_table);
	join_threads(dining_table->philo);
}
