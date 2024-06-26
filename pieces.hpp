#pragma once
#include<iostream>
#include "raylib.h"
#include <cassert>
#include <cmath>
#include <vector>
using std::vector;

const int swidth=800, sheight=800,row=8, col=8, dx = swidth/col, dy = sheight/row;
enum Pieces
{
    NONE,
    WKING,
    WQUEEN,
    WPAWN1,
    WPAWN2,
    WPAWN3,
    WPAWN4,
    WPAWN5,
    WPAWN6,
    WPAWN7,
    WPAWN8,
    WROOKL,
    WROOKR,
    WBISHOP,
    WKNIGHT,

    BKING,
    BQUEEN,
    BPAWN1,
    BPAWN2,
    BPAWN3,
    BPAWN4,
    BPAWN5,
    BPAWN6,
    BPAWN7,
    BPAWN8,
    BROOKL,
    BROOKR,
    BBISHOP,
    BKNIGHT
};

class Piece
{
    public:
    Texture2D texture;
    Image image;
    int value;
    bool isWhite, firstMove = true;

    Piece() = default;
    Piece(const char* path, int dx, int dy, int val, bool ISWHITE)
    {
        image = LoadImage(path);
        ImageResize(&image, dx-10, dy-10);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        value = val;
        isWhite = ISWHITE;

    }

    virtual bool isValidMove(vector<vector<int>>& arr,std::pair<int, int> originalPosition,std::pair<int, int> destination)
    {
        std::cerr<<"Error 1"<<std::endl;
        return false;
    }
    virtual void drawValidMoves(vector<vector<int>>& arr, std::pair<int,int> position)
    {
        std::cerr<<"Error 2"<<std::endl;
    }
    virtual bool canDeliverCheck(vector<vector<int>>& arr, std::pair<int,int> position)
    {
        std::cerr<<"Error 3"<<std::endl;
        return true;
    }
    void unload()
    {
        UnloadTexture(texture);
    }
};

class King: public Piece{
    public:
    bool isFirstMove = true;
    bool inCheck = false;
    King(): Piece() {};
    King(const char* path, int dx, int dy, int val, bool ISWHITE): Piece(path, dx, dy, val, ISWHITE){};

    bool isValidMove(vector<vector<int>>& arr,std::pair<int,int> originalpos, std::pair<int,int> destination)
    {
        if(!(destination.first>=0 && destination.first<row && destination.second >=0 && destination.second <col))
            return false; // if out of bounds
        if(destination.first == originalpos.first && destination.second == originalpos.second)
            return true;
        if(arr[destination.first][destination.second] != NONE)
        {
            if(isWhite)
            {
                if(arr[destination.first][destination.second] > WKING && arr[destination.first][destination.second] <= WKNIGHT)
                {
                    return false;
                }
            }
            else
            {
                if(arr[destination.first][destination.second] > BKING && arr[destination.first][destination.second] <= BKNIGHT)
                {
                    return false;
                }
            }
        }

        if(destination.first == originalpos.first + 1)
        {
            if(destination.second == originalpos.second)
                return true;
            if(destination.second == originalpos.second + 1)
                return true;
            if(destination.second == originalpos.second - 1)
                return true;
        }
        else if(destination.first == originalpos.first)
        {
            if(destination.second == originalpos.second)
                return true;
            if(destination.second == originalpos.second + 1)
                return true;
            if(destination.second == originalpos.second - 1)
                return true;
        }
        else if(destination.first == originalpos.first - 1)
        {
            if(destination.second == originalpos.second)
                return true;
            if(destination.second == originalpos.second + 1)
                return true;
            if(destination.second == originalpos.second - 1)
                return true;
        }
        return false;
    }
    void drawValidMoves(vector<vector<int>>& arr, std::pair<int,int> position)
    {
        for(int i = position.first-1; i <= position.first+1; i++)
        {
            for(int j= position.second-1; j<=position.second+1; j++)
            {
                if(i>=0 && i<row && j>=0 && j<col)
                {
                    if(this->isValidMove(arr,position, {i,j}))
                        DrawCircle(j*dx + 50, i*dy + 50, dx/8, BLACK);
                }
            }
        }
    }
    bool canDeliverCheck(vector<vector<int>>& arr, std::pair<int,int> position)
    {
        if(isWhite)
        {
            std::pair<int,int> dest;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(arr[i][j] == BKING)
                    {
                        dest = {i,j};
                        break;
                    }
                }
            }
            if(this->isValidMove(arr, position, dest))
                return true;
            
