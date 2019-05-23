// ------------------------------------------------------------
// AI 1 find the place that AI can put the stone and place it there
// ------------------------------------------------------------
#include "othello_ai.hpp"

// the name should be called OTHELLO_AI
class OTHELLO_AI{
private:
    Othello::GameInfo gameInfo;
    
public:
    OTHELLO_AI(const Othello::GameInfo & gameinfo) : gameInfo(gameinfo) {
    }
    
    // go through entire board
    Othello::Coord place(const Othello::Board & board){
        for(int i = 0; i < board.rows(); ++i){
            for(int j = 0; j < board.cols(); ++j){
                // duplicate the board
                Othello::Board board_tmp = Othello::Board(board);

                // check if it is possible to put the stone at the place
                if(board_tmp.put_and_flip(i, j, gameInfo.my_color()) > 0){
                    // return the place
                    return Othello::Coord(i, j);
                }
            }
        }
        
        // can't place the stone to anywhere
        return Othello::Coord();
    }
};
