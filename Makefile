NAME = fractol

SOURCE = test_main.c buttons.c init_cl1.c

OBJ = $(patsubst %.c,%.o,$(SOURCE))

LIB = -L libft -lft
OGK = -framework OpenGL -framework OpenCL
APK = -framework AppKit
LMX = -lmlx

all: $(NAME)

%.o: %.c
	gcc -Wall -Wextra -Werror -g -c -o $@ $<

$(NAME): $(OBJ)
	make -C ./libft
	make -C ./minilibx_macos
	gcc -o $(NAME) $(SOURCE:.c=.o) $(LIB) $(OGK) $(APK) $(LMX)

clean:
	/bin/rm -f $(SOURCE:.c=.o)
	make -C ./libft clean
	make -C ./minilibx_macos clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft fclean
	make -C ./minilibx_macos clean

re: fclean all
