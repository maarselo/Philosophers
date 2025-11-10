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

NAME=philo

SRC_DIR=src
#BONUS_DIR=bonus
OBJ_DIR=obj
INCLUDE=include

HEADER=$(INCLUDE)/philosophers.h
#HEADER_BONUS=$(INCLUDE)/philosophers_bonus.h

SRCS_FILES=main.c
#BONUS_FILES=

SRC=$(addprefix$(SRC_DIR) /, $(SRCS_FILES))
#SRC_BONUS=(addprefix$(BONUS_DIR) /, $(BONUS_FILES))

OBJS=(addprefix$(OBJ_DIR) /, $(SRCS_FILES:.c=.o))
BOBJS=(addprefix$(OBJ_DIR) /, $(SRCS_BONUS:.c=.o))

CC = cc -g
CFLAGS=-Wall -Werror -Wextra
