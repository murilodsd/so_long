/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:18:53 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/24 10:36:08 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
static void ft_printstringlst(t_list *head)
{
	t_list *temp = head;
	
	if (!head)
		printf("Lista inexistente\n");
	else
	{
	while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	printf("\n");
	}
}

int main(int argc, char const *argv[])
{
	char 	**matrix;

	t_mem_allocation mem_allocation;
	char *string1;
	char *string2;
	char *string3;

	mem_allocation.matrix_mem_list = NULL;
	mem_allocation.ptr_mem_list = NULL;
	matrix = ft_split("texto.texto2.texto3",'.');
	ft_check_mem_alloc(&mem_allocation, &(mem_allocation.matrix_mem_list),matrix,"ft_split failed");
	matrix = ft_split("texto.texto2.texto3",'.');
	ft_check_mem_alloc(&mem_allocation, &(mem_allocation.matrix_mem_list),matrix,"ft_split failed");
	(void)argc;
	(void)argv;

	string1 = ft_strdup("string1");
	ft_check_mem_alloc(&mem_allocation,&(mem_allocation.ptr_mem_list),string1,"erro");
	string2 = ft_strdup("string2");
	ft_check_mem_alloc(&mem_allocation,&(mem_allocation.ptr_mem_list),string2,"erro");
	string3 = ft_strdup("string3");
	ft_check_mem_alloc(&mem_allocation,&(mem_allocation.ptr_mem_list),string3,"erro");
	
	ft_printstringlst((mem_allocation.ptr_mem_list));
	// ft_printf(1,"%s\n",matrix[0]);
	// ft_printf(1,"%s\n",*(char **)(mem_allocation.matrix_mem_list->content));
	
	
	if (mem_allocation.ptr_mem_list != NULL)	
		ft_lstclear(&(mem_allocation.ptr_mem_list),free);
	if (mem_allocation.matrix_mem_list != NULL)	
		ft_lstclear(&(mem_allocation.matrix_mem_list),ft_free_matrix);
	//ft_printf(1, "matrix está apontando para %p", matrix);
	return 0;
}
