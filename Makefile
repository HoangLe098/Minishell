NAME		= minishell

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

PRINTF_INC	= -I ./printf
PRINTF_LIB	= -L ./printf -lftprintf

LIBFT_INC	= -I ./libft
LIBFT_LIB	= -L ./libft -lft

INCLUDES	= -lreadline

SRCS		= test_parsing.c tokenize.c expand.c parsing.c
OBJS		= $(SRCS:.c=.o)

all: subsystem $(NAME)

subsystem:
	@make -C ./libft all
	@make -C ./printf all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(PRINTF_INC) $(PRINTF_LIB) $(LIBFT_INC) $(LIBFT_LIB) $(INCLUDES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(PRINTF_INC) $(LIBFT_INC) $(INCLUDES) -c $< -o $@

clean:
	make -C libft/ clean
	make -C printf/ clean
	rm -f $(OBJS)

fclean: clean
	make -C libft/ fclean
	make -C printf/ fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
