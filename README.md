# FF-reloaded-

Installation: download everything, execute the command "export  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./SDL2/lib", execute "make" if needed, then run that shity game

Doxygen : http://info.univ-lemans.fr/~s171510/index.html

A final-fantasy-like 2d game by Nathalie Karman, Alexandre Papot, Valentin Girod

Tasks:
1- create player (stats, progress, inventory) 
  
  
struct character/monster : stats (integer), level, progression bar, health , mana, state (stunt, poisonned, sleep etc...)
  
enum class
  
  array of pointer on struct object : name char*
  
create typedef enum for armors/weapons/potions etc (pointer on maximum 30 objects)
  

2 - Valentin Grirod: menu/interface  
  SDL, switch, welcome menu, fighting menu, inventory menu, dialogue window , quests

3 - Alexandre Papot / Nathalie Karman / Valentin: map
  matrice (two, display and threat level), monster type (coordinate), random fight

4 - Nathalie Karman / Alexandre Papot: game goal
  

5 - Nathalie Karman / Alexandre Papot: monsters/combats
  bestiary (class ?)
  
  
