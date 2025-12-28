# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: habe <habe@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 16:21:00 by habe              #+#    #+#              #
#    Updated: 2025/05/14 18:35:21 by habe             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_FILES = atoi\
			bzero\
			calloc\
			isalnum\
			isalpha\
			isascii\
			isdigit\
			isprint\
			itoa\
			memchr\
			memcmp\
			memcpy\
			memmove\
			memset\
			putchar_fd\
			putendl_fd\
			putnbr_fd\
			putstr_fd\
			split\
			strchr\
			strdup\
			striteri\
			strjoin\
			strlcat\
			strlcpy\
			strlen\
			strmapi\
			strncmp\
			strnstr\
			strrchr\
			strtrim\
			substr\
			tolower\
			toupper

BONUS_SRC_FILES = lstnew\
			lstadd_front\
			lstsize\
			lstlast\
			lstadd_back\
			lstdelone\
			lstclear\
			lstiter\
			lstmap

SRC = $(addprefix ft_, $(addsuffix .c, $(SRC_FILES)))
OBJ = $(SRC:.c=.o)

BONUS_SRC = $(addprefix ft_, $(addsuffix _bonus.c, $(BONUS_SRC_FILES)))
BONUS_OBJ = $(BONUS_SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: .bonus

.bonus: $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)
	@touch .bonus

clean:
	$(RM) $(OBJ) $(BONUS_OBJ) .bonus

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
