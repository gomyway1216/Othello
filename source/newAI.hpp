// ------------------------------------------------------------ // AI 1 find the place that AI can put the stone and place it there // ------------------------------------------------------------ #include "othello_ai.hpp"

class OTHELLO_AI{
    private: Othello::GameInfo gameInfo;
    public: OTHELLO_AI(const Othello::GameInfo & gameinfo) : gameInfo(gameinfo) {
        
    }
    
    // keep track of the open spaces around the stone to be put and stones to be flipped
    int minOpenSum = 9999;
    Othello::Coord minOpenSpaces_Coord;
    // keep track of the number of stones flipped in the corner.
    // When choosing the corner, choose the one that can flip most stones
    // 0: top left, 1: top right, 2: buttom left, 3: buttom right
    int cornerNumFlipped[3];
    for(std::size_t i = 0; i < 3; i++){
        cornerNumFlipped[i] = 0;
        
    }
//    Othello::Coord corner_Coord[3];
    
    // go through entire board
    Othello::Coord place(const Othello::Board & board){
        for(int i = 0; i < board.rows(); ++i) {
            for(int j = 0; j < board.cols(); ++j){
                // duplicate the board
                Othello::Board board_tmp = Othello::Board(board);
                //check if it is possible to put the stone at the place
                // whether the stone is inside of the board is already checked by this method.
                if(board_tmp.put_and_flip(i, j, gameInfo.my_color()) > 0){
                    // check sum of open spaces of the stone itself and stones to be flipped.
                    // check if it is in the corner
                    // top left
                    if(i == 0 && j == 0){
                        cornerNumFlipped[0] = board_tmp.put_and_flip(i, j, gameInfo.my_color());
                    }
                    
//                    top right
                    if(i == 0 && j == board.rows() - 1) {
                        cornerNumFlipped[1] = board_tmp.put_and_flip(i, j, gameInfo.my_color());
                    }
                    
//                    buttom left
                    if(i == board.rows() - 1 && j == 0) {
                        cornerNumFlipped[2] = board_tmp.put_and_flip(i, j, gameInfo.my_color());
                    }
                    
//                    buttom right
                    if(i == board.rows() - 1 && j == board.rows() - 1) {
                        cornerNumFlipped[3] = board_tmp.put_and_flip(i, j, gameInfo.my_color());
                    }
                    
                    int tempOpenSum = Othello::openSpaces(board_tmp.put_and_flip(i, j, gameInfo.my_color());
                    if(tempFlippedSum < minOpenSpaces) {
                        minOpenSpaces = tempFlippedSum;
                        minOpenSpaces_Coord = Othello::Coord(i, j);
                    }
                }
            }
        }
                                                          maxCornerNum = -1;
      for(int i = 0; i < 3; i++) {
          if(maxCornerNum)
      }
        // return the placereturn
        return Othello::Coord(i, j);
        // can't place the stone to anywhere
        // return Othello::Coord();
    }
}
