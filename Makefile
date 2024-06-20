# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alarose <alarose@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 10:17:33 by alarose           #+#    #+#              #
#    Updated: 2024/06/12 19:23:52 by alarose          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCDIR = ./
SRC_FILES =		img_manager.c	\
				player_mov.c	\
				map_verif.c		\
				main.c			\
#				map_creation_tests.c	\

BONUSDIR = ./
BONUS =

LIBFT_PATH = ./libft/
LIBFT = libft.a
LIBFT_FILE = $(LIBFT_PATH)$(LIBFT)
LIBFT_FLAGS = $(LIBFT_FILE) -L$(LIBFT_PATH) -lft

MINI_LIB_PATH = /home/alarose/sgoinfre/mlx
MLX_FLAGS = -L$(MINI_LIB_PATH) -lmlx_Linux -lXext -lX11

INCLUDES_PATH = ./includes
INCLUDES = -I$(INCLUDES_PATH) -I$(LIBFT_PATH)

SRCS = $(addprefix $(SRCDIR), $(SRC_FILES))
BONUS_FILES = $(addprefix $(BONUSDIR), $(BONUS))
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(BONUS_FILES:.c=.o)

TESTDIR=./tests
TESTS = $(wildcard $(TESTDIR)/*.c)
TESTBINS = $(TESTS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all : $(NAME)

#insert flags when ready!
./%.o : ./%.c
	$(CC) $(INCLUDES) -o $@ -c $<

$(LIBFT_FILE) :
	make -C $(LIBFT_PATH)

$(NAME) : $(OBJS) $(LIBFT_FILE)
	$(CC) -o $@ $^ $(MLX_FLAGS) $(LIBFT_FLAGS)
#delete this one
	make clean

clean :
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJS)
#	$(RM) $(OBJS_BONUS)

fclean : clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re : fclean all

$(TESTDIR)/%: $(TESTDIR)/%.c
	make $(NAME)
	$(CC) $(INCLUDES) -o $@ $^ $(MLX_FLAGS) $(LIBFT_FLAGS) -lcriterion

test: $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

.PHONY: all clean fclean re test