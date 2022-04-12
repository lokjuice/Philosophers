NAME		=	philo_bonus

SRCS		= 	sources/main.c \
				sources/utils.c \
				sources/death.c \
				sources/activity.c \

OBJS		= 	$(patsubst %.c,%.o,$(SRCS))

CC			= 	@gcc

CFLAGS		= 	-Wall -Wextra -Werror

INCLUDES	= 	sources/philosophers.h

RM			= 	rm -rf

all: 			$(NAME)

$(OBJS):		$(INCLUDES)

$(NAME): 		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
				@echo "\033[30;42m      Program completed      "

clean:
				@${RM} $(OBJS)
				@echo "\033[30;43m        files deleted        "

fclean:			
				@${RM} $(OBJS) $(NAME)
				@echo "\033[30;43m        files deleted        "

re:				fclean all

.PHONY:			all clean fclean re