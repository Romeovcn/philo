#include "philo.h"

pthread_mutex_t lock;

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
	struct philo_data philo = *(struct philo_data *)p;
	if (philo.index % 2 == 1)
		usleep(100000);
	// printf("IS %d PAIR=%d\n", philo.index, philo.index % 2);
	pthread_mutex_lock(&lock);
	if (check_can_eat(philo.fork_lst, philo.index))
	{
		set_eat(philo.fork_lst, philo.index);
		struct timeval tv;
		struct timezone tz;
		gettimeofday(&tv, &tz);
		printf("%ld: SET %d TO EAT\n", tv.tv_sec * 1000 + tv.tv_usec / 1000, philo.index);
	}
	pthread_mutex_unlock(&lock);
	// printf("Im philo : %d Can i eat ? : %d\n", philo.index, check_can_eat(philo.fork_lst ,philo.index));
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
	// (*data).time_to_die = atoi(argv[2]);
	// (*data).time_to_eat = atoi(argv[3]);
	// (*data).time_to_sleep = atoi(argv[4]);
	// if (argv[5])
	// 	(*data).number_of_times_each_philosopher_must_eat = atoi(argv[5]);
}

void free_philo_list(philo_list *lst, int size)
{
	philo_list *next;
	while (size)
	{
		next = lst->next;
		free(lst);
		lst = next;
		size--;
	}
}

int	main(int argc, char **argv)
{
	pthread_t t[50];
	t_data data;
	int i;
	struct philo_data *philo_data;

	if (argc != 2 && argc != 5 && argc != 5)
	{
		printf("Wrong inputs\n");
		exit(1);
	}
	if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
	//-----------------------------------------//
	//				Fork list				   //
	//-----------------------------------------//
	get_data(&data, argv);

	philo_list *fork_lst;

	fork_lst = NULL;
	int j = 1;
	while (j <= data.number_of_philosophers)
		ft_lstadd_back(&fork_lst, ft_lstnew(j++));
	ft_lstset_previous(fork_lst);
	set_circular(fork_lst);
	// printf("BEFORE=%d\n", check_can_eat(philos, 5));
	// set_eat(philos, 5);
	// printf("%d\n", check_can_eat(philos, 1));
	// printf("%d\n", check_can_eat(philos, 2));
	// printf("%d\n", check_can_eat(philos, 3));
	// printf("%d\n", check_can_eat(philos, 4));
	// printf("%d\n", check_can_eat(philos, 5));

	//------------------------------------------//
	//				Time stamp					//
	//------------------------------------------//
	// struct timeval current_time;
	// gettimeofday(&current_time, NULL);
	// printf("seconds : %ld micro seconds : %ld\n",
	// 		current_time.tv_sec % 60,
	// 		current_time.tv_usec / 10000);
	//-----------------------------------------//
	//					Thread					//
	//-----------------------------------------//
	philo_data = malloc(data.number_of_philosophers * sizeof(struct philo_data));
	i = 1;
	while (i <= data.number_of_philosophers)
	{
		philo_data[i - 1].fork_lst = fork_lst;
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
	//				EXIT AND FREE				//
	//-----------------------------------------//
	free_philo_list(fork_lst, data.number_of_philosophers);
	free(philo_data);
	pthread_mutex_destroy(&lock);
//printf("%d\n", tv.tv_usec / 1000);
}