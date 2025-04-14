SRC_DIR = /src


SRC_DIR_PARSING = $(SRC_DIR)/parsing
SRC_DIR_PARSING_MAP = $(SRC_DIR_PARSING)/map
SRC_DIR_PARSING_FILE = $(SRC_DIR_PARSING)/file
SRC_DIR_PARSING_ELEMENTS = $(SRC_DIR_PARSING)/elements
SRC_PARSING = $(SRC_DIR_PARSING)/parsing.c \
			$(SRC_DIR_PARSING)/errors.c \
			$(SRC_DIR_PARSING)/parsing_utils.c \
			$(SRC_DIR_PARSING)/check_args_extension.c \
			$(SRC_DIR_PARSING_MAP)/check_characters.c \
			$(SRC_DIR_PARSING_MAP)/check_desc_map.c \
			$(SRC_DIR_PARSING_MAP)/check_player.c \
			$(SRC_DIR_PARSING_MAP)/check_walls.c \
			$(SRC_DIR_PARSING_MAP)/parse_desc_map.c \
			$(SRC_DIR_PARSING_FILE)/check_file.c \
			$(SRC_DIR_PARSING_FILE)/parse_file.c \
			$(SRC_DIR_PARSING_ELEMENTS)/check_color.c \
			$(SRC_DIR_PARSING_ELEMENTS)/check_texture.c \
			$(SRC_DIR_PARSING_ELEMENTS)/check_elements.c \
			$(SRC_DIR_PARSING_ELEMENTS)/parse_elements.c 

SRC_DIR_INIT = $(SRC_DIR)/init
SRC_INIT = $(SRC_DIR_INIT)/map.c \
		$(SRC_DIR_INIT)/key_val.c \
	
SRC_DIR_DEBUG = $(SRC_DIR)/debug
SRC_DEBUG = $(SRC_DIR_DEBUG)/map.c \
		$(SRC_DIR_DEBUG)/key_val.c \

SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/calculation_utils.c \
	$(SRC_DIR)/distance_calculation.c \
	$(SRC_DIR)/intersection_check.c \
	$(SRC_DIR)/ray_calculation.c \
	$(SRC_DIR)/raycasting.c \
	$(SRC_DIR)/wall_calculation.c \
	$(SRC_DIR)/draw_line.c \
	$(SRC_DIR)/minimap.c \
	$(SRC_DIR)/keyhook.c \
	$(SRC_PARSING) \
	$(SRC_INIT) \
	$(SRC_DEBUG) \


ALLDIR = $(OBJ_DIR) \
		$(OBJ_DIR)$(SRC_DIR) \
		$(OBJ_DIR)$(SRC_DIR_DEBUG) \
		$(OBJ_DIR)$(SRC_DIR_INIT) \
		$(OBJ_DIR)$(SRC_DIR_PARSING) \
		$(OBJ_DIR)$(SRC_DIR_PARSING_MAP) \
		$(OBJ_DIR)$(SRC_DIR_PARSING_FILE) \
		$(OBJ_DIR)$(SRC_DIR_PARSING_ELEMENTS) \
		
OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
CC = cc
MLX_FLAGS = -ldl -lglfw -pthread -lm
CFLAGS += -g -Isrc -Ilib/MLX42/include/MLX42
# CFLAGS += -Wall -Wextra -Werror -g -Isrc -Ilib/MLX42/include/MLX42
NAME = cub3D

LIB_DIR = ./lib
MLX42_DIR = $(LIB_DIR)/MLX42
MLX42_DIR_BUILD = $(MLX42_DIR)/build
MLX42 = $(MLX42_DIR_BUILD)/libmlx42.a
MYLIB42_DIR = $(LIB_DIR)/MYLIB42
MYLIB42 = $(MYLIB42_DIR)/mylib42.a

all : $(NAME)

$(ALLDIR):
	mkdir $@

$(OBJ): $(OBJ_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -c $(<) -o $(@)

$(NAME) : $(MLX42) $(MYLIB42) $(ALLDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX42) $(MLX_FLAGS) $(MYLIB42) -o $(NAME)

$(MLX42_DIR) :
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR)
	
$(MYLIB42_DIR) :
	git clone https://github.com/Nvnrs/MYLIB42.git $(MYLIB42_DIR)

$(MLX42) : $(MLX42_DIR)
	cmake $(MLX42_DIR) -B $(MLX42_DIR_BUILD)
	$(MAKE) -C $(MLX42_DIR_BUILD)

$(MYLIB42) : $(MYLIB42_DIR)
	$(MAKE) -C $(MYLIB42_DIR)

#test : $(MLX42_DIR)
#	$(MLX42)

clean :
	rm -rf $(OBJ)
	$(MAKE) clean -C $(MYLIB42_DIR)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(LIB_DIR)

re : fclean all

PHONY : clean fclean re all