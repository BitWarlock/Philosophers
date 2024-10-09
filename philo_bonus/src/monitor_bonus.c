/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:42:15 by mrezki            #+#    #+#             */
/*   Updated: 2024/10/09 19:42:16 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

static int	philo_died(t_agora *philo)
{
	return ((get_time_in_mc() - philo->last_meal)
		>= philo->time_die);
}

int	philo_is_fed(t_agora *philo)
{
	return (philo->limited_meals
		&& philo->meals_count >= philo->num_meals);
}

void	dinner_ongoing(t_agora *philo)
{
	if (philo_died(philo))
	{
		print_philo_action(philo, DIE);
		exit(EXIT_FAILURE);
	}
}

void	*ripper_routine(t_agora *philo)
{
	while (1)
		dinner_ongoing(philo);
	return (NULL);
}

void	start_monitoring(t_agora *philo, int id)
{
	philo->id = id;
	philo->last_meal = get_time_in_mc();
	philo->start_time = get_time_in_ms();
	pthread_create(&philo->ripper, NULL, (void *)ripper_routine, philo);
	pthread_detach(philo->ripper);
}
