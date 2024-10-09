/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:41:52 by mrezki            #+#    #+#             */
/*   Updated: 2024/10/09 19:42:01 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

static void	think(t_agora *philo)
{
	print_philo_action(philo, THINK);
	usleep_(philo->num_philos, philo);
}

static void	sleep_(t_agora *philo)
{
	print_philo_action(philo, SLEEP);
	usleep_(philo->time_sleep, philo);
}

static void	take_forks(t_agora *philo)
{
	sem_wait(philo->waiter);
	sem_wait(philo->forks);
	print_philo_action(philo, FORK);
	sem_wait(philo->forks);
	print_philo_action(philo, FORK);
	sem_post(philo->waiter);
}

static void	eat(t_agora *philo)
{
	take_forks(philo);
	philo->last_meal = get_time_in_mc();
	philo->meals_count++;
	print_philo_action(philo, EAT);
	usleep_(philo->time_eat, philo);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	dinner_table(t_agora *philo, int id)
{
	start_monitoring(philo, id);
	while (!philo_is_fed(philo))
	{
		eat(philo);
		sleep_(philo);
		think(philo);
	}
	exit(EXIT_SUCCESS);
}
