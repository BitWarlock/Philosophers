/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:20:00 by mrezki            #+#    #+#             */
/*   Updated: 2024/09/28 22:20:01 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_error(t_errno error)
{
	if (error == WRONG_USAGE)
		printf("Error: Wrong usage.\tUsage:\n./philo number_of_philosophers"
			" time_to_die time_to_eat time_to_sleep number_of_meals.\n");
	if (error == INVALID_CHAR)
		printf("Error: Invalid character. Only numeric input is allowed.\n");
	if (error == NEGATIVE_NUM)
		printf("Error: Only positive non-zero integers are allowed.\n");
	if (error == BIG_NUM)
		printf("Error: Number exceeds INT_MAX.\n");
}

void	print_philo_action(t_philo *philo, t_action action)
{
	pthread_mutex_lock(&philo->data->print);
	if (dinner_ongoing(philo))
	{
		if (action == THINK)
			printf("%lld %d is thinking\n",
				get_time_in_ms() - philo->start_time, philo->id + 1);
		if (action == FORK)
			printf("%lld %d has taken a fork\n",
				get_time_in_ms() - philo->start_time, philo->id + 1);
		if (action == SLEEP)
			printf("%lld %d is sleeping\n",
				get_time_in_ms() - philo->start_time, philo->id + 1);
		if (action == EAT)
			printf("%lld %d is eating\n",
				get_time_in_ms() - philo->start_time, philo->id + 1);
	}
	else if (!dinner_ongoing(philo) && action == DIE)
		printf("%lld %d died\n",
			get_time_in_ms() - philo->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->print);
}
