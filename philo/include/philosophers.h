/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:59:44 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 19:59:45 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define ODD "odd"
# define EVEN "even"

typedef enum e_error
{
	ARGUMENTS_NUMBER,
	ARGS_NOT_NUMERIC,
	NEGATIVE_NUMBERS,
	CREATING_VARIABLES,
	CREATING_THREADS,
}	t_error;

typedef enum e_state
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	ALL_MEALS,
	DIE,
}	t_state;

typedef struct s_data	t_data;

typedef struct s_philo
{
	long			philo_number;
	pthread_mutex_t	fork;
	int				meals;
	bool			is_eating;
	unsigned long	limit_time;
	pthread_mutex_t	philo_state_mutex;
	pthread_t		thread;
	struct s_philo	*left_philo;
	struct s_philo	*right_philo;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	long			total_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_meals;
	t_philo			*philos;
	pthread_mutex_t	write_mutex;
	bool			stop_routines;	
	pthread_mutex_t	stop_routine_mutex;
	unsigned long	start_time;
}	t_data;

//utils.c
int				ft_isspace(char c);
int				ft_isdigit(char c);
long			ft_atol(char *str);

//entry.c
int				ft_valid_arguments(int argc, char **argv);

//parser_utils.c
void			ft_append_philo(t_philo *philo_created, t_philo *philo_list);
void			ft_link_previous_philo(t_philo *philo_created,
					t_philo *philo_list);
void			ft_linked_first_with_last_philo(t_philo *top_philo);
unsigned long	ft_get_time(void);
//parser.c
t_data			*ft_init_data(int argc, char **argv);
int				ft_init_philos_data(t_data *data);
int				ft_init_philos_routine(t_data *data);

//routine_utils.c
int				ft_should_continue(t_philo *philo);
int				ft_check_only_one(t_philo *philo);
void			ft_handler_one_philo(t_philo *philo);
void			ft_unlock_both_forks(t_philo *philo);
//routine.c
void			*ft_routine(void *philo_arg);

//monitor.c
void			ft_monitor(t_data *data);
//message.c
void			ft_display_message(int message, t_philo *philo);
//free.c
void			ft_free_philos_list(t_philo *philo_list);
void			ft_free_data(t_data *data);

//error.c
int				ft_error_handler(int error);

//test
void			ft_printf_data(t_data *data);
#endif
