#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}					t_data;

typedef struct s_list
{
	int				index;
	int				left;
	int				right;
	struct s_list	*next;
	struct s_list	*previous;
}					philo_list;

typedef struct philo_data
{
	int				index;
	t_data			*data;
	philo_list		*fork_lst;
	long			last_eat;
}					p_data;

philo_list			*ft_lstnew(int index);
philo_list			*ft_lstlast(philo_list *lst);
void				ft_lstadd_back(philo_list **lst, philo_list *new);
void				ft_lstset_previous(philo_list *lst);
void				set_circular(philo_list *lst);

#endif