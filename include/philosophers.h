/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:17:56 by mrezki            #+#    #+#             */
/*   Updated: 2024/09/28 22:20:22 by mrezki           ###   ########.fr       */
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

typedef enum s_action
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
	int				is_full;
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
	pthread_mutex_t	meals;
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
	int				philo_meal_count;
}				t_agora;

long long	get_time_in_mc(void);
long long	get_time_in_ms(void);

void		print_philo_action(t_philo *philo, t_action action);
void		limited_meals_check(t_agora *dining_table);
void		meals_count(t_agora *dining_table, int id);
void		usleep_(long long ms, t_philo *philo);
void		start_dining(t_agora *dining_table);
void		death_check(t_agora *dining_table);
void		print_error(t_errno error);
void		eat(t_philo *philo);

int			process_input(int ac, char *av[], t_agora *dining_table);
int			str_to_int(const char *str, t_errno *error);
int			init_dining_table(t_agora *dining_table);
int			dinner_ongoing(t_philo *philo);

#endif // !PHILOSOPHERS_H
