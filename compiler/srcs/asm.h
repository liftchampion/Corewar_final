/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 21:03:41 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/28 21:03:41 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <sys/stat.h>
# include <zconf.h>
# include <fcntl.h>
# include <stdint.h>
# include "libft.h"
# include "asm.h"

# ifndef MIN_REG_IDX
#  define MIN_REG_IDX 1
# endif
# define IND_SIZE 2
# define REG_SIZE 4
# define DIR_SIZE REG_SIZE
# define REG_CODE 1
# define DIR_CODE 2
# define IND_CODE 3
# define COMMENT_CHAR '#'
# define ALT_CMT_CHAR ';'
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define SEPARATOR_CHAR ','
# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING ".name"
# define COMMENT_CMD_STRING ".comment"
# define T_REG 1u
# define T_DIR 2u
# define T_IND 4u
# define T_LAB 8u
# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3
# define BUFF_SIZE 4096
# define SET_SILENT(flags)	((flags) |= 1u << 0u)
# define SET_HELP(flags)	((flags) |= 1u << 1u)
# define GET_SILENT(flags)	(((flags) & (1u << 0u)) != 0)
# define FRMT(frmt) (g_is_silent ? "" : (frmt))

typedef struct	s_op
{
	char			name[6];
	uint8_t			arg[3];
	uint8_t			need_types_byte;
	uint8_t			short_dir;
	int				namelen;
	int				arg_count;
}				t_op;

typedef enum	e_error
{
	UNEXP_TOKEN = 0,
	SAME_LINE_EXP = 1,
	BAD_BYTE = 2,
	MISSING_PARAM = 3,
	WRONG_CHAR_LBL = 4,
	MISS_LBL_CHAR = 5,
	MULT_LABEL = 6,
	BAD_CMD = 7,
	BAD_ARG = 8,
	BAD_REG_IDX = 9,
	BAD_ARG_COUNT = 10,
	MISSING_SEP = 11,
	EXTRA_SEP = 12,
	MISS_ARG_AFT_PRFX = 13,
	MISS_ARG = 14,
	NM_CMD_WRONG_PLACE = 15,
	BAD_ARG_TYPE = 16,
	UNKNOWN_LAB = 17,
	UNKNOWN_FLAG = 18,
	MISSING_INPUT = 19,
	MISSING_OUTPUT = 20,
	WRG_EXT = 21,
}				t_error;

typedef enum	e_token_type
{
	NAME,
	COMMENT
}				t_token_type;

typedef enum	e_file_type
{
	INPUT = 0,
	OUTPUT = 1
}				t_file_type;

typedef struct	s_cmd
{
	unsigned char	cmd;
	unsigned char	arg_types[3];
	void			*args[3];
	int				lbl_line;
	int				lbl_poses[3];
	int				address;
	int				arg_count;
	int				size;
	int				begin_pos;
}				t_cmd;

typedef struct	s_champ
{
	t_string		*name;
	unsigned int	size;
	t_string		*comment;
	t_string		*res;
	t_vector		*cmds;
	char			*curr_ln;
	int				line;
	char			*file;
	int				fd;
	int				error_count;
	t_map			*labels;
	t_vector		*current_labels;
	int				address;
	t_cmd			*curr_cmd;
}				t_champ;

typedef struct	s_flags
{
	t_vector		*srcs;
	t_vector		*outputs;
	unsigned char	flags;
	t_file_type		file_type;
	unsigned char	is_error;
	unsigned char	was_input;
	char			*out_to_free;
}				t_flags;

extern char		g_wrn_ignored[];
extern char		g_err_missing_out[];
extern char		g_missing_param[];
extern t_op		g_functions[16];
extern char		g_names[][300];
extern t_flags	*g_fls;
extern char		g_exp_same_line[];
extern char		g_help[];
extern char		g_unexp_token[];
extern char		g_mult_label[];
extern char		g_bad_byte[];
extern char		g_miss_arg[];
extern char		g_chars[];
extern char		g_nm_cmd_wrg_place[];
extern char		g_bad_arg_type[];
extern char		*g_errors[];
extern char		g_bad_cmd[];
extern char		g_wrn_wrong_ext[];
extern char		g_extra_sep[];
extern char		g_types[6][30];
extern char		g_backslash_literals[];
extern char		g_usage[];
extern char		g_wrong_char_lbl[];
extern char		g_miss_lbl_chr[];
extern char		g_unknown_lbl[];
extern char		g_pos_before[];
extern char		g_wrn_too_long[];
extern char		g_bad_reg_idx[];
extern char		g_miss_arg_aft_prfx[];
extern char		g_wrn_double[];
extern char		g_wrn_empty[];
extern char		g_bad_arg_count[];
extern char		g_err_unknown_flag[];
extern char		g_is_silent;
extern char		g_missing_sep[];
extern char		g_bad_arg[];
extern char		g_pos[];
extern char		g_err_missing_in[];
extern char		g_nbrs[][4];

