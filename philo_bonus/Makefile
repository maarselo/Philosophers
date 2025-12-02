# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 13:08:36 by mvillavi          #+#    #+#              #
#    Updated: 2025/11/10 13:08:37 by mvillavi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_bonus

SRC_DIR=src
OBJ_DIR=obj
INCLUDE_DIR=include

HEADER=$(INCLUDE_DIR)/philosophers_bonus.h

SRCS_FILES = main_bonus.c entry_bonus.c  			     \
				parser_bonus.c parser_utils_bonus.c      \
			 	utils_bonus.c free_bonus.c error_bonus.c

SRC=$(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS=$(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))

CC = cc #-lpthread -lrt
CFLAGS = -Wall -Werror -Wextra -I$(INCLUDE_DIR) 
DEBUG_FLAGS = -g -fsanitize=address,leak

MKDIR = mkdir -p
RM = rm -rf

YELLOW=\033[1;33m
RED=\033[1;31m
GREEN=\033[1;32m
BLUE=\033[1;34m
RESET=\033[0m
BULLET = $(BLUE)•$(RESET)
BULLET_RED = $(RED)•$(RESET)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) Makefile
	@$(CC) $(OBJS)  -o $(NAME)
	@echo "$(GREEN)Compilation completed!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)▶ Compiling $(RESET) $<..."

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)
	@echo "$(BULLET) $(BLUE)Created:$(RESET) $@/"

clean :
	@$(RM) $(OBJ_DIR)
	@echo "$(BULLET_RED) $(RED)Cleaning:$(RESET) object files"

fclean : clean
	@$(RM) $(NAME)
	@echo "$(BULLET_RED) $(RED)Removing:$(RESET) $(NAME)"

re : fclean all

run: $(NAME)
	@./$(NAME)

debug: CC+= $(DEBUG_FLAGS)
debug: re
	@echo "$(GREEN)▶ Running $(NAME) with sanitizers...$(RESET)"

valgrind: $(NAME)
	@valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re run run-debug valgrind