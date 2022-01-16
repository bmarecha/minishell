SRCS	=	parsing/pa_init.c \
			parsing/pa_check.c \
			parsing/pa_parse.c \
			parsing/pa_signals.c \
			parsing/pa_test.c \
			parsing/pa_utils.c \
			parsing/pa_redirections.c \
			parsing/gnl/get_next_line.c \
			parsing/gnl/get_next_line_utils.c \
			executing/chain_cmd.c \
			executing/built_in.c \
			executing/vne_built_in.c \
			executing/get_cmd.c \
			executing/utils.c

OBJS	=	${SRCS:.c=.o}

NAME	=	minishell

LIBFT = libft/libft.a

INCLUDES = -Ilibft/ \
		-Iparsing/ \
		-Iparsing/get_next_line \
		-Iexecuting/

LIBS = -lft -Llibft/

.c.o	:
	gcc -Wall -Werror -Wextra -c $< ${INCLUDES} -o ${<:.c=.o}

all     :   ${NAME}

$(LIBFT) :
	make -C libft/

$(NAME)	: ${OBJS}
	@make --no-print-directory -C libft
	gcc -g -o ${NAME} ${OBJS} ${INCLUDES} ${LIBS}

clean	:
	rm -f ${OBJS}
	@make --no-print-directory clean -C libft/

fclean	:	clean
	@make --no-print-directory fclean -C libft/
	rm -f ${NAME}

re		: fclean all 

.PHONY	: all clean fclean re
