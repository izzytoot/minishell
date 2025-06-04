# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/28 13:30:18 by icunha-t          #+#    #+#              #
#    Updated: 2025/06/04 14:35:17 by icunha-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                NAMES & PATHS                                 #
#==============================================================================#
NAME = libft.a

HEADER_PATH = ./libft.h
BASIC_PATH = ./basic
PRINTF_PATH = ./printf
GNL_PATH = ./gnl
DPRINTF_PATH = ./dprintf

SRCS = $(addprefix $(BASIC_PATH)/, ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
			ft_strcpy.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memcmp.c \
			ft_memcpy.c ft_memmove.c ft_array_join.c ft_memset.c ft_memchr.c ft_strchr.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strcmp.c ft_strnstr.c ft_strrchr.c \
			ft_tolower.c ft_safe_strjoin.c ft_toupper.c ft_strdup_until.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c \
			ft_strjoin_w_space.c ft_safe_free.c ft_safe_malloc.c ft_array_dup_w_null.c ft_array_dup.c ft_strtrim.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_free_array_w_null.c ft_putnbr_fd.c ft_itoa.c ft_split.c ft_unsplit.c \
			ft_lstnew.c ft_lstdelone.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstiter.c \
			ft_lstlast.c ft_char_to_str.c ft_lstmap.c ft_init_var.c ft_lstsize.c ft_list_to_array.c ft_strlen_until.c \
			ft_free_arrays.c ft_free_matrix.c ft_error_msg.c ft_close_pipe.c ft_atoi_base.c ft_atol.c \
			ft_is_space.c ft_atoll.c ft_is_dir.c)
PRINTF_SRCS = $(addprefix $(PRINTF_PATH)/, src/ft_printf.c src/ft_printchar.c src/ft_printstr.c \
			src/ft_printint_nb.c src/ft_printint_u.c src/ft_printint_hex.c src/ft_printptr.c)
GNL_SRCS = $(addprefix $(GNL_PATH)/, get_next_line.c get_next_line_utils.c)
DPRINTF_SRCS = $(addprefix $(DPRINTF_PATH)/, src/ft_dprintf.c src/ft_dprintf_utils.c src/ft_hex_utils.c)

OBJS = $(SRCS:.c=.o)
PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)
DPRINTF_OBJS = $(DPRINTF_SRCS:.c=.o)
#==============================================================================#
#                            FLAGS & COMMANDS                                  #
#==============================================================================#
C_COMP = cc

FLAGS = -Wall -Werror -Wextra

FLAGS += -g -fPIE

RM = rm -f

AR = ar rcs

MAKE = make
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
#                                  RULES                                       #
#==============================================================================#
all: extra $(NAME) clean

%.o: %.c $(HEADER_PATH)
	$(C_COMP) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo $(BGRN) "$(NAME) was created successfully!" $(RESET)
	
extra: $(OBJS) $(PRINTF_OBJS) $(GNL_OBJS) $(DPRINTF_OBJS)
	@$(AR) $(NAME) $(OBJS) $(PRINTF_OBJS) $(GNL_OBJS) $(DPRINTF_OBJS)
	@echo $(BGRN) "$(NAME) was created with extras successfully!" $(RESET)

#==============================================================================#
#                                  CLEAN RULES                                 #
#==============================================================================#
clean:
	@$(RM) -f $(OBJS) $(PRINTF_OBJS) $(GNL_OBJS) $(DPRINTF_OBJS)
	@echo $(RED) "All libft .o files were deleted!" $(RESET)
	
fclean:
	@$(RM) $(NAME)
	@echo $(RED) "$(NAME) was deleted!" $(RESET)

re: fclean all

.PHONY: all clean fclean re extra
