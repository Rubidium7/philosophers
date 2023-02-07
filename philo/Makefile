NAME = philo

C_GREEN=\033[0;32m
C_RED=\033[0;31m
C_BLUE=\033[0;34m
C_END=\033[0m

SRC_PATH = src
OBJ_PATH = obj

SRC_NAME = main.c the_feast.c input_validation.c libft_functions.c list_utils.c utils.c 
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@cc -o $@ $^
	@echo "$(C_GREEN)$@ created$(C_END)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) 2> /dev/null
	@cc -Wall -Werror -Wextra -pthread -o $@ -c $<
	@echo "$(C_BLUE)object file created$(C_END)"

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "$(C_RED)object files removed$(C_END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(C_RED)$(NAME) removed$(C_END)"

re: fclean all
