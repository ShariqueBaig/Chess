#include<iostream>
#include "raylib.h"
#include <cassert>

const int swidth=800, sheight=800,row=8, col=8, dx = swidth/col, dy = sheight/row;
class Pieces
{
    public:
    const int None = 0;
    const int wKing = 1;
    const int wQueen = 2;
    const int wPawn = 3;
    const int wRook = 4;
    const int wBishop = 5;
    const int wKnight = 6;

    const int bKing = -1;
    const int bQueen = -2;
    const int bPawn = -3;
    const int bRook = -4;
    const int bBishop = -5;
    const int bKnight = -6;
};

class Board
{
    public:
    int arr[8][8] = {};

    Texture2D wKing; // talk to sir about this issue
    Texture2D wQueen;
    Texture2D wRook;
    Texture2D wKnight;
    Texture2D wBishop;
    Texture2D wPawn;

    Texture2D bKing;
    Texture2D bQueen;
    Texture2D bRook;
    Texture2D bKnight;
    Texture2D bBishop;
    Texture2D bPawn;
    
    Pieces piece;
    Board()
    {
        Image wKingImage = LoadImage("./chess_pieces/wking.png");
        Image wQueenImage = LoadImage("./chess_pieces/wqueen.png");
        Image wRookImage = LoadImage("./chess_pieces/wrook.png");
        Image wKnightImage = LoadImage("./chess_pieces/wknight.png");
        Image wBishopImage = LoadImage("./chess_pieces/wbishop.png");
        Image wPawnImage = LoadImage("./chess_pieces/wpawn.png");

        // assert(IsImageReady(wKingImage))
        //     std :: cout<<"Unexpected";

        ImageResize(&wKingImage, dx-10, dy-10);
        ImageResize(&wKnightImage, dx-10, dy-10);
        ImageResize(&wRookImage, dx-10, dy-10);
        ImageResize(&wBishopImage, dx-10, dy-10);
        ImageResize(&wQueenImage, dx-10, dy-10);
        ImageResize(&wPawnImage, dx-10, dy-10);
        
        wKing = LoadTextureFromImage(wKingImage);
        // std::cout<<&wKingImage;
        wQueen = LoadTextureFromImage(wQueenImage);
        wRook = LoadTextureFromImage(wRookImage);
        wKnight = LoadTextureFromImage(wKnightImage);
        wBishop = LoadTextureFromImage(wBishopImage);
        wPawn = LoadTextureFromImage(wPawnImage);

        UnloadImage(wKingImage);
        UnloadImage(wQueenImage);
        UnloadImage(wRookImage);
        UnloadImage(wKnightImage);
        UnloadImage(wBishopImage);
        UnloadImage(wPawnImage);

        Image bKingImage = LoadImage("./chess_pieces/bking.png");
        Image bQueenImage = LoadImage("./chess_pieces/bqueen.png");
        Image bRookImage = LoadImage("./chess_pieces/brook.png");
        Image bKnightImage = LoadImage("./chess_pieces/bknight.png");
        Image bBishopImage = LoadImage("./chess_pieces/bbishop.png");
        Image bPawnImage = LoadImage("./chess_pieces/bpawn.png");


        ImageResize(&bKingImage, dx-10, dy-10);
        ImageResize(&bKnightImage, dx-10, dy-10);
        ImageResize(&bRookImage, dx-10, dy-10);
        ImageResize(&bBishopImage, dx-10, dy-10);
        ImageResize(&bQueenImage, dx-10, dy-10);
        ImageResize(&bPawnImage, dx-10, dy-10);

        bKing = LoadTextureFromImage(bKingImage);
        bQueen = LoadTextureFromImage(bQueenImage);
        bRook = LoadTextureFromImage(bRookImage);
        bKnight = LoadTextureFromImage(bKnightImage);
        bBishop = LoadTextureFromImage(bBishopImage);
        bPawn = LoadTextureFromImage(bPawnImage);

        UnloadImage(bKingImage);
        UnloadImage(bQueenImage);
        UnloadImage(bRookImage);
        UnloadImage(bKnightImage);
        UnloadImage(bBishopImage);
        UnloadImage(bPawnImage);

        arr[0][0] = piece.bRook;
        arr[0][1] = piece.bKnight;
        arr[0][2] = piece.bBishop;
        arr[0][3] = piece.bQueen;
        arr[0][4] = piece.bKing;
        arr[0][5] = piece.bBishop;
        arr[0][6] = piece.bKnight;
        arr[0][7] = piece.bRook;
        arr[1][0] = piece.bPawn;
        arr[1][1] = piece.bPawn;
        arr[1][2] = piece.bPawn;
        arr[1][3] = piece.bPawn;
        arr[1][4] = piece.bPawn;
        arr[1][5] = piece.bPawn;
        arr[1][6] = piece.bPawn;
        arr[1][7] = piece.bPawn;

        arr[6][0] = piece.wPawn;
        arr[6][1] = piece.wPawn;
        arr[6][2] = piece.wPawn;
        arr[6][3] = piece.wPawn;
        arr[6][4] = piece.wPawn;
        arr[6][5] = piece.wPawn;
        arr[6][6] = piece.wPawn;
        arr[6][7] = piece.wPawn;
        arr[7][0] = piece.wRook;
        arr[7][1] = piece.wKnight;
        arr[7][2] = piece.wBishop;
        arr[7][3] = piece.wQueen;
        arr[7][4] = piece.wKing;
        arr[7][5] = piece.wBishop;
        arr[7][6] = piece.wKnight;
        arr[7][7] = piece.wRook;
    }

