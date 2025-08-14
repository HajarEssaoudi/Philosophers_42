/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:43:05 by hes-saou          #+#    #+#             */
/*   Updated: 2025/08/14 11:51:27 by hes-saou         ###   ########.fr       */
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

struct	s_data;

typedef struct s_philosopher
{
	int				id;
	int				full;
	int				meals_eaten;
	long long		last_time_eat;
	struct s_data	*data;
	pthread_t		thread;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philosopher;

typedef struct s_data
{
	int				num_philo;
	int				someone_died;
	int				is_full;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_per_philo;
	long			start_time;
	pthread_t		death_thread;
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
void				print_action(t_philosopher *philo, const char *message);
int					handle_check(t_philosopher *philo);

/* functions to verify the input*/
int					verify_num(int ac, char **av);
int					verify_sign(int ac, char **av);
int					check_args(int ac, char **av);

/* function of the time */
long long			get_time_ms(void);
long long			get_time_now(t_data *data);

/*function of structs's initialization*/
int					init_all(t_data *data, char **av);

/*freeing fnctions*/
void				clean_up(t_data *data);

/*threads functions*/
void				create_philos(t_data *data);

/*philos's routine */
void				take_a_fork(t_philosopher *philo);
void				drop_forks(t_philosopher *philo);
void				philo_eats(t_philosopher *philo);
void				philo_sleep(t_philosopher *philo);
void				philo_think(t_philosopher *philo);
void				*check_death(void *arg);
void				*philos_routine(void *arg);

/*philo finished*/
int					philo_died(t_data *data, int i);
void				clean_up(t_data *data);
void				destroy_philos(t_data *data);
int					is_dead(t_data *data);

#endif