/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initArgs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:49:44 by mvillavi          #+#    #+#             */
/*   Updated: 2025/06/10 10:49:45 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*ft_routine(void *argv)
{
	printf("Hello World!");
}
static uint64_t	ft_get_init_time(void)
{
	uint64_t		seconds_to_mili;
	uint64_t		micro_to_mili;
	struct	timeval time;

	gettimeofday(&time, NULL);
	seconds_to_mili = time.tv_sec * 1000;
	micro_to_mili = time.tv_usec / 1000;
	return (seconds_to_mili + micro_to_mili);
}

t_philo	*ft_init_philo(int argc, char **argv)
{
	int		i;
	int		total_philos;
	t_philo	*philo;

	i = -1;
	total_philos = ft_atouint64(argv[1]);
	philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (NULL);
	while (++i < total_philos)
	{
		philo[i].id = i + 1;
		philo[i].state = 1;
		philo[i].total_eats = 0;
		if (pthread_create(philo[i].pthread, NULL, ft_routine, NULL) != 0)
			ft_free_philo_while_init_thread(i, philo);/////
		if (pthread_mutex_init(&philo[i].fork_lock, NULL) != 0)
			ft_free_philo_while_init_mutex(i, philo);////////
	}
	return (philo);
}

t_data	*ft_init_argv(int argc, char **argv)
{
	int		total_philos;
	t_data	*data;
	t_philo	*philo;

	total_philos = ft_atouint64(argv[1]);
	data = (t_data *)malloc(sizeof(data));
	if (!data)
		return (NULL);
	data->num_philos = total_philos;
	if (argc == 6)
		data->must_eats = ft_atouint64(argv[argc -1]);
	else
		data->must_eats = 0;
	data->start_time = ft_get_init_time();
	data->time_to_die = ft_atouint64(argv[2]);
	data->time_to_eat = ft_atouint64(argv[3]);
	data->time_to_sleep = ft_atouint64(argv[4]);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (free(data), NULL);
	philo = ft_init_philo(argc, argv);
	if (!philo)
		return (pthread_mutex_destroy(&data->write_lock),free(data), NULL);
	data->philo = philo;
	return (data);
}

