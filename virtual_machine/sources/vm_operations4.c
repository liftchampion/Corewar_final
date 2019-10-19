/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:51:10 by axtazy            #+#    #+#             */
/*   Updated: 2019/08/29 13:23:47 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		get_op(t_area *area, t_process **carr)
{
	t_process *const	process = *carr;
	const unsigned char	byte = area->map[process->pc];

	if (byte > 0 && byte < 17)
	{
		process->f = g_ops[byte].f;
		process->sleep = g_ops[byte].sleep;
	}
	else
	{
		process->f = g_ops[0].f;
		process->sleep = g_ops[0].sleep;
	}
}

void		lfork_op(t_area *area, t_process **carr)
{
	int32_t		result;
	t_process	*process;
	int			process_id;
	t_process	backup;

	process = *carr;
	process_id = process->ordinal_number;
	backup = *process;
	result = get16(area, process, 1);
	new_process(area, &backup, result);
	process = area->carriages->data + process_id;
	PC = SHIFT(3);
	process->f = get_op;
	process->sleep = 1;
	*carr = process;
}

void		aff_op(t_area *area, t_process **carr)
{
	t_process *const	process = *carr;

	if (R_T(OCT00) && IS_REG(PPC(2)) && (area->flags & AFF_ON))
	{
		ft_printf("Aff: %c\n", (char)PREG(PPC(2)));
	}
	PC = SHIFT(2 + shift_size(PPC(1), 1, 4));
	process->f = get_op;
	process->sleep = 1;
}
