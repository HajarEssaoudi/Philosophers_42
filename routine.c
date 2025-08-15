/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:41:30 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/15 17:02:29 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_a_fork(t_philosopher *philo)
{
	if (is_dead(philo->data))
		return ;
	if (philo->id % 2 == 0)
	{
		usleep(1000);
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "is taking a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "is taking a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "is taking a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "is taking a fork");
	}
}

void	drop_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_eats(t_philosopher *philo)
{
	if (is_dead(philo->data))
		return ;
	print_action(philo, "is eating");
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_time_eat = get_time_now(philo->data);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_mutex);
	my_sleep(philo->data->time_to_eat, philo->data);
}

void	philo_sleep(t_philosopher *philo)
{
	if (is_dead(philo->data))
		return ;
	print_action(philo, "is sleeping");
	my_sleep(philo->data->time_to_sleep, philo->data);
}

void	philo_think(t_philosopher *philo)
{
	long long	time_to_think;

	if (is_dead(philo->data))
		return ;
	print_action(philo, "is thinking");
	if (philo->data->num_philo % 2 == 0)
		return ;
	if (philo->data->time_to_eat >= philo->data->time_to_sleep)
	{
		time_to_think = philo->data->time_to_eat;
		my_sleep(time_to_think, philo->data);
	}
}
