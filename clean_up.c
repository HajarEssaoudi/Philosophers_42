/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:09:45 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/15 16:23:45 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (data->philos[i].meal_mutex)
		{
			pthread_mutex_destroy(data->philos[i].meal_mutex);
			free(data->philos[i].meal_mutex);
		}
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(data->philos[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(data->philos);
}

void	destroy_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
	}
	pthread_join(data->death_thread, NULL);
	clean_up(data);
}

int	is_full(t_data *data)
{
	int	full;

	pthread_mutex_lock(&data->full_mutex);
	full = data->is_full;
	pthread_mutex_unlock(&data->full_mutex);
	return (full);
}

void	set_full(t_data *data)
{
	pthread_mutex_lock(&data->full_mutex);
	data->is_full = 1;
	pthread_mutex_unlock(&data->full_mutex);
}

int	should_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->death_mutex);
	pthread_mutex_lock(&data->full_mutex);
	stop = (data->someone_died || data->is_full);
	pthread_mutex_unlock(&data->full_mutex);
	pthread_mutex_unlock(&data->death_mutex);
	return (stop);
}
