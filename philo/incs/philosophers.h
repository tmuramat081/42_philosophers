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
# define PHILO_MAX 200

# include <libc.h>
# include <pthread.h>
# include <assert.h>
# include "philosophers.h"
# include "ft_deque.h"

typedef struct s_philo_dto		t_philo_dto;
typedef struct s_environ		t_environ;
typedef struct s_monitor		t_monitor;
typedef struct s_philosopher	t_philosopher;
typedef struct s_arbitrator		t_arbitrator;
typedef struct timeval			t_timeval;

/**
 * @brief コマンドライン引数の取得型
 *
 */
struct s_philo_dto
{
	long	num_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_of_eating;
};

/**
 * @brief 哲学者の管理情報
 *
 */
struct s_philosopher
{
	size_t			id;
	pthread_t		thread_id;
	long			started_at;
	pthread_mutex_t	mut;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	long			last_eat_at;
	size_t			count_eaten;
	t_monitor		*monitor;
	t_arbitrator	*waiter;
};

/**
 * @brief 監視者の管理情報
 *
 */
struct s_monitor
{
	pthread_t		thread_id;
	long			started_at;
	size_t			num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	long			num_of_eat;
	bool			is_sim_over;
	pthread_mutex_t	mut_io;
	t_philosopher	*philos;
	t_arbitrator	*waiter;
};

/**
 * @brief 配膳人の
 *
 */
struct s_arbitrator
{
	pthread_t	thread_id;
	t_deque		*queue;
	t_monitor	*monitor;
};

struct s_environ
{
	t_philosopher	philos[200];
	t_monitor		monitor;
	t_arbitrator	waiter;
	pthread_mutex_t	forks[200];
	long			started_at;
};

/** Main functions */
bool			input_arguments(char **av, t_philo_dto *philo);
t_environ		init_environs(t_philo_dto input);
void			simulate_problem(t_environ *envs);

/** Initalize threads */
void			start_dinner(t_philosopher *philos, t_monitor *monitor,
					t_arbitrator *waiter);

/** Thread for philosophers */
void			*lifecycle(void *philo);
int				do_eat(t_philosopher *philo, t_monitor *monitor);
int				do_sleep(t_philosopher *philo, t_monitor *monitor);
int				do_think(t_philosopher *philo);

/** Thread for monitor */
void			*checker(void *p_monitor);
bool			is_philo_dead(t_monitor *monitor, t_philosopher *philos);
bool			is_philo_full(t_monitor *monitor, t_philosopher *philos);

/** Thread for Arbitrator (waiter) */
void			*server(void *p_waiter);
void			send_message(t_philosopher *philo);
int				receive_message(t_philosopher *philo);

/** Util functions */
long			ft_strtol_d(const char *nptr, char **endp);
int				ft_isspace(int c);
int				ft_isdigit(int c);
void			ft_sleep(long time_to_wait);
int				put_error(void);
long			gettime_ms(void);
int				put_timestamp(char *string, t_philosopher *philo);
long			get_elapsed_time(long start_ms, long end_ms);

#endif