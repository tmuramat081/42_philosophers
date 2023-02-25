/* ************************************************************************** */
/*                                                                            */
/*                                                        :::::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:19:30 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/04 11:47:09 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MSG_TAKEN_FORK "has taken a fork"
# define MSG_EATING "is eating"
# define MSG_SLEEPING "is sleeping"
# define MSG_THINKING "is thinking"
# define MSG_DIED "died"
# define PHILO_MAX 500

# include <libc.h>
# include <pthread.h>
# include "libft.h"
# include "philosophers.h"

typedef struct s_philo_dto		t_philo_dto;
typedef struct timeval			t_timeval;
typedef struct s_monitor		t_monitor;
typedef struct s_philosopher	t_philosopher;

/**
 * @brief コマンドライン引数からの取得用DTO型
 *
 */
struct s_philo_dto
{
	size_t	num_of_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	num_of_eating;
};

struct s_philosopher
{
	size_t			id;
	pthread_t		thread_id;
	long			started_at;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	long			last_eat_at;
	size_t			count_eaten;
	t_monitor		*monitor;
};

struct s_monitor
{
	pthread_t		thread_id;
	long			started_at;
	pthread_mutex_t	forks[PHILO_MAX];
	size_t			num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			num_of_eat;
	bool			is_any_died;
	pthread_mutex_t	io;
	t_philosopher	*philos;
};

t_philo_dto		input_arguments(char **av);
void			simulate_problem(t_philo_dto input);
t_monitor		init_monitor(t_philo_dto input);
t_philosopher	*init_philosophers(t_philo_dto input, t_monitor *monitor);
void			handle_error(void);
void			*lifecycle(void *philo);
int				do_eat(t_philosopher *philo, t_monitor *monitor);
int				do_sleep(t_philosopher *philo, t_monitor *monitor);
int				do_think(t_philosopher *philo);
void			start_dinner(t_philosopher *philos, t_monitor *monitor);
long			gettime_ms(void);
long			get_elapsed_time(long start_ms, long end_ms);
int				put_timestamp(char *string, t_philosopher *philo);
void 			*monitor(void *p_monitor);

#endif