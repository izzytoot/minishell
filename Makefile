# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 12:06:47 by icunha-t          #+#    #+#              #
#    Updated: 2025/06/12 16:52:48 by icunha-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                NAMES & PATHS                                 #
#==============================================================================#
NAME = minishell
INC_PATH = details
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
							30_tokens/36_sub_tokenize_files.c\
							30_tokens/37_sub_tokenize_utils.c\
							30_tokens/38_token_utils.c\
							40_empties/40_empties.c\
							40_empties/41_rm_empties.c\
							40_empties/42_empties_utils.c\
							50_build_tree/50_tokens_to_tree.c\
							50_build_tree/51_build_pipe_nodes.c\
							50_build_tree/52_build_redir_nodes.c\
							50_build_tree/53_build_redir_nodes_utils.c\
							50_build_tree/54_build_cmd_nodes.c\
							50_build_tree/55_type_is_utils.c\
							50_build_tree/56_tree_utils.c\
							60_built_ins/60_pwd.c\
							60_built_ins/61_cd.c\
							60_built_ins/62_env.c\
							60_built_ins/63_echo.c\
							60_built_ins/64_exit.c\
							60_built_ins/65_unset.c\
							60_built_ins/66_export.c\
							60_built_ins/67_export_utils.c\
							60_built_ins/68_export_utils_2.c\
							70_exec/70_exec_tree.c\
							70_exec/71_exec_pipe.c\
							70_exec/72_exec_redir.c\
							70_exec/73_exec_heredoc.c\
							70_exec/74_exec_cmd.c\
							70_exec/75_remake_args_utils.c\
							70_exec/76_exec_dir_path.c\
							70_exec/77_exec_utils.c\
							70_exec/78_exec_utils_2.c\
							70_exec/79_exec_cmd_utils.c\
							70_exec/79_1_exec_pipe_utils.c\
							80_expander/80_expand_args.c\
							80_expander/81_expand_fname.c\
							80_expander/82_expand_hd.c\
							80_expander/83_build_kw_lst.c\
							80_expander/84_expand_key_words.c\
							80_expander/85_get_parts.c\
							80_expander/86_final_expander.c\
							80_expander/87_expand_utils.c\
							80_expander/88_expand_utils_2.c\
							90_signals/90_signals.c\
							90_signals/91_signals_utils.c\
							100_close_and_free/100_free_msh.c\
							100_close_and_free/101_close_msh.c\
							100_close_and_free/102_other_frees.c\
							11_debug_utils.c)
TMP = ./tmp
OBJ = $(patsubst $(SRC_PATH)%,$(TMP)/%,$(SRC:.c=.o))


LIBFT_DIR = ./inc/libft
LIBFT = $(LIBFT_DIR)/libft.a
#==============================================================================#
#                            FLAGS & COMMANDS                                  #
#==============================================================================#
C_COMP = cc

FLAGS = -Wall -Werror -Wextra
FLAGS += -g -O0 -fPIE
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

$(TMP)/%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(C_COMP) $(FLAGS) -I $(INC_PATH) -I $(LIBFT_DIR) -c $< -o $@

#==============================================================================#
#                                  CLEAN RULES                                 #
#==============================================================================#
valgrind:
	@echo "{\n readline leaks\n   Memcheck:Leak\n...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n...\n   fun:add_history\n}" > readline.supp
	/usr/bin/valgrind --track-fds=yes --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all -q ./$(NAME)
	
fullvalgrind:
	@echo "{\n readline leaks\n   Memcheck:Leak\n...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n...\n   fun:add_history\n}" > readline.supp
	/usr/bin/valgrind --track-fds=yes --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all ./$(NAME)

sync:
	@tmux new-window -n sync
	@tmux send-keys './minishell' C-m
	@tmux split-window -h
	@tmux send-keys -t sync.2 'bash' C-m
	@tmux select-pane -t sync.1
	@tmux setw synchronize-panes on

clean:
	@$(RM) $(OBJ)
	@rm -rf $(TMP)
	@echo $(RED) "All minishell .o files were deleted!" $(RESET)
	
fclean: clean
	@$(RM) $(NAME)
	@echo $(RED) "$(NAME) was deleted!" $(RESET)

fcleanall: fclean
	@$(MAKE) $(NODIR) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re cleanall fcleanall sync fullvalgrind valgrind
