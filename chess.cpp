#include "board.hpp"

/*To do
1. Implement stalemate          done
2. Implement castling           done
3. Implement en passant
4. Implement pawn promotion
5. Correct bugs regarding discovered check
*/

int main()
{
    InitWindow(swidth, sheight, "Chess go brrrr!!!!");
    InitAudioDevice();
    
    Board gameboard;
    SetTargetFPS(60);

    gameboard.play_game();
    CloseWindow();
    return 0;
}
