#include "othello_ai.hpp"

class OTHELLO_AI{
    private:
        Othello::GameInfo gameInfo;
    public:
        OTHELLO_AI(const Othello::GameInfo & gameinfo) : gameInfo(gameinfo) {
        }

        int checkSide(Othello::Board board, int i, int j) {
          // top or buttom
          if(i == 0 || i == board.rows() - 1){
              int c;

              // check to the left
              for(c = j-1; c >= 0; --c){
                  // check if the stone contines until the corner stone of its color
                  if(board.get(i, c) != gameInfo.my_color())
                    break;
              }
              if(c == -1)
                return 1;

              // check to the right
              for(c = j+1; c < board.cols(); ++c){
                  if(board.get(i, c) != gameInfo.my_color())
                    break;
              }

              if(c == board.cols())
                return 1;
          }

          // left or right
          if(j == 0 || j == board.cols() - 1){
              int c;

              // check to the top
              for(c = i-1; c >= 0; --c){
                  if(board.get(c, j) != gameInfo.my_color())
                  break;
              }
              if(c == -1)
                return 1;

              // check to the buttom
              for(c = i+1; c < board.rows(); ++c){
                  if(board.get(c, j) != gameInfo.my_color())
                  break;
              }

              if(c == board.rows())
              return 1;
          }

          // if we can't find any
          return 0;
        }



        // go through entire board
        Othello::Coord place(const Othello::Board & board){

          // keep track of the open spaces around the stone to be put and stones to be flipped
          int minOpenSum = 9999;
          int best_row = -1;
          int best_col = -1;

          for(int i = 0; i < board.rows(); ++i) {
              for(int j = 0; j < board.cols(); ++j){
                  // duplicate the board
                  Othello::Board board_tmp = Othello::Board(board);
                  //check if it is possible to put the stone at the place
                  // whether the stone is inside of the board is already checked by this method.
                  if(board_tmp.put_and_flip(i, j, gameInfo.my_color()) > 0){
                      // corner is the highest priority. This could be modifed for future algorithm
                      // if a stone can be placed in any of the corner, just place the stone thered

                      // Othello::Coord corner = checkCorner(board_tmp, i, j);
                      if((i == 0 || i == board.rows() - 1) && (j == 0 || j == board.cols() - 1)) {
                        return Othello::Coord(i, j);
                      }


                      if(checkSide(board_tmp, i, j) == 1) {
                        return Othello::Coord(i, j);
                      }
                      
                      int tempOpenSum = board.openSpaceCount(i, j, gameInfo.my_color());

                      // check if the coordinate is adjcent to the corner
                      // for instance, if the corner this ai is pointing at is 0,0
                      // if the stone in 0,0 is opponent, 0,1 1,0 and 1,1 should be avoided
                      if((i == 0 && j == 1 && board.get(0, 0) != gameInfo.my_color())
                        || (i == 1 && j == 1 && board.get(0, 0) != gameInfo.my_color())
                        || (i == 1 && j == 0 && board.get(0, 0) != gameInfo.my_color())
                        || (i == 1 && j == 7 && board.get(0, 7) != gameInfo.my_color())
                        || (i == 1 && j == 6 && board.get(0, 7) != gameInfo.my_color())
                        || (i == 0 && j == 6 && board.get(0, 7) != gameInfo.my_color())
                        || (i == 6 && j == 0 && board.get(7, 0) != gameInfo.my_color())
                        || (i == 6 && j == 1 && board.get(7, 0) != gameInfo.my_color())
                        || (i == 7 && j == 1 && board.get(7, 0) != gameInfo.my_color())
                        || (i == 7 && j == 6 && board.get(7, 7) != gameInfo.my_color())
                        || (i == 6 && j == 6 && board.get(7, 7) != gameInfo.my_color())
                        || (i == 6 && j == 7 && board.get(7, 7) != gameInfo.my_color())) {
                          // Technically, this should not increase tempOpenSum
                          //# TODO make score val in the future and add it to the score
                          tempOpenSum += 15;
                        }

                      // for the rest,
                      // check sum of open spaces of the stone itself and stones to be flipped.
                      if(tempOpenSum < minOpenSum) {
                        minOpenSum = tempOpenSum;
                        best_row = i;
                        best_col = j;
                      }
                  }
              }
          }

          // return the placereturn
          return Othello::Coord(best_row, best_col);
          // can't place the stone to anywhere
          // return Othello::Coord();
        }
};