            return false;
        }
        else
        {
            std::pair<int,int> dest;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(arr[i][j] == WKING)
                    {
                        dest = {i,j};
                        break;
                    }
                }
            }
            if(this->isValidMove(arr, position, dest))
                return true;
            
            return false;
        }
    }
};
class Pawn: public Piece{
    public:
    Pawn(): Piece(){};
    Pawn(const char* path, int dx, int dy, int val, bool ISWHITE): Piece(path, dx, dy, val, ISWHITE){};

    bool isValidMove(vector<vector<int>>& arr,std::pair<int,int> originalpos, std::pair<int,int> destination)
    {
        if(!(destination.first>=0 && destination.first<row && destination.second >=0 && destination.second <col))
            return false; // if out of bounds
        if(destination.first == originalpos.first && destination.second == originalpos.second)
            return true;
        if(arr[destination.first][destination.second] != NONE)
        {
            if(isWhite)
            {
                if(arr[destination.first][destination.second] >= WKING && arr[destination.first][destination.second] <= WKNIGHT)
                {
                    return false;
                }

                if(destination.first == originalpos.first-1 && (destination.second == originalpos.second - 1 || destination.second == originalpos.second + 1))
                    return true;
            }
            else
            {
                if(arr[destination.first][destination.second] >= BKING && arr[destination.first][destination.second] <= BKNIGHT)
                {
                    return false;
                }

                if(destination.first == originalpos.first+1 && (destination.second == originalpos.second - 1 || destination.second == originalpos.second + 1))
                    return true;
            }
            return false;
        }
        if(isWhite)
        {
            if(destination.first == originalpos.first -1 && destination.second == originalpos.second)
            {
                return true;
            }
            else if(firstMove && destination.first == originalpos.first -2 && destination.second == originalpos.second && arr[originalpos.first-1][originalpos.second] == NONE && arr[originalpos.first-2][originalpos.second]==NONE)
            {
                return true;
            }
            else 
                return false;
        }
        else
        {
            if(destination.first == originalpos.first +1 && destination.second == originalpos.second)
            {
                return true;
            }
            else if(firstMove && destination.first == originalpos.first +2 && destination.second == originalpos.second && arr[originalpos.first+1][originalpos.second] == NONE && arr[originalpos.first+2][originalpos.second] == NONE)
            {
                return true;
            }
            else 
                return false;
        }
    }

    void drawValidMoves(vector<vector<int>>& arr, std::pair<int,int> position)
    {
        if(this->isValidMove(arr,position, {position.first-1,position.second}))
            DrawCircle(position.second*dx + 50, (position.first-1)*dy + 50, dx/8, BLACK);
        if(this->isValidMove(arr,position, {position.first+2,position.second}))
            DrawCircle(position.second*dx + 50, (position.first+2)*dy + 50, dx/8, BLACK);
        if(this->isValidMove(arr,position, {position.first+2,position.second}))
            DrawCircle(position.second*dx + 50, (position.first-2)*dy + 50, dx/8, BLACK);
        if(this->isValidMove(arr,position, {position.first-2,position.second}))
            DrawCircle(position.second*dx + 50, (position.first+1)*dy + 50, dx/8, BLACK); //for up and down movement

        if(this->isValidMove(arr,position, {position.first-1,position.second-1})) //for captures
            DrawCircle((position.second-1)*dx + 50, (position.first-1)*dy + 50, dx/8, BLACK);
        if(this->isValidMove(arr,position, {position.first-1,position.second+1})) 
            DrawCircle((position.second+1)*dx + 50, (position.first-1)*dy + 50, dx/8, BLACK);
        if(this->isValidMove(arr,position, {position.first+1,position.second-1})) 
            DrawCircle((position.second-1)*dx + 50, (position.first+1)*dy + 50, dx/8, BLACK);
        if(this->isValidMove(arr,position, {position.first+1,position.second+1})) 
            DrawCircle((position.second+1)*dx + 50, (position.first+1)*dy + 50, dx/8, BLACK);
        
    }
    bool canDeliverCheck(vector<vector<int>>& arr, std::pair<int,int> position)
    {
        if(isWhite)
        {
            std::pair<int,int> dest;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(arr[i][j] == BKING)
                    {
                        dest = {i,j};
                        break;
                    }
                }
            }
            if(this->isValidMove(arr, position, dest))
                return true;
            
