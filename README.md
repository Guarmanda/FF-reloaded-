# FF-reloaded-

Installation: download everything, execute the command "export  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./SDL2/lib", execute "make" if needed, then run that shity game

A final-fantasy-like 2d game by Nathalie Karman, Alexandre Papot, Valentin Girod

Tasks:
1- create player (stats, progress, inventory) 
  
  
struct character/monster : stats (integer), level, progression bar, health , mana, state (stunt, poisonned, sleep etc...)
  
enum class
  
  array of pointer on struct object : name char*
  
create typedef enum for armors/weapons/potions etc (pointer on maximum 30 objects)
  

2 - menu/interface  
  SDL, switch, welcome menu, fighting menu, inventory menu, dialogue window , 

3 - map
  matrice (two, display and threat level), monster type (coordinate), random fight

4 - quests (game goal)
  char*

5 - monsters/combats
  bestiary (class ?)
  
  
