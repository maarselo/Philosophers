/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:36:37 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/13 22:36:38 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	t_philo	*philo_tmp;

	philo_tmp = philo_list;
	while (philo_tmp)
	{
		if (philo_tmp->right_philo == philo_created)
		{
			philo_tmp->right_philo->left_philo = philo_tmp;
			return ;
		}
		philo_tmp = philo_tmp->right_philo;
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

