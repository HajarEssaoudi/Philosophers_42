/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_infos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:01:33 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/14 11:01:13 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_infos(t_data *data, char **av)
{
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
	data->is_full = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
	{
		ft_putstr_fd("failed to allocate\n", 2);
		return (0);
	}
	return (1);
}

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	data->philos = malloc(sizeof(t_philosopher) * data->num_philo);
	if (!data->philos)
	{
		ft_putstr_fd("allocation failed\n", 2);
		return (0);
	}
	while (++i < data->num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].full = 0;
		data->philos[i].last_time_eat = get_time_now(data);
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		if (i == data->num_philo - 1)
			data->philos[i].right_fork = &data->forks[0];
		else
			data->philos[i].right_fork = &data->forks[i + 1];
	}
	return (1);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->num_philo)
	{
		data->philos[i].meal_mutex = malloc(sizeof(pthread_mutex_t));
		if (!data->philos[i].meal_mutex)
		{
			ft_putstr_fd("failed to allocate\n", 2);
			return (0);
		}
		pthread_mutex_init(data->philos[i].meal_mutex, NULL);
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	return (1);
}

int	init_all(t_data *data, char **av)
{
	if (!init_infos(data, av))
		return (0);
	if (!init_philo(data))
		return (0);
	if (!init_mutexes(data))
		return (0);
	return (1);
}
