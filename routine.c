/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:57:45 by root              #+#    #+#             */
/*   Updated: 2025/07/23 16:30:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(long long duration, t_data *data)
{
	long long	start;

	start = get_time_now(data);
	while(!data->someone_died)
	{
		if(get_time_now(data) - start >= duration)
		{
			break;
		}
		usleep(100);
	}
}

void	print_action(t_philosopher *philo, const char *message)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->someone_died)
	{
		timestamp = get_time_now(philo->data);
		printf("%lld %d %s\n", timestamp, philo->id, message);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	drop_forks(t_philosopher *philo)
{
	if (philo->left_fork_is_locked)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->left_fork_is_locked = 0;
	}
	if (philo->right_fork_is_locked)
	{
		pthread_mutex_unlock(philo->right_fork);
		philo->right_fork_is_locked = 0;
	}
}

void	take_a_fork(t_philosopher *philo)
{
	if (philo->data->someone_died)
		return;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	philo->left_fork_is_locked = 1;
	philo->right_fork_is_locked = 1;
}

void	philo_eats(t_philosopher *philo)
{
	if (philo->data->someone_died)
		return;

	pthread_mutex_lock(philo->meal_mutex);
	philo->last_time_eat = get_time_now(philo->data);
	philo->meals_eaten++;
	if (philo->data->meals_per_philo != -1 &&
		philo->meals_eaten >= philo->data->meals_per_philo)
		philo->full = 1;
	pthread_mutex_unlock(philo->meal_mutex);

	print_action(philo, "is eating");

	my_sleep(philo->data->time_to_eat, philo->data);
}

void	check_death(t_data *data)
{
	int	i;
	int	full_count;

	while (1)
	{
		full_count = 0;
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(data->philos[i].meal_mutex);
			if (get_time_now(data) - data->philos[i].last_time_eat > data->time_to_die)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->someone_died = 1;
				pthread_mutex_unlock(&data->death_mutex);

				print_action(&data->philos[i], "died");
				pthread_mutex_unlock(data->philos[i].meal_mutex);
				return;
			}
			if (data->philos[i].full)
				full_count++;
			pthread_mutex_unlock(data->philos[i].meal_mutex);
			i++;
		}
		if (data->meals_per_philo != -1 && full_count == data->num_philo)
			break;
		usleep(1000);
	}
}

void	philo_sleep(t_philosopher *philo)
{
	if (philo->data->someone_died)
		return;
    print_action(philo, "is sleeping");
	my_sleep(philo->data->time_to_sleep, philo->data);
}

void	*philos_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;

	while (1)
	{
		if (philo->data->someone_died || philo->full)
			break;
		take_a_fork(philo);
		philo_eats(philo);
		drop_forks(philo);
		philo_sleep(philo);
        print_action(philo, "is thinking");
		// philo_think(philo);
	}
	return (NULL);
}

