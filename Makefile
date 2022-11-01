# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 12:06:00 by tyuan             #+#    #+#              #
#    Updated: 2021/01/03 10:33:46 by tyuan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

CFILES	= main.c  cam.c	start_rt.c bmp.c color.c \
		  hit.c	 hit_shadow.c	hit_obj.c hit_obj2.c hit_obj3.c \
		  parse_env.c	parse_objets.c parse_objets2.c parse_tools.c\
		  tools_atoi.c tools_vec.c tools_vec2.c tools_vec3.c \
		  tools.c tools2.c tools3.c\
		  event_exit.c event_hook.c event_hook2.c\
		  texture.c texture_uvmap.c

SRCS	= $(addprefix srcs/, ${CFILES})

OBJS	= ${SRCS:.c=.o}

CFILE_B	= start_rt_bonus.c

SRCS_B	= $(addprefix srcs/, ${CFILE_B})

OBJS_B	= ${SRCS_B:.c=.o}

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -I includes/ -I libft/includes/ -I minilibx_mms_20200219

HEADER	= mini_rt.h

RM	= rm -f

all:	${NAME}

${NAME}:
	@make -s -C libft
	@make -s -C minilibx_mms_20200219
	@cp minilibx_mms_20200219/libmlx.dylib .
	@${CC} ${CFLAGS} ${SRCS}  -Llibft -lft -L . -lmlx -o $@

bonus:
	@make -s -C libft
	@make -s -C minilibx_mms_20200219
	@cp minilibx_mms_20200219/libmlx.dylib .
	@${CC} ${CFLAGS} ${SRCS} ${SRCS_B} -Llibft -lft -L . -lmlx -pthread -g -o ${NAME}

clean:
	@make clean -s -C libft
	@make clean -s -C minilibx_mms_20200219
	@${RM} libmlx.dylib
	@${RM} ${OBJS} ${OBJS_B}

fclean: clean
	@make fclean -s -C libft
	@${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re
