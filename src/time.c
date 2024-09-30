/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:20:15 by mrezki            #+#    #+#             */
/*   Updated: 2024/09/28 22:20:17 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	get_time_in_mc(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

long long	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	usleep_(long long ms, t_philo *philo)
{
	long long	start;
	long long	end;

	start = get_time_in_mc();
	end = start + ms;
	while (1)
	{
		start = get_time_in_mc();
		if (start < 0
			|| start >= end)
			break ;
		if (philo)
			if (!dinner_ongoing(philo))
				break ;
		usleep(100);
	}
}
