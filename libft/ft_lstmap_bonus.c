/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhuang <mzhuang@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:51:07 by mzhuang           #+#    #+#             */
/*   Updated: 2024/05/20 20:10:08 by mzhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*node;
	void	*currentcontent;

	if (lst && f)
	{
		result = NULL;
		while (lst)
		{
			currentcontent = f(lst->content);
			node = ft_lstnew(currentcontent);
			if (!node)
			{
				del(currentcontent);
				ft_lstclear(&result, del);
				return (NULL);
			}
			ft_lstadd_back(&result, node);
			lst = lst->next;
		}
		return (result);
	}
	else
		return (NULL);
}
