NAME = cub3D

SRCS = srcs/init.c \
			srcs/win_init.c \
			srcs/ft_utils_1.c \
			srcs/get_next_line.c \
			srcs/get_next_line_utils.c \
			srcs/parsing.c \
			srcs/error.c \
			srcs/parsing_map.c \
			srcs/input.c \

OBJS = srcs/init.o \
			srcs/win_init.o \
			srcs/ft_utils_1.o \
			srcs/get_next_line.o \
			srcs/get_next_line_utils.o \
			srcs/parsing.o \
			srcs/error.o \
			srcs/parsing_map.o \
			srcs/input.o \

INCLUDES = -I/includes/cube.h

CFLAGS = -Wall -Werror -Wextra -g

GCC = gcc 

LIB = libmlx_Linux.a -I./usr/include -L /usr/lib/ -Lmlx_linux -Imlx_linux -lXext -lX11 -lm

RM = rm -f

all: ${NAME}

${NAME}: ${OBJS}
		${GCC} ${CFLAGS} ${INCLUDES} ${OBJS} ${LIB} -o ${NAME}

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: clean fclean re