/*
** ft_args_parse.c
*/
int				ft_check_arg(t_champ *champ, char **ln, char *begin,
			unsigned int type);
int				ft_get_arg_type(char **ln, t_champ *champ);
void			*ft_get_arg_val(char **ln, unsigned int type,
			t_champ *champ, const char *begin);
void			ft_move_to_next_arg(t_champ *champ, char **ln);
void			ft_check_arg_type_for_op(t_champ *champ, t_cmd *cmd,
			unsigned int type, char *begin);
/*
** ft_champ.c
*/
t_champ			*ft_make_champ(char *file, int fd);
void			ft_champ_upd_line(t_champ *champ, char *line);
/*
** ft_cmds_parse.c
*/
int				ft_is_command(char *line);
int				ft_get_op_size(t_cmd *cmd);
void			ft_parse_command(t_champ *champ, char *ln, int cmd_num);
size_t			ft_find_bad_cmd_len(char *ln);
/*
** ft_compile.c
*/
char			*ft_get_out_name(char *src, char *out);
int				ft_compile_one(char *src, char *out);
int				ft_compile_all(t_flags *fl);
/*
** ft_find_s_h_flags.c
*/
t_flags			*ft_find_s_h_flags(int ac, char const *const *av);
/*
** ft_flag_parse_utils.c
*/
void			ft_output_flag(t_flags *fl);
void			ft_parse_l_flag(char *ln, t_flags *fl);
void			ft_parse_s_flag(char *ln, t_flags *fl);
int				ft_ask(char *que, char *param[3]);
int				ft_isdir(char *name);
/*
** ft_flags.c
*/
void			ft_parse_filename(char *ln, t_flags *fl);
t_flags			*ft_parse_flags(t_flags *fl, int ac, char **av);
/*
** ft_freeshers.c
*/
int				ft_free_champ(t_champ **champ, int ret);
void			ft_free_cmd(void *p);
int				ft_free_flags(t_flags *fl, int ret);
/*
** ft_header_utils.c
*/
void			ft_parse_byte(char **ln, t_string **res, t_champ *champ);
void			ft_parse_backslash(char **ln, t_string **res,
			t_champ *champ);
int				ft_check_empty_string(char *ln, t_champ *champ,
			t_token_type type);
void			ft_skip_line(char *ln, int *qoute_count);
void			ft_skip_string(t_champ *champ, char *ln);
/*
** ft_labels_parse.c
*/
char			*ft_get_lbl_name(t_champ *champ, char **s, char *stop_chars);
void			ft_upd_labels(t_champ *champ);
void			ft_add_label(t_champ *champ, char *lbl);
void			ft_parse_label(t_champ *champ, char *ln);
int				ft_is_lbl(char *ln, t_champ *champ, int is_cmd, int pos);
/*
** ft_parse_header.c
*/
void			ft_parse_header(t_champ *champ, int fd);
void			ft_parse_name_comment(t_champ *champ, char *ln,
			t_token_type type);
int				ft_validate_string(t_champ *champ, char **ln,
			t_token_type type);
void			ft_parse_string(char *ln, t_string **res, t_token_type type,
			t_champ *champ);
int				ft_get_data_from_line(char *ln, t_string **res,
			t_token_type type, t_champ *chmp);
/*
** ft_translator.c
*/
int				ft_translate_to_bytecode(t_champ *champ);
/*
** ft_utils.c
*/
size_t			ft_get_max_len(t_token_type type);
t_flags			*ft_make_flags(void);
void			ft_make_error(t_error type, t_champ *champ, int pos,
			void *args[4]);
unsigned int	ft_get_lbl_arg(t_champ *champ, t_cmd *cmd, int i);
void			ft_check_exist_name_cmt(t_champ *champ);
/*
** parser.c
*/
int				ft_parse_arg(t_champ *champ, t_cmd *cmd, char **ln);
void			ft_check_arg_count(t_champ *champ, t_cmd *cmd);
void			ft_parse_line(t_champ *champ, char *ln);
void			ft_parse_exec(t_champ *champ, int fd);
t_champ			*ft_parser(char *file);
#endif
