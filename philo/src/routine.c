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
/*

#include "philosophers.h"

//Función mejorada para esperar de forma más precisa 
static void	ft_precise_sleep(long time_in_ms, t_philo *philo)
{
	long	start;
	long	current;

	start = ft_get_time();
	while (ft_should_continue(philo))
	{
		current = ft_get_time();
		if (current - start >= time_in_ms)
			break;
		usleep(500);
	}
}

static int	ft_take_forks(t_philo *philo)
{
	if (ft_check_only_one(philo))
		return (ft_handler_one_philo(philo), 1);
	
	// Los filósofos impares toman primero su fork derecho 
	if (philo->philo_number % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork);
		if (!ft_should_continue(philo))
			return (pthread_mutex_unlock(&philo->fork), 1);
		ft_display_message(TAKEN_FORK, philo);
		
		pthread_mutex_lock(&philo->left_philo->fork);
		if (!ft_should_continue(philo))
		{
			pthread_mutex_unlock(&philo->left_philo->fork);
			pthread_mutex_unlock(&philo->fork);
			return (1);
		}
		ft_display_message(TAKEN_FORK, philo);
	}
	// Los filósofos pares toman primero el fork izquierdo
	else
	{
		pthread_mutex_lock(&philo->left_philo->fork);
		if (!ft_should_continue(philo))
			return (pthread_mutex_unlock(&philo->left_philo->fork), 1);
		ft_display_message(TAKEN_FORK, philo);
		
		pthread_mutex_lock(&philo->fork);
		if (!ft_should_continue(philo))
		{
			pthread_mutex_unlock(&philo->fork);
			pthread_mutex_unlock(&philo->left_philo->fork);
			return (1);
		}
		ft_display_message(TAKEN_FORK, philo);
	}
	return (0);
}

static void	ft_leave_forks(t_philo *philo)
{
	//Desbloquear en orden inverso al bloqueo 
	if (philo->philo_number % 2 != 0)
	{
		pthread_mutex_unlock(&philo->left_philo->fork);
		pthread_mutex_unlock(&philo->fork);
	}
	else
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
	ft_precise_sleep(philo->data->time_to_eat, philo);
	
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
	ft_precise_sleep(philo->data->time_to_sleep, philo);
}

static void	ft_think(t_philo *philo)
{
	long	time_to_think;

	if (!ft_should_continue(philo))
		return ;
	
	ft_display_message(THINKING, philo);
	
	// Calcular tiempo de pensamiento para evitar que mueran 
	time_to_think = (philo->data->time_to_die 
		- philo->data->time_to_eat 
		- philo->data->time_to_sleep) / 2;
	
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	
	if (time_to_think > 0)
		ft_precise_sleep(time_to_think, philo);
}

void	*ft_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	
	// Sincronización inicial: los filósofos pares esperan un poco 
	if (philo->philo_number % 2 == 0)
		usleep(1000);
	
	while (ft_should_continue(philo))
	{
		ft_eat(philo);
		if (!ft_should_continue(philo))
			break;
		ft_sleep(philo);
		if (!ft_should_continue(philo))
			break;
		ft_think(philo);
	}
	return (NULL);
}*/