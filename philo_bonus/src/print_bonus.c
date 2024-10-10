/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:20:00 by mrezki            #+#    #+#             */
/*   Updated: 2024/10/09 19:42:22 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	print_error(t_errno error)
{
	if (error == WRONG_USAGE)
		printf("\033[31mError: Wrong usage.\033[0m\n"
			"./philo number_of_philosophers"
			" time_to_die time_to_eat time_to_sleep number_of_meals.\n");
	if (error == INVALID_CHAR)
		printf("\033[31mError: Invalid character."
			" Only numeric input is allowed.\033[0m\n");
	if (error == NEGATIVE_NUM)
		printf("\033[31mError: Only positive "
			"non-zero integers are allowed.\033[0m\n");
	if (error == BIG_NUM)
		printf("\033[31mError: Number exceeds INT_MAX.\033[0m\n");
	if (error == PTHREAD)
		printf("\033[31mError: pthread function failed.\033[0m\n");
}

void	print_philo_action(t_agora *philo, t_action action)
{
	sem_wait(philo->print);
	if (action == THINK)
		printf("\033[40;37m%lld\033[0m\t%d\t\033[95mis thinking\033[0m\n",
			get_time_in_ms() - philo->start_time, philo->id + 1);
	if (action == FORK)
		printf("\033[40;37m%lld\033[0m\t%d\t\033[96mhas taken a fork\033[0m\n",
			get_time_in_ms() - philo->start_time, philo->id + 1);
	if (action == SLEEP)
		printf("\033[40;37m%lld\033[0m\t%d\t\033[93mis sleeping\033[0m\n",
			get_time_in_ms() - philo->start_time, philo->id + 1);
	if (action == EAT)
		printf("\033[40;37m%lld\033[0m\t%d\t\033[92mis eating\033[0m\n",
			get_time_in_ms() - philo->start_time, philo->id + 1);
	if (action == DIE)
		printf("\033[31m%lld\t%d\tdied\033[0m\n",
			get_time_in_ms() - philo->start_time, philo->id + 1);
	if (action != DIE)
		sem_post(philo->print);
}
