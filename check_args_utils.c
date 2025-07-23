/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:44:43 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/22 13:34:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verify_num(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_isdigit(av[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	verify_sign(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{                                                                                                                                                                                                                                                                                                                                                                            
		print_error(1);
		return (0);
	}
	if (!verify_num(ac, av))
	{
		print_error(2);
		return (0);
	}
	if (!verify_sign(ac, av))
	{
		print_error(3);
		return (0);
	}
	return (1);
}
