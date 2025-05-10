# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/10 00:34:01 by smamalig          #+#    #+#              #
#    Updated: 2025/05/10 20:50:06 by smamalig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      = libmlx.a
CC        = cc
CFLAGS    = -Wall -Wextra -MMD -MP
SRC_FILES = init.c get_visual.c new_window.c loop.c pixel_put.c \
	glx_check_version.c init_opengl.c init_display.c prevent_resize.c \
	destroy_display.c destroy_window.c
SRC_DIR   = src
OBJ_DIR   = obj
SRCS     := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS     := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS     := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRCS))
INCLUDES  = -Iinclude
LDFLAGS   = -lX11 -lGL

ifeq ($(DEBUG), 1)
	CFLAGS += -Wpedantic -O0 -g3
else
	CFLAGS += -Werror -O3
endif

all: $(NAME)

-include $(DEPS)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	@make all
	
.PHONY: all clean fclean re
