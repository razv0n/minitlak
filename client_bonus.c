/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:51:37 by mfahmi            #+#    #+#             */
/*   Updated: 2025/03/09 17:22:43 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

volatile int	g_ack = 0;

pid_t	ft_atoi(char *str)
{
	pid_t	pid;

	pid = 0;
	while (*str == ' ' || (*str > 9 && *str < 13))
		str++;
	while (*str)
	{
		pid = pid * 10 + (*str - '0');
		str++;
	}
	return (pid);
}

void	handler(int signum)
{
	if (signum == SIGUSR1)
		g_ack = 1;
	if (signum == SIGUSR2)
		write(1, "The Message Sent\n", 17);
}

void	send_char(int nm, pid_t pid_server)
{
	int	num_bits;

	num_bits = 8;
	while (num_bits >= 0)
	{
		if ((nm >> num_bits) & 1)
			kill(pid_server, SIGUSR2);
		else
			kill(pid_server, SIGUSR1);
		num_bits--;
		while (!g_ack)
			;
		g_ack = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					i;
	pid_t				pid_server;

	if (ac == 3)
	{
		pid_server = ft_atoi(av[1]);
		sa.sa_handler = handler;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		if (kill(pid_server, 0) == -1)
		{
			write(1, "The PID Is Not Valide\n", 22);
			return (1);
		}
		i = 0;
		while (av[2][i])
		{
			send_char(av[2][i], pid_server);
			i++;
		}
		send_char('\0', pid_server);
	}
}
