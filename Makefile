NAME_1 = server
NAME_2 = client
SRC_1 = server.c
SRC_2 = client.c
SRC_1_BONUS = server_bonus.c
SRC_2_BONUS = client_bonus.c
OBJ_1_BONUS = $(SRC_1_BONUS:.c=.o)
OBJ_2_BONUS = $(SRC_2_BONUS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
OBJ_1 = $(SRC_1:.c=.o)
OBJ_2 = $(SRC_2:.c=.o)

all: $(NAME_1) $(NAME_2)

$(NAME_1): $(OBJ_1)
	$(CC) $(CFLAGS) $^ -o $@

$(NAME_2): $(OBJ_2)
	$(CC) $(CFLAGS) $^ -o $@

bonus: server_bonus client_bonus

server_bonus: $(OBJ_1_BONUS)
	$(CC) $(CFLAGS) $^ -o $@

client_bonus: $(OBJ_2_BONUS)
	$(CC) $(CFLAGS) $^ -o $@


clean:
	rm -rf $(OBJ_1) $(OBJ_2) $(OBJ_1_BONUS) $(OBJ_2_BONUS) bonus

fclean: clean
	rm -rf $(NAME_1) $(NAME_2) server_bonus client_bonus

re: fclean all

.PHONY: all clean fclean re bonus