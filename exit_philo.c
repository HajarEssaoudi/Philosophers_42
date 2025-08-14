/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:37:24 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/14 11:19:14 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_data *data, int i)
{
	long long	time_since_last_meal;

	pthread_mutex_lock(data->philos[i].meal_mutex);
	time_since_last_meal = get_time_now(data) - data->philos[i].last_time_eat;
	if (data->time_to_die <= time_since_last_meal)
	{
		pthread_mutex_unlock(data->philos[i].meal_mutex);
		pthread_mutex_lock(&data->death_mutex);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d %s\n", get_time_now(data), i + 1, "died");
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(data->philos[i].meal_mutex);
	return (0);
}

void	*check_death(void *arg)
{
	t_data	*data;
	int		i;
	int		full_count;

	data = (t_data *)arg;
	while (!is_dead(data) && !data->is_full)
	{
		full_count = 0;
		i = -1;
		while (++i < data->num_philo)
		{
			if (philo_died(data, i))
				return (NULL);
			if (data->meals_per_philo != -1)
			{
				pthread_mutex_lock(data->philos[i].meal_mutex);
				if (data->philos[i].meals_eaten >= data->meals_per_philo)
					full_count++;
				pthread_mutex_unlock(data->philos[i].meal_mutex);
			}
		}
		if (data->meals_per_philo != -1 && full_count == data->num_philo)
			data->is_full = 1;
		usleep(100);
	}
	return (NULL);
}

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
		// pthread_mutex_destroy(data->philos[i].right_fork);
		i++;
	}
	// pthread_mutex_destroy(data->philos[i].right_fork);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(data->philos);
}

void	destroy_philos(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->num_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
	}
	pthread_join(data->death_thread, NULL);
	clean_up(data);
}