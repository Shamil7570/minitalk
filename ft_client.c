/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:06:42 by medeana           #+#    #+#             */
/*   Updated: 2021/11/23 18:31:30 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	handler(int signum)
{
	(void)signum;
}

int	ft_atoi(const char *s)
{
	int		i;
	char	*p;
	int		res;

	i = 0;
	res = 0;
	p = (char *)s;
	while ((s[i] >= 0x09 && s[i] <= 0x0D) || (s[i] == ' '))
		i++;
	if (p[i] == '-' || p[i] == '+')
		i++;
	while (p[i] >= '0' && p[i] <= '9')
	{
		res = (res * 10) + (p[i] - '0');
		i++;
	}
	return (res);
}

void	send_messge(char str, int pid)
{
	int		byte;

	byte = 128;
	while (byte > 0)
	{
		if (str & byte)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		byte /= 2;
		pause();
		usleep(130);
	}
}

int	main(int ac, char **av)
{
	struct sigaction	ab;
	int					pid;
	int					i;

	i = 0;
	if (ac != 3)
	{
		write(1, "ERROR", 5);
		exit(0);
	}
	ab.sa_handler = handler;
	pid = ft_atoi(av[1]);
	sigaction(SIGUSR1, &ab, 0);
	sigaction(SIGUSR2, &ab, 0);
	while (av[2][i])
	{
		send_messge(av[2][i], pid);
		i++;
	}
	return (0);
}
