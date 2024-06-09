# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alarose <alarose@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 10:17:33 by alarose           #+#    #+#              #
#    Updated: 2024/06/09 17:27:47 by alarose          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCDIR = ./
SRC_FILES = 	sandbox.c	\

BONUSDIR = ./
BONUS = ft_lstnew_bonus.c		\
		ft_lstadd_front_bonus.c	\

LIBFT_PATH = ./
LIBFT = libft.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

MINI_LIB_PATH = /home/alarose/sgoinfre/mlx
MLX_FLAGS = -L$(MINI_LIB_PATH) -lmlx_Linux -lXext -lX11 -I$(MINI_LIB_PATH)

INCLUDES_PATH = ./includes
INCLUDES = -I $(INCLUDES_PATH) -I $(MINI_LIB_PATH)

SRCS = $(addprefix $(SRCDIR), $(SRC_FILES))
BONUS_FILES = $(addprefix $(BONUSDIR), $(BONUS))
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(BONUS_FILES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all : $(NAME)

#insert flags when ready!
%.o : %.c
	$(CC) $(INCLUDES) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(INCLUDES) -o $@ $< $(MLX_FLAGS) $(LIBFT_FLAGS)

clean :
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

bonus :

.PHONY: all clean fclean re bonus