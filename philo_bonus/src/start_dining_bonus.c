/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dining_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:20:08 by mrezki            #+#    #+#             */
/*   Updated: 2024/10/09 19:42:29 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

static void	wait_for_philos(t_agora *table)
{
	int	status;
	int	i;

	i = -1;
	while (1)
	{
		if (waitpid(-1, &status, 0) < 0)
			break ;
		if (WIFEXITED(status)
			&& WEXITSTATUS(status) == EXIT_FAILURE)
		{
			while (++i < table->num_philos)
				kill(table->pids[i], SIGTERM);
			break ;
		}
	}
}

void	start_dining(t_agora *table)
{
	int			i;
	int			status;

	i = 0;
	table->pids = malloc(sizeof(pid_t) * table->num_philos);
	if (!table->pids)
		return ((void)printf("Error: malloc failed\n"));
	while (i < table->num_philos)
	{
		table->pids[i] = fork();
		if (table->pids[i] < 0)
			return ((void)printf("Error: fork failed\n"));
		if (table->pids[i] == 0)
			dinner_table(table, i);
		i++;
	}
	wait_for_philos(table);
}
