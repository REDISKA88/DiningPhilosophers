#include "philo.h"
void	*start_routine(void *phil)
{
	t_phil	*p;

	p = phil;
	if (p->id % 2)
		usleep(10000);
	while (p->table->finish != 1 && p->eat_count != p->table->must_eat)
	{
		ft_eating(p);
		if (p->table->must_eat != -1)
		{
			if (how_much_to_eat(p))
				break ;
		}
		if (p->table->finish)
			break ;
		ft_message(p, "is sleeping");
		ft_sleeping(p);
		if (p->table->finish)
			break ;
		ft_message(p, "is thinking");
		if (p->table->finish)
			break ;
	}
	return (NULL);
}

void	*start_monitoring(void *phil)
{
	t_phil	*p;

	p = phil;
	while (p->table->finish != 1)
	{
		pthread_mutex_lock(&p->lock);
		if (ft_get_time() - p->start >= p->table->die && p->eat_count
			>= p->table->must_eat)
		{
			ft_message(p, "dead");
			p->table->finish = 1;
			pthread_mutex_unlock(&p->lock);
			break ;
		}
		pthread_mutex_unlock(&p->lock);
		usleep(100);
	}
	return (NULL);
}

void	ft_eating(t_phil *p)
{
	if (p->table->num == 1)
		ft_one_eating(p);
	else
	{
		pthread_mutex_lock(p->l_fork);
		ft_message(p, "has taken a fork");
		pthread_mutex_lock(p->r_fork);
		ft_message(p, "has taken a fork");
		pthread_mutex_lock(&p->lock);
		ft_message(p, "is eating");
		p->start = ft_get_time();
		pthread_mutex_unlock(&p->lock);
		p->eat_count++;
		p->time_start = ft_get_time();
		while (!(p->table->finish))
		{
			p->time_last = ft_get_time();
			if ((p->time_last - p->time_start) >= p->table->eat)
				break ;
			usleep(10);
		}
		pthread_mutex_unlock(p->l_fork);
		pthread_mutex_unlock(p->r_fork);
	}
}

void	ft_one_eating(t_phil *p)
{
	pthread_mutex_lock(p->r_fork);
	ft_message(p, "has taken a fork");
	while (p->table->finish != 1)
		usleep(1000);
	pthread_mutex_unlock(p->r_fork);
}

void	ft_sleeping(t_phil *p)
{
	p->time_start = ft_get_time();
	while (!(p->table->finish))
	{
		p->time_last = ft_get_time();
		if ((p->time_last - p->time_start) >= p->table->sleep)
			break ;
		usleep(10);
	}
}
