cmake_minimum_required(VERSION 3.14)
project(asm C)

set(CMAKE_C_STANDARD 99)

find_library(OPEN_GL OpenGl)
find_library(APP_KIT AppKit)
link_libraries(mlx)

add_compile_options(-Wall -Wextra)

include_directories(./libft/includes)
FILE(GLOB LIBFT_SRCS ./libft/*.c ./libft/*/*.c)

add_executable(asm srcs/main.c ${LIBFT_SRCS} srcs/ft_utils.c srcs/parser.c
               srcs/globals.c srcs/ft_parse_header.c srcs/ft_champ.c
               srcs/ft_header_utils.c libft/ft_str/ft_skip_spaces.c srcs/ft_translator.c srcs/ft_flags.c srcs/ft_find_s_h_flags.c srcs/ft_flag_parse_utils.c srcs/ft_freeshers.c srcs/ft_compile.c srcs/ft_labels_parse.c srcs/ft_args_parse.c srcs/ft_cmds_parse.c)

target_link_libraries(asm ${OPEN_GL} ${APP_KIT})