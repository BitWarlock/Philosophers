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

int	main(int argc, char *argv[])
{
	t_agora	dining_table;

	if (!process_input(argc, argv, &dining_table))
		return (print_error(dining_table.error), EXIT_FAILURE);
	if (!init_dining_table(&dining_table))
		return (EXIT_FAILURE);
	start_dining(&dining_table);
	return (EXIT_SUCCESS);
}
