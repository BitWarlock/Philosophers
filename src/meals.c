/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:19:56 by mrezki            #+#    #+#             */
/*   Updated: 2024/09/28 22:19:57 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	meals_count(t_agora *dining_table, int id)
{
	pthread_mutex_lock(&dining_table->meals);
	if (dining_table->limited_meals
		&& !dining_table->philo[id].is_full)
	{
		if (dining_table->philo[id].meals_eaten >= dining_table->num_meals)
		{
			dining_table->philo[id].is_full = 1;
			dining_table->philo_meal_count++;
		}
	}
	pthread_mutex_unlock(&dining_table->meals);
}

void	limited_meals_check(t_agora *dining_table)
{
	pthread_mutex_lock(&dining_table->meals);
	if (dining_table->limited_meals)
	{
		if (dining_table->philo_meal_count == dining_table->num_philos)
		{
			dining_table->end_dinner = 1;
			dining_table->philos_fed = 1;
		}
	}
	pthread_mutex_unlock(&dining_table->meals);
}

void	forks_priority(int *first, int *second, int id, int num_philos)
{
	if (id % 2 == 0)
	{
		*second = id;
		*first = (id + 1) % num_philos;
	}
	else
	{
		*first = id;
		*second = (id + 1) % num_philos;
	}
}
