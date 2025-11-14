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
	pthread_mutex_t	write_mutex;

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
	if (pthread_mutex_init(&write_mutex, NULL) != 0);
		return (ft_free_data(data), NULL);
	data->write_mutex = write_mutex;
	return (data);
}
