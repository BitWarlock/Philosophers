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
	if (pthread_mutex_lock(&dining_table->meals))
		return (print_error(MUTEX_L));
	if (dining_table->limited_meals
		&& !dining_table->philo[id].is_full)
	{
		if (dining_table->philo[id].meals_eaten >= dining_table->num_meals)
		{
			dining_table->philo[id].is_full = 1;
			dining_table->philo_meal_count++;
		}
	}
	if (pthread_mutex_unlock(&dining_table->meals))
		return (print_error(MUTEX_U));
}

void	limited_meals_check(t_agora *dining_table)
{
	if (pthread_mutex_lock(&dining_table->meals))
		return (print_error(MUTEX_L));
	if (dining_table->limited_meals)
	{
		if (dining_table->philo_meal_count == dining_table->num_philos)
		{
			dining_table->end_dinner = 1;
			dining_table->philos_fed = 1;
		}
	}
	if (pthread_mutex_unlock(&dining_table->meals))
		return (print_error(MUTEX_U));
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
