/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:47:12 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/23 16:47:13 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_should_continue(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stop_routine_mutex);
	if (philo->data->stop_routines)
	{
		pthread_mutex_unlock(&philo->data->stop_routine_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->stop_routine_mutex);
	return (1);
}

int	ft_check_only_one(t_philo *philo)
{
	if (philo->data->total_philos == 1)
		return (1);
	return (0);
}

void	ft_handler_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_display_message(TAKEN_FORK, philo);
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_lock(&philo->data->stop_routine_mutex);
	philo->data->stop_routines = true;
	pthread_mutex_unlock(&philo->data->stop_routine_mutex);
}

void	ft_precise_sleep(long time_in_milliseconds, t_philo *philo)
{
	long	start;
	long	current;

	start = ft_get_time();
	while (ft_should_continue(philo))
	{
		current = ft_get_time();
		if (current - start >= time_in_milliseconds)
			break ;
		usleep(500);
	}
}

void	ft_unlock_both_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->left_philo->fork);
}
