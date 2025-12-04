/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:31:43 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:31:44 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_data	*ft_init_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->total_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->must_meals = ft_atol(argv[5]);
	else
		data->must_meals = 0;
	data->philos = NULL;
	sem_unlink("/forks");
	sem_unlink("/writer");
	data->forks = sem_open("/forks", O_CREAT, 0644, ft_atol(argv[1]));
	if (data->forks == SEM_FAILED)
		return (free(data), NULL);
	data->writer = sem_open("/writer", O_CREAT, 0644, 1);
	if (data->writer == SEM_FAILED)
		return (ft_free_data(data), NULL);
	data->start_time = ft_get_time();
	return (data);
}

static t_philo	*ft_init_philo(long philo_number, t_data *data)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_number = philo_number;
	philo->is_eating = false;
	if (data->must_meals)
		philo->meals = 0;
	else
		philo->meals = -1;
	philo->name_sem_state = ft_get_name_sem_state(philo_number);
	if (!philo->name_sem_state)
		return (free(philo), NULL);
	philo->sem_state = NULL;
	philo->situation = ALIVE;
	philo->name_sem_situation = ft_get_name_sem_situation(philo_number);
	if (!philo->name_sem_situation)
		return (free(philo->name_sem_state), free(philo), NULL);
	philo->sem_situation = NULL;
	philo->pid = -1;
	philo->left_philo = NULL;
	philo->right_philo = NULL;
	philo->data = data;
	return (philo);
}

void	ft_init_philos_data(t_data *data)
{
	long		i;
	t_philo		*philo_top;
	t_philo		*philo_created;

	i = 0;
	philo_top = NULL;
	while (++i <= data->total_philos)
	{
		philo_created = ft_init_philo(i, data);
		if (!philo_created)
		{
			ft_free_data(data);
			ft_free_philo_list(philo_top);
			ft_error_handler(CREATING_VARIABLES);
		}
		if (!philo_top)
			philo_top = philo_created;
		else
		{
			ft_append_philo(philo_created, philo_top);
			ft_link_previous_philo(philo_created, philo_top);
		}
	}
	ft_linked_first_with_last_philo(philo_top);
	data->philos = philo_top;
}

static void	ft_init_philo_routine(t_philo *philo)
{
	sem_unlink(philo->name_sem_state);
	philo->sem_state = sem_open(philo->name_sem_state, O_CREAT, 0644, 1);
	if (philo->sem_state == SEM_FAILED)
		ft_finish_philosopher(philo, ERROR);
	sem_unlink(philo->name_sem_situation);
	philo->sem_situation = sem_open(philo->name_sem_situation,
			O_CREAT, 0644, 1);
	if (philo->sem_situation == SEM_FAILED)
		ft_finish_philosopher(philo, ERROR);
	philo->limit_time = ft_get_time() + philo->data->time_to_die;
	if (philo->data->total_philos > 1)
	{
		if (pthread_create(&philo->thread, NULL,
				ft_process_monitor, philo) != 0)
		{
			ft_error_handler(CREATING_THREADS);
			ft_finish_philosopher(philo, ERROR);
		}
	}
	ft_routine(philo);
}

int	ft_init_philos_processes(t_data *data)
{
	int		i;
	t_philo	*philo_tmp;

	i = 1;
	philo_tmp = data->philos;
	while (i++ <= data->total_philos)
	{
		philo_tmp->pid = fork();
		if (philo_tmp->pid == -1)
			return (ERROR);
		else if (philo_tmp->pid == 0)
			ft_init_philo_routine(philo_tmp);
		philo_tmp = philo_tmp->right_philo;
	}
	return (SUCCESS);
}
