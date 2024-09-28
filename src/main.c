/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:18:02 by mrezki            #+#    #+#             */
/*   Updated: 2024/09/15 20:18:03 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	philo_died(t_philo philo);
int	dinner_ongoing(t_philo *philo);
void	put_forks(t_philo *philo);
void	join_threads(t_philo *philos);

void	print_error(t_errno error)
{
	if (error == WRONG_USAGE)
		printf("Error: Wrong usage.\nUsage: ./philo number_of_philosophers"
			"time_to_die time_to_eat time_to_sleep number_of_meals\n");
	if (error == INVALID_CHAR)
		printf("Error: Invalid character. Only numeric input is allowed\n");
	if (error == NEGATIVE_NUM)
		printf("Error: Only positive numbers are allowed\n");
	if (error == BIG_NUM)
		printf("Error: Number exceeds INT_MAX.\n");
}

t_philo	*t_philo_array(int size)
{
	t_philo	*arr;

	arr = malloc(sizeof(t_philo) * size);
	if (!arr)
		return (NULL);
	return (arr);
}

t_mutex	*mutex_array(int size)
{
	t_mutex	*arr;

	arr = malloc(sizeof(pthread_mutex_t) * size);
	if (!arr)
		return (NULL);
	return (arr);
}

int	init_mutexes(t_mutex *forks, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_init(&forks[i].fork, NULL))
			return (0);
		forks[i].taken = 0;
		i++;
	}
	return (1);
}

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

int	init_philos_data(t_agora *dining_table)
{
	int	i;
	int	num_philos;

	i = 0;
	num_philos = dining_table->num_philos;
	dining_table->philo = t_philo_array(num_philos);
	dining_table->forks = mutex_array(num_philos);
	if (!dining_table->philo || !dining_table->forks)
		return (perror("malloc"), 0);
	if (!init_mutexes(dining_table->forks, num_philos))
		return (perror("mutex"), 0);
	while (i < dining_table->num_philos)
	{
		dining_table->philo[i].id = i;
		dining_table->philo[i].data = dining_table;
		dining_table->philo[i].last_meal = get_time_in_mc();
		dining_table->philo[i].start_time = get_time_in_ms();
		dining_table->philo[i].meals_eaten = 0;
		dining_table->philo[i].fork = &dining_table->forks[i].fork;
		i++;
	}
	return (1);
}

void	print_philo_action(t_philo *philo, t_action action)
{
	pthread_mutex_lock(&philo->data->print);
	if (dinner_ongoing(philo))
	{
		if (action == THINK)
			printf("%lld %d is thinking\n", get_time_in_ms() - philo->start_time, philo->id + 1);
		if (action == FORK)
			printf("%lld %d has taken a fork\n", get_time_in_ms() - philo->start_time, philo->id + 1);
		if (action == SLEEP)
			printf("%lld %d is sleeping\n", get_time_in_ms() - philo->start_time, philo->id + 1);
		if (action == EAT)
			printf("%lld %d is eating\n", get_time_in_ms() - philo->start_time, philo->id + 1);
	}
	else if (!dinner_ongoing(philo) && action == DIE)
		printf("%lld %d died\n", get_time_in_ms() - philo->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->print);
}

void	left_right_fork(int *left, int *right, t_philo *philo)
{
	int	tmp;

	(void)philo;
	if (*left > *right)
	{
		tmp = *left;
		*left = *right;
		*right = tmp;
	}
}

int	request_forks(t_philo *philo)
{
	int		right;
	int		left;

	right = philo->id;
	left = (philo->id + 1) % philo->data->num_philos;
	pthread_mutex_lock(&philo->data->forks[left].fork);
	philo->data->forks[left].taken = 1;
	print_philo_action(philo, FORK);
	if (!dinner_ongoing(philo) || philo->data->num_philos == 1)
		return (0);
	pthread_mutex_lock(&philo->data->forks[right].fork);
	philo->last_meal = get_time_in_mc();
	philo->data->forks[right].taken = 1;
	print_philo_action(philo, FORK);
	return (1);
}

int	dinner_ongoing(t_philo *philo)
{
	int	ongoing;

	pthread_mutex_lock(&philo->data->end);
	ongoing = !philo->data->end_dinner;
	pthread_mutex_unlock(&philo->data->end);
	return (ongoing);
}

void	usleep_(long long ms, t_philo *philo)
{
	long long	start;
	long long	end;

	start = get_time_in_mc();
	end = start + ms;
	while (1)
	{
		start = get_time_in_mc();
		if (start >= end)
			break ;
		if (philo)
			if (!dinner_ongoing(philo))
				break ;
		usleep(50);
	}
}

void	think(t_philo *philo)
{
	print_philo_action(philo, THINK);
}
void	one_philo(t_philo *philo)
{
	if (philo->data->num_philos != 1)
		return ;
	pthread_mutex_unlock(philo->fork);
	usleep_(philo->data->time_die, philo);
}
void	take_forks(t_philo *philo)
{
	if (philo->id % 2 != 0 && philo->meals_eaten == 0)
		usleep_(50, philo);
	while (!request_forks(philo) && dinner_ongoing(philo))
	{
		one_philo(philo);
		usleep_(50, philo);
	}
}

void	eat(t_philo *philo)
{
	int		right;
	int		left;

	right = philo->id;
	left = (philo->id + 1) % philo->data->num_philos;
	print_philo_action(philo, EAT);
	usleep_(philo->data->time_eat, philo);
	put_forks(philo);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->forks[left].fork);
	pthread_mutex_unlock(&philo->data->forks[right].fork);
}

void	put_forks(t_philo *philo)
{
	int		right;
	int		left;
	t_mutex	*forks;

	right = philo->id;
	left = (philo->id + 1) % philo->data->num_philos;
	pthread_mutex_lock(&philo->data->waiter);
	forks = philo->data->forks;
	forks[left].taken = 0;
	forks[right].taken = 0;
	pthread_mutex_unlock(&philo->data->waiter);
}

void	sleep_(t_philo *philo)
{
	print_philo_action(philo, SLEEP);
	usleep_(philo->data->time_sleep, philo);
}

void	*dinner_table(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (dinner_ongoing(philo))
	{
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		sleep_(philo);
		think(philo);
	}
	return (NULL);
}

int	philo_died(t_philo philo)
{
	long long	time_after_meal;
	long long	time_die;

	pthread_mutex_lock(&philo.data->end);
	time_after_meal = get_time_in_mc() - philo.last_meal;
	time_die = philo.data->time_die;
	pthread_mutex_unlock(&philo.data->end);
	if (time_after_meal >= time_die)
		return (1);
	return (0);
}

void	*monitor_check(void *arg)
{
	int		i;
	int		exit;
	t_agora	*dining_table;

	dining_table = (t_agora *)arg;
	exit = 0;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&dining_table->waiter);
		while (i < dining_table->num_philos && dinner_ongoing(dining_table->philo))
		{
			if (philo_died(dining_table->philo[i]))
			{
				dining_table->end_dinner = 1;
				print_philo_action(&dining_table->philo[i], DIE);
				exit = 1;
			}
			i++;
		}
		pthread_mutex_unlock(&dining_table->waiter);
		if (exit)
			return (NULL);
		usleep_(50, NULL);
	}
	return (NULL);
}

void	start_dining(t_agora *dining_table)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	dining_table->end_dinner = 0;
	pthread_mutex_init(&dining_table->print, NULL);
	pthread_mutex_init(&dining_table->waiter, NULL);
	pthread_mutex_init(&dining_table->end, NULL);
	while (i < dining_table->num_philos)
	{
		pthread_create(&dining_table->philo[i].philosopher, NULL, dinner_table, &dining_table->philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_check, dining_table);
	pthread_join(monitor, NULL);
	join_threads(dining_table->philo);
	pthread_mutex_destroy(&dining_table->waiter);
	pthread_mutex_destroy(&dining_table->print);
}

void	join_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->num_philos)
	{
		pthread_join(philos[i].philosopher, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_agora	dining_table;

	printf("pid %d\n", getpid());
	if (!process_input(argc, argv, &dining_table))
		return (print_error(dining_table.error), EXIT_FAILURE);
	if (!init_philos_data(&dining_table))
		return (EXIT_FAILURE);
	start_dining(&dining_table);
	return (EXIT_SUCCESS);
}
