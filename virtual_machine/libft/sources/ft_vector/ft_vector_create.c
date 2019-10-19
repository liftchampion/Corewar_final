/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:49:35 by dwiegand          #+#    #+#             */
/*   Updated: 2019/08/23 05:10:54 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector_assets.h"

t_vector		*ft_vector_create(size_t n, void (*del)(void **))
{
	t_vector	*p;

	p = NULL;
	if ((p = (t_vector *)malloc(sizeof(t_vector))) == NULL)
		ERRF(ERRALLOC);
	if ((p->data = (struct s_vector_data *)malloc(sizeof(struct s_vector_data)))
			== NULL)
		ERRF(ERRALLOC);
	((struct s_vector_data*)p->data)->begin =
			ft_memalloc(sizeof(void *) * (n + 1));
	if (((struct s_vector_data*)p->data)->begin == NULL)
		ERRF(ERRALLOC);
	((struct s_vector_data*)p->data)->size = n;
	((struct s_vector_data*)p->data)->end = 0;
	((struct s_vector_data*)p->data)->free = del;
	p->v = ((struct s_vector_data*)p->data)->begin;
	p->begin = &ft_vector_begin;
	p->end = &ft_vector_end;
	p->push_back = &ft_vector_push_back;
	p->size = &ft_vector_size;
	p->delete_elem = &ft_vector_delete_elem;
	return (p);
}
