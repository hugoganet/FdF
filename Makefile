# Name of the output executable
NAME = fdf

# Path to the libft directory
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# MLX
MLX_DIR = minilibx-linux

# Source structure
SRC_DIR = src

SRC_SUBDIRS = \
	$(SRC_DIR)/drawing \
	$(SRC_DIR)/parsing \
	$(SRC_DIR)/UX

SRC_FILES = \
	main.c \
	free_and_exit.c \
	events.c \
	color.c \
	draw.c \
	draw_utils.c \
	image.c \
	line.c \
	transform.c \
	parse_map.c \
	parse_utils.c

# Prefixed source paths
SRCS = $(foreach dir, $(SRC_SUBDIRS), $(wildcard $(dir)/*.c))
SRCS += src/main.c

# Object directory and paths
OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Include directories
INCLUDES = -Iincludes -I$(LIBFT_DIR)/includes -I$(MLX_DIR)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

# Default rule
all: $(NAME)

# Compile libft
$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR)

# Compile rule for .o files in mirrored structure under obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Linking rule
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

# Clean object files
clean:
	@echo "Cleaning object files..."
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

# Clean everything
fclean: clean
	@echo "Cleaning $(NAME)..."
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

# Rebuild everything
re: fclean all

bonus:
	@echo "Bonus part here"

.PHONY: all clean fclean re bonus
