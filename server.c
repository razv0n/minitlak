/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:51:40 by mfahmi            #+#    #+#             */
/*   Updated: 2025/03/05 17:52:17 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
pid_t pid_g = 0;
void    putnbr(pid_t n)
{
    char c;
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

void    putstr(char *str)
{
    while (*str)
        write(1, str++, 1);
}

void sig_handler(int signum, siginfo_t *info, void *nul)
{
    static char nm = 1;
    static int byte = 1;
    static char res = 0;
    static pid_t pid = -1;
    if (pid != info->si_pid && pid != -1)
    {
        nm = 1;
        byte = 1;
        res = 0;
    }
    pid = info->si_pid;
    if (SIGUSR2 == signum)
        res += nm;
    if (byte == 8)
    {
        write(1, &res ,1);
        byte = 0;
        nm = 1;
        res = 0;
    }
    byte++;
    if (byte == 1)
        nm = 1;
    else
        nm *= 2;
    kill(pid, SIGUSR1);
}

int main()
{
    pid_t pid = getpid();
    struct sigaction sa;
    sa.sa_sigaction = sig_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    putstr("PID: ");
    putnbr(pid);
    putstr("\n");
    while(1);
    return (0);
}