            return false;
        }
        else
        {
            std::pair<int,int> dest;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(arr[i][j] == WKING)
                    {
                        dest = {i,j};
                        break;
                    }
                }
            }
            if(this->isValidMove(arr, position, dest))
                return true;
            
            return false;
        }
    }
};
class Knight: public Piece{
    public:
    Knight(): Piece(){};
    Knight(const char* path, int dx, int dy, int val, bool ISWHITE): Piece(path, dx, dy, val, ISWHITE){};

    bool isValidMove(vector<vector<int>>& arr,std::pair<int,int> originalpos, std::pair<int,int> destination)
    {
        if(!(destination.first>=0 && destination.first<row && destination.second >=0 && destination.second <col))
            return false; // if out of bounds
        if(destination.first == originalpos.first && destination.second == originalpos.second)
            return true;
        if(arr[destination.first][destination.second] != NONE)
        {
            if(isWhite)
            {
                if(arr[destination.first][destination.second] >= WKING && arr[destination.first][destination.second] <= WKNIGHT)
                {
                    return false;
                }
            }
            else
            {
                if(arr[destination.first][destination.second] >= BKING && arr[destination.first][destination.second] <= BKNIGHT)
                {
                    return false;
                }
            }
        }
        if(destination.first == originalpos.first-2 && (destination.second == originalpos.second-1 || destination.second == originalpos.second+1))
            return true;

        else if(destination.first == originalpos.first+2 && (destination.second == originalpos.second-1 || destination.second == originalpos.second+1))
            return true;

        else if(destination.second == originalpos.second+2 && (destination.first == originalpos.first-1 || destination.first == originalpos.first+1))
            return true;

        else if(destination.second == originalpos.second-2 && (destination.first == originalpos.first-1 || destination.first == originalpos.first+1))
            return true;

        else 
            return false;  
    }
    void drawValidMoves(vector<vector<int>>& arr, std::pair<int,int> position)
    {
        if(this->isValidMove(arr,position, {position.first-2,position.second-1}))
            DrawCircle((position.second-1)*dx + 50, (position.first-2)*dy + 50, dx/8, BLACK);
        if(this->isValidMove(arr,position, {position.first-2,position.second+1}))
            DrawCircle((position.second+1)*dx + 50, (position.first-2)*dy + 50, dx/8, BLACK);

        if(this->isValidMove(arr,position, {position.first+2,position.second-1}))
            DrawCircle((position.second-1)*dx + 50, (position.first+2)*dy + 50, dx/8, BLACK);
        if(this->isValidMove(arr,position, {position.first+2,position.second+1}))
            DrawCircle((position.second+1)*dx + 50, (position.first+2)*dy + 50, dx/8, BLACK);
        
        if(this->isValidMove(arr,position, {position.first-1,position.second-2}))
            DrawCircle((position.second-2)*dx + 50, (position.first-1)*dy + 50, dx/8, BLACK);
        if(this->isValidMove(arr,position, {position.first+1,position.second-2}))
            DrawCircle((position.second-2)*dx + 50, (position.first+1)*dy + 50, dx/8, BLACK);
        
        if(this->isValidMove(arr,position, {position.first-1,position.second+2}))
            DrawCircle((position.second+2)*dx + 50, (position.first-1)*dy + 50, dx/8, BLACK);
        if(this->isValidMove(arr,position, {position.first+1,position.second+2}))
            DrawCircle((position.second+2)*dx + 50, (position.first+1)*dy + 50, dx/8, BLACK);
        
    }
    bool canDeliverCheck(vector<vector<int>>& arr, std::pair<int,int> position)
    {
        if(isWhite)
        {
            std::pair<int,int> dest;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(arr[i][j] == BKING)
                    {
                        dest = {i,j};
                        break;
                    }
                }
            }
            if(this->isValidMove(arr, position, dest))
                return true;
            
            return false;
        }
        else
        {
            std::pair<int,int> dest;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(arr[i][j] == WKING)
                    {
                        dest = {i,j};
                        break;
                    }
                }
            }
            if(this->isValidMove(arr, position, dest))
                return true;
            
            return false;
        }
    }
};
class Rook: public Piece{
    public:
    bool isFirstMove = true;
    Rook(): Piece(){};
    Rook(const char* path, int dx, int dy, int val, bool ISWHITE): Piece(path, dx, dy, val, ISWHITE){};
    
