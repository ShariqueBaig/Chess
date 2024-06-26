#include "pieces.hpp"
class Board
{
    vector<vector<int>> arr;
    vector<vector<bool>> selected;
    std::pair<int,int> originalPosition, destination; //first x, second y
    bool isOver = false;
    bool stalemate = false;
    bool moveWhite = true;
    bool PieceWhite;
    bool initialstate = true; // 0 when the piece is not selected and 1 when piece is selected 
    // bool holding=false;
    Vector2 mousepos = {0.0f, 0.0f};
    Sound soundMove = LoadSound("chess_sound/move.wav");
    Sound soundCapture = LoadSound("chess_sound/capture.wav");
    Sound soundCheck = LoadSound("chess_sound/check.wav");
    Sound soundCastling = LoadSound("chess_sound/castling.wav");

    // Piece blank;
    Piece* movedPiece = nullptr;

    King wKing; // talk to sir about this issue
    Queen wQueen;
    Rook wRookl;
    Rook wRookr;
    Knight wKnight;
    Bishop wBishop;
    Pawn wPawn1;
    Pawn wPawn2;
    Pawn wPawn3;
    Pawn wPawn4;
    Pawn wPawn5;
    Pawn wPawn6;
    Pawn wPawn7;
    Pawn wPawn8;

    King bKing;
    Queen bQueen;
    Rook bRookl;
    Rook bRookr;
    Knight bKnight;
    Bishop bBishop;
    Pawn bPawn1;
    Pawn bPawn2;
    Pawn bPawn3;
    Pawn bPawn4;
    Pawn bPawn5;
    Pawn bPawn6;
    Pawn bPawn7;
    Pawn bPawn8;
    
    public:
    Board() : arr(row, vector<int>(col)), selected(row, vector<bool>(col, 0))
    {   
        wKing = King("./chess_pieces/wking.png", dx-10, dy-10, WKING, true);
        wQueen = Queen("./chess_pieces/wqueen.png", dx-10, dy-10, WQUEEN, true);
        wRookl = Rook("./chess_pieces/wrook.png", dx-10, dy-10, WROOKL, true);
        wRookr = Rook("./chess_pieces/wrook.png", dx-10, dy-10, WROOKR, true);
        wKnight = Knight("./chess_pieces/wknight.png", dx-10, dy-10, WKNIGHT, true);
        wBishop = Bishop("./chess_pieces/wbishop.png", dx-10, dy-10, WBISHOP, true);
        wPawn1 = Pawn("./chess_pieces/wpawn.png", dx-10, dy-10, WPAWN1, true);
        wPawn2 = Pawn("./chess_pieces/wpawn.png", dx-10, dy-10, WPAWN2, true);
        wPawn3 = Pawn("./chess_pieces/wpawn.png", dx-10, dy-10, WPAWN3, true);
        wPawn4 = Pawn("./chess_pieces/wpawn.png", dx-10, dy-10, WPAWN4, true);
        wPawn5 = Pawn("./chess_pieces/wpawn.png", dx-10, dy-10, WPAWN5, true);
        wPawn6 = Pawn("./chess_pieces/wpawn.png", dx-10, dy-10, WPAWN6, true);
        wPawn7 = Pawn("./chess_pieces/wpawn.png", dx-10, dy-10, WPAWN7, true);
        wPawn8 = Pawn("./chess_pieces/wpawn.png", dx-10, dy-10, WPAWN8, true);

        bKing = King("./chess_pieces/bking.png", dx-10, dy-10, BKING, false);
        bQueen = Queen("./chess_pieces/bqueen.png", dx-10, dy-10, BQUEEN, false);
        bRookl = Rook("./chess_pieces/brook.png", dx-10, dy-10, BROOKL, false);
        bRookr = Rook("./chess_pieces/brook.png", dx-10, dy-10, BROOKR, false);
        bKnight = Knight("./chess_pieces/bknight.png", dx-10, dy-10, BKNIGHT, false);
        bBishop = Bishop("./chess_pieces/bbishop.png", dx-10, dy-10, BBISHOP, false);
        bPawn1 = Pawn("./chess_pieces/bpawn.png", dx-10, dy-10, BPAWN1, false);
        bPawn2 = Pawn("./chess_pieces/bpawn.png", dx-10, dy-10, BPAWN2, false);
        bPawn3 = Pawn("./chess_pieces/bpawn.png", dx-10, dy-10, BPAWN3, false);
        bPawn4 = Pawn("./chess_pieces/bpawn.png", dx-10, dy-10, BPAWN4, false);
        bPawn5 = Pawn("./chess_pieces/bpawn.png", dx-10, dy-10, BPAWN5, false);
        bPawn6 = Pawn("./chess_pieces/bpawn.png", dx-10, dy-10, BPAWN6, false);
        bPawn7 = Pawn("./chess_pieces/bpawn.png", dx-10, dy-10, BPAWN7, false);
        bPawn8 = Pawn("./chess_pieces/bpawn.png", dx-10, dy-10, BPAWN8, false);

        arr[0][0] = BROOKL;
        arr[0][1] = BKNIGHT;
        arr[0][2] = BBISHOP;
        arr[0][3] = BQUEEN;
        arr[0][4] = BKING;
        arr[0][5] = BBISHOP;
        arr[0][6] = BKNIGHT;
        arr[0][7] = BROOKR;
        arr[1][0] = BPAWN1;
        arr[1][1] = BPAWN2;
        arr[1][2] = BPAWN3;
        arr[1][3] = BPAWN4;
        arr[1][4] = BPAWN5;
        arr[1][5] = BPAWN6;
        arr[1][6] = BPAWN7;
        arr[1][7] = BPAWN8;

        for(int i=2; i<6; ++i)
        {
            for(int j=0; j<col; ++j)
            {
                arr[i][j] = NONE;
            }
        }

        arr[6][0] = WPAWN1;
        arr[6][1] = WPAWN2;
        arr[6][2] = WPAWN3;
        arr[6][3] = WPAWN4;
        arr[6][4] = WPAWN5;
        arr[6][5] = WPAWN6;
        arr[6][6] = WPAWN7;
        arr[6][7] = WPAWN8;
        arr[7][0] = WROOKL;
        arr[7][1] = WKNIGHT;
        arr[7][2] = WBISHOP;
        arr[7][3] = WQUEEN;
        arr[7][4] = WKING;
        arr[7][5] = WBISHOP;
        arr[7][6] = WKNIGHT;
        arr[7][7] = WROOKR;
    }

