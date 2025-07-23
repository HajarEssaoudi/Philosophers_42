/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:07:39 by root              #+#    #+#             */
/*   Updated: 2025/07/23 16:36:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philos_routine, &data->philos[i]) != 0)
		{
			ft_putstr_fd("pthread_create failed\n", 2);
            destroy_philos(data, i);
            return (0);
		}
		i++;
	}
    return (1);
}
