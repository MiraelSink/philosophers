NAME	= philo

CFLAGS	= -Wall -Werror -Wextra -pthread -g

CC	= cc

INC	= -I include/

OBJ_DIR	= obj

SRC	= $(addprefix src/, free.c init.c time.c main.c utils.c routine.c error.c monitor_utils.c)

OBJ	= $(SRC:%.c=$(OBJ_DIR)/%.o)

all		: $(NAME)

$(NAME)		: $(OBJ)
	@$(CC) $(INC) $(CFLAGS) $(OBJ) -o $@
	@echo "\033[0;92mExecutable '"'philo'"' was created successfully\033[0m"

$(OBJ_DIR)/%.o	: %.c
	@mkdir -p '$(@D)'
	@$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean		:
	@rm -rf $(OBJ_DIR)
	@clear
	@echo "\033[0;93mAll objects was suppressed\033[0m"

fclean		: clean
	@rm -rf $(NAME)
	@clear
	@echo "\033[0;91mphilo was suppressed\033[0m"

re		: fclean all

.PHONY		: clean fclean all re
