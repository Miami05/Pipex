# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ledio <ledio@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/01 21:18:49 by ledio             #+#    #+#              #
#    Updated: 2024/12/07 12:04:00 by ledio            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name
NAME = pipex
BONUS_NAME = pipex_bonus

# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I include -I libft/include
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Color codes
RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m

# Source files for pipex
SRCS = src/pipex.c src/pipex_utils.c
BONUS_SRCS = bonus/pipex_bonus.c bonus/pipex_utils_bonus.c bonus/pipex_utils_bonus_2.c

# Default infile and outfile for display
INFILE = infile
OUTFILE = outfile

# Object files
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# Main target
all: outfile infile $(LIBFT) $(NAME)

# Compiling infile
infile:
		@echo "This is a default infile content" > infile
		@echo "$(GREEN)Infile created successfully!$(RESET)"
		
# Compiling outfile
outfile:
		@echo " " > outfile
		@echo "$(GREEN) Outfile created successfully!$(RESET)"

# Compiling libft
$(LIBFT):
		@echo "$(GREEN)Compiling libft..$(RESET)"
		@$(MAKE) -C $(LIBFT_DIR)
		@echo "$(GREEN)Libft compiled successfully!$(RESET)"

# Compile pipex
$(NAME):$(OBJS)
		@echo "$(GREEN)Compiling pipex...$(RESET)"
		$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
		@echo "$(GREEN)Pipex compiled successfully!$(RESET)"

# Compile bonus
bonus: $(LIBFT) $(BONUS_OBJS) $(INFILE) $(OUTFILE)
		@echo "$(GREEN)Compiling pipex bonus...$(RESET)"
		$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_OBJS) -L$(LIBFT_DIR) -lft -o $(BONUS_NAME)
		@echo "$(GREEN)Pipex bonus compiled successfully!$(RESET)"

# Compile individual object files
%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
		@echo "$(RED)Cleaning object files...$(RESET)"
		@rm -f $(OBJS) $(BONUS_OBJS)
		@$(MAKE) -C $(LIBFT_DIR) clean
		@echo "$(GREEN)Object files cleaned successfully...$(RESET)"

# Remove executables and object files
fclean:
		@echo "$(RED)Removing executables...$(RESET)"
		@rm -f $(NAME) $(OBJS) infile outfile $(BONUS_NAME) $(BONUS_OBJS)
		@$(MAKE) -C $(LIBFT_DIR) fclean
		@echo "$(GREEN)Executable files removed successfully!$(RESET)"

# Rebuild everything
re: fclean all

.PHONY: all bonus clean fclean re
