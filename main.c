/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:42:26 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/14 12:12:25 by hes-saou         ###   ########.fr       */
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
		ft_putstr_fd("the arguments should be integers\n", 2);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_args(ac, av))
	{
		return (1);
	}
	if (!init_all(&data, av))
	{
		clean_up(&data);
		return (1);
	}
	create_philos(&data);
	destroy_philos(&data);
	return (0);
}