    bool isValidMove(vector<vector<int>>& arr,std::pair<int,int> originalpos, std::pair<int,int> destination)
    {
        if(!(destination.first>=0 && destination.first<row && destination.second >=0 && destination.second <col))
            return false; // if out of bounds
        if(destination.first == originalpos.first && destination.second == originalpos.second)
            return true;
        if(arr[destination.first][destination.second] != NONE)
        {
            if(isWhite)
            {
                if(arr[destination.first][destination.second] >= WKING && arr[destination.first][destination.second] <= WKNIGHT)
                {
                    return false;
                }
            }
            else
            {
                if(arr[destination.first][destination.second] >= BKING && arr[destination.first][destination.second] <= BKNIGHT)
                {
                    return false;
                }
            }
        }
        if(destination.first != originalpos.first && destination.second != originalpos.second)
        {
            return false;
        }
        if (destination.first == originalpos.first) // Moving horizontally
        {
            int startCol = std::min(originalpos.second, destination.second) + 1;
            int endCol = std::max(originalpos.second, destination.second);
            for (int col = startCol; col < endCol; ++col)
            {
                if (arr[destination.first][col] != NONE)
                    return false; // There's a piece blocking the path
            }
        }
        else // Moving vertically
        {
            int startRow = std::min(originalpos.first, destination.first) + 1;
            int endRow = std::max(originalpos.first, destination.first);
            for (int row = startRow; row < endRow; ++row)
            {
                if (arr[row][destination.second] != NONE)
                    return false; // There's a piece blocking the path
            }
        }

        return true;
    }
    void drawValidMoves(vector<vector<int>>& arr, std::pair<int,int> position)
    {
        for(int i=0; i<row;i++)
        {
            if(this->isValidMove(arr,position, {i,position.second}))
                DrawCircle(i*dx + 50, (position.second)*dy + 50, dx/8, BLACK);
        }
        for(int j=0; j<col;j++)
        {
            if(this->isValidMove(arr,position, {position.first,j}))
                DrawCircle(position.first*dx + 50, j*dy + 50, dx/8, BLACK);
        }
    }
    bool canDeliverCheck(vector<vector<int>>& arr, std::pair<int,int> position)
    {
        if(isWhite)
        {
            std::pair<int,int> dest;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(arr[i][j] == BKING)
                    {
                        dest = {i,j};
                        break;
                    }
                }
            }
            if(this->isValidMove(arr, position, dest))
                return true;
            
            return false;
        }
        else
        {
            std::pair<int,int> dest;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(arr[i][j] == WKING)
                    {
                        dest = {i,j};
                        break;
                    }
                }
            }
            if(this->isValidMove(arr, position, dest))
                return true;
            
            return false;
        }
    }
};
class Bishop: public Piece{
    public:
    Bishop(): Piece(){};
    Bishop(const char* path, int dx, int dy, int val, bool ISWHITE): Piece(path, dx, dy, val, ISWHITE){};

    bool isValidMove(vector<vector<int>>& arr,std::pair<int,int> originalpos, std::pair<int,int> destination)
    {
        if(!(destination.first>=0 && destination.first<row && destination.second >=0 && destination.second <col))
            return false; // if out of bounds
        if(!(destination.first>=0 && destination.first<row && destination.second >=0 && destination.second <col))
            return false; // if out of bounds
        if(destination.first == originalpos.first && destination.second == originalpos.second)
            return true;
        if(arr[destination.first][destination.second] != NONE)
        {
            if(isWhite)
            {
                if(arr[destination.first][destination.second] >= WKING && arr[destination.first][destination.second] <= WKNIGHT)
                {
                    return false;
                }
            }
            else
            {
                if(arr[destination.first][destination.second] >= BKING && arr[destination.first][destination.second] <= BKNIGHT)
                {
                    return false;
                }
            }
        }
        
        if(abs(destination.first - originalpos.first) == abs(destination.second - originalpos.second))
        {
            int deltaRow = destination.first - originalpos.first;
            int deltaCol = destination.second - originalpos.second;
            int delta = abs(deltaRow); // Delta for both row and column is the same

            int rowDir = deltaRow / abs(deltaRow);
            int colDir = deltaCol / abs(deltaCol);

            for (int i = 1; i < delta; ++i) {
                int row = originalpos.first + rowDir * i;
                int col = originalpos.second + colDir * i;
                if (arr[row][col] != NONE) {
                    return false; // Obstacle in the path
                }
            }
            return true;
        }
        return false;
    }
    void drawValidMoves(vector<vector<int>>& arr, std::pair<int,int> position) {
       for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                // Check if the destination is a valid move
                if (this->isValidMove(arr, position, {i, j})) {
                    // Draw a circle at the valid move position
                    DrawCircle(j * dx + 50, i * dy + 50, dx / 8, BLACK);
                }
            }
        }
    }
    bool canDeliverCheck(vector<vector<int>>& arr, std::pair<int,int> position)
    {
        if(isWhite)
        {
            std::pair<int,int> dest;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(arr[i][j] == BKING)
                    {
                        dest = {i,j};
                        break;
                    }
                }
            }
            if(this->isValidMove(arr, position, dest))
                return true;
            
            return false;
        }
        else
        {
            std::pair<int,int> dest;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(arr[i][j] == WKING)
                    {
                        dest = {i,j};
                        break;
                    }
                }
            }
            if(this->isValidMove(arr, position, dest))
                return true;
            
            return false;
        }
    }
};
class Queen: public Piece{
    public:
    Queen(): Piece(){};
    Queen(const char* path, int dx, int dy, int val, bool ISWHITE): Piece(path, dx, dy, val, ISWHITE){};

