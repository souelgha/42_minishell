NAME	= minishell
CFLAGS	= -Wall -Wextra -Werror -g
LIBFT	= libft.a

#DIRECTORY
SRC_PATH = src/
OBJ_PATH = obj/
HEADER_FOLDER = includes

SRC 	= main.c \
			exe_do_command.c exe_do_command_utils.c do_cd.c do_echo.c \
		 	do_env.c do_exit.c do_export.c do_export_utils.c \
			do_pwd.c do_unset.c envp.c error.c \
			exe_command.c free.c interpret.c interpret_utils.c\
			loop.c node_arg.c node_info.c \
			parsing.c parsing_arg.c parsing_redirect.c\
			parsing_utils.c do_export_maj.c\
			read_line.c read_lines_utils.c \
			signal.c exe_redirect.c\
			exe_fd_dup.c exe_arg_reading.c read_here_doc.c \
			token_management.c read_here_doc_utils.c \
			interpret_dollar_num.c interpret_clean_str_dollar.c \
			do_export_arg.c envp_utils.c exe_forking.c node_command.c \
			loop_utils.c read_line_outils.c read_here_doc_utils_2.c \
			interpret_utils_2.c exe_fd_dup_help.c exe_command_path_1.c \
			do_cd_2.c error_2.c error_3.c free_2.c read_syn_manag.c \
			parsing_split.c exe_command_path_2.c do_checkname_var.c \
			parsing_redirect_2.c parsing_arg_2.c parsing_2.c \
			parsing_3.c parsing_redirect_3.c interpret_2.c \
			interpret_utils_pipe.c signal_2.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INCS	= -I ./includes/


all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS) 
		@cc $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline
		@echo "$(GREEN) compilation ok $(RESET)"



$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@if [ ! -e $(OBJ_PATH) ]; then\
		mkdir -p $(OBJ_PATH);\
	fi
	@make -sC ./libft
	@cp ./libft/libft.a .
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCS) 

$(LIBFT) : 
		@$(MAKE) -C ./libft
		@cp ./libft/libft.a .

clean :
		@rm -rf $(OBJ_PATH)
		@$(MAKE) -s clean -C ./libft
		@echo "$(CLEAR) $(BLUE) cleaned $(RESET)"

fclean : clean
		@rm -rf $(NAME) $(LIBFT)
		@$(MAKE) -s fclean -C ./libft
		@echo "$(CLEAR) $(BLUE) fcleaned $(RESET)"

re : fclean all

.PHONY: all clean fclean re
	
RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[38;5;97m
CLEAR = \033[2J\033[H
RESET = \033[0m
