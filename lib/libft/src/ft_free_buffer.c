/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:30:52 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/19 16:51:56 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Frees the memory dynamic allocated in a buffer.
 *
 * This function frees the memory dynamic allocated in a buffer by iterating through
 * each element and calling the `free` function. It also sets each element to
 * `NULL` after freeing the memory.
 *
 * @param buffer The buffer to be freed.
 * @param size The size of the buffer.
 */
#include "libft.h"

void	ft_free_buffer(char **buffer, int size)
{
	int	i;
	
	i = 0;	
	while (i < size)
	{
		if (buffer[i])
		{
			free(buffer[i]);
			buffer[i] = NULL;
		}
		i++;
	}
}