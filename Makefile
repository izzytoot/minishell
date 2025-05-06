# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isabel <isabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 12:06:47 by icunha-t          #+#    #+#              #
#    Updated: 2025/05/06 16:23:01 by isabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                NAMES & PATHS                                 #
#==============================================================================#
NAME = minishell
INC_PATH = ./inc/minishell.h
SRC_PATH = ./src/
SRC = $(addprefix $(SRC_PATH), ./00_main/00_main.c \
							./10_init/10_init_msh.c \
							./10_init/11_envp_copies.c\
							./10_init/12_init_utils.c \
							./20_syntax/20_syntax_check.c \
							./20_syntax/21_syntax_quotes.c \
							./20_syntax/22_syntax_pipes.c \
							./20_syntax/23_syntax_redir.c \
							./20_syntax/24_syntax_utils.c \
							./30_tokens/30_tokenizer.c \
							./30_tokens/31_token_words.c \
							./30_tokens/32_token_pipes_and_redir_r.c \
							./30_tokens/33_token_redir_l.c\
							./30_tokens/34_handle_quotes.c\
							./30_tokens/35_sub_tokenize.c\
							./30_tokens/36_sub_tokenize_utils.c\
							./30_tokens/37_token_utils.c\
							./40_build_tree/40_tokens_to_tree.c\
							./40_build_tree/41_build_pipe_nodes.c\
							./40_build_tree/42_build_redir_nodes.c\
							./40_build_tree/43_build_cmd_nodes.c\
							./40_build_tree/44_tree_utils.c\
							./50_built_ins/50_pwd.c\
							./50_built_ins/51_cd.c\
							./50_built_ins/52_env.c\
							./50_built_ins/53_echo.c\
							./50_built_ins/54_exit.c\
							./50_built_ins/55_unset.c\
							./50_built_ins/56_export.c\
							./60_exec/60_exec_tree.c\
							./60_exec/61_exec_pipe.c\
							./60_exec/62_exec_redir.c\
							./60_exec/63_exec_heredoc.c\
							./60_exec/64_exec_cmd.c\
							./60_exec/65_remake_args_utils.c\
							./60_exec/66_exec_utils.c\
							./70_expander/70_expand_tree.c\
							./70_expander/71_expand_token.c\
							./70_expander/72_expand_token_utils.c\
							./70_expander/73_get_exp_parts.c\
							./70_expander/74_final_expander.c\
							./70_expander/75_expand_utils.c\
							./80_close_and_free/80_free_msh.c\
							./80_close_and_free/81_close_msh.c\
							11_debug_utils.c)
OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./inc/libft/
LIBFT = ./inc/libft/libft.a
#==============================================================================#
#                            FLAGS & COMMANDS                                  #
#==============================================================================#
C_COMP = cc

FLAGS = -Wall -Werror -Wextra
FLAGS += -g -O0
LDFLAGS = -lreadline
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
	@$(CC) $(FLAGS) $(OBJ) $(LDFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo $(BGRN)" $(NAME) was created successfully!" $(RESET)
#==============================================================================#
#                                  CLEAN RULES                                 #
#==============================================================================#
msg:
	@echo $(BCYA)" This $(NAME) program was created by icunha-t and ddo-carm! ✨" $(RESET)

valgrind:
	@echo "{\n readline leaks\n   Memcheck:Leak\n...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n...\n   fun:add_history\n}" > readline.supp
	/usr/bin/valgrind --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all ./$(NAME)

clean:
	@$(RM) $(OBJ)
	@echo $(RED) "All minishell .o files were deleted!" $(RESET)

fclean: clean
	@$(RM) $(NAME)
	@echo $(RED) "$(NAME) was deleted!" $(RESET)

fcleanall: fclean
	@$(MAKE) $(NODIR) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re cleanall fcleanall
