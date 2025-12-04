/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:19:45 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/17 16:19:46 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_check_philos_must_foods(t_data *data)
{
	long	i;
	t_philo	*philo;

	i = -1;
	philo = data->philos;
	while (++i < data->total_philos)
	{
		pthread_mutex_lock(&philo->philo_state_mutex);
		if (philo->meals < data->must_meals)
			return (pthread_mutex_unlock(&philo->philo_state_mutex), 0);
		pthread_mutex_unlock(&philo->philo_state_mutex);
		philo = philo->right_philo;
	}
	return (1);
}

static int	ft_check_anyone_is_die(t_data *data)
{
	long	i;
	t_philo	*philo;

	i = -1;
	philo = data->philos;
	while (++i < data->total_philos)
	{
		pthread_mutex_lock(&philo->philo_state_mutex);
		if (!philo->is_eating && philo->limit_time < ft_get_time())
		{
			pthread_mutex_unlock(&philo->philo_state_mutex);
			ft_display_message(DIE, philo);
			return (1);
		}
		pthread_mutex_unlock(&philo->philo_state_mutex);
		philo = philo->right_philo;
	}
	return (0);
}

void	ft_monitor(t_data *data)
{
	while (true)
	{
		if (data->must_meals)
		{
			if (ft_check_philos_must_foods(data))
			{
				pthread_mutex_lock(&data->stop_routine_mutex);
				data->stop_routines = true;
				pthread_mutex_unlock(&data->stop_routine_mutex);
				printf("All philosophers reached the must meals.\n");
				return ;
			}
		}
		if (ft_check_anyone_is_die(data))
		{
			pthread_mutex_lock(&data->stop_routine_mutex);
			data->stop_routines = true;
			pthread_mutex_unlock(&data->stop_routine_mutex);
			return ;
		}
		usleep(1000);
	}
}
