# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 11:22:28 by mde-souz          #+#    #+#              #
#    Updated: 2024/09/12 17:51:58 by mde-souz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CCFLAGS=-Wall -Wextra -Werror -g
NAME=so_long
NAME_BONUS=so_long_bonus
SRC_PATH=src/
SRCS_NAMES=so_long.c map_functions.c keyboard_events.c \
so_long_utils.c animation_functions.c check_map_functions.c \
close_game.c check_mem_alloc.c
SRCS=$(addprefix $(SRC_PATH), $(SRCS_NAMES))
#SRCS_NAMES_BONUS= 
#SRCS_BONUS=$(addprefix $(SRC_PATH), $(SRCS_NAMES))
OBJ_PATH=build/
OBJS_NAMES=$(SRCS_NAMES:.c=.o)
OBJS=$(addprefix $(OBJ_PATH), $(OBJS_NAMES))
#OBJS_NAMES_BONUS=$(SRCS_NAMES_BONUS:.c=.o)
#OBJS_BONUS=$(addprefix $(OBJ_PATH), $(OBJS_NAMES_BONUS))
MY_LIB_STATIC_NAME = libft.a
LIBS= $(MY_LIB_STATIC_NAME:.a=) libmlx_Linux libX11 libXext libm
LIB_PATH=lib/
LIBS_FLAGS= -L$(LIB_PATH) $(patsubst lib%, -l%, $(LIBS))
LIB_STATIC = $(addprefix $(LIB_PATH) , $(INCLUDE_PATH))
INCLUDE_PATH=./include/ ./lib/*/include/
INCLUDE_FLAG=$(addprefix -I , $(INCLUDE_PATH))
RM=rm -f

all: libs $(NAME)

$(NAME): $(OBJS) $(LIB_STATIC)
	$(CC) $(CCFLAGS) $(OBJS) $(INCLUDE_FLAG) $(LIBS_FLAGS) -o $(NAME)

libs:
	make all -C lib/libft

bonus: libs $(NAME_BONUS)

$(NAME_BONUS): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(INCLUDE_FLAG) $(LIBS_FLAGS) -o $(NAME_BONUS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CCFLAGS) -c $< -o $@ $(INCLUDE_FLAG)

clean:
	make clean -C lib/libft
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	make fclean -C lib/libft
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all bonus

norm:
	norminette -R CheckDefine $(INCLUDE_PATH)*.h
	norminette -R CheckForbiddenSourceHeader $(SRC_PATH)*.c

.PHONY=all bonus clean fclean re norm libs
