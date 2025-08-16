/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:42:26 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/16 16:59:40 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(int flag)
{
	if (flag == 1)
		ft_putstr_fd("Error: invalid number of arguments.\n"
			"Usage: ./philo number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 2);
	if (flag == 2)
		ft_putstr_fd("Error: arguments must contain only digits.\n", 2);
	if (flag == 3)
		ft_putstr_fd("Error: arguments must be positive integers.\n", 2);
	if (flag == 4)
		ft_putstr_fd("Error: number of philosophers must not exceed 200.\n", 2);
	if (flag == 5)
		ft_putstr_fd("Error: time_to_die, time_to_eat, and time_to_sleep must be at least 60 ms.\n", 2);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_args(ac, av))
		return (1);
	if (!init_args_check(&data, av))
		return (1);
	if (!init_all(&data))
	{
		clean_up(&data);
		return (1);
	}
	create_philos(&data);
	destroy_philos(&data);
	return (0);
}
