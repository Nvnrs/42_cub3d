SRC_DIR = /src

SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/calculation_utils.c \
	$(SRC_DIR)/distance_calculation.c \
	$(SRC_DIR)/intersection_check.c \
	$(SRC_DIR)/ray_calculation.c \
	$(SRC_DIR)/raycasting.c \
	$(SRC_DIR)/wall_calculation.c \
	$(SRC_DIR)/draw_line.c \
	$(SRC_DIR)/minimap.c


ALLDIR = $(OBJ_DIR) \
		$(OBJ_DIR)$(SRC_DIR)
		
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