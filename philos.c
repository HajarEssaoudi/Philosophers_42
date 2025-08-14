/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:09:06 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/14 11:18:55 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(long long duration, t_data *data)
{
	long long	start;

	start = get_time_now(data);
	while(!is_dead(data))
	{
		if(get_time_now(data) - start >= duration)
		{
			break ;
		}
		usleep(100);
	}
}

void	create_philos(t_data *data)
{
	int		i;

	i = -1;
	while(++i < data->num_philo)
	{
		pthread_create(&data->philos[i].thread, NULL, philos_routine, &data->philos[i]);
	}
	pthread_create(&data->death_thread, NULL, check_death, data);
}