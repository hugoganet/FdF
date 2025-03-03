# Name of the output executable
NAME = fdf

# Path to the libft directory
LIBFT_DIR = libft
# Name of the libft static library
LIBFT = $(LIBFT_DIR)/libft.a

# Directory containing Fdf source files
SRC_DIR = src
# Source files for Fdf
SRC_FILES = draw.c parse_map.c main.c
# Full path to the source files
SRCS := $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Directory where the object files will be stored
OBJ_DIR = obj
# Full path to object files, replacing .c with .o
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Include directory for header files
# - -I flag tells the compiler where to look for header files
# - `includes` contains Fdf headers
# - `$(LIBFT_DIR)` is for libft headers
INCLUDES = -Iincludes -I$(LIBFT_DIR)/includes -Iminilibx_macos


# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Linker flags
LDFLAGS = -Lminilibx_macos -lmlx -framework AppKit -framework Metal -framework OpenGL

# Default rule: Build the executable
all: $(NAME)

# Rule to build the libft library by invoking its Makefile
# -C flag tells make to change to the directory containing the Makefile before building
# This is necessary because the libft Makefile uses relative paths
$(LIBFT):
	@echo "Building libft..."
	$(MAKE) -C $(LIBFT_DIR)

# Rule to compile source files into object files
# -c flag tells the compiler to compile the source file without linking
# - $< is the first dependency (the source file)
# - $@ is the target (object file)
# - @mkdir -p $(OBJ_DIR)  (Ensure the object directory exists)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to link the object files into the final executable
# -L flag tells the linker where to look for the libft library
# -lft flag tells the linker to link against the libft library
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -L$(LIBFT_DIR) -lft

# Rule to clean object files
clean:
	@echo "Cleaning object files..."
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

# Rule to clean the executable and object files
fclean: clean
	@echo "Cleaning $(NAME)..."
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# Rule to recompile everything
re: fclean all

# Rule for bonus part (placeholder)
bonus:
	@echo "Bonus part here"

# Phony targets to avoid conflicts with files of the same name
.PHONY: all clean fclean re bonus
