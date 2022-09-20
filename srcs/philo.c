#include "philo.h"

void	*function(void *p)
{
	printf("Value recevied as argument in starting routine: ");
	printf("%i\n", *(int *)p);
	(*(int*)p)++;
	return NULL;
}

//void	function(void *p)
//{
//}

//void philosophers()
//{
//	while (1)
//	{
//		if (FOURCHETTE_LEFT && FOURCHETTE_RIGHT)
//		{
//			PRINT INDEX TAKE FORK x2
//			usleep

//		}
//	}
//}



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

void get_data(t_data *data, char **argv)
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

	//if (argc != 5 && argc != 5)
	//{
	//	printf("Wrong inputs\n");
	//	exit(1);
	//}
	get_data(&data, argv);
	i = 1;
	while (i <= data.number_of_philosophers)
	{
		int j = 10;
		pthread_create(&t[i - 1], NULL, function, &j);
		i++;
	}
	i = 1;
	while (i <= data.number_of_philosophers)
	{
		pthread_join(t[i - 1], NULL);
		i++;
	}

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