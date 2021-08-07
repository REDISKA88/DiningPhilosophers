#include "philo.h"
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	if (!*str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_message(t_phil *p, char *message)
{
	pthread_mutex_lock(&p->table->message);
	if (!p->table->finish)
		printf("%ld %d %s\n", ft_get_time() - p->table->start_life, p->id + 1,
			message);
	pthread_mutex_unlock(&p->table->message);
}

int	how_much_to_eat(t_phil *p)
{
	int	i;

	i = -1;
	while (++i < p->table->num)
	{
		if (p->table->philos[i].eat_count < p->table->must_eat)
			return (0);
	}
	p->table->finish = 1;
	return (1);
}
