/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:42:39 by ifreire           #+#    #+#             */
/*   Updated: 2026/06/09 19:12:46 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(long int nb)
{
	size_t	len;

	if (nb < 0)
		nb *= -1;
	len = 1;
	while (nb >= 10)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static char	*ft_negative(long int n)
{
	size_t		len;
	long int	index;
	char		*str;
	long int	nb;

	nb = n;
	nb *= -1;
	len = ft_intlen(nb) + 1;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	index = len - 1;
	while (index > 0)
	{
		str[index] = (nb % 10) + '0';
		nb /= 10;
		index--;
	}
	str[0] = '-';
	str[len] = 0;
	return (str);
}

char	*ft_itoa(int n)
{
	size_t		len;
	char		*str;
	long int	index;

	if (n < 0)
		return (ft_negative(n));
	len = ft_intlen(n);
	index = len - 1;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	while (index >= 0)
	{
		str[index] = (n % 10) + '0';
		n /= 10;
		index--;
	}
	str[len] = 0;
	return (str);
}
