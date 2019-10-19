/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_push_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:27:20 by dwiegand          #+#    #+#             */
/*   Updated: 2019/07/04 17:05:09 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector_assets.h"

void		ft_vector_push_back(t_vector *this, void *elem)
{
	size_t		new_size;
	int			ptr_pos;
	int			end_pos;

	if (V_DATA(this)->end == V_DATA(this)->size)
	{
		new_size = V_DATA(this)->size * 2lu;
		ptr_pos = this->v - V_DATA(this)->begin;
		end_pos = V_DATA(this)->end;
		V_DATA(this)->begin = ft_realloc(V_DATA(this)->begin,
			V_DATA(this)->size * sizeof(void *),
			new_size * sizeof(void *));
		if (V_DATA(this)->begin == NULL)
			ERRF(ERRALLOC);
		V_DATA(this)->size = new_size;
		V_DATA(this)->end = end_pos;
		this->v = V_DATA(this)->begin + ptr_pos;
	}
	this->v[V_DATA(this)->end] = elem;
	V_DATA(this)->end++;
}
