/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:51:40 by mfahmi            #+#    #+#             */
/*   Updated: 2025/03/09 17:56:58 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	putnbr(pid_t n)
{
	char	c;

	if (n > 9)
	{
		putnbr(n / 10);
		putnbr(n % 10);
	}
	else
	{
		c = n + '0';
		write(1, &c, 1);
	}
}

void	putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	sig_handler(int signum, siginfo_t *info, void *nul)
{
	static char		c = 0;
	static int		byte = 0;
	static pid_t	pid = -1;

	nul = NULL;
	if (pid != info->si_pid && pid != -1)
		1 && (byte = 0, c = 0);
	pid = info->si_pid;
	if (SIGUSR2 == signum)
		c = (c << 1) | 1;
	else if (SIGUSR1 == signum)
		c = (c << 1) | 0;
	if (byte == 8)
	{
		if (c == 0)
			kill(pid, SIGUSR2);
		else
			write(1, &c, 1);
		(1) && (byte = -1, c = 0);
	}
	byte++;
	kill(pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	putstr("THE PID IS: ");
	putnbr(pid);
	putstr("\n");
	while (1)
		pause();
}
