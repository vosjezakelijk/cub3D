NAME = cub3D

LIBNAME = cub3d.a

SRCS =	cub3d.c get_next_line.c raycast.c raycast_utils.c\
		render_spr.c initialize_utils.c initialize.c \
		make_screenshot.c parse_ea_we_s_c_f.c \
		parse_res_no_so.c parse_utils.c parse_utils2.c \
		utils.c utils2.c utils3.c validate.c

SRCS_BONUS = main_mlx_bonus.c  movement_bonus.c utils4_bonus.c 

SRCS_INC = main_mlx.c movement.c utils4.c 

OBJS = $(patsubst %.c,%.o,$(SRCS))

OBJS_BONUS = $(patsubst %.c,%.o,$(SRCS_BONUS))

OBJS_INC = $(patsubst %.c,%.o,$(SRCS_INC))                     

CC = gcc

CFLAGS = -Wall -Wextra -Werror -O3 -I

RM = rm -f

MLXLIB = mlx

MLXNAME = libmlx.dylib

MLXFLAGS = -framework OpenGL -framework AppKit -L. -lmlx

bonus:
	$(MAKE) WITH_BONUS=1 all

ifdef WITH_BONUS
	AOFILES = $(OBJS) $(OBJS_BONUS)
else
	AOFILES = $(OBJS) $(OBJS_INC)
endif

all: $(NAME)

$(NAME): $(AOFILES)
	make -C $(MLXLIB)
	mv mlx/$(MLXNAME) ./
	$(CC) $(MLXFLAGS) $(AOFILES) -o $(NAME) 

%.o:%.c
	$(CC) $(CFLAGS) cube3d.h -I $(MLXLIB) -c $< -o $@

norme:
			@norminette  $(SRCS) cub3d.h

clean:
		$(RM) $(OBJS)
		$(RM) $(MLXNAME)
		$(RM) $(OBJS_BONUS)
		$(RM) $(OBJS_INC)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBNAME)
	$(RM) cub3D.bmp

re: fclean all

.PHONY: all, clean, fclean, re