/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:15:08 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/03/26 18:31:59 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Deletes and frees the given element and every successor
 * of that element, using the function ’del’ and free(3).
 * Finally, the pointer to the list must be set to NULL.
 */

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;

	ptr = *lst;
	while (ptr)
	{
		ptr = ptr->next;
		if ((*lst)->next != NULL)
			(*lst)->next = NULL;
		ft_lstdelone(*lst, del);
		*lst = ptr;
	}
	free(ptr);
}
