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
# include <pthread.h>
# include <stdlib.h>

typedef enum e_erro
{
	ARGUMENTS_NUMBER,
	ARGS_NOT_NUMERIC,
	NEGATIVE_NUMBERS,
	CREATING_VARIABLES,
}	t_error;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				philo_number;
	pthread_t		pthread;
	pthread_mutex_t	fork;
	struct s_philo	*left_philo;
	struct s_philo	*right_philo;
	int				total_meals;
	unsigned long	last_meal;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				total_philos;//
	long			time_to_die;//
	long			time_to_eat;//
	long			time_to_sleep;//
	int				must_meals;//
	t_philo			*philos;
	pthread_mutex_t	write_mutex;//
	bool			stop_routines;
}	t_data;

//entry.c
int				ft_isspace(char c);
int				ft_isdigit(char c);
int				ft_valid_arguments(int argc, char **argv);

//parser_utils.c
long			ft_atol(char *str);
//parser.c
t_data			*ft_init_data(int argc, char **argv);
//free.c
void			ft_free_data(t_data *data);

//error.c
int				ft_error_handler(int error);

//test
void			ft_printf_data(t_data *data);
#endif
