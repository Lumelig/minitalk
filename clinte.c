/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clinte.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:40:53 by jpflegha          #+#    #+#             */
/*   Updated: 2025/02/18 16:12:26 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_server_status = BUSY;

void	end_handler(int signo)
{
	write(STDOUT_FILENO, "Message received\n", 17);
	exit(EXIT_SUCCESS);
}

void	ack_handler(int signo)
{
	g_server_status = READY;
}

void	send_message(pid_t server, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & 1)
			kill(server, SIGUSR1);
		else
			kill(server, SIGUSR2);
		c >>= 1;
		i++;
		while (BUSY == g_server_status)
		{
			usleep(100);
		}
		g_server_status = BUSY;
	}
}

int	main(int ac, char **av)
{
	pid_t	server;
	char	*str;
	int		i;

	i = 0;
	if (3 != ac)
	{
		printf("Usage: %s <server_pid> <string>\n", av[0]);
		return (EXIT_FAILURE);
	}
	server = atoi(av[1]);
	str = av[2];
	my_signal(SIGUSR1, ack_handler, false);
	my_signal(SIGUSR2, end_handler, false);
	while (str[i])
	{
		send_message(server, str[i]);
		i++;
	}
	send_message(server, '\0');
	return (EXIT_SUCCESS);
}
