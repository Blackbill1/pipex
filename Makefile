# Nom de l'exécutable final
NAME = pipex

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I $(INCDIR) -I $(LIB) -I$(INCLIB)

LIB = koalib
LIBFT = $(LIB)/libft.a

# Dossiers
SRCDIR = src
INCDIR = inc
INCLIB = koalib/includes
OBJDIR = obj

# Récupération des fichiers sources
SRC = pipex.c \
		exec.c \
		utils.c \

# Chemin complet pour les fichiers objets dans obj/
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# Règle par défaut
all: $(LIBFT) $(NAME)

# Compilation de l'exécutable avec les bibliothèques
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "Compilation de $(NAME) terminée."

# Compilation de la libft
$(LIBFT):
	@$(MAKE) --quiet -C $(LIB)
	@echo "Koalib compilée."

# Compilation des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Création du dossier obj si nécessaire
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) --quiet -C $(LIB) clean
	@echo "Nettoyage des fichiers objets."

# Nettoyage complet (objets + exécutable + bibliothèques)
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --quiet -C $(LIB) fclean
	@echo "Nettoyage complet."

# Recompile tout depuis zéro
re: fclean all

# Vérification de la norme avec norminette
norm:
	@echo "Norminette de $(NAME) dans $(SRCDIR) et $(INCDIR)..."
	@if norminette $(SRCDIR)/*.c $(INCDIR)/*.h | grep -v "OK!" | grep -q "Error!"; then \
		norminette $(SRCDIR)/*.c $(INCDIR)/*.h | grep -v "OK!" | \
		while read line; do \
			if echo $$line | grep -q "Error!"; then \
				echo "\033[0;31m$$line\033[0m"; \
			else \
				echo "$$line"; \
			fi; \
		done; \
	else \
		echo "\033[0;32mAll files are norminette friendly !\033[0m"; \
	fi

# Ignorer les erreurs sur ces règles
.PHONY: all clean fclean re norm
