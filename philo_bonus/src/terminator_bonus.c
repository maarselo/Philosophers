/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminator_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:31:43 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:31:44 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_finish_philosopher(t_philo *philo, int exit_code)
{
	t_data	*tmp_data;

	tmp_data = philo->data;
	if (philo->sem_state && philo->sem_state != SEM_FAILED)
	{
		sem_close(philo->sem_state);
		sem_unlink(philo->name_sem_state);
	}
	if (philo->sem_situation && philo->sem_situation != SEM_FAILED)
	{
		sem_close(philo->sem_situation);
		sem_unlink(philo->name_sem_situation);
	}
	pthread_join(philo->thread, NULL);
	if (philo->data->total_philos == 1)
		ft_free_philo(philo);
	else
		ft_free_philo_list(philo->data->philos);
	sem_close(tmp_data->forks);
	sem_close(tmp_data->writer);
	free(tmp_data);
	exit(exit_code);
}

void	ft_kill_all_processes(pid_t pid_die, t_data *data)
{
	int		i;
	t_philo	*philo_tmp;

	i = 1;
	philo_tmp = data->philos;
	while (i++ <= data->total_philos)
	{
		if (philo_tmp->pid == -1 || philo_tmp->pid == pid_die)
		{
			i++;
			philo_tmp = philo_tmp->right_philo;
			continue ;
		}
		kill(philo_tmp->pid, SIGKILL);
		philo_tmp = philo_tmp->right_philo;
	}
}
