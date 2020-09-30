# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/28 12:41:17 by nieyraud          #+#    #+#              #
#    Updated: 2020/09/30 10:57:42 by nieyraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

rose='\033[1;31m'
violetfonce='\033[0;35m'
violetclair='\033[1;35m'
neutre='\033[0m'
cyanfonce='\033[0;36m'
cyanclair='\033[1;36m'
vertfonce='\033[0;32m'
vertclair='\033[1;32m'
rouge='\033[31m'

NAME = philo_two

SRCS = main.c ft_atoi.c compare_time.c philosopher_state.c \
		print_state.c ft_strjoin.c ft_strlen.c ft_memcpy.c ft_ultoa.c \
		create_philosopher.c ft_free.c ft_ultox.c \
		my_sleep.c check_validity.c

SRCS_PATH = srcs
OBJS_PATH = objs
OBJS = ${addprefix $(OBJS_PATH)/, $(SRCS:%.c=%.o)}

HEADER = philo_two.h
INCLUDE = include

FLAGS = -Wall -Wextra
CC = clang

all: $(NAME)

$(NAME): $(INCLUDE) $(OBJS)
	@$(CC) $(OBJS) -I $(INCLUDE) -lpthread -o ${NAME}
	@echo '\n'$(vertclair)$(NAME) "Compiled" $(neutre)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@$(CC) $(FLAGS) -c -o $@ -I $(INCLUDE) $<
	@/bin/echo -n "."

clean:
	@rm -rf $(OBJS)
	@echo $(rouge)"Object remove" $(neutre)

fclean: clean
	@rm -rf $(NAME)
	@echo $(rouge)$(NAME) "remove" $(neutre)

re: fclean all

.PHONY: all fclean re clean