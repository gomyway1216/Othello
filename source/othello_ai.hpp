#ifndef OTHELLO_AI_HPP
#define OTHELLO_AI_HPP

#define OTHELLO_AI_USE_CPP11

#include <cstddef>
#include <vector>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>

namespace Othello{
#ifdef OTHELLO_AI_USE_CPP11
    enum class Color : char {
        BLACK = 1, // black is placed
        WHITE = 2, // white is placed
        EMPTY = 0, // no any stone is placed
        INVALID = 4 // if we want to specify invalid coordinate
        };
#else
        class Color {
        private:
            char val_;
        public:
            Color();
            Color(char val);
            operator char() const;
            bool operator ==(Color other) const;
            bool operator <(Color other) const;
            
            static const char BLACK;
            static const char WHITE;
            static const char EMPTY;
            static const char INVALID;
        };
#endif
        
        // get the color of opponent
        Color get_opponent_color(Color color);
        
        // convert from Black White space to actual characters to be printed
        char toPrintedPiece(Color color);
        
        class GameInfo{
        private:
            Color my_color_, opponent_color_;
//            int rows_num, cols_num;
            
        public:
            GameInfo(Color my, int r, int c);
            Color my_color() const;
            Color opponent_color() const;
        };
        
        constexpr int COORD_NULL = -1;
        
        class Coord{
        private:
            int row_, col_;
        public:
            Coord();
            Coord(int r, int c);
            Coord(const Coord & other);
            
            int row() const;
            int col() const;
            bool is_valid() const;
        };
        
        class Board{
        private:
            int rows_num, cols_num;
            std::vector<Color> places_;
            
            // check if the coodinate is within the board
            bool is_within_board(int i, int j) const;
            
        public:
            Board();
            Board(int rows, int cols);
            Board(const Board & other); // copy constructor
            static Board init(int rows, int cols); // initialize the board with 2 pieces for each team
            
            int rows() const;
            int cols() const;
            
            // initialize 1d array that stores the color of the stones including empty
            // rows * rowNum + column number
            std::map<Color, std::size_t> pieces() const;
            
            Color get(const Coord & coord) const;
            Color get(int i, int j) const;
            
            // new method
            int countOpenSpaces(int i, int j) const;
            int openSpaceCount(int i, int j, Color my_color) const;
            
            bool put_only(const Coord & coord, Color color);
            bool put_only(int i, int j, Color color);
    
            std::size_t put_and_flip(const Coord & coord, Color my_color);
            std::size_t put_and_flip(int i, int j, Color my_color);
            
            std::string state(const Coord & coord) const;
            std::string state(int current_r, int current_c) const;
            std::string state(void) const;
        };
    }
    
#endif // OTHELLO_AI_HPP
