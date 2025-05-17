# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 12:06:47 by icunha-t          #+#    #+#              #
#    Updated: 2025/05/17 13:48:39 by ddo-carm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                NAMES & PATHS                                 #
#==============================================================================#
NAME = minishell
INC_PATH = ./inc/minishell.h
SRC_PATH = ./src/
SRC = $(addprefix $(SRC_PATH), 00_main/00_main.c \
							10_init/10_init_msh.c \
							10_init/11_envp_copies.c\
							10_init/12_init_utils.c \
							20_syntax/20_syntax_check.c \
							20_syntax/21_syntax_quotes.c \
							20_syntax/22_syntax_pipes.c \
							20_syntax/23_syntax_redir.c \
							20_syntax/24_syntax_utils.c \
							30_tokens/30_tokenizer.c \
							30_tokens/31_token_words.c \
							30_tokens/32_token_pipes_and_redir_r.c \
							30_tokens/33_token_redir_l.c\
							30_tokens/34_handle_quotes.c\
							30_tokens/35_sub_tokenize.c\
							30_tokens/36_sub_tokenize_utils.c\
							30_tokens/37_token_utils.c\
							30_tokens/38_token_empties.c\
							40_build_tree/40_tokens_to_tree.c\
							40_build_tree/41_build_pipe_nodes.c\
							40_build_tree/42_build_redir_nodes.c\
							40_build_tree/43_build_cmd_nodes.c\
							40_build_tree/44_type_is_utils.c\
							40_build_tree/45_tree_utils.c\
							50_built_ins/50_pwd.c\
							50_built_ins/51_cd.c\
							50_built_ins/52_env.c\
							50_built_ins/53_echo.c\
							50_built_ins/54_exit.c\
							50_built_ins/55_unset.c\
							50_built_ins/56_export.c\
							50_built_ins/57_export_utils.c\
							60_exec/60_exec_tree.c\
							60_exec/61_exec_pipe.c\
							60_exec/62_exec_redir.c\
							60_exec/63_exec_heredoc.c\
							60_exec/64_exec_cmd.c\
							60_exec/65_remake_args_utils.c\
							60_exec/66_exec_utils.c\
							60_exec/67_exec_dir_path.c\
							70_expander/70_expand_args.c\
							70_expander/71_expand_fname.c\
							70_expander/72_expand_hd.c\
							70_expander/73_build_kw_lst.c\
							70_expander/74_expand_key_words.c\
							70_expander/75_get_parts.c\
							70_expander/76_final_expander.c\
							70_expander/77_expand_utils.c\
							80_close_and_free/80_free_msh.c\
							80_close_and_free/81_close_msh.c\
							80_close_and_free/82_other_frees.c\
							11_debug_utils.c)
OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./inc/libft
LIBFT = $(LIBFT_DIR)/libft.a
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

# Background colors
BGRED	= "\033[41m"
BGGRN	= "\033[42m"
BGYEL	= "\033[43m"
BGBLU	= "\033[44m"
BGMAG	= "\033[45m"
BGCYA	= "\033[46m"
BGWHI	= "\033[47m"
BGBLA	= "\033[40m"

# Bright (bold/high intensity) background colors
BGBRED	= "\033[101m"
BGBGRN	= "\033[102m"
BGBYEL	= "\033[103m"
BGBBLU	= "\033[104m"
BGBMAG	= "\033[105m"
BGBCYA	= "\033[106m"
BGBWHI	= "\033[107m"

#==============================================================================#
#                               RULES & DEPS                                   #
#==============================================================================#
all: $(NAME)
	
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJ) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)
	@clear
	@echo $(BBLU) "		   __  __ _      _    _        _ _ "
	@echo $(BBLU) "		  |  \/  (_)_ _ (_)__| |_  ___| | |"
	@echo $(BBLU) "		  | |\/| | | ' \| (_-< ' \/ -_) | |"
	@echo $(BBLU) "		  |_|  |_|_|_||_|_/__/_||_\___|_|_|" $(RESET)
	@echo "\n"
	@echo $(BGRN)" $(NAME) was created successfully!" $(RESET)
	@echo $(BCYA)" This $(NAME) program was created by icunha-t and ddo-carm! ✨" $(RESET)

$(LIBFT):
	@$(MAKE) $(NODIR) -C $(LIBFT_DIR)

%.o: %.c 
	@$(C_COMP) $(FLAGS) -I $(INC_PATH) -I $(LIBFT_DIR) -c $< -o $@
#==============================================================================#
#                                  CLEAN RULES                                 #
#==============================================================================#

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

.PHONY: all clean fclean re cleanall fcleanall msg
