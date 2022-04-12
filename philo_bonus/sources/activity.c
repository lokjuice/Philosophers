/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wroyal <wroyal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:27:34 by wroyal            #+#    #+#             */
/*   Updated: 2021/11/07 13:03:53 by wroyal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print(char *str, t_philo *ph)
{
	long int	time;

	time = time_get() - ph->das->start_time;
	sem_wait(ph->das->sem_wrt);
	printf("%ld Philo %d %s\n", time, ph->ph_id, str);
	if (!ph->das->dead_flag)
		sem_post(ph->das->sem_wrt);
}

void	ft_sleep(int time)
{
	long int	start;

	start = time_get();
	while ((time_get() - start) < (long int)time)
		usleep(100);
}

void	ft_wait(t_data *data)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (i < data->cnt_of_ph)
	{
		waitpid(-1, &status, 0);
		i++;
		if (status)
		{
			i = 0;
			while (i < data->cnt_of_ph)
			{
				kill(data->pids_mas[i], SIGKILL);
				i++;
			}
		}
	}
	free(data->pids_mas);
	free(data->ph);
}

void	*ft_dead(void *das)
{
	t_philo	*ph;

	ph = (t_philo *)das;
	ph->das->counter = 0;
	while (1)
	{
		if (check_death_dop(ph))
			return (NULL);
		if (ph->das->counter >= ph->das->cnt_of_ph)
		{
			ft_sleep(ph->eat_tm);
			exit(1);
			return (NULL);
		}
	}
	return (NULL);
}

void	activity(t_philo *ph)
{
	sem_wait(ph->das->sem_frk);
	ft_print("has taken fork", ph);
	sem_wait(ph->das->sem_frk);
	ft_print("has taken fork", ph);
	ft_print("is eating", ph);
	ph->cnt_eat++;
	ph->life = time_get();
	ft_sleep(ph->eat_tm);
	sem_post(ph->das->sem_frk);
	sem_post(ph->das->sem_frk);
	ft_print("is sleeping", ph);
	ft_sleep(ph->slp_tm);
	ft_print("is thinking", ph);
}
