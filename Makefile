NAME = cub3D

SRCS = srcs/init.c \
			srcs/get_next_line_utils.c \
			srcs/get_next_line.c \
			srcs/win_init.c \

OBJS = srcs/init.o \
			srcs/get_next_line_utils.o \
			srcs/get_next_line.o \
			srcs/win_init.o \

INCLUDES = -I./includes/*.h

CFLAGS = -Wextra

GCC = gcc 

LIB = libmlx_Linux.a -I./usr/include -L /usr/lib/ -Lmlx_linux -Imlx_linux -lXext -lX11 -lm

RM = rm -f

all: ${NAME}

${NAME}: ${OBJS}
		${RM} ${NAME}
		${GCC} ${CFLAGS} ${OBJS} ${INCLUDES} ${LIB} -o ${NAME}

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: clean fclean re