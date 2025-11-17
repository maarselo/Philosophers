/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:59:51 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 19:59:54 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free_philos_list(t_philo *philo_list)
{
	t_philo	*philo_free;
	t_philo	*philo_next;

	if (!philo_list)
		return ;
	philo_free = philo_list;
	philo_free->left_philo->right_philo = NULL;
	while (philo_free)
	{
		philo_next = philo_free->right_philo;
		pthread_join(philo_free->thread, NULL);
		pthread_mutex_destroy(&philo_free->fork);
		philo_free->data = NULL;
		free(philo_free);
		philo_free = philo_next;
	}
}

void	ft_free_data(t_data *data)
{
	pthread_mutex_lock(&data->stop_routine_mutex);
	data->stop_routines = true;
	pthread_mutex_unlock(&data->stop_routine_mutex);
	if (data)
	{
		if (data->philos)
			ft_free_philos_list(data->philos);
		pthread_mutex_destroy(&data->write_mutex);
		free(data);
	}
}
