include Makefile.compilation
#make file pour les tests et prog principal

fichier_inventaire_test=test_inventaire.o inventaire.o commun.o
fichier_perso_test=test_perso.o commun_perso.o inventaire.o commun.o perso_monstre.o perso_joueur.o
fichier_combat_test=test_combat.o combat.o commun_perso.o inventaire.o commun.o map_menace.o perso_monstre.o perso_joueur.o

fichier_projet_FF= projet_FF.o combat.o commun_perso.o inventaire.o commun.o map_menace.o perso_monstre.o perso_joueur.o sauvegarde.o
#
# Tests + fichier principal
#

BIN = test_inventaire test_perso test_combat projet_FF

test_inventaire : $(fichier_inventaire_test)
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fichier_inventaire_test) -o test_inventaire
test_inventaire.o : test_inventaire.c inventaire.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_inventaire.c -o test_inventaire.o -I./

test_perso : $(fichier_perso_test)
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fichier_perso_test) -o test_perso
test_perso.o : test_perso.c inventaire.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_perso.c -o test_perso.o -I./

test_combat : $(fichier_combat_test)
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fichier_combat_test) -o test_combat
test_combat.o : test_combat.c combat.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_combat.c -o test_combat.o -I./

projet_FF : $(fichier_projet_FF)
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fichier_projet_FF) -o projet_FF
projet_FF.o : projet_FF.c combat.h	#voir si il faut changer le .h plus tard !!!!
	$(CCOBJ) $(CFLAGS) $(LIBMATH) projet_FF.c -o projet_FF.o -I./
#
# Modules(objets)
#

OBJ =  commun.o inventaire.o commun_perso.o map_menace.o combat.o	perso_monstre.o perso_joueur.o sauvegarde.o

commun.o : commun.c commun.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) commun.c -o commun.o -I./

perso_monstre.o : perso_monstre.c commun_perso.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) perso_monstre.c -o perso_monstre.o -I./

perso_joueur.o : perso_joueur.c commun_perso.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) perso_joueur.c -o perso_joueur.o -I./

map_menace.o : map_menace.c map_menace.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) map_menace.c -o map_menace.o -I./

inventaire.o : inventaire.c inventaire.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) inventaire.c -o inventaire.o -I./

commun_perso.o : commun_perso.c commun_perso.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) commun_perso.c -o commun_perso.o -I./

sauvegarde.o : sauvegarde.c commun_perso.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) sauvegarde.c -o sauvegarde.o -I./

combat.o : combat.c combat.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) combat.c -o combat.o -I./

#
# Headers
#

inventaire.h : commun.h
	touch inventaire.h
commun_perso.h : inventaire.h
	touch commun_perso.h
combat.h : commun_perso.h
	touch commun_perso.h

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
