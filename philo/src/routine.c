/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:38:58 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/17 11:39:01 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_take_forks(t_philo *philo)
{
	if (ft_check_only_one(philo))
		return (ft_handler_one_philo(philo), 1);
	if (philo->philo_number % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork);
		if (!ft_should_continue(philo))
			return (pthread_mutex_unlock(&philo->fork), 1);
		ft_display_message(TAKEN_FORK, philo);
		pthread_mutex_lock(&philo->left_philo->fork);
	}
	else if (philo->philo_number % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_philo->fork);
		if (!ft_should_continue(philo))
			return (pthread_mutex_unlock(&philo->left_philo->fork), 1);
		ft_display_message(TAKEN_FORK, philo);
		pthread_mutex_lock(&philo->fork);
	}
	if (!ft_should_continue(philo))
		return (ft_unlock_both_forks(philo), 1);
	ft_display_message(TAKEN_FORK, philo);
	return (0);
}

static void	ft_leave_forks(t_philo *philo)
{
	if (philo->philo_number % 2 != 0)
	{
		pthread_mutex_unlock(&philo->left_philo->fork);
		pthread_mutex_unlock(&philo->fork);
	}
	else if (philo->philo_number % 2 == 0)
	{		
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->left_philo->fork);
	}
}

static void	ft_eat(t_philo *philo)
{
	if (!ft_should_continue(philo) || ft_take_forks(philo))
		return ;
	pthread_mutex_lock(&philo->philo_state_mutex);
	philo->is_eating = true;
	philo->limit_time = ft_get_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->philo_state_mutex);
	ft_display_message(EATING, philo);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->philo_state_mutex);
	philo->is_eating = false;
	if (philo->data->must_meals)
		philo->meals++;
	pthread_mutex_unlock(&philo->philo_state_mutex);
	ft_leave_forks(philo);
}

static void	ft_sleep(t_philo *philo)
{
	if (!ft_should_continue(philo))
		return ;
	ft_display_message(SLEEPING, philo);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*ft_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	while (ft_should_continue(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		if (ft_should_continue(philo))
		{
			ft_display_message(THINKING, philo);
			usleep(500);
		}
	}
	return (NULL);
}
