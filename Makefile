# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 20:21:35 by yel-yaqi          #+#    #+#              #
#    Updated: 2024/09/15 20:18:15 by mrezki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ERASE			= \033[2K\r
ORANGE			= \033[38;5;214m
TEAL			= \033[38;5;228m
RED				= \033[38;5;196m
GREEN			= \033[92m
NEON			= \033[38;5;51m
PURPLE			= \033[38;5;92;1m
RESET			= \033[0m

CFLAGS			= -Wall -Wextra -Werror -g -O1# -fPIE -fsanitize=thread
# LDFLAGS			= -fsanitize=thread
NAME			= philo
SRCS		 	= src/main.c src/str_to_int.c src/process_input.c
OBJS		 	= $(SRCS:src/%.c=obj/%.o)
HEADER 			= include/philosophers.h

define PRINT_LOADING
	@for i in $(shell seq 0 15); do \
		printf "\033[2K\r$(NEON)Compiling src/$*.c... $(NEON)[ "; \
		for j in $$(seq 0 $$i); do printf "▓"; done; \
		for j in $$(seq $$i 15); do printf " "; done; \
		printf "]$(RESET)"; \
	done; \
	printf ""
endef

all: $(NAME)
	@echo "\n\t\t$(GREEN)DONE$(RESET)"

obj/%.o: src/%.c $(HEADER) Makefile
	@mkdir -p obj
	$(PRINT_LOADING)
	@cc -c $< -o $@ $(CFLAGS)

$(NAME): $(OBJS)
	@cc $^ -o $@ $(LDFLAGS)

clean:
	@echo "$(RED)Cleaning up...$(RESET)"
	@$(RM) -rf $(MAIN_OBJ) obj
	@echo "$(RED)clean finished$(RESET)"

fclean: clean
	@$(RM) -rf $(NAME)
	@echo "$(RED)fclean finished$(RESET)"

re: fclean all

.PHONY: check
