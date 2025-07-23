/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:04:30 by root              #+#    #+#             */
/*   Updated: 2025/07/22 15:59:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_infos(t_data *data, char **av)
{
	int i;

	data->start_time = get_time_ms();
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->meals_per_philo = ft_atoi(av[5]);
	else
		data->meals_per_philo = -1;

	data->someone_died = 0;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0
		|| pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		ft_putstr_fd("Mutex failed\n", 2);
		return (0);
	}

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
	{
		ft_putstr_fd("Failed to allocate forks\n", 2);
		return (0);
	}

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			ft_putstr_fd("Mutex failed\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int init_philo(t_data *data)
{
	int i;

	data->philos = malloc(sizeof(t_philosopher) * data->num_philo);
	if (!data->philos)
	{
		ft_putstr_fd("Allocation failed\n", 2);
		return (0);
	}
	i = 0;
	while (i < data->num_philo)
	{
		t_philosopher *philo = &data->philos[i];

		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->full = 0;
		philo->right_fork_is_locked = 0;
		philo->left_fork_is_locked = 0;
		philo->last_time_eat = data->start_time;
		philo->data = data;

		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[(i + 1) % data->num_philo];
		philo->meal_mutex = malloc(sizeof(pthread_mutex_t));
		if (!philo->meal_mutex)
		{
			ft_putstr_fd("Allocation failed\n", 2);
			return (0);
		}

		if (pthread_mutex_init(philo->meal_mutex, NULL) != 0)
		{
			ft_putstr_fd("Mutex failed\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
