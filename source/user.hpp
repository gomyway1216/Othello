// ------------------------------------------------------------
// AI 1 find the place that AI can put the stone and place it there
// ------------------------------------------------------------
#include <iostream>
#include <string>

#include "othello_ai.hpp"

// the name should be called OTHELLO_AI
class OTHELLO_AI{
private:
    Othello::GameInfo gameInfo;
    
public:
    OTHELLO_AI(const Othello::GameInfo & gameinfo) : gameInfo(gameinfo) {
    }
    
    std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
    {
        str.erase(0, str.find_first_not_of(chars));
        return str;
    }
    
    std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
    {
        str.erase(str.find_last_not_of(chars) + 1);
        return str;
    }
    
    std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
    {
        return ltrim(rtrim(str, chars), chars);
    }
    
    bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
    }
    
    // go through entire board
    Othello::Coord place(const Othello::Board & board){
        
        bool moveExist = false;
        for(int i = 0; i < board.rows(); ++i){
            for(int j = 0; j < board.cols(); ++j){
                // duplicate the board
                Othello::Board board_tmp = Othello::Board(board);
                
                
                // check if it is possible to put the stone at the place
                if(board_tmp.put_and_flip(i, j, gameInfo.my_color()) > 0){
                    // return the place
                    moveExist = true;
                }
            }
        }
        
        if(!moveExist)
            return Othello::Coord();
        
        // so from here, there is a move exist
        int row;
        int col;
        while(true) {
            std::cout << "Please enter the coodinate Format: row,col" << std::endl;
            std::string input;
            std::cin >> input;
            
            std::string delimiter = ",";
            
            if (input.find(delimiter) == std::string::npos || input.length() < 3)
                continue;

            std::string token;
            row = -1;
            col = -1;
            token = input.substr(0, input.find(delimiter));
            if(is_number(token)){
                int temp = stoi(token);
                if(temp < 1 || temp > 8)
                    continue;
                row = temp;
            }
               
            else
                continue;
                 
            if(token.length() == 0 || input.length()-1 < input.find(delimiter) + 1)
                continue;
            
            // column
            token = input.substr(input.find(delimiter) + 1);
               if(is_number(token)){
                int temp = stoi(token);
                if(temp < 1 || temp > 8)
                    continue;
                col = temp;
            }
            else
                continue;
            
            Othello::Board board_tmp = Othello::Board(board);
            if(board_tmp.put_and_flip(row-1, col-1, gameInfo.my_color()) > 0) {
                return Othello::Coord(row-1, col-1);
            }
            
            else
                std::cout << "Please choose the proper place" << std::endl;
            
        }

    }
};

