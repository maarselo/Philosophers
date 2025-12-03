/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:36:37 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:36:38 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

char	*ft_get_name_sem_state(long philo_number)
{
	long	i;
	int		total_digits;
	char	*philo_str;
	char	*semname;

	total_digits = 0;
	i = philo_number;
	total_digits = ft_length_count((void *)&philo_number, NB);
	philo_str = "/philo";
	semname = malloc(ft_length_count(philo_str, STR) + total_digits + 1);
	if (!semname)
		return (NULL);
	i = -1;
	while (++i < ft_length_count(philo_str, STR))
		semname[i] = philo_str[i];
	i = ft_length_count(philo_str, STR) + total_digits - 1;
	while (philo_number > 0)
	{
		semname[i--] = '0' + (philo_number % 10);
		philo_number /= 10;
	}
	semname[i + total_digits + 1] = '\0';
	return (semname);
}

char	*ft_get_name_sem_situation(long philo_number)
{
	long	i;
	int		total_digits;
	char	*philo_str;
	char	*semname;

	total_digits = 0;
	i = philo_number;
	total_digits = ft_length_count((void *)&philo_number, NB);
	philo_str = "/situation";
	semname = malloc(ft_length_count(philo_str, STR) + total_digits + 1);
	if (!semname)
		return (NULL);
	i = -1;
	while (++i < ft_length_count(philo_str, STR))
		semname[i] = philo_str[i];
	i = ft_length_count(philo_str, STR) + total_digits - 1;
	while (philo_number > 0)
	{
		semname[i--] = '0' + (philo_number % 10);
		philo_number /= 10;
	}
	semname[i + total_digits + 1] = '\0';
	return (semname);
}

void	ft_append_philo(t_philo *philo_created, t_philo *philo_list)
{
	t_philo	*philo_tmp;

	philo_tmp = philo_list;
	while (philo_tmp->right_philo)
		philo_tmp = philo_tmp->right_philo;
	philo_tmp->right_philo = philo_created;
}

void	ft_link_previous_philo(t_philo *philo_created, t_philo *philo_list)
{
	t_philo	*philo_previous;

	philo_previous = philo_list;
	while (philo_previous)
	{
		if (philo_previous->right_philo == philo_created)
		{
			philo_previous->right_philo->left_philo = philo_previous;
			return ;
		}
		philo_previous = philo_previous->right_philo;
	}
}

void	ft_linked_first_with_last_philo(t_philo *top_philo)
{
	t_philo	*philo_tmp;

	if (!top_philo->right_philo)
		return ;
	philo_tmp = top_philo;
	while (philo_tmp->right_philo)
		philo_tmp = philo_tmp->right_philo;
	top_philo->left_philo = philo_tmp;
	philo_tmp->right_philo = top_philo;
}
