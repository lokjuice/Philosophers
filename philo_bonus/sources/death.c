/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:29:26 by wroyal            #+#    #+#             */
/*   Updated: 2021/11/07 13:11:00 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(char *str)
{
	int		i;

	i = 0;
	while (*str != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		str++;
	}
	return (0);
}

int	ft_error(char *str)
{
	ft_putstr_fd(str, 1);
	return (0);
}

int	check_death_dop(t_philo *ph)
{
	if (ph->cnt_eat > ph->das->must_eat && ph->das->must_eat != -1)
		ph->das->counter++;
	if (ph->das->tm_to_die < time_get() - ph->life)
	{
		sem_wait(ph->das->sem_dth);
		sem_wait(ph->das->sem_wrt);
		printf("%ld Philo %d is died\n", time_get() - ph->das->start_time, \
		ph->ph_id);
		exit(1);
		sem_post(ph->das->sem_dth);
	}
	return (0);
}
