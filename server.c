/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:41:34 by jpflegha          #+#    #+#             */
/*   Updated: 2025/02/19 15:25:50 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signo, siginfo_t *info, void *more_info)
{
	static char		c;
	static int		i;
	static pid_t	client_pid;

	(void)more_info;
	client_pid = info->si_pid;
	if (SIGUSR1 == signo)
		c |= (1 << i);
	else if (SIGUSR2 == signo)
		c &= ~(1 << i);
	i++;
	if (8 == i)
	{
		i = 0;
		if ('\0' == c)
		{
            write(STDOUT_FILENO, "\n", 1);
			c = 0;
			kill(client_pid, SIGUSR2);
            client_pid = 0;
			return ;
		}
		write(STDOUT_FILENO, &c, 1);
		c = 0;
	}
	kill(client_pid, SIGUSR1);
    
}

int	main(void)
{
	printf("PID %d\n", getpid());
	my_signal(SIGUSR1, handler, true);
	my_signal(SIGUSR2, handler, true);
	while (1)
	{
		pause();
	}
	return (EXIT_SUCCESS);
}
