#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_phil {
    struct s_table	*table;
    pthread_mutex_t	*r_fork;
    pthread_mutex_t	*l_fork;
    pthread_mutex_t	lock;
    pthread_t		thread;
    pthread_t		monitor;
    int				eat_count;
    int				id;
    long			start;
}				t_phil;

typedef struct s_table {
    pthread_mutex_t	*forks;
    pthread_mutex_t	message;
    t_phil			*philos;
    int				must_eat;
    long			start_life;
    int				sleep;
    int				finish;
    int				num;
    int				die;
    int				eat;

}				t_table;

int     ft_isdigit(int c);
int     ft_atoi(const char *str);
int     ft_init_args(t_table *t, int argc, char **argv);
int     ft_init_phil(t_table *t);
void    ft_start_threads(t_table *t);
long    ft_get_time(void);
void    *start_routine(void *phil);
void    *start_monitoring(void *phil);
void    ft_message(t_phil *p, char *message);
void	ft_one_eating(t_phil *p);
int     how_much_to_eat(t_phil *p);
void    ft_eating(t_phil *p);
void    ft_sleeping(t_phil *p);
void	ft_destroy(t_table *t);

#endif
