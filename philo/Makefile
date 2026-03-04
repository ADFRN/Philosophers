# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afournie <afournie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/12 17:14:16 by afournie          #+#    #+#              #
#    Updated: 2026/03/04 11:42:41 by afournie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -I$(HEADERS_DIR)

HEADERS_DIR	= includes

SRCS		= main.c		\
			  init.c		\
			  utils.c		\
			  error.c		\
			  jarvis.c		\
			  actions.c		\
			  routine.c		\
			  free_exit.c	\

OBJS        = $(SRCS:.c=.o)

RED			= \033[0;31m
GREEN		= \033[0;32m
CYAN		= \033[0;36m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) && echo "$(GREEN)[OK] Compilation réussie, exécutable créé$(RESET)" || (echo "$(RED)[FAIL] Compilation échouée$(RESET)"; exit 1)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@echo "$(CYAN)Fichiers objets supprimés$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(CYAN)Exécutable supprimé$(RESET)"

re: fclean all

.PHONY: all clean fclean re
