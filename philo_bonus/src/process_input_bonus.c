/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:20:04 by mrezki            #+#    #+#             */
/*   Updated: 2024/10/09 19:42:25 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

static void	init_vars(t_agora *dining_table)
{
	dining_table->meals_count = 0;
	dining_table->id = 0;
	dining_table->limited_meals = 0;
	dining_table->time_die = 0;
	dining_table->time_eat = 0;
	dining_table->num_meals = 0;
	dining_table->time_sleep = 0;
	dining_table->num_philos = 0;
	dining_table->philos_fed = 0;
	dining_table->error = -1;
}

static int	check_opt_arg(int ac, char *av[], t_agora *dining_table)
{
	int	num_meals;

	(void)dining_table;
	if (ac != 6)
		return (0);
	num_meals = str_to_int(av[5], &dining_table->error);
	if (num_meals == -1)
		return (-1);
	dining_table->num_meals = num_meals;
	dining_table->limited_meals = 1;
	return (0);
}

static int	fill_dining_table(int ac, char *av[], t_agora *dining_table)
{
	if (check_opt_arg(ac, av, dining_table) < 0)
		return (0);
	dining_table->num_philos = str_to_int(av[1], &dining_table->error);
	dining_table->time_die = str_to_int(
			av[2], &dining_table->error) * 1000;
	dining_table->time_eat = str_to_int(
			av[3], &dining_table->error) * 1000;
	dining_table->time_sleep = str_to_int(
			av[4], &dining_table->error) * 1000;
	if ((int)dining_table->error != -1)
		return (0);
	return (1);
}

int	process_input(int ac, char *av[], t_agora *dining_table)
{
	if (ac > 6 || ac < 5)
	{
		dining_table->error = WRONG_USAGE;
		return (0);
	}
	init_vars(dining_table);
	if (!fill_dining_table(ac, av, dining_table))
		return (0);
	return (1);
}
