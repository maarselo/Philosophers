/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:31:43 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:31:44 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

bool	ft_check_only_one(t_data *data)
{
	if (data->total_philos == 1)
		return (true);
	return (false);
}

void	ft_handler_one_philo(t_philo *philo)
{
	sem_wait(philo->data->forks);
	ft_display_message(TAKEN_FORK, philo);
	usleep(philo->data->time_to_die * 1000);
	sem_post(philo->data->forks);
	sem_wait(philo->sem_situation);
	philo->situation = DIED;
	sem_post(philo->sem_situation);
	ft_display_message(DIE, philo);
	ft_finish_philosopher(philo, DIED);
}

bool	ft_check_should_continue(t_philo *philo)
{
	sem_wait(philo->sem_situation);
	if (philo->situation == FINISHED_MEALS
		|| philo->situation == DIED)
		return (sem_post(philo->sem_situation), false);
	sem_post(philo->sem_situation);
	return (true);
}

void	ft_precise_sleep(long milliseconds, t_philo *philo)
{
	long	start_time;
	long	current;

	start_time = ft_get_time();
	while (ft_check_should_continue(philo))
	{
		current = ft_get_time();
		if (current - start_time >= milliseconds)
			break ;
		usleep(500);
	}	
}
int	ft_get_exit_code(t_philo *philo)
{
	int	exit_code;

	sem_wait(philo->sem_situation);
	exit_code = philo->situation;
	sem_post(philo->sem_situation);
	return (exit_code);
}