    bool isValidMove(vector<vector<int>>& arr,std::pair<int,int> originalpos, std::pair<int,int> destination)
    {
        if(!(destination.first>=0 && destination.first<row && destination.second >=0 && destination.second <col))
            return false; // if out of bounds
        if(destination.first == originalpos.first && destination.second == originalpos.second)
            return true;
        if(arr[destination.first][destination.second] != NONE)
        {
            if(isWhite)
            {
                if(arr[destination.first][destination.second] >= WKING && arr[destination.first][destination.second] <= WKNIGHT)
                {
                    return false;
                }
            }
            else
            {
                if(arr[destination.first][destination.second] >= BKING && arr[destination.first][destination.second] <= BKNIGHT)
                {
                    return false;
                }
            }
        }
        
        if (abs(destination.first - originalpos.first) == abs(destination.second - originalpos.second) || destination.first == originalpos.first || destination.second == originalpos.second)
        {
            if (abs(destination.first - originalpos.first) == abs(destination.second - originalpos.second))
            {
                int deltaRow = destination.first - originalpos.first;
                int deltaCol = destination.second - originalpos.second;
                int delta = abs(deltaRow); // Delta for both row and column is the same

                int rowDir = deltaRow / abs(deltaRow);
                int colDir = deltaCol / abs(deltaCol);

                for (int i = 1; i < delta; ++i) {
                    int row = originalpos.first + rowDir * i;
                    int col = originalpos.second + colDir * i;
                    if (arr[row][col] != NONE) {
                        return false; // Obstacle in the path
                    }
                }
                return true;
            }
    
            else // horizontal movement 
            {
                if (destination.first == originalpos.first) // Moving horizontally
                {
                    int startCol = std::min(originalpos.second, destination.second) + 1;
                    int endCol = std::max(originalpos.second, destination.second);
                    for (int col = startCol; col < endCol; ++col)
                    {
                        if (arr[destination.first][col] != NONE)
                            return false; // There's a piece blocking the path
                    }
                }
                else // Moving vertically
                {
                    int startRow = std::min(originalpos.first, destination.first) + 1;
                    int endRow = std::max(originalpos.first, destination.first);
                    for (int row = startRow; row < endRow; ++row)
                    {
                        if (arr[row][destination.second] != NONE)
                            return false; // There's a piece blocking the path
                    }
                }
            }
            return true;
        }
        return false;
    }
    void drawValidMoves(vector<vector<int>>& arr, std::pair<int, int> position)
    {
        for(int i=0; i<row; ++i)
        {
            for(int j=0; j<col; ++j)
            {
                if(this->isValidMove(arr, position, {i,j}))
                    DrawCircle(j*dx + 50, (i)*dy + 50, dx/8, BLACK);
            }
        }
    }
    bool canDeliverCheck(vector<vector<int>>& arr, std::pair<int,int> position)
    {
        if(isWhite)
        {
            std::pair<int,int> dest;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(arr[i][j] == BKING)
                    {
                        dest = {i,j};
                        break;
                    }
                }
            }
            if(this->isValidMove(arr, position, dest))
                return true;
            
            return false;
        }
        else
        {
            std::pair<int,int> dest;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(arr[i][j] == WKING)
                    {
                        dest = {i,j};
                        break;
                    }
                }
            }
            if(this->isValidMove(arr, position, dest))
                return true;
            
            return false;
        }
    }
};
