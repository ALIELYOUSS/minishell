/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:30:19 by alel-you          #+#    #+#             */
/*   Updated: 2024/11/11 22:53:52 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	tmp;

	if (fd < 0)
		return ;
	tmp = n;
	if (tmp == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (tmp < 0)
	{
		ft_putchar_fd('-', fd);
		tmp = -tmp;
	}
	if (tmp > 9)
	{
		ft_putnbr_fd(tmp / 10, fd);
	}
	ft_putchar_fd((tmp % 10) + '0', fd);
}
