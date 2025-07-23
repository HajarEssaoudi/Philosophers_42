/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:32:59 by root              #+#    #+#             */
/*   Updated: 2025/07/23 16:38:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_data *data)
{
	int	i;

	if (data->philos)
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (data->philos[i].meal_mutex)
			{
				pthread_mutex_destroy(data->philos[i].meal_mutex);
				free(data->philos[i].meal_mutex);
				data->philos[i].meal_mutex = NULL;
			}
			i++;
		}
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
    if (&data->print_mutex)
	    pthread_mutex_destroy(&data->print_mutex);
    if (&data->print_mutex)
	    pthread_mutex_destroy(&data->death_mutex);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}

void	destroy_philos(t_data *data, int last_created)
{
	int	i;

	i = 0;
	while (i < last_created)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
