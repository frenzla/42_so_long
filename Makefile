# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alarose <alarose@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 10:17:33 by alarose           #+#    #+#              #
#    Updated: 2024/06/28 11:36:37 by alarose          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCDIR = ./srcs/
SRC_FILES =		img_manager.c	\
				player_mov.c	\
				map_parsing.c	\
				map_verif.c		\
				map_handler.c	\
				main.c			\
				win_handler.c	\
				map_verif_2.c

BONUSDIR = ./bonuses/
BONUS =		img_manager_bonus.c	\
			player_mov_bonus.c	\
			map_parsing_bonus.c	\
			map_verif_bonus.c	\
			map_handler_bonus.c	\
			main_bonus.c		\
			win_handler_bonus.c	\
			map_verif_2_bonus.c	\
			mov_count_bonus.c

LIBFT_PATH = ./libft/
LIBFT = libft.a
LIBFT_FILE = $(LIBFT_PATH)$(LIBFT)
LIBFT_FLAGS = $(LIBFT_FILE) -L$(LIBFT_PATH) -lft

MINI_LIB_PATH = $(HOME)/sgoinfre/mlx
MLX_FLAGS = -L$(MINI_LIB_PATH) -lmlx_Linux -lXext -lX11

INCLUDES_PATH = ./includes
INCLUDES = -I$(INCLUDES_PATH) -I$(LIBFT_PATH)

SRCS = $(addprefix $(SRCDIR), $(SRC_FILES))
OBJS = $(SRCS:.c=.o)
BONUS_FILES = $(addprefix $(BONUSDIR), $(BONUS))
OBJS_BONUS = $(BONUS_FILES:.c=.o)

TESTDIR=./tests
TESTS = $(wildcard $(TESTDIR)/*.c)
TESTBINS = $(TESTS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all : $(NAME)

./%.o : ./%.c
	$(CC) $(CFLAGS) -g3 -ggdb3 $(INCLUDES) -o $@ -c $<

$(LIBFT_FILE) :
	make -C $(LIBFT_PATH)

$(NAME) : $(OBJS) $(LIBFT_FILE)
	$(CC) $(CFLAGS) -g3 -ggdb3 -o $@ $^ $(MLX_FLAGS) $(LIBFT_FLAGS)

clean :
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJS)
	$(RM) $(TESTBINS)
	$(RM) $(OBJS_BONUS)

fclean : clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re : fclean all

re_test : fclean test

$(TESTDIR)/%.o : $(TESTDIR)/%.c
	$(CC) $(INCLUDES) $< $(OBJS) -g3 -ggdb3 -o $@ $(MLX_FLAGS) $(LIBFT_FLAGS) -I$(HOME)/Criterion/include/criterion -Wl,-rpath=$(HOME)/Criterion/build/src -L$(HOME)/Criterion/build/src -W -lcriterion

test: $(OBJS) $(LIBFT_FILE) $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

bonus : ${OBJS_BONUS} $(LIBFT_FILE)
	$(CC) $(CFLAGS) -g3 -ggdb3 -o $(NAME) $^ $(MLX_FLAGS) $(LIBFT_FLAGS)

.PHONY: all clean fclean re test bonus