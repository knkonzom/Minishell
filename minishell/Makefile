NAME		=	minishell
CC			=	gcc
INCLUDES	= 	-I ./includes -I ./libft/includes/
LIBFT		= 	libft/libft.a
SRCS		= 	./srcs/main.c\
				./srcs/environ.c\
				./srcs/env.c\
				./srcs/setenv.c\
				./srcs/unsetenv.c\
				./srcs/cd.c\
				./srcs/echo.c\
				./srcs/error.c\
				./srcs/exec.c\
				./srcs/exit.c\
				./srcs/helper.c\
				./srcs/signal_handler.c\

OPTIONS		= 	-Wall -Wextra -Werror
RM			= 	rm -rf

$(NAME):
	@make -C libft
	@$(CC) $(SRCS) $(INCLUDES) $(LIBFT) -o $(NAME) $(OPTIONS)
	@echo "\nMinishell has been built.\n"

clean:
	@make -C libft fclean

fclean: clean
	@$(RM) $(NAME)
	@echo "Minishell has been removed."
	@echo "---------------------------"

re: fclean all

all: $(NAME)

