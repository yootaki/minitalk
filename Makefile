
CLIENT = client
SERVER = server

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBS = includes/libft/libft.a

DEBUG_DIR = client.dSYM server.dSYM

# **************************************************
# **************************************************

all: $(CLIENT) $(SERVER)

$(CLIENT): $(LIBS)
	$(CC) $(CFLAGS) -o $(CLIENT) client.c $(LIBS)
$(SERVER): $(LIBS)
	$(CC) $(CFLAGS) -o $(SERVER) server.c $(LIBS)

$(LIBS):
	$(MAKE) -C includes/libft/

bonus: all

# **************************************************
# **************************************************

clean:
	rm -rf $(DEBUG_DIR)
	$(MAKE) fclean -C includes/libft/

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
