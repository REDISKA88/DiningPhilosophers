#include "philo.h"
void	ft_start_threads(t_table *t)
{
	int	i;

	i = 0;
	t->start_life = ft_get_time();
	while (i < t->num)
	{
		pthread_create(&t->philos[i].thread, NULL, start_routine,
			&t->philos[i]);
		t->philos[i].start = ft_get_time();
		pthread_create(&t->philos[i].monitor, NULL, start_monitoring,
			&t->philos[i]);
		i++;
	}
	i = 0;
	while (i < t->num)
	{
		pthread_join(t->philos[i].thread, NULL);
		pthread_join(t->philos[i].monitor, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	t;

	if (argc != 5 && argc != 6)
		return (-1);
	if (!ft_init_args(&t, argc, argv))
		return (1);
	if (!ft_init_phil(&t))
	{
		if (t.philos)
			free(t.philos);
		return (1);
	}
	ft_start_threads(&t);
	ft_destroy(&t);
	return (0);
}
