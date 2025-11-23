/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:26:39 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:26:40 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*ft_init_data(int argc, char **argv)
{
	t_data			*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->total_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->must_meals = ft_atol(argv[5]);
	else
		data->must_meals = 0;
	data->philos = NULL;
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (free(data), NULL);
	if (pthread_mutex_init(&data->stop_routine_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&data->write_mutex), free(data), NULL);
	data->stop_routines = false;
	data->start_time = ft_get_time();
	return (data);
}

static t_philo	*ft_init_philo(long i, t_data *data)
{
	t_philo	*philo_created;

	philo_created = (t_philo *)malloc(sizeof(t_philo));
	if (!philo_created)
		return (NULL);
	philo_created->philo_number = i;
	if (pthread_mutex_init(&philo_created->fork, NULL) != 0)
		return (free(philo_created), NULL);
	if (data->must_meals)
		philo_created->meals = 0;
	else
		philo_created->meals = -1;
	philo_created->is_eating = false;
	if (pthread_mutex_init(&philo_created->philo_state_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&philo_created->fork),
			free(philo_created), NULL);
	philo_created->left_philo = NULL;
	philo_created->right_philo = NULL;
	philo_created->data = data;
	return (philo_created);
}

int	ft_init_philos_data(t_data *data)
{
	long			i;
	t_philo			*top_philo;
	t_philo			*philo_created;

	i = 0;
	top_philo = NULL;
	while (++i <= data->total_philos)
	{
		philo_created = ft_init_philo(i, data);
		if (!philo_created)
			return (ft_free_philos_list(top_philo), ft_free_data(data), 1);
		if (!top_philo)
			top_philo = philo_created;
		else
		{
			ft_append_philo(philo_created, top_philo);
			ft_link_previous_philo(philo_created, top_philo);
		}
	}
	ft_linked_first_with_last_philo(top_philo);
	data->philos = top_philo;
	return (0);
}

int	ft_init_philos_routine(t_data *data)
{
	long	i;
	t_philo	*philo;

	i = 0;
	philo = data->philos;
	while (i < data->total_philos)
	{
		philo->limit_time = ft_get_time() + philo->data->time_to_die;
		if (pthread_create(&philo->thread, NULL, ft_routine, philo) != 0)
			return (ft_free_data(data), 1);
		philo = philo->right_philo;
		i++;
		usleep(100);
	}
	return (0);
}
