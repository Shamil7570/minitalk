/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:34:31 by medeana           #+#    #+#             */
/*   Updated: 2021/11/23 19:42:43 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	if (s)
	{
		if (fd >= 0)
		{
			while (s[i] != '\0')
			{
				write(fd, &s[i], 1);
				i++;
			}
		}
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{	
	int		num;
	char	s[10];

	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (n == 0)
		write(1, "0", 1);
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	num = 0;
	while (n > 0)
	{
		s[num] = n % 10 + '0';
		n = n / 10;
		num++;
	}
	num--;
	while (num >= 0)
	{
		write(1, &s[num], 1);
		num--;
	}
}

void	get_message(int signum, siginfo_t *siginfo, void *context)
{
	static unsigned char	out_char;
	static int				counter;
	static int				pid1;

	(void)context;
	if (pid1 != siginfo->si_pid)
	{
		out_char = 0;
		counter = 128;
		pid1 = siginfo->si_pid;
	}
	if (signum == SIGUSR1)
		out_char += counter;
	counter /= 2;
	if (counter == 0)
	{
		ft_putchar(out_char);
		out_char = 0;
		counter = 128;
	}
	usleep(130);
	if (kill(pid1, SIGUSR1) == -1)
	{
		ft_putstr_fd("error", 1);
	}
}

int	main(void)
{
	struct sigaction	sig;
	int					pid;

	write(1, "PID: ", 5);
	ft_putnbr_fd(pid = getpid(), 1);
	write(1, "\n", 1);
	sig.sa_sigaction = get_message;
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, 0);
	sigaction(SIGUSR2, &sig, 0);
	while (1)
		pause();
	return (0);
}
