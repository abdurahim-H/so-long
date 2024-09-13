NAME = so_long
CC = cc -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
MLX_PATH = lib/MiniLibX/build/
MLX_REPO = https://github.com/codam-coding-college/MLX42.git
MLX_BUILD_PATH = lib/MiniLibX/build/
MLX = $(MLX_PATH)libmlx42.a -framework OpenGL -framework AppKit -lglfw
SRC_DIR1 = src/
SRC_DIR2 = src/srcs/
OBJ_DIR = obj/
INC_DIR = inc/

# Define colors
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m
ORANGE = \033[1;33m
RESET = \033[0m

SRCS = $(wildcard $(SRC_DIR1)*.c) $(wildcard $(SRC_DIR2)*.c)
OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

all: $(NAME)

$(NAME): $(MLX_PATH)libmlx42.a $(OBJS)
	@echo "$(CYAN)Starting linking process...$(RESET)"
	@echo "$(YELLOW)Linking object files...$(RESET)"
	$(CC) $(OBJS) $(MLX) -o $(NAME)
	@echo "$(GREEN)Linking done. Executable created: $(NAME)$(RESET)"
	@echo "$(CYAN)Linking process finished.$(RESET)"

$(MLX_PATH)libmlx42.a:
	@echo "$(CYAN)Building MiniLibX...$(RESET)"
	@if [ ! -d "lib/MiniLibX" ]; then \
		echo "$(YELLOW)Cloning MiniLibX...$(RESET)"; \
		git clone $(MLX_REPO) lib/MiniLibX; \
	fi
	@cd lib/MiniLibX && cmake -B build && cmake --build build -j4
	@echo "$(GREEN)MiniLibX built successfully.$(RESET)"

$(OBJ_DIR)%.o: %.c
	@echo "$(CYAN)Starting compilation process for $<...$(RESET)"
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@echo "$(BLUE)Compiled $< to $@.$(RESET)"
	@echo "$(CYAN)Compilation process for $< finished.$(RESET)"

clean:
	@echo "$(CYAN)Starting cleaning process...$(RESET)"
	@echo "$(MAGENTA)Cleaning object files...$(RESET)"
	@echo "$(ORANGE)"
	rm -rf $(OBJ_DIR)
	@echo "$(RESET)"
	@echo "$(RED)Cleaning done.$(RESET)"
	@echo "$(CYAN)Cleaning process finished.$(RESET)"

fclean: clean
	@echo "$(CYAN)Starting full cleaning process...$(RESET)"
	@echo "$(MAGENTA)Full cleaning...$(RESET)"
	@echo "$(ORANGE)"
	rm -f $(NAME)
	rm -rf $(MLX_BUILD_PATH)
	@echo "$(RESET)"
	@echo "$(RED)Full cleaning done. Removed executable: $(NAME) and MiniLibX build folder.$(RESET)"
	@echo "$(CYAN)Full cleaning process finished.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
