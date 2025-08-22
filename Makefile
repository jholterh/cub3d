# Compiler
CC = cc

# Flags
CFLAGS = #-Wall -Werror -Wextra 

# Directories
HEADER_DIR = includes
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft

# Libraries
LIBS = -L$(LIBFT_DIR) -lft

# Source files
SRC = src/parsing/1_file_format.c src/parsing/utils.c src/cub3d.c src/parsing/0_start.c \
	src/parsing/extract_utils.c \
    src/parsing/texture_parsing.c \
    src/parsing/grid_utils.c \
    src/parsing/color_utils.c \
    src/parsing/map_building.c \
    src/parsing/flood_fill_utils.c \
    src/parsing/validation_utils.c \
	src/parsing/free_functions.c \
	src/parsing/flood_fill.c \
	src/parsing/texture_logic.c \
	src/parsing/texture_check.c

# Object files (replace src/ with obj/)
OBJ = $(SRC:src/%.c=obj/%.o)

# Executable name
NAME = cub3d

# Include directories
INCLUDES = -I$(HEADER_DIR)

# Rules
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
