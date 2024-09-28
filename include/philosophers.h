/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:17:56 by mrezki            #+#    #+#             */
/*   Updated: 2024/09/15 20:17:58 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_agora	t_agora;

typedef enum
{
	THINK,
	EAT,
	SLEEP,
	FORK,
	DIE,
	PUT
}	t_action;

typedef enum s_errno
{
	WRONG_USAGE,
	NEGATIVE_NUM,
	BIG_NUM,
	INVALID_CHAR
}			t_errno;

typedef struct s_mutex
{
	int				taken;
	pthread_mutex_t	fork;
}				t_mutex;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	t_agora			*data;
	long long		last_meal;
	long long		start_time;
	pthread_t		philosopher;
	pthread_mutex_t	*fork;
}				t_philo;

typedef struct s_agora
{
	pthread_mutex_t	print;
	pthread_mutex_t	waiter;
	pthread_mutex_t	end;
	t_mutex			*forks;
	t_philo			*philo;
	t_errno			error;
	int				num_philos;
	int				time_eat;
	int				time_die;
	int				time_sleep;
	int				num_meals;
	int				limited_meals;
	int				end_dinner;
	int				philos_fed;
}				t_agora;

int	process_input(int ac, char *av[], t_agora *dining_table);
int	str_to_int(const char *str, t_errno *error);

#endif // !PHILOSOPHERS_H
