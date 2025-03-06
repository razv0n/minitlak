/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:51:37 by mfahmi            #+#    #+#             */
/*   Updated: 2025/03/06 16:00:30 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

volatile int ack = 0;
pid_t      ft_atoi(char *str)
{
    pid_t pid = 0;
    while (*str == ' ' || (*str > 9 && *str < 13))
        str++;
    while (*str)
    {
        pid = pid * 10 + (*str - '0');
        str++;
    }
    return pid;
}

char    *asci_to_binary(char a)
{
    int nm = a;
    int i;
    char *binary = malloc(9 * sizeof(char));
    if (!binary)
        exit(1);
    i = 0;
    binary[8] = '\0';
    while (i < 8)
    {
        binary[i] = '0';    
        i++;
    }
    i = 0;
    while (nm > 0)
    {
        binary[i] = nm % 2 + '0';
        nm /= 2;
        i++;
    }
    return (binary);
}

void    handler(int signum)
{
    if (signum == SIGUSR1)
        ack = 1;
    if (signum == SIGUSR2)
        write(1, "DONE\n", 6);
}

void    send_char(char a, pid_t pid_server)
{
    int j;
    char *binary;

    binary = asci_to_binary(a);
    j = 0;
    while (binary[j])
    {
        if (binary[j] == '0')
            kill(pid_server, SIGUSR1);
        else
            kill(pid_server, SIGUSR2);
        while(!ack);
        ack = 0;
        j++;
    }
    free(binary);
}

int main(int ac, char **av)
{
    if (ac == 3)
    {
        struct sigaction sa;
        int i;
        pid_t pid_server = ft_atoi(av[1]);
        if (kill(pid_server, 0) == -1)
            return 1;
        i = 0;
        sa.sa_handler = handler;
        sigaction(SIGUSR1, &sa, NULL);
        sigaction(SIGUSR2, &sa, NULL);
        while(av[2][i])
        {
            send_char(av[2][i], pid_server);
            i++;
        }
        send_char('\0', pid_server);
    }
}
