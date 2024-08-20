/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:26:58 by mde-souz          #+#    #+#             */
/*   Updated: 2024/07/01 17:13:44 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  atoi() function converts the initial portion of the string pointed
to by nptr to int. */

#include "libft.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

long	ft_atoi(const char *nptr)
{
	long	n;
	long	signal;

	signal = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		nptr++;
		signal = -1;
	}
	n = 0;
	while (ft_isdigit(*nptr))
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * signal);
}
/* #include <stdio.h>
int	main(void)
{
	printf("%d\n",ft_atoi("5"));
	printf("%d\n",ft_atoi("0"));
	printf("%d\n",ft_atoi(""));
	printf("%d\n",ft_atoi("22a"));
	printf("%d\n",ft_atoi("a22a"));
	printf("%d\n",ft_atoi("    -22a"));
	printf("%d\n",ft_atoi("+22a"));
	printf("%d\n",ft_atoi("2147483647"));
	printf("%d\n",ft_atoi("-2147483648"));
} */