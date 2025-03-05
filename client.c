/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:51:37 by mfahmi            #+#    #+#             */
/*   Updated: 2025/03/05 17:48:42 by mfahmi           ###   ########.fr       */
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
}

int main(int ac, char **av)
{
    if (ac == 3)
    {
        struct sigaction sa;
        int i = 0;
        int j;
        char *binary;
        pid_t pid_server = ft_atoi(av[1]);
        int a = kill(pid_server, 0);
        if (a == -1)
            return 1;// -1 if the process does not exist 0 if it exists 
        sa.sa_handler = handler;
        sigaction(SIGUSR1, &sa, NULL);
        sigaction(SIGUSR2, &sa, NULL);//for succ message
        while(av[2][i])
        {
            binary = asci_to_binary(av[2][i]);
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
            i++;
        }
    }
}
