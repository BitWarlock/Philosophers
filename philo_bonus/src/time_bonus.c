/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:20:15 by mrezki            #+#    #+#             */
/*   Updated: 2024/10/09 19:42:36 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

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

void	usleep_(long long mc, t_agora *philo)
{
	long long	start;
	long long	end;

	start = get_time_in_mc();
	end = start + mc;
	while (1)
	{
		dinner_ongoing(philo);
		start = get_time_in_mc();
		if (start < 0
			|| start >= end)
			break ;
		usleep(100);
	}
}
