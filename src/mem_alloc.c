/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:18:53 by mde-souz          #+#    #+#             */
/*   Updated: 2024/08/21 17:54:04 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(void	*matrix_address_void)
{
	char	**matrix_address;
	int		i;

	matrix_address = (char **)matrix_address_void;
	if (!matrix_address)
		return ;
	i = 0;
	while (matrix_address[i])
	{
		free(matrix_address[i]);
		matrix_address[i] = NULL;
		i++;
	}
	free(matrix_address);
}

void	exit_error_free(t_mem_allocation *mem_allocation, char *error_msg)
{
	if (errno)
		ft_printf(2, "Error\n%s: %s\n", error_msg, strerror(errno));
	else
		ft_printf(2, "Error\n%s\n", error_msg);
	get_next_line(-1);
	if (mem_allocation->ptr_mem_list != NULL)	
		ft_lstclear(&(mem_allocation->ptr_mem_list),free);
	if (mem_allocation->matrix_mem_list != NULL)	
		ft_lstclear(&(mem_allocation->matrix_mem_list),ft_free_matrix);
	exit(EXIT_FAILURE);
}

void	save_pointer(t_mem_allocation *mem_allocation, t_list **ptr_or_matrix_list, void *ptr)
{
	t_list	*new_node;
/* 	int		i;

	if (ptr_type == TYPE_POINTER)
	{
		i = 0;
		while(((void **)ptr)[i])
		{
			new_node = ft_lstnew(ptr);
			if (!new_node)
				exit_error_free(ptr_mem_list, "Failed to allocate mem for a node");
			ft_lstadd_back(ptr_mem_list, new_node);
			free(new_node);
			i++;
		} 
	} */
	new_node = ft_lstnew(ptr);
	if (!new_node)
		exit_error_free(mem_allocation, "Failed to allocate mem for a node");
	ft_lstadd_back(ptr_or_matrix_list, new_node);
}
void	check_mem_alloc(t_mem_allocation *mem_allocation, t_list **ptr_or_matrix_list, void *ptr, char *error_msg)
{
	if (!ptr)
		exit_error_free(mem_allocation, error_msg);
	else
		save_pointer(mem_allocation, ptr_or_matrix_list, ptr);
}


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
	check_mem_alloc(&mem_allocation, &(mem_allocation.matrix_mem_list),matrix,"ft_split failed");
	matrix = ft_split("texto.texto2.texto3",'.');
	check_mem_alloc(&mem_allocation, &(mem_allocation.matrix_mem_list),matrix,"ft_split failed");
	(void)argc;
	(void)argv;

	string1 = ft_strdup("string1");
	check_mem_alloc(&mem_allocation,&(mem_allocation.ptr_mem_list),string1,"erro");
	string2 = ft_strdup("string2");
	check_mem_alloc(&mem_allocation,&(mem_allocation.ptr_mem_list),string2,"erro");
	string3 = ft_strdup("string3");
	check_mem_alloc(&mem_allocation,&(mem_allocation.ptr_mem_list),string3,"erro");
	
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
