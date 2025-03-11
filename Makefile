# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 12:06:47 by icunha-t          #+#    #+#              #
#    Updated: 2025/03/11 17:36:54 by icunha-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                NAMES & PATHS                                 #
#==============================================================================#
NAME = minishell
INC_PATH = ./inc/minishell.h
SRC_PATH = ./src/
SRC = $(addprefix $(SRC_PATH), 01_main.c)
OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./inc/libft/
LIBFT = ./inc/libft/libft.a

#==============================================================================#
#                            FLAGS & COMMANDS                                  #
#==============================================================================#
C_COMP = cc

FLAGS = -Wall -Werror -Wextra
FLAGS += -g

RM = rm -f

AR = ar rcs

MAKE = make

NODIR = --no-print-directory
#==============================================================================#
#                                  COLORS                                      #
#==============================================================================#
RED		= "\033[0;31m"
GRN		= "\033[0;32m"  
YEL		= "\033[0;33m"
BLU		= "\033[0;34m"
BLA		= "\033[0;30m"
CYA		= "\033[0;36m"
GREY	= "\033[0;90m"
BBLA	= "\033[30;1m"
BRED 	= "\033[31;1m"
BGRN	= "\033[32;1m"
BYEL	= "\033[33;1m"
BBLU	= "\033[34;1m"
BMAG	= "\033[35;1m"
BCYA	= "\033[36;1m"
BWHI	= "\033[37;1m"
RESET	= "\033[0m"
#==============================================================================#
#                               RULES & DEPS                                   #
#==============================================================================#
all: $(LIBFT) $(NAME) clean msg

%.o: %.c 
	@$(C_COMP) $(FLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) $(NODIR) -C $(LIBFT_DIR)
	
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo $(BGRN)" $(NAME) was created successfully!" $(RESET)

#==============================================================================#
#                                  CLEAN RULES                                 #
#==============================================================================#
msg:
	@echo $(BCYA)" This $(NAME) program was created by icunha-t and ddo-carm! ✨" $(RESET)
	
clean:
	@$(RM) $(OBJ)
	@echo $(RED) "All minishell .o files were deleted!" $(RESET)

fclean:
	@$(RM) $(NAME)
	@echo $(RED) "$(NAME) was deleted!" $(RESET)

fcleanall: fclean
	@$(MAKE) $(NODIR) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re cleanall fcleanall
