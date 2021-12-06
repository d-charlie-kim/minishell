/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind_node_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 03:48:17 by jaejeong          #+#    #+#             */
/*   Updated: 2021/07/06 17:44:35 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind_node(t_list *lst, int index)
{
	int	i;

	if (ft_lstsize(lst) <= index)
		return (0);
	i = 0;
	while (i < index)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
