#include <iostream>
#include "logic.h"

using std::cout, std::endl;

// TODO(student): Write unit tests for the functions in logic.h
//                You should end up with at least 500 lines of test code

int main() {
    
    // example
    /*
    example.txt
    -----------
    5 3
    3 0
    M + -
    - + -
    - + !
    - - -
    @ - $
    */
    ////////////////////
    // this is the only code _required_ to get coverage points on part 1 (test first)
    //   invocation --> coverage
    int maxRow;
    int maxCol;
    Player player;
    char** level = loadLevel("example.txt", maxRow, maxCol, player);
    ////////////////////
    
    ////////////////////
    // this is required to prevent memory leaks on part 1 (test first)
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }
    ////////////////////
    level=loadLevel("example1.txt",maxRow, maxCol,player);
    level=loadLevel("example2.txt",maxRow, maxCol,player);
    level=loadLevel("example3.txt",maxRow, maxCol,player);
    level=loadLevel("example4.txt",maxRow, maxCol,player);
    level=loadLevel("example5.txt",maxRow, maxCol,player);
    level=loadLevel("example6.txt",maxRow, maxCol,player);
    level=loadLevel("example7.txt",maxRow, maxCol,player);
    level=loadLevel("example8.txt",maxRow, maxCol,player);
    level=loadLevel("example9.txt",maxRow, maxCol,player);
    level=loadLevel("example10.txt",maxRow, maxCol,player);
    level=loadLevel("example11.txt",maxRow, maxCol,player);
    level=loadLevel("example12.txt",maxRow, maxCol,player);
    level=loadLevel("example13.txt",maxRow, maxCol,player);
    level=loadLevel("example14.txt",maxRow, maxCol,player);
    level=loadLevel("example15.txt",maxRow, maxCol,player);
    level=loadLevel("example16.txt",maxRow, maxCol,player);
    level=loadLevel("example17.txt",maxRow, maxCol,player);
    level=loadLevel("example18.txt",maxRow, maxCol,player);
    level=loadLevel("example",maxRow, maxCol,player);
    
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }
    //test getDirection

    int nrow;
    int ncol;

    //happy movement cases
    char move='w';
    getDirection(move,nrow,ncol);
    move='a';
    getDirection(move,nrow,ncol);
    move='s';
    getDirection(move,nrow,ncol);
    move='d';
    getDirection(move,nrow,ncol);
    //invalid case
    move='q';
    getDirection(move,nrow,ncol);
    

    //test deleteMap
    level = loadLevel("example.txt", maxRow, maxCol, player);
    deleteMap(level,maxRow); 

    level = loadLevel("example14.txt", maxRow, maxCol, player);
    deleteMap(level,maxRow);

    //test Resizemap
    level = loadLevel("example.txt", maxRow, maxCol, player);
    char**r=resizeMap(level,maxRow,maxCol);

    if(r){
        for (int row = 0; row < 10; row++) {
            delete[] r[row];
        }
        delete[] r;
    }

    //test doPlayerMove
    level = loadLevel("example.txt", maxRow, maxCol, player);
    
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=3;
    ncol=1;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=3;
    ncol=4;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=6;
    ncol=0;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=0;
    ncol=4;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=-3;
    ncol=1;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=3;
    ncol=-1;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=1;
    ncol=0;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=-1;
    ncol=0;


    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=1;
    ncol=1;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=0;
    ncol=0;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=3;
    ncol=1;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=4;
    ncol=0;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=4;
    ncol=2;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=2;
    ncol=2;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=0;
    ncol=2;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    nrow=3;
    ncol=0;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example25.txt", maxRow, maxCol, player);
    nrow=3;
    ncol=0;
    doPlayerMove(level,maxRow,maxCol,player,nrow,ncol);

    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    //test doMonsterAttack
    level = loadLevel("example.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example19.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example20.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example21.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example22.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example23.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example24.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example25.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example26.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example27.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example28.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example29.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example30.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }

    level = loadLevel("example31.txt", maxRow, maxCol, player);
    doMonsterAttack(level,maxRow,maxCol,player);
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }


    return 0;
}
