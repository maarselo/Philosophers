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
	if (philo->data->total_philos == 1)
	{
		if (philo->situation == DIE)
			return (sem_post(philo->sem_state), 1);
		return (sem_post(philo->sem_state), 0);
	}
	else if (!philo->is_eating && ft_get_time() >= philo->limit_time)
		return (sem_post(philo->sem_state), 1);
	sem_post(philo->sem_state);
	return (0);
}

static void	ft_handler_situation_flag(int new_situation, t_philo *philo)
{
	if (new_situation == FINISHED_MEALS)
	{
		sem_wait(philo->sem_situation);
		philo->situation = FINISHED_MEALS;
		sem_post(philo->sem_situation);
	}
	else if (new_situation == DIED)
	{
		sem_wait(philo->sem_situation);
		philo->situation = DIED;
		sem_post(philo->sem_situation);
	}
}

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
				ft_handler_situation_flag(FINISHED_MEALS, philo);
				ft_display_message(ALL_MEALS, philo);
				break ;
			}
		}
		if (ft_check_anyone_has_died(philo))
		{
			ft_handler_situation_flag(DIED, philo);
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
	int		count_finished;

	count_finished = 0;
	while (true)
	{
		pid_die = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		if (exit_code == ERROR || exit_code == DIED
			|| count_finished == data->total_philos)
		{
			ft_kill_all_processes(pid_die, data);
			break ;
		}
		else if (exit_code == FINISHED_MEALS)
		{
			count_finished++;
			if (count_finished == data->total_philos)
				printf("All philosophers reached the must meals.\n");
			continue ;
		}
	}
}
