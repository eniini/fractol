# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 10:20:49 by eniini            #+#    #+#              #
#    Updated: 2021/05/21 12:40:21 by eniini           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

#compiler
CC = gcc
#march=native tunes code for the determined processor type of compiling machine
CFLAGS = -Wall -Wextra -Werror -O3 -march=native

#sources
SRCDIR = ./src/
OBJDIR = ./obj/
SRC =	main.c drawing.c events.c drawtools.c fractals.c interface.c
OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))
SRC_LINK = $(addprefix $(SRCDIR),$(SRC))
#headers
INC	= -Iincludes/

#libft
FT = ./libft/
FT_LIB = $(addprefix $(FT),libft.a)
FT_INC = -Ilibft/includes/

#minilibx
MLX = ./minilibx-linux/
MLX_LIB_LINUX = $(addprefix $(MLX), libmlx_Linux.a)
MLX_LIB = $(addprefix $(MLX), libmlx.a)

#linking
LIBRARIES = -L$(FT) -L$(MLX) -lmlx -lft -lXext -lX11 -lm

.PHONY:	obj all clean fclean re

all : obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(INC) $(FT_INC)  -o $@ -c $<

$(FT_LIB) :
	@make --no-print-directory -C $(FT)

$(MLX_LIB_LINUX) :
	@make --no-print-directory -C $(MLX)

$(MLX_LIB) :
	@make --no-print-directory -C $(MLX)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBRARIES) -o $(NAME)
	@echo -e "\033[0;32m[fractol] binary created!\033[0m"

clean :
	@rm -rf $(OBJDIR)
	@echo -e "\033[0;32m[fractol] .obj files removed\033[0m"
	@rm  -f $(SAVEFILE)
	@make --no-print-directory -C $(FT) clean

fclean : clean
	@rm -f $(NAME)
	@echo -e "\033[0;32m[fractol] program binary removed\033[0m"
	@make --no-print-directory -C$(FT) fclean
	@make --no-print-directory -C$(MLX) clean
	rm -f $(MLX_LIB)
	rm -f $(MLX_LIB_LINUX)
	@echo -e "\033[0;32m[fractol] MLX archive removed\033[0m"

re : fclean all