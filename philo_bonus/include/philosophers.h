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
# include <sys/time.h>

//# define ODD "odd"
//# define EVEN "even"

typedef enum e_error
{
	ARGUMENTS_NUMBER,
	ARGS_NOT_NUMERIC,
	NEGATIVE_NUMBERS,
	CREATING_VARIABLES,
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
	int				meals;
	bool			is_eating;
	unsigned long	limit_time;
	//pthread_mutex_t	philo_state_mutex;
	pid_t			pid;
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
	//pthread_mutex_t	write_mutex;
	bool			stop_routines;
	pthread_mutex_t	stop_routine_mutex;
	unsigned long	start_time;
}	t_data;

//utils.c
int				ft_isspace(char c);
int				ft_isdigit(char c);
long			ft_atol(char *str);
unsigned long	ft_get_time(void);

//entry.c
int				ft_valid_arguments(int argc, char **argv);

//parser_utils.c
//parser.c


//routine_utils.c
//routine.c

//monitor.c

//message.c
//void			ft_display_message(int message, t_philo *philo);
//free.c

//error.c
int				ft_error_handler(int error);

#endif