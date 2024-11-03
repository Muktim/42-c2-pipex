NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_PATH = ./
OBJ_PATH = obj/
LIBFT_PATH = ./LIBFT
LIBFT = $(LIBFT_PATH)/libft

SRC =	pipex.c \
		initialize_data.c \
		input_validate.c \
		parse.c \
		parent_children.c \
		exit_cleanup.c


SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH) all

bonus: all

clean:
	@rm -rf $(OBJ_PATH)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re bonus
