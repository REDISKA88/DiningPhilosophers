#include "philo.h"
int ft_init_args(t_table *t, int argc, char **argv)
{
    int i;

    i = 1;
    while(argv[i])
    {
        if (!ft_isdigit(ft_atoi(argv[i])) && ft_atoi(argv[i]) < 0)
            return (-1);
        i++;
    }
    t->num = ft_atoi(argv[1]);
    if (t->num <= 0 || t->num >= 200)
        return (-1);
    t->die = ft_atoi(argv[2]);
    t->eat = ft_atoi(argv[3]);
    t->sleep = ft_atoi(argv[4]);
    if (argc == 6)
        t->must_eat = ft_atoi(argv[5]);
    else
        t->must_eat = -1;
    if (t->must_eat == 0)
        return (-1);
    t->finish = 0;
    pthread_mutex_init(&t->message, NULL);
    return (1);
}

int ft_init_phil(t_table *t)
{
    int i;

    i = 0;
    t->philos = malloc(sizeof(t_phil) * t->num);
    if (!t->philos)
        return (-1);
    t->forks = malloc(sizeof(pthread_mutex_t) *t->num);
    if (!t->forks)
        return (-1);
    while (i < t->num)
    {
        t->philos[i].id = i;
        t->philos[i].eat_count = 0;
        t->philos[i].start = 0;
        t->philos[i].table = t;
        t->philos[i].r_fork = &t->forks[i];
        if (i == 0)
            t->philos[i].l_fork = &t->forks[t->num - 1];
        else
            t->philos[i].l_fork = &t->forks[i - 1];
        pthread_mutex_init(&t->philos[i].lock, NULL);
        i++;
    }
    return (1);
}

void	ft_destroy(t_table *t)
{
    int	i;

    i = -1;
    while (++i < t->num)
    {
        pthread_mutex_destroy(&t->forks[i]);
        pthread_mutex_destroy(&t->philos[i].lock);
    }
    pthread_mutex_destroy(&t->message);
    free(t->forks);
    free(t->philos);
}