include Makefile.compilation
#make file pour les tests

fichier_inventaire_test=test_inventaire.o inventaire.o
fichier_perso_test=test_perso.o perso.o inventaire.o


fichier_projet_FF= projet_FF.o perso.o inventaire.o
#
# Tests (executables+objets)
#

BIN = test_inventaire test_perso projet_FF

test_inventaire : $(fichier_inventaire_test)
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fichier_inventaire_test) -o test_inventaire
test_inventaire.o : test_inventaire.c inventaire.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_inventaire.c -o test_inventaire.o -I./

test_perso : $(fichier_perso_test)
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fichier_perso_test) -o test_perso
test_perso.o : test_perso.c inventaire.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_perso.c -o test_perso.o -I./

test_combat :

projet_FF : $(fichier_projet_FF)
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fichier_projet_FF) -o projet_FF
projet_FF.o : projet_FF.c inventaire.h	#voir si il faut changer le .h plus tard !!!!
	$(CCOBJ) $(CFLAGS) $(LIBMATH) projet_FF.c -o projet_FF.o -I./
#
# Modules(objets)
#

OBJ = inventaire.o perso.o

inventaire.o : inventaire.c inventaire.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) inventaire.c -o inventaire.o -I./

perso.o : perso.c perso.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) perso.c -o perso.o -I./



#
# Headers
#

inventaire.h : commun.h
	touch inventaire.h
perso.h : inventaire.h
	touch perso.h
#
#
#

all : $(BIN) $(OBJ)

clean :
	- rm  *.o
	- rm test_inventaire
	- rm test_perso
	- rm projet_FF

tests :
	./test_inventaire
	./test_perso
