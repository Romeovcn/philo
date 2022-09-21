#include "philo.h"

int	check_can_eat(philo_list *lst, int index)
{
	while (lst->index != index)
		lst = lst->next;
	if (lst->left && lst->right)
		return (1);
	return (0);
}

void	set_eat(philo_list *lst, int index)
{
	while (lst->index != index)
		lst = lst->next;
	lst->left = 0;
	lst->right = 0;
	lst->previous->right = 0;
	lst->next->left = 0;
}

void	*function(void *p)
{
	printf("Value received as argument in starting routine: %d\n", ((struct philo_data*)p)->index);
//	while (1)
//	{
//		if (FOURCHETTE_LEFT && FOURCHETTE_RIGHT)
//		{
//			printf("timestamp_in_ms X has taken a fork\n");
//			printf("timestamp_in_ms X has taken a fork\n");
//			printf("timestamp_in_ms X is eating\n");
//			update eat time
//			usleep(time to eat)
//			printf("timestamp_in_ms X is sleeping\n");
//			usleep(time to sleep)
//			printf("timestamp_in_ms X is thinking\n");
//		}
//	}
	return (NULL);
}


void	get_data(t_data *data, char **argv)
{
	(*data).number_of_philosophers = atoi(argv[1]);
	//(*data).time_to_die = atoi(argv[2]);
	//(*data).time_to_eat = atoi(argv[3]);
	//(*data).time_to_sleep = atoi(argv[4]);
	//if (argv[5])
	//	(*data).number_of_times_each_philosopher_must_eat = atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	pthread_t t[5];
	t_data data;
	int i;
	struct philo_data *philo_data;

	//if (argc != 5 && argc != 5)
	//{
	//	printf("Wrong inputs\n");
	//	exit(1);
	//}
	//-----------------------------------------//
	//				Time stamp				   //
	//-----------------------------------------//
	//struct timeval current_time;
	//gettimeofday(&current_time, NULL);
	//printf("seconds : %ld\nmicro seconds : %d",
	//		current_time.tv_sec,
	//		current_time.tv_usec);
	//-----------------------------------------//
	//					Thread				   //
	//-----------------------------------------//
	get_data(&data, argv);
	philo_data = malloc(data.number_of_philosophers * sizeof(struct philo_data));
	i = 1;
	while (i <= data.number_of_philosophers)
	{
		philo_data[i - 1].data = &data;
		philo_data[i - 1].index = i;
		pthread_create(&t[i - 1], NULL, function, &philo_data[i - 1]);
		i++;
	}
	i = 1;
	while (i <= data.number_of_philosophers)
	{
		pthread_join(t[i - 1], NULL);
		i++;
	}

	//-----------------------------------------//
	//				Fork list				   //
	//-----------------------------------------//
	//philo_list *philos;

	//philos = ft_lstnew(1);
	//ft_lstadd_back(&philos, ft_lstnew(2));
	//ft_lstadd_back(&philos, ft_lstnew(3));
	//ft_lstadd_back(&philos, ft_lstnew(4));
	//ft_lstadd_back(&philos, ft_lstnew(5));
	//ft_lstset_previous(philos);
	//set_circular(philos);
	//printf("%d\n", check_can_eat(philos, 5));
	//set_eat(philos, 5);
	//printf("%d\n", check_can_eat(philos, 4));
	//printf("%d\n", check_can_eat(philos, 1));
	//printf("%d\n", check_can_eat(philos, 5));
}