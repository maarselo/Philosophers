/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:31:43 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:31:44 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	ft_check_philo_must_foods(t_philo *philo)
{
	sem_wait(philo->sem_state);
	if (philo->meals >= philo->data->must_meals)
		return (sem_post(philo->sem_state), 1);
	sem_post(philo->sem_state);
	return (0);
}

static int	ft_check_anyone_has_died(t_philo *philo)
{
	sem_wait(philo->sem_state);
	if (!philo->is_eating && ft_get_time() >= philo->limit_time)
		return (sem_post(philo->sem_state), 1);
	sem_post(philo->sem_state);
	return (0);
}

//doesnt know if its okay printf the message into the checkers
void	*ft_process_monitor(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	while (true)
	{
		if (philo->data->must_meals)
		{
			if (ft_check_philo_must_foods(philo))
			{
				sem_wait(philo->sem_situation);
				philo->situation = FINISHED_MEALS;
				sem_post(philo->sem_situation);
				ft_display_message(ALL_MEALS, philo);
				break ;
			}
		}
		if (ft_check_anyone_has_died(philo))
		{
			sem_wait(philo->sem_situation);
			philo->situation = DIED;
			sem_post(philo->sem_situation);
			ft_display_message(DIE, philo);
			break ;
		}
	}
	return (NULL);
}

void	ft_main_monitor(t_data *data)
{
	int		status;
	int		exit_code;
	pid_t	pid_die;

	while (true)
	{
		pid_die = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		if (exit_code == ERROR && exit_code == DIED)
		{
			ft_kill_all_processes(pid_die, data);
			break ;
		}
		else if (exit_code == FINISHED_MEALS)
			continue ;
	}
}
