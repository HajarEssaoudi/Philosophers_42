/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:09:45 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/14 12:10:43 by hes-saou         ###   ########.fr       */
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
