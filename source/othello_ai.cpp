#include "othello_ai.hpp"

namespace Othello{
#ifdef OTHELLO_AI_USE_CPP11
    // define nothing
#else
    bool Color::Color() : val_(0) {
    }
    bool Color::Color(char val) : val_(val) {
    }
    Color::operator char() const {
        return static_cast<char>(val_);
    }
    bool Color::operator ==(Color other) const {
        return val_ == other.val_;
    }
    bool Color::operator <(Color other) const {
        return val_ < other.val_;
    }
    
    const char Color::BLACK = 1;
    const char Color::WHITE = 2;
    const char Color::EMPTY = 0;
    const char Color::INVALID = 4;
#endif
    
    // get the color of opponent
    Color get_opponent_color(Color color){
        
        // change turn
        if(color == Color::WHITE) {
            return Color::BLACK;
        } else if(color == Color::BLACK){
            return Color::WHITE;
        } else {
            return color;
        }
    }
    
    // convert black, white into 'B', 'W'
    // #TODO check what would be returned by this functions
    char toPrintedPiece(Color color){
        return ".BW"[static_cast<size_t>(color)];
    }
    
    ///////////////////////////////GameInfo/////////////////////////////////////////
    
    // geth the infomation such as own color, the number of rows and columns
    GameInfo::GameInfo(Color my, int r, int c) : my_color_(my) {
        opponent_color_ = get_opponent_color(my);
    }
    
    Color GameInfo::my_color() const{
        return my_color_;
    }
    
    Color GameInfo::opponent_color() const{
        return opponent_color_;
    }
    
    /////////////////////Coord//////////////////////////////////////////////
    Coord::Coord() : row_(COORD_NULL), col_(COORD_NULL) {
    }
    
    Coord::Coord(int r, int c) : row_(r), col_(c) {
    }
    
    Coord::Coord(const Coord & other) : row_(other.row_), col_(other.col_) {
    }
    
    int Coord::row() const{
        return row_;
    }
    
    int Coord::col() const{
        return col_;
    }
    
    bool Coord::is_valid() const{
        return(row_ != COORD_NULL || col_ != COORD_NULL);
    }
    
    ////////////////////Board//////////////////////////////////////////////////////
    
    // constructor
    Board::Board() : rows_num(0), cols_num(0) {
    }
    
    // initialize 1d array that stores the color of the stones including empty
    // rows * rowNum + column number
    Board::Board(int rows, int cols) : rows_num(rows), cols_num(cols), places_(rows * cols, Color::EMPTY) {
      }
    
    // copy constructor
    Board::Board(const Board & other)
    : rows_num(other.rows_num), cols_num(other.cols_num), places_(other.places_) {
    }
    
    // initialize the board with 2 whites and 2 blacks at the center
    Board Board::init(int rows, int cols){
        Board board(rows, cols);
        board.put_only(rows/2 - 1, cols/2 - 1, Color::WHITE);
        board.put_only(rows/2 - 1, cols/2,     Color::BLACK);
        board.put_only(rows/2,     cols/2 - 1, Color::BLACK);
        board.put_only(rows/2,     cols/2,     Color::WHITE);
        return board;
    }
    
    // check if the coodinate is inside of the board
    bool Board::is_within_board(int i, int j) const{
        return((i >= 0 && i < rows_num) && (j >= 0 && j < cols_num));
    }

    
    int Board::rows() const{
        return rows_num;
    }
    
    int Board::cols() const{
        return cols_num;
    }
    
    // get the number of stones
    // the pair is <color, and number of stones>
    std::map<Color, std::size_t> Board::pieces() const {
        std::map<Color, std::size_t> result;
        Color c;
        
        for(int i = 0; i < rows_num; ++i){
            for(int j = 0; j < cols_num; ++j){
                c = get(i, j);
                if(result.count(c) == 0)
                    result[c] = 0;
                ++(result[c]);
            }
        }
        return result;
    }
    
    // get the stone based on the coodinate
    Color Board::get(const Coord & coord) const{
        return get(coord.row(), coord.col());
    }
    
    Color Board::get(int i, int j) const{
        if(!is_within_board(i, j)) return Color::INVALID;
        return places_[i * cols_num + j];
    }
    
    
    // new method to check the adjecent open spaces
    int Board::countOpenSpaces(int i, int j) const {
        int counter = 0;
        if(get(i-1, j)== Color::EMPTY)
            counter++;
        if(get(i-1, j+1)== Color::EMPTY)
            counter++;
        if(get(i, j+1)== Color::EMPTY)
            counter++;
        if(get(i+1, j+1)== Color::EMPTY)
            counter++;
        if(get(i+1, j)== Color::EMPTY)
            counter++;
        if(get(i+1, j-1)== Color::EMPTY)
            counter++;
        if(get(i, j-1)== Color::EMPTY)
            counter++;
        if(get(i-1, j-1)== Color::EMPTY)
            counter++;
        return counter;
    }
    
//    // check open spaces for every stones to be flipped
//    std::size_t Board::(const Coord & coord, Color my_color){
//        return put_and_flip(coord.row(), coord.col(), my_color);
//    }
    
