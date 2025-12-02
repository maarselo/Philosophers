/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:59:44 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 19:59:45 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdbool.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <pthread.h>

# define SUCCESS 0
# define ERROR 1

# define STR 0
# define NB 1

typedef enum e_error
{
	ARGUMENTS_NUMBER,
	ARGS_NOT_NUMERIC,
	NEGATIVE_NUMBERS,
	CREATING_VARIABLES,
	//CREATING_THREADS,
}	t_error;

/*typedef enum e_state
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	ALL_MEALS,
	DIE,
}	t_state;*/

typedef struct s_data	t_data;

typedef struct s_philo
{
	long			philo_number;//
	bool			is_eating;//
	int				meals;//
	unsigned long	limit_time;
	char			*sem_name;
	sem_t			*sem_state;//
	pid_t			pid;
	pthread_t		*thread;//////
	struct s_philo	*left_philo;//////
	struct s_philo	*right_philo;/////
	t_data			*data;//
}	t_philo;

typedef struct s_data
{
	long			total_philos;//
	long			time_to_die;//
	long			time_to_eat;//
	long			time_to_sleep;//
	int				must_meals;//
	t_philo			*philos;//
	sem_t			*forks;//
	sem_t			*writer;//
	unsigned long	start_time;//
}	t_data;

//utils.c
int				ft_isspace(char c);
int				ft_isdigit(char c);
long			ft_atol(char *str);
long			ft_length_count(void *arg, int variable);
unsigned long	ft_get_time(void);

//entry.c
void			ft_valid_arguments(int argc, char **argv);

//parser_utils.c
char			*ft_get_semname(long philo_number);
void			ft_append_philo(t_philo *philo_created, t_philo *philo_list);
void			ft_link_previous_philo(t_philo *philo_created,
					t_philo *philo_list);
void			ft_linked_first_with_last_philo(t_philo *top_philo);
//parser.c
t_data			*ft_init_data(int argc, char **argv);
void			ft_init_philos_data(t_data *data);
//routine_utils.c
//routine.c

//monitor.c

//message.c
//void			ft_display_message(int message, t_philo *philo);

//free.c
void			ft_free_philo_list(t_philo *philo_list);
void			ft_free_data(t_data *data);

//error.c
void			ft_error_handler(int error);

void			ft_printf_data(t_data *data);
#endif