    ~Board()
    {
        // blank.unload();
        delete movedPiece;

        wKing.unload();
        wQueen.unload();
        wRookl.unload();
        wRookr.unload();
        wKnight.unload();
        wBishop.unload();
        wPawn1.unload();
        wPawn2.unload();
        wPawn3.unload();
        wPawn4.unload();
        wPawn5.unload();
        wPawn6.unload();
        wPawn7.unload();
        wPawn8.unload();

        bKing.unload();
        bQueen.unload();
        bRookl.unload();
        bRookr.unload();
        bKnight.unload();
        bBishop.unload();
        bPawn1.unload();
        bPawn2.unload();
        bPawn3.unload();
        bPawn4.unload();
        bPawn5.unload();
        bPawn6.unload();
        bPawn7.unload();
        bPawn8.unload();
    }

    void printOverScreen(bool moveWhite)
    {
        ClearBackground(BLUE);
        if(moveWhite)
            DrawText("Black Wins", 200, 200,50, YELLOW);
        else
            DrawText("White Wins", 200, 200,50, YELLOW);
    }
    void printStaleMate()
    {
        ClearBackground(BLUE);
        DrawText("Stalemate", 200, 200,50, YELLOW);
    }
    bool move(vector<vector<int>>& arr, std::pair<int,int> &originalPosition, std::pair<int,int> &destination, Piece* movedPiece)
    {
        if(movedPiece->value == WKING && originalPosition.first == 7 && originalPosition.second == 4 && movedPiece->firstMove)
        {
            if(destination.first == 7 && destination.second == 2)
            {
                arr[7][3] = WROOKL;
                arr[7][0] = NONE;
                arr[7][2] = WKING;
                return true;
            }
            if(destination.first == 7 && destination.second == 6)
            {
                arr[7][5] = WROOKR;
                arr[7][7] = NONE;
                arr[7][6] = WKING;
                return true;
            }
        }
        else if(movedPiece->value == BKING && originalPosition.first == 0 && originalPosition.second == 4 && movedPiece->firstMove)
        {
            if(destination.first == 0 && destination.second == 2)
            {
                arr[0][3] = BROOKL;
                arr[0][0] = NONE;
                arr[0][2] = BKING;
                return true;
            }
            if(destination.first == 0 && destination.second == 6)
            {
                arr[0][5] = BROOKR;
                arr[0][7] = NONE;
                arr[0][6] = BKING;
                return true;
            }
        }
        if(arr[destination.first][destination.second] == NONE)
            PlaySound(soundMove);
        else if (!(destination.first == originalPosition.first && destination.second == originalPosition.second))
            PlaySound(soundCapture);
        if(!(originalPosition.first == destination.first && originalPosition.second == destination.second))
        {
            selected[destination.first][destination.second] = false;
            arr[destination.first][destination.second] = arr[originalPosition.first][originalPosition.second];
            arr[originalPosition.first][originalPosition.second] = NONE;
        }
        selected[originalPosition.first][originalPosition.second] = false;

        movedPiece = nullptr;
        return true;
    }
    vector<vector<int>> movecopy(vector<vector<int>> arr, std::pair<int,int> originalPosition, std::pair<int,int> destination, Piece* movedPiece)
    {
        if(!(originalPosition.first == destination.first && originalPosition.second == destination.second))
        {
            arr[destination.first][destination.second] = arr[originalPosition.first][originalPosition.second];
            arr[originalPosition.first][originalPosition.second] = NONE;
        }
        return arr;
    }
    bool isLegalMove(vector<vector<int>>& arr,std::pair<int, int> originalPosition,std::pair<int, int> destination, Piece* movedPiece)
    {
        //castling
        if(movedPiece->value == WKING && originalPosition.first == 7 && originalPosition.second == 4)
        {
            if(destination.first == 7 && destination.second == 2)
            {
                if(arr[7][0] == WROOKL && arr[7][1] == NONE && arr[7][2] == NONE && arr[7][3] == NONE && movedPiece->firstMove && wRookl.firstMove)
                {
                    vector<vector<int>> arr2(row, vector<int>(col));
                    arr2 = movecopy(arr, originalPosition, destination, movedPiece);
                    if(isKingInCheck(arr2, movedPiece->isWhite))
                        return false;
                    return true;
                }
            }
            if(destination.first == 7 && destination.second == 6)
            {
                if(arr[7][7] == WROOKR && arr[7][6] == NONE && arr[7][5] == NONE && movedPiece->firstMove && wRookr.firstMove)
                {
                    vector<vector<int>> arr2(row, vector<int>(col));
                    arr2 = movecopy(arr, originalPosition, destination, movedPiece);
                    if(isKingInCheck(arr2, movedPiece->isWhite))
                        return false;
                    return true;
                }
            }
        }
        if(movedPiece->value == BKING && originalPosition.first == 0 && originalPosition.second == 4)
        {
            if(destination.first == 0 && destination.second == 2)
            {
                if(arr[0][0] == BROOKL && arr[0][1] == NONE && arr[0][2] == NONE && arr[0][3] == NONE && movedPiece->firstMove && bRookl.firstMove)
                {
                    vector<vector<int>> arr2(row, vector<int>(col));
                    arr2 = movecopy(arr, originalPosition, destination, movedPiece);
                    if(isKingInCheck(arr2, movedPiece->isWhite))
                        return false;
                    return true;
                }
            }
            if(destination.first == 0 && destination.second == 6)
            {
                if(arr[0][7] == BROOKR && arr[0][6] == NONE && arr[0][5] == NONE && movedPiece->firstMove && bRookr.firstMove)
                {
                    vector<vector<int>> arr2(row, vector<int>(col));
                    arr2 = movecopy(arr, originalPosition, destination, movedPiece);
                    if(isKingInCheck(arr2, movedPiece->isWhite))
                        return false;
                    return true;
                }
            }
        }

        if(originalPosition.first == destination.first && originalPosition.second == destination.second)
            return true;
        if(movedPiece->isValidMove(arr,originalPosition, destination))
        {
            vector<vector<int>> arr2(row, vector<int>(col));
            arr2 = movecopy(arr, originalPosition, destination, movedPiece);
            
            if(isKingInCheck(arr2, movedPiece->isWhite))
                return false;
            
            return true;
        }
        return false;
    }
    bool isKingInCheck(vector<vector<int>>& arr, bool checkForWhite)
    {
        std::pair<int,int> kingPosition;
        if(checkForWhite)
        {
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<col; ++j)
                {
                    if(arr[i][j] == WKING)
                    {
                        kingPosition.first = i;
                        kingPosition.second = j;
                    }
                }
            }
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<col; ++j)
                {
                    if(arr[i][j] > BKING && arr[i][j] <= BKNIGHT)
                    {
                        Piece* temp = nullptr;
                        switch (arr[i][j])
                        {
                        case BKING:
                            temp = &bKing;
                            break;
                        case BKNIGHT:
                            temp = &bKnight;
                            break;
                        case BQUEEN:
                            temp = &bQueen;
                            break;
                        case BPAWN1:
                            temp = &bPawn1;
                            break;
                        case BPAWN2:
                            temp = &bPawn2;
                            break;
                        case BPAWN3:
                            temp = &bPawn3;
                            break;
                        case BPAWN4:
                            temp = &bPawn4;
                            break;
                        case BPAWN5:
                            temp = &bPawn5;
                            break;
                        case BPAWN6:
                            temp = &bPawn6;
                            break;
                        case BPAWN7:
                            temp = &bPawn7;
                            break;
                        case BPAWN8:
                            temp = &bPawn8;
                            break;
                        case BROOKL:
                            temp = &bRookl;
                            break;
                        case BROOKR:
                            temp = &bRookr;
                            break;
                        case BBISHOP:
                            temp = &bBishop;
                            break;
                        }
                        if(isLegalMove(arr, {i,j}, kingPosition, temp))
                            return true;
                    }
                }
            }
        }
        else
        {
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<col; ++j)
                {
                    if(arr[i][j] == BKING)
                    {
                        kingPosition.first = i;
                        kingPosition.second = j;
                    }
                }
            }
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<col; ++j)
                {
                    if(arr[i][j] > WKING && arr[i][j] <= WKNIGHT)
                    {
                        Piece* temp = nullptr;
                        switch (arr[i][j])
                        {
                        case WKING:
                            temp = &wKing;
                            break;
                        case WKNIGHT:
                            temp = &wKnight;
                            break;
                        case WQUEEN:
                            temp = &wQueen;
                            break;
                        case WPAWN1:
                            temp = &wPawn1;
                            break;
                        case WPAWN2:
                            temp = &wPawn2;
                            break;
                        case WPAWN3:
                            temp = &wPawn3;
                            break;
                        case WPAWN4:
                            temp = &wPawn4;
                            break;
                        case WPAWN5:
                            temp = &wPawn5;
                            break;
                        case WPAWN6:
                            temp = &wPawn6;
                            break;
                        case WPAWN7:
                            temp = &wPawn7;
                            break;
                        case WPAWN8:
                            temp = &wPawn8;
                            break;
                        case WROOKL:
                            temp = &wRookl;
                            break;
                        case WROOKR:
                            temp = &wRookr;
                            break;
                        case WBISHOP:
                            temp = &wBishop;
                            break;
                        }
                        if(temp->isValidMove(arr, {i,j}, kingPosition))
                            return true;
                    }
                }
            }
        }
        return false;
    }
    
    bool isCheckMate(vector<vector<int>>&arr, bool checkForWhite)
    {
        if(isKingInCheck(arr, checkForWhite))
        {
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<col; ++j)
                {
                    if(checkForWhite)
                    {
                        if(arr[i][j] >= WKING && arr[i][j] <= WKNIGHT)
                        {
                            Piece* temp = nullptr;
                            switch (arr[i][j])
                            {
                            case WKING:
                                temp = &wKing;
                                break;
                            case WKNIGHT:
                                temp = &wKnight;
                                break;
                            case WQUEEN:
                                temp = &wQueen;
                                break;
                            case WPAWN1:
                                temp = &wPawn1;
                                break;
                            case WPAWN2:
                                temp = &wPawn2;
                                break;
                            case WPAWN3:
                                temp = &wPawn3;
                                break;
                            case WPAWN4:
                                temp = &wPawn4;
                                break;
                            case WPAWN5:
                                temp = &wPawn5;
                                break;
                            case WPAWN6:
                                temp = &wPawn6;
                                break;
                            case WPAWN7:
                                temp = &wPawn7;
                                break;
                            case WPAWN8:
                                temp = &wPawn8;
                                break;
                            case WROOKL:
                                temp = &wRookl;
                                break;
                            case WROOKR:
                                temp = &wRookr;
                                break;
                            case WBISHOP:
                                temp = &wBishop;
                                break;
                            }
                            if(temp == nullptr)
                                std::cerr<<"temp is null"<<std::endl;
                            
                            for(int k=0; k<row; ++k)
                            {
                                for(int l=0; l<col; ++l)
                                {
                                    if(isLegalMove(arr, {i,j}, {k,l}, temp))
                                        return false;
                                }
                            }
                        }
                    }
                    else
                    {
                        if(arr[i][j] >= BKING && arr[i][j] <= BKNIGHT)
                        {
                            Piece* temp = nullptr;
                            switch (arr[i][j])
                            {
                            case BKING:
                                temp = &bKing;
                                break;
                            case BKNIGHT:
                                temp = &bKnight;
                                break;
                            case BQUEEN:
                                temp = &bQueen;
                                break;
                            case BPAWN1:
                                temp = &bPawn1;
                                break;
                            case BPAWN2:
                                temp = &bPawn2;
                                break;
                            case BPAWN3:
                                temp = &bPawn3;
                                break;
                            case BPAWN4:
                                temp = &bPawn4;
                                break;
                            case BPAWN5:
                                temp = &bPawn5;
                                break;
                            case BPAWN6:
                                temp = &bPawn6;
                                break;
                            case BPAWN7:
                                temp = &bPawn7;
                                break;
                            case BPAWN8:
                                temp = &bPawn8;
                                break;
                            case BROOKL:
                                temp = &bRookl;
                                break;
                            case BROOKR:
                                temp = &bRookr;
                                break;
                            case BBISHOP:
                                temp = &bBishop;
                                break;
                            }
                            if(temp == nullptr)
                                std::cerr<<"temp is null"<<std::endl;

                            for(int k=0; k<row; ++k)
                            {
                                for(int l=0; l<col; ++l)
                                {
                                    if(isLegalMove(arr, {i,j}, {k,l}, temp))
                                        return false;
                                }
                            }
                        }
                    }
                }
            }
            return true;
        }
        return false;
    }

    bool isStaleMate(vector<vector<int>>& arr)
    {
        int counterw = 0;
        int counterb = 0;
        for(int i=0; i<row; ++i)
        {
            for(int j=0; j<col; ++j)
            {
                if(arr[i][j] >= WKING && arr[i][j] <= WKNIGHT)
                {
                    Piece* temp = nullptr;
                    switch (arr[i][j])
                    {
                    case WKING:
                        temp = &wKing;
                        break;
                    case WKNIGHT:
                        temp = &wKnight;
                        break;
                    case WQUEEN:
                        temp = &wQueen;
                        break;
                    case WPAWN1:
                        temp = &wPawn1;
                        break;
                    case WPAWN2:
                        temp = &wPawn2;
                        break;
                    case WPAWN3:
                        temp = &wPawn3;
                        break;
                    case WPAWN4:
                        temp = &wPawn4;
                        break;
                    case WPAWN5:
                        temp = &wPawn5;
                        break;
                    case WPAWN6:
                        temp = &wPawn6;
                        break;
                    case WPAWN7:
                        temp = &wPawn7;
                        break;
                    case WPAWN8:
                        temp = &wPawn8;
                        break;
                    case WROOKL:
                        temp = &wRookl;
                        break;
                    case WROOKR:
                        temp = &wRookr;
                        break;
                    case WBISHOP:
                        temp = &wBishop;
                        break;
                    }
                    if(temp == nullptr)
                        std::cerr<<"temp is null"<<std::endl;
                    for(int k=0; k<row; ++k)
                    {
                        for(int l=0; l<col; ++l)
                        {
                            if(isLegalMove(arr, {i,j}, {k,l}, temp))
                                counterw++;
                        }
                    }
                    // delete temp;
                }
                else if(arr[i][j] >= BKING && arr[i][j] <= BKNIGHT)
                {
                    Piece* temp = nullptr;
                    switch (arr[i][j])
                    {
                    case BKING:
                        temp = &bKing;
                        break;
                    case BKNIGHT:
                        temp = &bKnight;
                        break;
                    case BQUEEN:
                        temp = &bQueen;
                        break;
                    case BPAWN1:
                        temp = &bPawn1;
                        break;
                    case BPAWN2:
                        temp = &bPawn2;
                        break;
                    case BPAWN3:
                        temp = &bPawn3;
                        break;
                    case BPAWN4:
                        temp = &bPawn4;
                        break;
                    case BPAWN5:
                        temp = &bPawn5;
                        break;
                    case BPAWN6:
                        temp = &bPawn6;
                        break;
                    case BPAWN7:
                        temp = &bPawn7;
                        break;
                    case BPAWN8:
                        temp = &bPawn8;
                        break;
                    case BROOKL:
                        temp = &bRookl;
                        break;
                    case BROOKR:
                        temp = &bRookr;
                        break;
                    case BBISHOP:
                        temp = &bBishop;
                        break;
                    }
                    if(temp == nullptr)
                        std::cerr<<"temp is null"<<std::endl;
                    for(int k=0; k<row; ++k)
                    {
                        for(int l=0; l<col; ++l)
                        {
                            if(isLegalMove(arr, {i,j}, {k,l}, temp))
                                counterb++;
                        }
                    }
                    // delete temp;
                }
            }
        }
        counterw--;
        counterb--;
        if(counterw ==0 || counterb == 0)
            return true;
        return false;
    }
    void drawLegalTiles(vector<vector<int>>& arr, std::pair<int,int> originalPosition, Piece* movedPiece)
    {
        for(int i=0; i<row; ++i)
        {
            for(int j=0; j<col; ++j)
            {
                std::pair<int,int> dest = {i,j};
                if(isLegalMove(arr, originalPosition, dest, movedPiece) && (originalPosition.first != dest.first || originalPosition.second != dest.second))
                    DrawCircle(j*dx + 50, i*dy + 50, dx/8, YELLOW);
            }
        }
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

                if(arr[i][j] == BKING && !selected[i][j]) //to do
                    DrawTexture(bKing.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == BQUEEN && !selected[i][j])
                    DrawTexture(bQueen.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == BKNIGHT && !selected[i][j])
                    DrawTexture(bKnight.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == BROOKL && !selected[i][j])
                    DrawTexture(bRookl.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == BROOKR && !selected[i][j])
                    DrawTexture(bRookr.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == BBISHOP && !selected[i][j])
                    DrawTexture(bBishop.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == BPAWN1 && !selected[i][j])
                    DrawTexture(bPawn1.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == BPAWN2 && !selected[i][j])
                    DrawTexture(bPawn2.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == BPAWN3 && !selected[i][j])
                    DrawTexture(bPawn3.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == BPAWN4 && !selected[i][j])
                    DrawTexture(bPawn4.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == BPAWN5 && !selected[i][j])
                    DrawTexture(bPawn5.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == BPAWN6 && !selected[i][j])
                    DrawTexture(bPawn6.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == BPAWN7 && !selected[i][j])
                    DrawTexture(bPawn7.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == BPAWN8 && !selected[i][j])
                    DrawTexture(bPawn8.texture, j*dx+10, i*dy+10, RAYWHITE);

                if(arr[i][j] == WKING && !selected[i][j])
                    DrawTexture(wKing.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == WQUEEN && !selected[i][j])
                    DrawTexture(wQueen.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == WKNIGHT && !selected[i][j])
                    DrawTexture(wKnight.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == WROOKL && !selected[i][j])
                    DrawTexture(wRookl.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == WROOKR && !selected[i][j])
                    DrawTexture(wRookr.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == WBISHOP && !selected[i][j])
                    DrawTexture(wBishop.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == WPAWN1 && !selected[i][j])
                    DrawTexture(wPawn1.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == WPAWN2 && !selected[i][j])
                    DrawTexture(wPawn2.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == WPAWN3 && !selected[i][j])
                    DrawTexture(wPawn3.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == WPAWN4 && !selected[i][j])
                    DrawTexture(wPawn4.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == WPAWN5 && !selected[i][j])
                    DrawTexture(wPawn5.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == WPAWN6 && !selected[i][j])
                    DrawTexture(wPawn6.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == WPAWN7 && !selected[i][j])
                    DrawTexture(wPawn7.texture, j*dx+10, i*dy+10, RAYWHITE);
                if(arr[i][j] == WPAWN8 && !selected[i][j])
                    DrawTexture(wPawn8.texture, j*dx+10, i*dy+10, RAYWHITE);
                
                counter++;
            }
            counter--;
        }
    }

    void play_game()
    {
        while(!WindowShouldClose())
        {
            if (isOver)
            {
                BeginDrawing();
                printOverScreen(moveWhite);
                EndDrawing();
                continue;
            }
            if(stalemate)
            {
                BeginDrawing();
                printStaleMate();
                EndDrawing();
                continue;
            }

            BeginDrawing();
            ClearBackground(WHITE);
            drawBoard();
            
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                mousepos = GetMousePosition();
                for(int i=0; i<row; ++i)
                {
                    for(int j=0; j<col; ++j)
                    {
                        if(mousepos.x >= j*dx && mousepos.x < (j+1)*dx && mousepos.y >= i*dy && mousepos.y < (i+1)*dy)
                        {
                            std::cout<<i<<" "<<j<<std::endl;

                            if(initialstate)
                            {
                                if(moveWhite && (arr[i][j] >= WKING && arr[i][j] <= WKNIGHT))
                                {       
                                    originalPosition.first = i;
                                    originalPosition.second = j;
                                    selected[i][j] = true;
                                }
                                else if(!moveWhite && (arr[i][j] >= BKING && arr[i][j] <= BKNIGHT))
                                {
                                    originalPosition.first = i;
                                    originalPosition.second = j;
                                    selected[i][j] = true;
                                }
                                else
                                {
                                    std::cerr<<"Invalid move"<<std::endl;
                                    break;
                                }
                    
                                originalPosition.first = i;
                                originalPosition.second = j;
                                selected[i][j] = true;
                                initialstate = false;
                                if(selected[originalPosition.first][originalPosition.second])
                                {
                                    // movedPiece->value = arr[originalPosition.first][originalPosition.second];
                                    if(arr[originalPosition.first][originalPosition.second] == BKING) 
                                        movedPiece = &bKing;
                                    else if(arr[originalPosition.first][originalPosition.second] == BQUEEN) 
                                        movedPiece= &bQueen;
                                    else if(arr[originalPosition.first][originalPosition.second] == BROOKL) 
                                        movedPiece = &bRookl;
                                    else if(arr[originalPosition.first][originalPosition.second] == BROOKR) 
                                        movedPiece = &bRookr;
                                    else if(arr[originalPosition.first][originalPosition.second] == BKNIGHT) 
                                        movedPiece = &bKnight;
                                    else if(arr[originalPosition.first][originalPosition.second] == BBISHOP) 
                                        movedPiece = &bBishop;
                                    else if(arr[originalPosition.first][originalPosition.second] == BPAWN1) 
                                        movedPiece = &bPawn1;
                                    else if(arr[originalPosition.first][originalPosition.second] == BPAWN2) 
                                        movedPiece = &bPawn2;
                                    else if(arr[originalPosition.first][originalPosition.second] == BPAWN3) 
                                        movedPiece = &bPawn3;
                                    else if(arr[originalPosition.first][originalPosition.second] == BPAWN4) 
                                        movedPiece = &bPawn4;
                                    else if(arr[originalPosition.first][originalPosition.second] == BPAWN5) 
                                        movedPiece = &bPawn5;
                                    else if(arr[originalPosition.first][originalPosition.second] == BPAWN6) 
                                        movedPiece = &bPawn6;
                                    else if(arr[originalPosition.first][originalPosition.second] == BPAWN7) 
                                        movedPiece = &bPawn7;
                                    else if(arr[originalPosition.first][originalPosition.second] == BPAWN8) 
                                        movedPiece = &bPawn8;

                                    else if(arr[originalPosition.first][originalPosition.second] == WKING) 
                                        movedPiece = &wKing;
                                    else if(arr[originalPosition.first][originalPosition.second] == WQUEEN) 
                                        movedPiece = &wQueen;
                                    else if(arr[originalPosition.first][originalPosition.second] == WROOKL) 
                                        movedPiece = &wRookl;
                                    else if(arr[originalPosition.first][originalPosition.second] == WROOKR) 
                                        movedPiece = &wRookr;
                                    else if(arr[originalPosition.first][originalPosition.second] == WKNIGHT) 
                                        movedPiece= &wKnight;
                                    else if(arr[originalPosition.first][originalPosition.second] == WBISHOP) 
                                        movedPiece = &wBishop;
                                    else if(arr[originalPosition.first][originalPosition.second] == WPAWN1) 
                                        movedPiece = &wPawn1;
                                    else if(arr[originalPosition.first][originalPosition.second] == WPAWN2) 
                                        movedPiece = &wPawn2;
                                    else if(arr[originalPosition.first][originalPosition.second] == WPAWN3) 
                                        movedPiece = &wPawn3;
                                    else if(arr[originalPosition.first][originalPosition.second] == WPAWN4) 
                                        movedPiece = &wPawn4;
                                    else if(arr[originalPosition.first][originalPosition.second] == WPAWN5) 
                                        movedPiece = &wPawn5;
                                    else if(arr[originalPosition.first][originalPosition.second] == WPAWN6) 
                                        movedPiece = &wPawn6;
                                    else if(arr[originalPosition.first][originalPosition.second] == WPAWN7) 
                                        movedPiece = &wPawn7;
                                    else if(arr[originalPosition.first][originalPosition.second] == WPAWN8) 
                                        movedPiece = &wPawn8;
                                    else
                                    {
                                        initialstate = true;
                                        movedPiece = nullptr;
                                    }

                                }
                            }
                        
                            else
                            {
                                destination.first = i;
                                destination.second = j;
                                if(movedPiece != nullptr)
                                {
                                    if(isLegalMove(arr,originalPosition,destination, movedPiece)) //movedPiece->isValidMove(arr, originalPosition, destination)
                                    {
                                        // if(isKingInCheck(arr, moveWhite))xcvzx // error
                                        
                                        move(arr, originalPosition, destination, movedPiece);//implement check detection
                                        if((arr[destination.first][destination.second] == WKING && !movedPiece->isWhite)|| (arr[destination.first][destination.second] == BKING && movedPiece->isWhite))
                                        {
                                            std::cout<<"The game should be over"<<std::endl;
                                            isOver = true;
                                        }
                                        if(isKingInCheck(arr, !moveWhite))
                                        {
                                            PlaySound(soundCheck);
                                            if(moveWhite)
                                            {
                                                std::cout<<"Black king in check"<<std::endl;
                                                bKing.inCheck = true;
                                            }
                                            
                                            else
                                            {
                                                std::cout<<"White king in check"<<std::endl;
                                                wKing.inCheck = true;
                                            }
                                        }else if(isKingInCheck(arr, moveWhite))
                                        {
                                            PlaySound(soundCheck);
                                            if(moveWhite)
                                            {
                                                std::cout<<"Black king in check"<<std::endl;
                                                bKing.inCheck = true;
                                            }
                                            
                                            else
                                            {
                                                std::cout<<"White king in check"<<std::endl;
                                                wKing.inCheck = true;
                                            }
                                        }
                                        else
                                        {
                                            if(moveWhite)
                                            {
                                                // std::cout<<"Black king not in check"<<std::endl;
                                                bKing.inCheck = false;
                                            }
                                            
                                            else
                                            {
                                                // std::cout<<"White king not in check"<<std::endl;
                                                wKing.inCheck = false;
                                            }
                                        }
                                        if(!(destination.first == originalPosition.first && destination.second == originalPosition.second))
                                        {
                                            moveWhite = !moveWhite;
                                            movedPiece->firstMove = false;
                                        }
                                        if(isCheckMate(arr, moveWhite))
                                        {
                                            std::cout<<"Checkmate"<<std::endl;
                                            isOver = true;
                                        }
                                        if(isStaleMate(arr))
                                        {
                                            std::cout<<"Stalemate"<<std::endl;
                                            stalemate = true;
                                        }
                                        // if(!IsMusicReady(musicMove))
                                        // {
                                        //     std::cerr<<"Error in music"<<std::endl;
                                        // }
                                        movedPiece = nullptr;
                                        std::cout<<"valid move"<<std::endl;
                                        initialstate = true;
                                    }
                                    else
                                        std::cout<<"Invalid move"<<std::endl;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            mousepos = GetMousePosition();
            if(movedPiece != nullptr)
            {
                DrawTextureV(movedPiece->texture, {mousepos.x-40, mousepos.y-40}, RAYWHITE);
                drawLegalTiles(arr, originalPosition, movedPiece);
                // movedPiece->drawValidMoves(arr, originalPosition);
            }
            EndDrawing();
        }
    }
};
