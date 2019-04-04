include Makefile.compilation
#make file pour les tests et prog principal

fichier_inventaire_test=test_inventaire.o inventaire.o commun.o
fichier_perso_test=test_perso.o perso.o inventaire.o commun.o
fichier_combat_test=test_combat.o combat.o perso.o inventaire.o commun.o map_menace.o

fichier_projet_FF= projet_FF.o combat.o perso.o inventaire.o commun.o map_menace.o
#
# Tests + fichier principal
#

BIN = test_inventaire test_perso test_combat projet_FF

test_inventaire : $(fichier_inventaire_test)
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(LIBNCURSES) $(fichier_inventaire_test) -o test_inventaire
test_inventaire.o : test_inventaire.c inventaire.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) $(LIBNCURSES) test_inventaire.c -o test_inventaire.o -I./

test_perso : $(fichier_perso_test)
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(LIBNCURSES) $(fichier_perso_test) -o test_perso
test_perso.o : test_perso.c inventaire.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) $(LIBNCURSES) test_perso.c -o test_perso.o -I./

test_combat : $(fichier_combat_test)
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(LIBNCURSES) $(fichier_combat_test) -o test_combat
test_combat.o : test_combat.c combat.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) $(LIBNCURSES) test_combat.c -o test_combat.o -I./

projet_FF : $(fichier_projet_FF)
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(LIBNCURSES) $(fichier_projet_FF) -o projet_FF
projet_FF.o : projet_FF.c combat.h	#voir si il faut changer le .h plus tard !!!!
	$(CCOBJ) $(CFLAGS) $(LIBMATH) $(LIBNCURSES) projet_FF.c -o projet_FF.o -I./
#
# Modules(objets)
#

OBJ =  commun.o inventaire.o perso.o map_menace.o combat.o

commun.o : commun.c commun.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) $(LIBNCURSES) commun.c -o commun.o -I./

map_menace.o : map_menace.c map_menace.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) $(LIBNCURSES) map_menace.c -o map_menace.o -I./

inventaire.o : inventaire.c inventaire.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) $(LIBNCURSES) inventaire.c -o inventaire.o -I./

perso.o : perso.c perso.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) $(LIBNCURSES) perso.c -o perso.o -I./

combat.o : combat.c combat.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) $(LIBNCURSES) combat.c -o combat.o -I./

#
# Headers
#

inventaire.h : commun.h
	touch inventaire.h
perso.h : inventaire.h
	touch perso.h
combat.h : perso.h
	touch combat.h

#
#
#

all : $(BIN) $(OBJ)

clean :
	- rm  *.o
	- rm test_inventaire
	- rm test_perso
	- rm test_combat
	- rm projet_FF

clean2 :
	- rm  *.o

tests :
	./test_inventaire
	./test_perso
	./test_combat