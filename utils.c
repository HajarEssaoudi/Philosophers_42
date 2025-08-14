/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:45:10 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/14 11:06:53 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long long	get_time_ms(void)
{
	struct timeval	tv;
	long long		timestamp;

	timestamp = 0;
	if (gettimeofday(&tv, NULL) == 0)
	{
		timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
	return (timestamp);
}

long long	get_time_now(t_data *data)
{
	return (get_time_ms() - data->start_time);
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
