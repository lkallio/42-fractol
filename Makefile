NAME = fractol
SRC = burning_ship.c globals.c main.c rect_divide.c\
		draw.c init.c mandelbrot.c more_events.c save_image.c \
		fract.c julia.c misc.c events.c thread_helpers.c even_more_events.c
SRCDIR = src/
OBJ = $(SRC:.c=.o)
OBJDIR = obj/
INC = includes/
INCLIBFT = libft/includes
INCMLX = minilibx
LIBFT = libft/libft.a
FLAGS = -Wall -Wextra -Werror

SETCYAN = \033[38;5;213m
SETPINK = \033[38;5;231m
SETASD = \033[38;5;225m
SETGREEN = \033[38;5;50m
UNSETCOLOR = \033[0m

.PHONY: all clean fclean re notify makeobj

all: $(NAME)

notify:
	@[ -d obj ] || mkdir obj
	@printf "$(SETCYAN)Updating object files...$(UNSETCOLOR)\n"

$(OBJDIR)%.o: $(SRCDIR)%.c | notify
	@gcc -g $(FLAGS) -c $< -I $(INC) -I $(INCLIBFT) -I $(INCMLX) -o $@

$(NAME): $(addprefix $(OBJDIR), $(OBJ))
	@printf "$(SETPINK)Making libft...\n$(UNSETCOLOR)"
	@make -C libft
	@gcc -g $^ $(LIBFT) $(FLAGS) -Lminilibx -lmlx -lX11 -lXext -lpng -o $(NAME)
	@printf "$(SETASD)$(SETGREEN)fractol compiled.\n$(UNSETCOLOR)"

clean:
	@make clean -C libft
	@rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all
