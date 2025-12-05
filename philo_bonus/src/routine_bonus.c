/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:31:43 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:31:44 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	ft_leave_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

static int	ft_take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	if (!ft_check_should_continue(philo))
		return (sem_post(philo->data->forks), 1);
	ft_display_message(TAKEN_FORK, philo);
	sem_wait(philo->data->forks);
	if (!ft_check_should_continue(philo))
		return (ft_leave_forks(philo), 1);
	ft_display_message(TAKEN_FORK, philo);
	return (0);
}

void	ft_eat(t_philo *philo)
{
	if (!ft_check_should_continue(philo))
		return ;
	if (ft_take_forks(philo) == DIED)
		return ;
	sem_wait(philo->sem_state);
	philo->is_eating = true;
	philo->limit_time = ft_get_time() + philo->data->time_to_die;
	sem_post(philo->sem_state);
	ft_display_message(EATING, philo);
	ft_precise_sleep(philo->data->time_to_eat, philo);
	sem_wait(philo->sem_state);
	philo->is_eating = false;
	if (philo->data->must_meals)
		philo->meals++;
	sem_post(philo->sem_state);
	ft_leave_forks(philo);
}

static void	ft_sleep(t_philo *philo)
{
	if (!ft_check_should_continue(philo))
		return ;
	ft_display_message(SLEEPING, philo);
	ft_precise_sleep(philo->data->time_to_sleep, philo);
}

void	ft_routine(t_philo *philo)
{
	int	exit_code;

	if (ft_check_only_one(philo->data))
		return (ft_handler_one_philo(philo));
	while (ft_check_should_continue(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		if (ft_check_should_continue(philo))
			ft_display_message(THINKING, philo);
	}
	exit_code = ft_get_exit_code(philo);
	ft_finish_philosopher(philo, exit_code);
}
