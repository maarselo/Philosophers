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
	if (philo->data->stop_routines
		|| (philo->data->must_meals
			&& philo->data->must_meals <= philo->meals))
	{
		pthread_mutex_unlock(&philo->data->stop_routine_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->stop_routine_mutex);
	return (1);
}

void	ft_unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
}

void	ft_unlock_both_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->left_philo->fork);
}
