/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:18:02 by mrezki            #+#    #+#             */
/*   Updated: 2024/09/28 22:19:53 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	cleanup(t_agora *dining_table)
{
	int	i;

	i = 0;
	while (i < dining_table->num_philos)
	{
		pthread_mutex_destroy(&dining_table->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&dining_table->print);
	pthread_mutex_destroy(&dining_table->meals);
	pthread_mutex_destroy(&dining_table->waiter);
	pthread_mutex_destroy(&dining_table->end);
	free(dining_table->forks);
	free(dining_table->philo);
}

int	main(int argc, char *argv[])
{
	t_agora	dining_table;

	if (!process_input(argc, argv, &dining_table))
		return (print_error(dining_table.error), EXIT_FAILURE);
	if (!init_dining_table(&dining_table))
		return (cleanup(&dining_table), EXIT_FAILURE);
	start_dining(&dining_table);
	cleanup(&dining_table);
	return (EXIT_SUCCESS);
}
