#sources files
SRC = main.c checker.c init.c
#append .o to each .c files in the SRC
#OBJS := $(SRC:%.c=%.o)
OBJS = ${SRC:.c=.o}
#build target name
NAME = so_long
LIBFT = libft/libft.a
#compiler
CC = gcc
#compiler flags
CCFLAGS = -Wall -Wextra -Werror
#include directory == dossier includes
INC_DIR = .
INC_MLX = -Lminilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx-linux -lXext -lX11
#preprocessor flag
CPPFLAGS = -I$(INC_DIR)
#rm
RM = rm -f
#archive
#first rull is always "all" she is calling $(NAME)
all: $(NAME)
#NAME  "@"hide in command in terminal
$(NAME): $(OBJS)
	@make -C libft/
	gcc $(OBJS) $(LIBFT) $(INC_MLX) -o $(NAME)
# "%.o" rule compie .c file into corresponding .o file
# "%" is a wildcard for "name of the files without extension"
# $@ = target, here target = .o "$<" = first dependencies here = .c
%.o: %.c
	$(CC) $(CPPFLAGS) $(CCFLAGS) -Iminilibx-linux -o $@ -c $<
#clean delete all .o files
clean:
	$(RM) $(OBJS)
	make -C libft/ clean
#after executing clean delete the lib
fclean: clean
	$(RM) $(NAME)
	make -C libft/ fclean
#delete everything then re create it
re: fclean all
#phony targets
.PHONY: all clean fclean re