    ~Board()
    {
        UnloadTexture(wKing);
        UnloadTexture(wQueen);
        UnloadTexture(wRook);
        UnloadTexture(wKnight);
        UnloadTexture(wBishop);
        UnloadTexture(wPawn);

        UnloadTexture(bKing);
        UnloadTexture(bQueen);
        UnloadTexture(bRook);
        UnloadTexture(bKnight);
        UnloadTexture(bBishop);
        UnloadTexture(bPawn);
    }

    void drawBoard() const
    {
        int counter=0;
        ClearBackground(WHITE);
        for(int i=0; i<8; ++i)
        {
            for(int j=0; j<8; ++j)
            {
                // color choice = GetColor(779954);
                if(counter % 2 == 0)
                    DrawRectangle(j*dx,i*dy,dx,dy,WHITE);
                else
                    DrawRectangle(j*dx,i*dy,dx,dy,ColorFromHSV(90, 29, 46));

                if(arr[i][j] == piece.bKing)
                    DrawTexture(bKing, j*dx, i*dy, RAYWHITE);
                if(arr[i][j] == piece.bQueen)
                    DrawTexture(bQueen, j*dx, i*dy, RAYWHITE);
                if(arr[i][j] == piece.bKnight)
                    DrawTexture(bKnight, j*dx, i*dy, RAYWHITE);
                if(arr[i][j] == piece.bRook)
                    DrawTexture(bRook, j*dx, i*dy, RAYWHITE);
                if(arr[i][j] == piece.bBishop)
                    DrawTexture(bBishop, j*dx, i*dy, RAYWHITE);
                if(arr[i][j] == piece.bPawn)
                    DrawTexture(bPawn, j*dx, i*dy, RAYWHITE);

                if(arr[i][j] == piece.wKing)
                    DrawTexture(wKing, j*dx, i*dy, RAYWHITE);
                if(arr[i][j] == piece.wQueen)
                    DrawTexture(wQueen, j*dx, i*dy, RAYWHITE);
                if(arr[i][j] == piece.wKnight)
                    DrawTexture(wKnight, j*dx, i*dy, RAYWHITE);
                if(arr[i][j] == piece.wRook)
                    DrawTexture(wRook, j*dx, i*dy, RAYWHITE);
                if(arr[i][j] == piece.wBishop)
                    DrawTexture(wBishop, j*dx, i*dy, RAYWHITE);
                if(arr[i][j] == piece.wPawn)
                    DrawTexture(wPawn, j*dx, i*dy, RAYWHITE);
                


                counter++;
            }
            counter--;
        }
    }

};

int main()
{
    InitWindow(swidth, sheight, "Chess go brrrr!!!!");
    Board gameboard;
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        gameboard.drawBoard();
        EndDrawing();

    }
    CloseWindow();
    return 0;
}