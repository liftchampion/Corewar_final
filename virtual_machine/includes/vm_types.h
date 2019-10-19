/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/08/30 14:30:08 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_TYPES_H
# define VM_TYPES_H

# include "libft.h"
# include "vm_constants.h"
# include <stdbool.h>
# include <stdint.h>

typedef struct s_process			t_process;
typedef struct s_player				t_player;
typedef struct s_cor_file			t_cor_file;
typedef struct s_area				t_area;
typedef struct s_ops				t_ops;
typedef struct s_game_condition		t_gcond;

typedef struct	s_vm_vector_int
{
	int32_t		*data;
	uint32_t	len;
	uint32_t	capacity;
}				t_vm_vector_int;

typedef struct	s_vm_vector_prc
{
	t_process	*data;
	int32_t		len;
	int32_t		capacity;
}				t_vm_vector_prc;

typedef struct	s_timsort_rng
{
	uint32_t	beg;
	uint32_t	len;
}				t_timsort_rng;

typedef struct	s_vm_vector_rng
{
	t_timsort_rng	*data;
	uint32_t		len;
	uint32_t		capacity;
}				t_vm_vector_rng;

struct			s_process
{
	uint32_t		pc;
	uint32_t		sleep;
	int32_t			reg[REG_NUMBER];
	bool			carry;
	int32_t			n_lives;
	uint32_t		ordinal_number;
	void			(*f)(t_area*, t_process**);
};

struct			s_player
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	uint32_t		ordinal_number;
	uint32_t		start_pos;
};

struct			s_cor_file
{
	char			*file_name;
	int32_t			champ_index;

	int32_t			fd;
	int32_t			code_size;
};

struct			s_game_condition
{
	int32_t			cycle_to_die_delta;
	int32_t			cycle_to_die;
	int32_t			not_changed_checks;

	int32_t			lives_in_round;

	int32_t			cycle_to_dump;

	uint32_t		n_players;
	uint32_t		n_processes;

	uint32_t		next_process_index;

};

struct			s_area
{
	t_vm_vector_prc *carriages;
	uint8_t			*map;
	t_gcond			g_stats;

	t_player		*players;
	t_vm_vector_int	*time;

	uint32_t		flags;
	int32_t			win;

	int32_t			n_die_cycle;

	int32_t			current_index;
};

struct			s_ops
{
	char		name[6];
	int32_t		sleep;
	void		(*f)(t_area*, t_process**);
};

#endif
