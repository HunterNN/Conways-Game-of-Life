#include "raylib.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 500;
    const int screenHeight = 500;
    const int fieldSize = 20;
    const int cellSize = 25;

    enum STATE{
        DEAD,
        ALIVE
    };

    int field[fieldSize][fieldSize];
    int filedNextGen[fieldSize][fieldSize];

    int i, j;
    for(i = 0; i < fieldSize; i++){
        for(j = 0; j < fieldSize; j++){
            field[i][j] = DEAD;
        }
    }

    // Create Frog
    field[9][10] = ALIVE;
    field[10][10] = ALIVE;
    field[11][10] = ALIVE;
    field[10][11] = ALIVE;
    field[11][11] = ALIVE;
    field[12][11] = ALIVE;

    InitWindow(screenWidth, screenHeight, "Conways Spiel des Lebens");

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

    SetTargetFPS(2);               // frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            for(i = 0; i < fieldSize; i++){
                for(j = 0; j < fieldSize; j++){
                    if (field[i][j] == ALIVE){
                        DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, ORANGE);
                    }
                }
            }

        EndDrawing();
        //----------------------------------------------------------------------------------

        // Field Update
        //----------------------------------------------------------------------------------

        // Reset Nect Gen Field
        for(i = 0; i < fieldSize; i++){
            for(j = 0; j < fieldSize; j++){
                filedNextGen[i][j] = field[i][j];
            }
        }

        for(i = 0; i < fieldSize; i++){
            for(j = 0; j < fieldSize; j++){
                int neighbourCounter = 0;
                int n, m;
                for(n = i - 1; n <= i + 1; n++){
                    for(m = j - 1; m <= j + 1; m++){
                        // Don't count if it's own cell or if cell is outside of field
                        if (!(n == i && m == j) && n < fieldSize && m < fieldSize){
                            if (field[n][m] == ALIVE){
                                neighbourCounter += 1;
                            }
                        }
                    } 
                }

                if (field[i][j] == ALIVE){
                    if (neighbourCounter < 2){
                        filedNextGen[i][j] = DEAD;
                    }
                    else if(neighbourCounter > 3){
                        filedNextGen[i][j] = DEAD;
                    }
                }
                else if (field[i][j] == DEAD){
                    if(neighbourCounter == 3){
                        filedNextGen[i][j] = ALIVE;
                    }
                }
            }
        }

        // Update Field to next gen
        for(i = 0; i < fieldSize; i++){
            for(j = 0; j < fieldSize; j++){
                field[i][j] = filedNextGen[i][j];
            }
        }
    }
    //----------------------------------------------------------------------------------
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
