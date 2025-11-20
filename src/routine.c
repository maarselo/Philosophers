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
//idk how ll start at the same ttie, and if all ihave to create variable 
//to starttime, the last meat is created with the same value
//pensar si crear otro proceso que monitorize si alguien llego a cmidas definitivas

//sleep pude fallar

int	ft_check_whether_continue(t_philo *philo)
{
	if (philo->data->stop_routines || (philo->data->must_meals
			&& philo->data->must_meals <= philo->meals))
		return (0);
	return (1);
}

static void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_philo->fork);
	ft_display_message(TAKEN_FORK, philo);
	pthread_mutex_lock(&philo->fork);
	ft_display_message(TAKEN_FORK, philo);
}

static void	ft_leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_philo->fork);
	pthread_mutex_unlock(&philo->fork);
}

static void	ft_eat(t_philo *philo)
{
	if (!ft_check_whether_continue(philo))
		return ;
	ft_take_forks(philo);
	philo->is_eating = true;
	ft_display_message(EATING, philo);
	usleep(philo->data->time_to_die * 1000);
	philo->limit_time = ft_get_time() + philo->data->time_to_die;
	philo->is_eating = false;
	if (philo->data->must_meals)
		philo->meals++;
	ft_leave_forks(philo);
}

static void	ft_sleep(t_philo *philo)
{
	if (!ft_check_whether_continue(philo))
		return ;
	ft_display_message(SLEEPING, philo);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*ft_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	while (!philo->data->stop_routines
			|| (philo->data->must_meals != 0
			&& philo->data->must_meals > philo->meals))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_display_message(THINKING, philo);
	}
	return (NULL);
}
