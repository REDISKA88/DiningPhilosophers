#include "philo.h"
void *start_routine(void *phil)
{
    t_phil *p;

    p = phil;
    if (p->id % 2 == 0)
        usleep(p->table->eat * 1000);
    while (p->table->finish != 1)
    {
        if (p->table->num == 1)
            ft_one_eating(p);
        ft_eating(p);
        if (p->table->must_eat != -1)
        {
            if (how_much_to_eat(p))
            break ;
        }
        if (p->table->finish)
            break ;
        ft_sleeping(p);
        if (p->table->finish)
            break ;
        ft_message(p, "is thinking");
        if (p->table->finish)
            break ;
    }
   return (NULL);
}

void ft_eating(t_phil *p)
{
    pthread_mutex_lock(p->r_fork);
    ft_message(p, "has taken a fork");
    pthread_mutex_lock(p->l_fork);
    ft_message(p, "has taken a fork");
    pthread_mutex_lock(&p->lock);
    p->start = ft_get_time();
    ft_message(p, "is eating");
    pthread_mutex_unlock(&p->lock);
    while ((ft_get_time() - p->start) <= p->table->eat && p->table->finish != 1)
        usleep(1000);
    p->eat_count++;
    pthread_mutex_unlock(p->r_fork);
    pthread_mutex_unlock(p->l_fork);
}

void *start_monitoring(void *phil)
{
    t_phil *p;

    p = phil;
    while (p->table->finish != 1)
    {
        pthread_mutex_lock(&p->lock);
        if (ft_get_time() - p->start >= p->table->die)
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

void ft_sleeping(t_phil *p)
{
    long	start_sleep;

    start_sleep = ft_get_time();
    ft_message(p, "is sleeping");
    while (ft_get_time() - start_sleep <= p->table->sleep && \
    !p->table->finish)
    usleep(1000);
}

void	ft_one_eating(t_phil *p)
{
    pthread_mutex_lock(p->r_fork);
    ft_message(p, "has taken a fork");
    while (p->table->finish != 1)
        usleep(1000);
    pthread_mutex_unlock(p->r_fork);
}

