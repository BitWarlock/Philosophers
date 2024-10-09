/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:17:56 by mrezki            #+#    #+#             */
/*   Updated: 2024/10/09 19:42:48 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H

# define PHILOSOPHERS_BONUS_H

# include <sys/semaphore.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>
# include <sys/fcntl.h>

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
	INVALID_CHAR,
	PTHREAD
}			t_errno;

typedef struct s_agora
{
	pthread_t		ripper;
	long long		start_time;
	long long		last_meal;
	t_errno			error;
	sem_t			*print;
	sem_t			*waiter;
	sem_t			*forks;
	pid_t			*pids;
	int				num_philos;
	int				time_eat;
	int				time_die;
	int				time_sleep;
	int				num_meals;
	int				limited_meals;
	int				philos_fed;
	int				meals_count;
	int				id;
}			t_agora;

long long	get_time_in_ms(void);
long long	get_time_in_mc(void);

int			process_input(int ac, char *av[], t_agora *dining_table);
int			str_to_int(const char *str, t_errno *error);
int			init_dining_table(t_agora *dining_table);
int			philo_is_fed(t_agora *philo);

void		print_philo_action(t_agora *philo, t_action action);
void		start_monitoring(t_agora *philo, int id);
void		usleep_(long long ms, t_agora *philo);
void		dinner_table(t_agora *philo, int id);
void		start_dining(t_agora *dining_table);
void		dinner_ongoing(t_agora *philo);
void		print_error(t_errno error);

#endif // !PHILOSOPHERS_BONUS_H
