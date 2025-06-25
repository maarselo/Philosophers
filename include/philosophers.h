/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:11:53 by mvillavi          #+#    #+#             */
/*   Updated: 2025/06/09 11:11:54 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				state;
	int				total_eats;
	pthread_t		pthread;
	pthread_mutex_t	fork_lock;
}				t_philo;

typedef struct s_data
{
	int				num_philos;
	int				must_eats;
	int64_t		start_time;
	int64_t		time_to_die;
	int64_t		time_to_eat;
	int64_t		time_to_sleep;
	pthread_mutex_t	write_lock;
	t_philo			*philo;
}				t_data;

//Chekck entry and utils
int64_t		ft_atoint64(char *str);
int			ft_check_entry(int argc, char **argv);

//Init the struct for philo and data
t_data	*ft_init_argv(int argc, char **argv);

#endif
