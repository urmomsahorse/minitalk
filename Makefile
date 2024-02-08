SER = server

CLI = client


all: ${SER} ${CLI}

${SER}: server.c
	cc server.c -o server

${CLI}: client.c
	cc client.c -o client

clean:
	rm -rf server
	rm -rf client

fclean: clean 

re: clean all
   

.PHONY: all clean fclean re


# SRCSCLIENT =  client.c
# SRCSSERVER = server.c
 			
# OBJSCLIENT = ${SRCSCLIENT:.c=.o}
# OBJSSERVER = ${SRCSSERVER:.c=.o}

# NAMESERVER = server
# NAMECLIENT = client

# CC = gcc
# RM = rm -f
# CFLAGS = #-Wall -Wextra -Werror
 
# %.o:%.c 	$(HEADER) Makefile
# 			$(CC) $(CFLAGS) -c $< -o $@

# all: ${NAMESERVER} ${NAMECLIENT}

# ${NAMESERVER}: ${OBJSSERVER}
# 	cc server.c -o server

# ${NAMECLIENT}: ${OBJSCLIENT}
# 	cc client.c -o client

# clean:
# 	rm -rf server
# 	rm -rf client

# re: clean all
   

# .PHONY: all clean re

