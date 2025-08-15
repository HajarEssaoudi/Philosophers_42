/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:37:24 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/15 16:23:41 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_data *data, int i)
{
	long long	time_since_last_meal;

	pthread_mutex_lock(data->philos[i].meal_mutex);
	time_since_last_meal = get_time_now(data) - data->philos[i].last_time_eat;
	pthread_mutex_unlock(data->philos[i].meal_mutex);
	if (data->time_to_die <= time_since_last_meal)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d %s\n", get_time_now(data), i + 1, "died");
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

int	all_philos_full(t_data *data)
{
	int	i;
	int	full_count;

	full_count = 0;
	i = -1;
	while (++i < data->num_philo)
	{
		pthread_mutex_lock(data->philos[i].meal_mutex);
		if (data->philos[i].meals_eaten >= data->meals_per_philo)
			full_count++;
		pthread_mutex_unlock(data->philos[i].meal_mutex);
	}
	if (full_count == data->num_philo)
		return (1);
	else
		return (0);
}

void	*check_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!should_stop(data))
	{
		i = -1;
		while (++i < data->num_philo)
			if (philo_died(data, i))
				return (NULL);
		if (data->meals_per_philo != -1 && all_philos_full(data))
			set_full(data);
		usleep(100);
	}
	return (NULL);
}

int	is_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->death_mutex);
	dead = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (dead);
}
