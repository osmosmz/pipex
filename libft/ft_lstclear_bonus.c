/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:51:23 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/20 20:00:19 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*current;

	if (lst && del)
	{
		current = *lst;
		while (current)
		{
			temp = current;
			current = current->next;
			ft_lstdelone(temp, del);
		}
		*lst = NULL;
	}
}
