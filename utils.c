/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpflegha <jpflegha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:57:03 by jpflegha          #+#    #+#             */
/*   Updated: 2025/02/19 15:24:58 by jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

void	ft_kill(pid_t pid, int signum)
{
	if (kill(pid, signum) < 0)
	{
		write(STDOUT_FILENO, "Signal transmission failed\n", 28);
		exit(EXIT_FAILURE);
	}
}

void	my_signal(int signo, void *handler, bool use_siginfo)
{
	static struct sigaction	sa = {0};

	if (use_siginfo)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handler;
	}
	else
		sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(signo, &sa, NULL) < 0)
	{
		write(STDOUT_FILENO, "Signal handler failed\n", 22);
		exit(EXIT_FAILURE);
	}
}
