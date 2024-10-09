/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos_data_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:19:49 by mrezki            #+#    #+#             */
/*   Updated: 2024/10/09 19:42:09 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

static int	init_semaphores(t_agora *table, int num_philos)
{
	sem_unlink("/waiter");
	sem_unlink("/print");
	sem_unlink("/forks");
	table->forks = sem_open("/forks", O_CREAT, 0600, num_philos);
	table->print = sem_open("/print", O_CREAT, 0600, 1);
	table->waiter = sem_open("/waiter", O_CREAT, 0600, num_philos);
	if (table->waiter == SEM_FAILED
		|| table->print == SEM_FAILED
		|| table->forks == SEM_FAILED)
		return (0);
	return (1);
}

int	init_dining_table(t_agora *dining_table)
{
	int	num_philos;

	num_philos = dining_table->num_philos;
	if (!init_semaphores(dining_table, num_philos))
		return (0);
	return (1);
}
