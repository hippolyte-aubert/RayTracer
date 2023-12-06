##
## EPITECH PROJECT, 2023
## RayTracer
## File description:
## Makefile
##

SRC_DIRS = ./src

BIN = raytracer

DEBUG = no

ifeq ($(DEBUG),yes)
	CFLAGS += -g3
endif

SRCS := $(shell find $(SRC_DIRS) -name "*.cpp")

OBJS = $(SRCS:.cpp=.o)

CPPFLAGS = $(shell find ./include -type d | awk '{printf "-I%s ", $$0}')
CPPFLAGS += -g3

LDLIBS = -lconfig++

CC = g++

all : $(BIN)

$(BIN) : $(OBJS)
	@$(CC) $(OBJS) -o $(BIN) $(LDFLAGS) $(LDLIBS)

%.o :	%.cpp
	@echo "\e[92;1m[\e[36;1m⏳ \e[92;1m] \
\e[1;32mCompiling\e[1;35m $< \e[1;32m...\e[1;0m"
	@$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
	@echo "    \e[32;1m✔ \e[34m\"\e[1;35m$(@)\e[34m\" \
\e[1;32mSuccessfully compiled !"

re : fclean all

fclean : clean
	@ $(RM) -rf $(BIN)

clean :
	@ $(RM) -rf $(OBJS)
