/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:42:26 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/22 16:50:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(int flag)
{
	if (flag == 1)
		ft_putstr_fd("number of arguments is incorrect\n", 2);
	if (flag == 2)
		ft_putstr_fd("the arguments should be numbers\n", 2);
	if (flag == 3)
		ft_putstr_fd("the arguments should be > 0\n", 2);
}

int main (int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (!check_args(ac, av))
	{
		clean_up(&data);
		return (1);
	}
	if (!init_infos(&data, av))
	{
		clean_up(&data);
		return (1);
	}
	if (!init_philo(&data))
	{	
		clean_up(&data);
		return (1);
	}
	if (!create_philos(&data))
	{
		clean_up(&data);
		return (1);
	}
	destroy_philos(&data, data.num_philo);
	clean_up(&data);
	return(0);
}
