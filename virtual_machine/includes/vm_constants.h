/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_constants.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/08/28 21:33:41 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_CONSTANTS_H
# define VM_CONSTANTS_H

# define INIT_VECTOR_SIZE 256
# define INIT_CARRIAGES_COUNT 4096
# define INIT_SORT_BUF_SIZE 100000
# define INIT_SORT_RANGES_COUNT 3000

/*
**					FLAGS_DEFINES
*/
# define DUMP				1u
# define AFF_ON				2u

/*
**					OCTET_OP DEFINES
*/
# define OCT00				((PPC(1) & 0b11000000) >> 6)
# define OCT01				((PPC(1) & 0b00110000) >> 4)
# define OCT02				((PPC(1) & 0b00001100) >> 2)

/*
**					CHECK_VALUE DEFINES
*/
# define R_T(x)				(x == REG_CODE)
# define D_T(x) 			(x == DIR_CODE)
# define I_T(x) 			(x == IND_CODE)
# define DI_T(x)			(x == DIR_CODE || x == IND_CODE)
# define RD_T(x)			(x == REG_CODE || x == DIR_CODE)
# define RI_T(x)			(x == REG_CODE || x == IND_CODE)
# define RDI_T(x)			(x == REG_CODE || x == DIR_CODE || x == IND_CODE)

# define IS_REG(x)			(x > 0 && x < 17)

/*
**					OPERATION DEFINES
*/
# define SHIFT(x)			((PC + x) % MEM_SIZE)
# define ISHIFT(x)			((PC + x % IDX_MOD) % MEM_SIZE)

# define PPC(x)				area->map[(PC + x) % MEM_SIZE]
# define PREG(x)			process->reg[x - 1]

/*
**					PROCESS STRUCT DEFINES
*/
# define PC					process->pc
# define CARRY				process->carry

# define MAP				area->map
# define TIMELINE_SIZE		1001

# define SDIE_CYCLE			area->g_stats.cycle_to_die
# define SDIE_CYCLE_DELTA	area->g_stats.cycle_to_die_delta
# define SNOT_CHANGED		area->g_stats.not_changed_checks
# define SLIVES_IN_ROUND	area->g_stats.lives_in_round
# define SDUMP_CYCLE		area->g_stats.cycle_to_dump
# define SN_PLAYERS			area->g_stats.n_players
# define SN_PROCESS			area->g_stats.n_processes

# define PRS_KEY(x)			(((t_pair *)(x))->key)
# define PRS_VALUE(x)		((t_process *)(((t_pair *)(x))->value))

/*
**					VERSION DEFINES
*/
# if defined(COREWAR_VERSION)
#  if COREWAR_VERSION == 2018
#   define OP_1 (result)
#   define OP_2 (get32(area, process, get16(area, process, shift)))
#  else
#   define OP_1 ((result >> 16) & 0xFFFF)
#   define OP_2 (get32(area, process, get16(area, process, shift) % IDX_MOD))
#  endif
# else
#  define OP_1 ((result >> 16) & 0xFFFF)
#  define OP_2 (get32(area, process, get16(area, process, shift) % IDX_MOD))
# endif

/*
**					OP.H DEFINES
*/

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_PLAYERS			4

# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xea83f3

#endif