    int Board::openSpaceCount(int i, int j, Color my_color) const {
        // if the coodinate is in the outside, return 0
        if(!is_within_board(i, j)) return 0;
        
        // if the stone already existed in the spot, we cannot put the stone there
        if(get(i, j) != Color::EMPTY) return 0;
        
        // get the opponent stone color
        Color opponent_color = get_opponent_color(my_color);
        
        // going for 8 direction
        int distance;
        int openSpaceSum = 0;
        for(int row_direction = -1; row_direction <= 1; ++row_direction){
            for(int col_direction = -1; col_direction <= 1; ++col_direction){
                int tempOpenSum = 0;
                // this means it is not moving either row direction or col direction
                if(row_direction == 0 && col_direction == 0) continue;
                
                // if the next stone isn't the opponent, don't flip
                if(get(i + row_direction, j + col_direction) != opponent_color){
                    continue;
                }
                
                // find the place that opponent stone continues and my stone appears
                distance = 1;
                while(get(i + distance * row_direction, j + distance * col_direction) == opponent_color){
                    tempOpenSum += countOpenSpaces(i + distance * row_direction, j + distance * col_direction);
                    ++distance;
                }
                
                // if the last stone is my color, we could flip the stones, otherwise we can't flip them
                // if we can't flip, we don't need to increment the openSpaceSum
                if(get(i + distance * row_direction, j + distance * col_direction) == my_color){
                    openSpaceSum += tempOpenSum;
                }
            }
        }
        return openSpaceSum;
    }
    
    // choose the place and put a stone
    bool Board::put_only(const Coord & coord, Color color){
        return put_only(coord.row(), coord.col(), color);
    }
    
    bool Board::put_only(int i, int j, Color color){
        if(!is_within_board(i, j))
            return false;
        places_[i * cols_num + j] = color;
        return true;
    }
    
    // pick the coodinate, put the user's stone. return the number of the stones flipped
    std::size_t Board::put_and_flip(const Coord & coord, Color my_color){
        return put_and_flip(coord.row(), coord.col(), my_color);
    }
    
    std::size_t Board::put_and_flip(int i, int j, Color my_color){
        // if the coodinate is in the outside, return 0
        if(!is_within_board(i, j)) return 0;
        
        // if the stone already existed in the spot, we cannot put the stone there
        if(get(i, j) != Color::EMPTY) return 0;
        
        // get the opponent stone color
        Color opponent_color = get_opponent_color(my_color);
        // the number of stones flipped
        int flipnum = 0;
        
        // going for 8 direction
        int distance;
        for(int row_direction = -1; row_direction <= 1; ++row_direction){
            for(int col_direction = -1; col_direction <= 1; ++col_direction){
                // this means it is not moving either row direction or col direction
                if(row_direction == 0 && col_direction == 0) continue;
                
                // if the next stone isn't the opponent, don't flip
                if(get(i + row_direction, j + col_direction) != opponent_color){
                    continue;
                }
                
                // find the place that opponent stone continues and my stone appears
                distance = 2;
                while(get(i + distance * row_direction, j + distance * col_direction) == opponent_color){
                    ++distance;
                }
                
                 // stones can be flipped if the next one if my stone, if not,
                // not stones are flipped
                if(get(i + distance * row_direction, j + distance * col_direction) == my_color){
                   
                    // increment the nubmer of the stones flipped
                    flipnum += distance - 1;
                    
                    // flip the stones
                    --distance;
                    for(; distance >= 1; --distance){
                        put_only(i + distance * row_direction, j + distance * col_direction, my_color);
                    }
                    
                    // current place that last stone is placed
                    put_only(i, j, my_color);
                }
            }
        }
        
        return flipnum;
    }
    
    // display where the stones are placed
    std::string Board::state(const Coord & coord) const{
        return state(coord.row(), coord.col());
    }
    
    std::string Board::state(int current_r, int current_c) const{
        std::stringstream ss;
        ss << "  ";
        int k;
        for(k = 1; k < 8; k++)
            ss << k << ' ';
        ss << k << '\n';
        
        for(int i = 0; i < rows_num; ++i){
            ss << i+1;
            for(int j = 0; j <= cols_num; ++j){
                if(i == current_r && j == current_c){
                    ss << '(';
                }else if(i == current_r && j == current_c+1){
                    ss << ')';
                }else{
                    ss << ' ';
                }
                if(j == cols_num) break;
                ss << toPrintedPiece(get(i, j));
            }
            ss << "\n";
        }
        return ss.str();
    }
    
    std::string Board::state(void) const{
        return state(-1, -1);
    }
}
