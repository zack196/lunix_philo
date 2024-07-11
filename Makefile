NAME = philo
CC = cc 
CFLAG = -Wall -Wextra -Werror -fsanitize=thread

SRC = ./main.c	\
	  ./utils.c	\
	  ./philo_routine.c \
	  ./geters_and_seters.c

OBJ = $(SRC:.c=.o)

all:$(NAME)

%.o:%.c philo.h
	$(CC) $(CFLAG) -c $< -o $@

$(NAME):$(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re : fclean all