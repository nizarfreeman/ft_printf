CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRC_FILES = \
	ft_atoi.c d_manager_unsigned_utils_1.c flags_parser.c p_manager_utils_1.c \
	s_manager_utils.c utils_4_counts.c Xx_manager_utils_1.c c_manager.c \
	d_manager_unsigned.c d_manager_unsigned_utils_2.c ft_printf.c p_manager_utils_2.c utils_1.c \
	utils_5.c Xx_manager_utils_2.c d_manager.c d_manager_utils_2.c process_string.c \
	utils_2.c  utils_6.c d_manager_unsigned_utils_1.c  flags_parser.c p_manager.c \
	s_manager.c utils_3_adress_hex.c Xx_manager.c d_manager_utils.c
OBJ_FILES = ${SRC_FILES:.c=.o}
NAME = libftprintf.a

all: ${NAME}

${NAME}: ${OBJ_FILES} 
	ar -rcs $@ $^

%.o: %.c ft_printf.h
	${CC} ${CFLAGS} -c $< -o $@

bonus: all

clean:
	rm -rf ${OBJ_FILES}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: clean
