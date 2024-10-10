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

static char	*fun_name(t_errno error)
{
	if (error == THREAD_C)
		return ("pthread_create");
	else if (error == THREAD_D)
		return ("pthread_detach");
	else if (error == THREAD_J)
		return ("pthread_join");
	else if (error == MUTEX_L)
		return ("mutex_lock");
	else if (error == MUTEX_U)
		return ("mutex_unlock");
	else if (error == MUTEX_I)
		return ("mutex_init");
	else if (error == MUTEX_D)
		return ("mutex_destroy");
	return ("");
}

void	print_error(t_errno error)
{
	if (error == WRONG_USAGE)
		printf("\033[31mError: Wrong usage.\033[0m\n"
			"./philo number_of_philosophers"
			" time_to_die time_to_eat time_to_sleep number_of_meals.\n");
	else if (error == INVALID_CHAR)
		printf("\033[31mError: Invalid character."
			" Only numeric input is allowed.\033[0m\n");
	else if (error == NEGATIVE_NUM)
		printf("\033[31mError: Only positive "
			"non-zero integers are allowed.\033[0m\n");
	else if (error == BIG_NUM)
		printf("\033[31mError: Number exceeds INT_MAX.\033[0m\n");
	else
		printf("\033[31mError: %s function failed.\033[0m\n", fun_name(error));
}

void	print_philo_action(t_philo *philo, t_action action)
{
	pthread_mutex_lock(&philo->data->print);
	if (dinner_ongoing(philo))
	{
		if (action == THINK)
			printf("\033[40;37m%lld\033[0m\t%d\t\033[95mis thinking\033[0m\n",
				get_time_in_ms() - philo->start_time, philo->id + 1);
		if (action == FORK)
			printf("\033[40;37m%lld\033[0m\t%d\t\033[96m"
				"has taken a fork\033[0m\n",
				get_time_in_ms() - philo->start_time, philo->id + 1);
		if (action == SLEEP)
			printf("\033[40;37m%lld\033[0m\t%d\t\033[93mis sleeping\033[0m\n",
				get_time_in_ms() - philo->start_time, philo->id + 1);
		if (action == EAT)
			printf("\033[40;37m%lld\033[0m\t%d\t\033[92mis eating\033[0m\n",
				get_time_in_ms() - philo->start_time, philo->id + 1);
	}
	else if (!dinner_ongoing(philo) && action == DIE)
		printf("\033[31m%lld\t%d\tdied\033[0m\n",
			get_time_in_ms() - philo->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->print);
}
