/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:18:02 by mrezki            #+#    #+#             */
/*   Updated: 2024/10/09 19:42:13 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

static void	cleanup(t_agora *table)
{
	if (sem_close(table->waiter) < 0
		|| sem_close(table->print) < 0
		|| sem_close(table->forks) < 0
		|| sem_unlink("/waiter") < 0
		|| sem_unlink("/forks") < 0
		|| sem_unlink("/print") < 0)
		return ((void)printf("Error: sem failed\n"));
	free(table->pids);
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
