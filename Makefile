# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alarose <alarose@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 10:17:33 by alarose           #+#    #+#              #
#    Updated: 2024/06/17 08:58:07 by alarose          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCDIR = ./srcs/
SRC_FILES =		img_manager.c	\
				player_mov.c	\
				map_parsing.c	\
				map_verif.c		\
				main.c			\
#				map_creation_tests.c	\

BONUSDIR = ./
BONUS =

LIBFT_PATH = ./libft/
LIBFT = libft.a
LIBFT_FILE = $(LIBFT_PATH)$(LIBFT)
LIBFT_FLAGS = $(LIBFT_FILE) -L$(LIBFT_PATH) -lft

MINI_LIB_PATH = $(HOME)/sgoinfre/mlx
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
	$(CC) -g3 -ggdb3 $(INCLUDES) -o $@ -c $<

$(LIBFT_FILE) :
	make -C $(LIBFT_PATH)

$(NAME) : $(OBJS) $(LIBFT_FILE)
	$(CC) -g3 -ggdb3 -o $@ $^ $(MLX_FLAGS) $(LIBFT_FLAGS)
#delete this one
#	make clean

clean :
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJS)
	$(RM) $(TESTBINS)
#	$(RM) $(OBJS_BONUS)

fclean : clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re : fclean all

re_test : fclean test

$(TESTDIR)/%.o : $(TESTDIR)/%.c
	$(CC) $(INCLUDES) $< $(OBJS) -g3 -ggdb3 -o $@ $(MLX_FLAGS) $(LIBFT_FLAGS) -I$(HOME)/Criterion/include/criterion -Wl,-rpath=$(HOME)/Criterion/build/src -L$(HOME)/Criterion/build/src -W -lcriterion --verbose

test: $(OBJS) $(LIBFT_FILE) $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

.PHONY: all clean fclean re test