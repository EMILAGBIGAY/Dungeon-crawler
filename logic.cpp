#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {

    //open file name
    ifstream f(fileName);

    //check if already opened
    if(!f.is_open()){
        return nullptr;
    }

    //determine max row and col
    f>>maxRow;
    if(!f.good())
        return nullptr;
    f>>maxCol;
    if(!f.good())
        return nullptr;

    //determine the player row and col
    f>>player.row;
    if(!f.good())
        return nullptr;
    f>>player.col;
    if(!f.good())
        return nullptr;

    //create new level map
    char**level=createMap(maxRow,maxCol);

    //check if map is valid cases for row and col
    if(level == nullptr){
        return nullptr;
    }
    if(maxRow<=0 || maxCol<=0){
        return nullptr;
    }
    if(player.row <0 ||player.col<0)
        return nullptr;
    if(player.row > maxRow || player.col >maxCol)
        return nullptr;
    if(maxRow>INT32_MAX/2 || maxCol >INT32_MAX/2)
        return nullptr;
    if(player.row>INT32_MAX/2 || player.col >INT32_MAX/2)
        return nullptr;
    

    //make pointer of map
    bool exit = false;   //find exit or door
    string spot = "-$@M+?!o"; //valid tile
    int tot=0;
    for(int i=0;i<maxRow;++i){
        for(int j=0;j<maxCol;++j){
            if(!f.eof()){
                f>>level[i][j];
                tot++;
                if(!f.good())
                    return nullptr;
                if(spot.find(level[i][j]) == std::string::npos)
                    return nullptr;
                if(level[i][j]==TILE_EXIT || level[i][j]==TILE_DOOR)
                    exit=true;
            }
            else{
                return nullptr;
            }
        }
    }   
    if(tot != maxRow*maxCol)
        return nullptr;
    if(!exit){
        return nullptr;
    }
    level[player.row][player.col]=TILE_PLAYER;
    return level;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {

    if(input==MOVE_UP)
        nextRow -=1;
    else if(input==MOVE_DOWN)
        nextRow +=1;
    else if(input==MOVE_LEFT)
        nextCol -=1;
    else if(input==MOVE_RIGHT)
        nextCol +=1;
    
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    //declare pointer new char array
    char**m=new char*[maxRow];
    for(int i=0;i<maxRow;++i){
        m[i]=new char[maxCol];
        for(int j=0;j<maxCol;++j){
            m[i][j]=TILE_OPEN;
        }
        
    }
    return m;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
  if(map != nullptr){
        for (int row = 0; row < maxRow; row++) {
            delete[] map[row];
        }
        delete[] map;
    }
  map=nullptr;
  maxRow=0;
    
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    
    int old=maxRow;
    //check if map exists
    if(map==nullptr){
        return nullptr;
    }

    //bounds
    if(maxRow < 1 || maxCol < 1){
        return nullptr;
    }

    //change row and col
    char**resize=createMap(maxRow*2,maxCol*2);

    //create the new map
    for(int i=0;i<maxRow;++i){
        for(int j=0;j<maxCol;++j){
            if(map[i][j] == TILE_PLAYER){
                resize[i][j]=TILE_PLAYER;
                resize[i+maxRow][j] = TILE_OPEN;
                resize[i][j+maxCol] = TILE_OPEN;
                resize[i+maxRow][j+maxCol] = TILE_OPEN;
            }
            else{
                resize[i][j]=map[i][j];
                resize[i+maxRow][j] = map[i][j];
                resize[i][j+maxCol] = map[i][j];
                resize[i+maxRow][j+maxCol] = map[i][j];
                
                
            }
        }
    }

    //memory
    deleteMap(map,old);
    maxRow *= 2;
	maxCol *= 2;

    return resize;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {

    

    //player has to stay
    if(nextRow < 0 || nextRow > maxRow-1|| nextCol < 0 || nextCol > maxCol-1|| map[nextRow][nextCol] == TILE_PILLAR || map[nextRow][nextCol] == TILE_MONSTER){
        nextRow=player.row;
        nextCol=player.col;
        return STATUS_STAY;
    }

    //player can move
    if(map[nextRow][nextCol]==TILE_OPEN){
        map[player.row][player.col]=TILE_OPEN;
        player.row=nextRow;
        player.col=nextCol;
        map[player.row][player.col]=TILE_PLAYER;
        return STATUS_MOVE;
    }

    //player find treasure
    if(map[nextRow][nextCol]==TILE_TREASURE){
        map[player.row][player.col]=TILE_OPEN;
        player.row=nextRow;
        player.col=nextCol;
        map[player.row][player.col]=TILE_PLAYER;
        player.treasure++;
        return STATUS_TREASURE;
    }

    //player finds amulet
    if(map[nextRow][nextCol]==TILE_AMULET){
        map[player.row][player.col]=TILE_OPEN;
        player.row=nextRow;
        player.col=nextCol;
        map[player.row][player.col]=TILE_PLAYER;
        return STATUS_AMULET;
    }

    //player finds door
    if(map[nextRow][nextCol]==TILE_DOOR){
        map[player.row][player.col]=TILE_OPEN;
        player.row=nextRow;
        player.col=nextCol;
        map[player.row][player.col]=TILE_PLAYER;
        return STATUS_LEAVE;
    }

    //player finds escape
    if(map[nextRow][nextCol]==TILE_EXIT && player.treasure >= 1){
        map[player.row][player.col]=TILE_OPEN;
        player.row=nextRow;
        player.col=nextCol;
        map[player.row][player.col]=TILE_PLAYER;
        return STATUS_ESCAPE;
    }
    else{
        nextRow=player.row;
        nextCol=player.col;
        return STATUS_STAY;
    }


}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    bool attack = false;
    //look up
    for(int i = player.row-1; i >= 0;--i){
        if(map[i][player.col]==TILE_PILLAR){
            break;
        }
        if(map[i][player.col]==TILE_MONSTER){
            map[i][player.col]=TILE_OPEN;
            map[i+1][player.col]=TILE_MONSTER;
            if(map[i+1][player.col]==map[player.row][player.col]){
              attack = true;
        }
      }
        
    }

    //look down
    for(int i = player.row+1; i < maxRow;++i){
        if(map[i][player.col]==TILE_PILLAR){
            break;
        }
        if(map[i][player.col]==TILE_MONSTER){
            map[i][player.col]=TILE_OPEN;
            map[i-1][player.col]=TILE_MONSTER;
            if(map[i-1][player.col]==map[player.row][player.col]){
             attack = true;
        }
      }
        
    }

    //look right
    for(int i = player.col+1; i < maxCol;++i){
        if(map[player.row][i]==TILE_PILLAR){
            break;
        }
        if(map[player.row][i]==TILE_MONSTER){
            map[player.row][i]=TILE_OPEN;
            map[player.row][i-1]=TILE_MONSTER;
            if(map[player.row][i-1]==map[player.row][player.col]){
              attack = true;
        }
      }
        
    }
    //look left
    for(int i = player.col-1; i >= 0;--i){
        if(map[player.row][i]==TILE_PILLAR){
            break;
        }
        if(map[player.row][i]==TILE_MONSTER){
            map[player.row][i]=TILE_OPEN;
            map[player.row][i+1]=TILE_MONSTER;
            if(map[player.row][i+1]==map[player.row][player.col]){
              attack = true;
        }
      }
        
    }

    //player dead or not
    if(attack){
      map[player.row][player.col]=TILE_MONSTER;
      return true;
    }
    return false;
}
