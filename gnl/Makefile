# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmullan <tmullan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/13 13:08:08 by tmullan       #+#    #+#                  #
#    Updated: 2020/05/13 15:47:11 by tmullan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a

OBJ = get_next_line.o get_next_line_utils.o

# FLAGS = -Wall -Wextra -Werror -g
# -D BUFFER_SIZE=1000

all: $(NAME)

$(NAME): $(OBJ)
		ar rcs $@ $^ 
		ranlib $(NAME)
		# $(FLAGS) 

%.o: %.c
		$(CC) -c -o $@ $< -I.

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all