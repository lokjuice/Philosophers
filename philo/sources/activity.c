/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:27:34 by wroyal            #+#    #+#             */
/*   Updated: 2021/11/06 16:41:57 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print(char *str, t_philo *ph)
{
	long int	time;

	time = time_get() - ph->das->start_time;
	pthread_mutex_lock(&ph->das->write_mutex);
	printf("%ld Philo %d %s\n", time, ph->ph_id, str);
	if (!ph->dead_flag)
		pthread_mutex_unlock(&ph->das->write_mutex);
}

void	ft_sleep(int time)
{
	long int	start;

	start = time_get();
	while ((time_get() - start) < (long int)time)
		usleep(100);
}

void	sleeping(t_philo *ph)
{
	ft_print("is sleeping", ph);
	ft_sleep(ph->slp_tm);
}

void	eating(t_philo *ph)
{
	ft_print("is eating", ph);
	ph->life = time_get();
	ft_sleep(ph->eat_tm);
	ph->cnt_eat++;
	pthread_mutex_unlock(&ph->l_f);
	pthread_mutex_unlock(ph->r_f);
}

void	forking(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_f);
	ft_print("has taken fork", ph);
	pthread_mutex_lock(ph->r_f);
	ft_print("has taken fork", ph);
}
