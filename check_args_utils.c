/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:44:43 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/14 11:07:01 by hes-saou         ###   ########.fr       */
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
		if (ft_atoi(av[i]) < 0)
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

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

int	ft_atoi(char *nptr)
{
	char	*ptr;
	int		i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	ptr = (char *)nptr;
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == 32)
		i++;
	if (ptr[i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (ptr[i] == '+')
		i++;
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		result = result * 10 + ptr[i] - '0';
		i++;
	}
	return (sign * result);
}
