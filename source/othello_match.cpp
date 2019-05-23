#include <string>
#include <iostream>
#include <cstdlib>
#include <cstddef>

#include "othello_ai.hpp"

// choose the AI names here.
#define OTHELLO_AI_1_NAME "user.hpp"
#define OTHELLO_AI_2_NAME "ai2.hpp"

#define OTHELLO_AI OthelloAI1
#include OTHELLO_AI_1_NAME // include the AI
#undef OTHELLO_AI
#define OTHELLO_AI OthelloAI2
#include OTHELLO_AI_2_NAME  // include the AI
#undef OTHELLO_AI

template <class OthelloAIClass>
bool conduct_placement(OthelloAIClass & ai, const char * ai_name, Othello::Color turn, Othello::Board & board)
{
    bool piece_placed = true;
    
    // initialize temp bord instance
    Othello::Board board_tmp(board);
    
    const Othello::Coord place_from_ai = ai.place(board_tmp);
    // if the return value specifies the valid coodinate
    if(place_from_ai.is_valid()){
        //  put the stone there
        // I guess this part can get the user input
        std::size_t flipped = board.put_and_flip(place_from_ai, turn);
        
        // if you cannot flip anything after putting the stone it is an error
        if(flipped == 0){
            std::cerr << "[ERROR] Player " << Othello::toPrintedPiece(turn) << " [" << ai_name << "]: No piece flipped after putting at (" << place_from_ai.row() << ", " << place_from_ai.col() << ")" << std::endl;
            std::exit(-1);
        }
        piece_placed = true;
    }else{
        // if the return value says there is no place to put the stone
        
        // if there still exists places that stones can be placed but AI said no,
        // it is an error
        for(int i = 0; i < board.rows(); ++i){
            for(int j = 0; j < board.cols(); ++j){
                board_tmp = Othello::Board(board);
                if(board_tmp.put_and_flip(i, j, turn) > 0){
                    std::cerr << "[ERROR] Player " << Othello::toPrintedPiece(turn) << " [" << ai_name << "]: Passed although he/she can put a piece" << std::endl;
                    std::exit(-1);
                }
            }
        }
        
        piece_placed = false;
    }
    std::cout << "Player " << Othello::toPrintedPiece(turn) << " [" << ai_name << "] put at (" << place_from_ai.row() << ", " << place_from_ai.col() << "):" << std::endl;
    // this part is priting value to the console
    std::cout << board.state(place_from_ai) << std::endl;
    
    return piece_placed;
}

// this should be called first
int main(int argc, char ** argv){
    std::cout << "Welcome to Othello game!" << std::endl;
    std::cout << "Player Black: " << OTHELLO_AI_1_NAME << std::endl;
    std::cout << "Player White: " << OTHELLO_AI_2_NAME << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    const std::size_t rows = 8;
    const std::size_t cols = 8;
    
    OthelloAI1 ai1(Othello::GameInfo(Othello::Color::BLACK, rows, cols));
    OthelloAI2 ai2(Othello::GameInfo(Othello::Color::WHITE, cols, cols));
    
    Othello::Board board = Othello::Board::init(rows, cols);
    // count the number of passes, if it becomes 2, the game ends because nobody can put the stone
    std::size_t passed = 0;
    char tmp_input[3];
    
    // print the initial board
    std::cout << board.state() << std::endl;
    
    // infinite loop until the game ends
    // there is goal check
    
    for(;;){
        if(conduct_placement(ai1, OTHELLO_AI_1_NAME, Othello::Color::BLACK, board)){
            passed = 0;
        }else{
            ++passed;
            if(passed >= 2) break;
        }
        
        if(conduct_placement(ai2, OTHELLO_AI_2_NAME, Othello::Color::WHITE, board)){
            passed = 0;
        }else{
            ++passed;
            if(passed >= 2) break;
        }
    }
    
    // count the result
    std::map<Othello::Color, std::size_t> result = board.pieces();
    
    std::cout << "Game Ended!" << std::endl;
    std::cout << "Player Black [" << OTHELLO_AI_1_NAME << "]: " << result[Othello::Color::BLACK] << std::endl;
    std::cout << "Player White [" << OTHELLO_AI_2_NAME << "]: " << result[Othello::Color::WHITE] << std::endl;
    
    // Ends game
    std::cerr << std::endl << "<Press Enter key to exit>" << std::endl;
    std::cin.getline(tmp_input, 3);
    
    return 0;
}
