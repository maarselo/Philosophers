NAME = philo

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

HEADER = $(INCLUDE_DIR)/philosophers.h

SRC_FILES = main.c 
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

CC = cc -g
CFLAGS = -Wall -Werror -Wextra -I$(INCLUDE_DIR)
RM = rm -rf

# Colores
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) Makefile
	@echo "$(GREEN)✔ Compilando $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)   Compilación completada!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compilando $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED)  Limpiando objetos...$(RESET)"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(RED)  Borrando ejecutables...$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re