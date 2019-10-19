/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_delete_elem.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 14:32:27 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 14:47:32 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector_assets.h"

void		ft_vector_delete_elem(t_vector *this, size_t index)
{
	if (!(index < V_DATA(this)->end))
		ERRF("Invalide delete elem index\n");
	if (V_DATA(this)->free != NULL)
		V_DATA(this)->free(&V_DATA(this)->begin[index]);
	V_DATA(this)->begin[index] = NULL;
}
