
CLIENT = client
SERVER = server

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBS = libft/libft.a

DEBUG_DIR = client.dSYM server.dSYM

# **************************************************
# **************************************************

all: $(LIBS)
	$(CC) $(CFLAGS) -o $(CLIENT) client.c $(LIBS)
	$(CC) $(CFLAGS) -o $(SERVER) server.c $(LIBS)

bonus: all

# **************************************************
# **************************************************

clean:
	rm -rf $(DEBUG_DIR)

fclean: clean
	rm -f $(CLIENT)
	rm -f $(SERVER)

re: fclean all

# **************************************************
# **************************************************

#セグフォなどのデバッグ用フラグ
debug: CFLAGS += -g3 -fsanitize=address

debug: re

# **************************************************
# **************************************************

.PHONY: all bonus debug fclean clean re
