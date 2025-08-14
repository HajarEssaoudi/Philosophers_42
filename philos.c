/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:09:06 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/14 12:02:42 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(long long duration, t_data *data)
{
	long long	start;

	start = get_time_now(data);
	while (!is_dead(data))
	{
		if (get_time_now(data) - start >= duration)
		{
			break ;
		}
		usleep(100);
	}
}

void	create_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		pthread_create(&data->philos[i].thread, NULL, philos_routine,
			&data->philos[i]);
	}
	pthread_create(&data->death_thread, NULL, check_death, data);
}

int	handle_check(t_philosopher *philo)
{
	if (philo->data->num_philo == 1)
	{
		printf("%lld %d has taken a fork\n", get_time_now(philo->data),
			philo->id);
		my_sleep(philo->data->time_to_die, philo->data);
		return (1);
	}
	if (philo->data->is_full || !philo->data->meals_per_philo)
		return (1);
	return (0);
}

void	*philos_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		if (handle_check(philo))
			break ;
		if (is_dead(philo->data))
			break ;
		take_a_fork(philo);
		philo_eats(philo);
		drop_forks(philo);
		if (is_dead(philo->data))
			break ;
		philo_sleep(philo);
		if (is_dead(philo->data))
			break ;
		philo_think(philo);
		if (is_dead(philo->data))
			break ;
	}
	return (NULL);
}
