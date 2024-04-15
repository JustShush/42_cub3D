NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES) -g# -fsanitize=address -static-libsan

includefolder = includes/
LIBFT_DIR = libft/
MLX_DIR = .mlx/
MLX = libmlx_Linux.a
LIBFT = $(LIBFT_DIR)/libft.a
LINK_FLAGS = -L $(LIBFT_DIR) -lft -lm -L $(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
INCLUDES = -I $(includefolder) -I $(LIBFT_DIR) -I $(MLX_DIR)

SRC_FOLDER = src/
OBJ_DIR = obj/

SRC_ROOT_FILES = main.c

INCLUDE_HEADERS = $(addprefix $(includefolder), cub3d.h)

FILES = \
	$(SRC_ROOT_FILES)
#$(addprefix b-ins/, $(B-INS_FILES)) \
#$(addprefix ex/, $(EX_FILES)) \
#$(addprefix pl/, $(PARSER_LEXER_FILES))

OBJS = $(addprefix $(OBJ_DIR), $(FILES:%.c=%.o))


# Reset
Color_Off='\033[0m'       # Text Reset

IRed='\033[0;91m'         # Red
IGreen='\033[0;92m'       # Green
IYellow='\033[0;93m'      # Yellow
ICyan='\033[0;96m'        # Cyan

MSG1 = @echo ${IGreen}"Compiled Successfully ✔︎"${Color_Off}
MSG4 = @echo ${IGreen}"Libft Compiled Successfully ✔︎"${Color_Off}
MSG2 = @echo ${IYellow}"Cleaned Successfully ✔︎"${Color_Off}
MSG3 = @echo ${ICyan}"Cleaned ${NAME} Successfully ✔︎"${Color_Off}

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_DIR)$(MLX) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LINK_FLAGS)
	$(MSG1)

$(OBJS): $(OBJ_DIR)%.o: $(SRC_FOLDER)%.c $(INCLUDE_HEADERS)
	@mkdir -p $(OBJ_DIR) $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	@make -s -C $(LIBFT_DIR)
	$(MSG4)

$(MLX_DIR)$(MLX):
	cd $(MLX_DIR) && ./configure

run: all
	@./$(NAME)

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make -s -C $(LIBFT_DIR) clean
	$(MSG2)

fclean: clean
	@/bin/rm -rf $(NAME) ${OBJ_DIR}
	@make -s -C $(LIBFT_DIR) fclean
	@make -s -C $(MLX_DIR) clean
	$(MSG3)

re: fclean all
cb: clean all
