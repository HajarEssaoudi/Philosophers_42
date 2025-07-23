/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:43:05 by hes-saou          #+#    #+#             */
/*   Updated: 2025/07/22 16:45:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct s_data;

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	int				full;
	long long		last_time_eat;
	struct s_data	*data;
	pthread_t		thread;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				right_fork_is_locked;
	int				left_fork_is_locked;
}					t_philosopher;

typedef struct s_data
{
	int				num_philo;
	int				someone_died;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_per_philo;
	long			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	t_philosopher	*philos;
}					t_data;

/*utils functions*/
int					ft_isdigit(char *str);
void				print_error(int flag);
void				ft_putstr_fd(char *s, int fd);
int					ft_atoi(char *nptr);
void				my_sleep(long long duration, t_data *data);

/* functions to verify the input*/
int					verify_num(int ac, char **av);
int					verify_sign(int ac, char **av);
int					check_args(int ac, char **av);	

/* function of the time */
long long			get_time_ms(void);
long long			get_time_now(t_data *data);

/*function of structs's initialization*/
int					init_infos(t_data *data, char **av);
int				init_philo(t_data *data);

/*freeing fnctions*/
void				clean_up(t_data *data);

/*threads functions*/
int					create_philos(t_data *data);
void				destroy_philos(t_data *data, int i);

/*philos's routine */
void				take_a_fork(t_philosopher *philo);
void				drop_the_fork(t_philosopher *philo);
void				philo_eats(t_philosopher *philo);
void				philo_sleep(t_philosopher *philo);
void				philo_think(t_philosopher *philo);
void				check_death(t_data *data);
void				*philos_routine(void *arg);

/*philo finished*/

int					philo_died(t_philosopher *philo);
void				check_death(t_data *data);
void				clean_up(t_data *data);
void				destroy_philos_and_clean(t_data *data);

#endif