# FF-reloaded-

commandes GIT:
git clone --single-branch --branch version_terminal https://github.com/Guarmanda/FF-reloaded-.git

git config --add user.email "addresse@domaine.fr"

git commit -m "Suppression des fichiers SDL"

Installation: download everything, execute the command "export  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./SDL2/lib", execute "make" if needed, then run that game.

A final-fantasy-like 2d game by Nathalie Karman, Alexandre Papot, Valentin Girod

Chronologie du projet

1) premières séances 
- Nathalie, Alexandre
                     => fichiers perso.c/perso.h (aujourd'hui perso_commun.c et autres);
                     => fichiers inventaire.c/inventaire.h
                     => boîte à outils (commun.c/commun.h)
                     => fichier test_inventaire.c qui à priori n'était basé que sur les fichiers inventaire.[hc]
                   
- Valentin 
           => prise en main SDL, éditeur de map créé (via SDL) ; l'éditeur permet de placer des objets différents sur la map et changer le fichier Map.txt avec la bonne valeur (int) qui est associée à de l'herbe, de l'eau, une maison, etc.

2) séances intermédiaires 
- Nathalie 
          => Makefile et résolution des dépendances circulaires entre les fichiers, réimplémentation de test_inventaire avec le makefile et implémentation de test_perso
- Alexandre 
            => première version de combat.c et combat.h
- Valentin 
            => tests avec la SDL et implémentation des fichiers perso.c/perso.h ; recherche de sprites et soucis avec redimension de l'écran pour l'affichage des statistiques du personnage (points de vie); améliorer les performances (utilisation CPU lors de l'utilisation sdl)

3) séances intermédiaires 
- Nathalie 
            => implémentation de test_combat.c, changements sur combat.[hc], débogage, maj Makefile.
- Alexandre 
            => Doxygen, ajout de fonctions à la boîte à outils commun.c + aide sur le débogage combat.c.
- Valentin 
            => continuation sur l'affichage des stats, débogage, création de quetes.txt quete.c (sdl) et quete.h (usage commun version terminal possible -à vérifier-) pour les tests d'affichage des pnj sur la map et de leur bulle de dialogue. Menu de début de jeu en ncurses pour aider à faire l'affichage version terminal + essais d'affichage ncurses map.

4) séances intermédiaires 
- Nathalie => débogage sur les fuites de mémoire pour test_perso, test_inventaire, création des sorts sur combat.c; essai d'implémentation  ncurses avec les fichiers de la version terminal === on continue sur ce qui était prévu dès le début : affichage terminal pur (séance non concluante).
- Alexandre => mise en place de sauvegarde.[hc] (chargement de partie) et des fonctions d'affichage de la map mise à l'échelle dans le main projet_FF.c.
- Valentin => continuation sdl.

5) séances intermédiaires 
- Nathalie => définition des biomes de la map, création map_menace.[hc], séparation du fichier perso.c en perso_commun.c et ses dérivés perso_monstre.c/perso_joueur.c. Débogage combat.c + affichage des actions en combat (gérer les menus, les retours, les game over, les monstres, etc).
- Alexandre => aide sur les sorts dans combat.c, continuation sur sauvegarde.c et affichage du personnage sur la map en version terminal.
- Valentin => implémentation map_menace.c (biomes) en sdl, recherches pour l'affichage du combat.

6) dernières séances
- Nathalie => amélioration du combat.c, sorts implémentés, affichage peaufiné.
- Alexandre => changements dans sauvegarde.c pour suivre les changements des fichiers perso_joueur.c
- Valentin => implémentation combat en SDL.



  

