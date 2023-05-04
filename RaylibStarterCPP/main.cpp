/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

Vector2 rotatePoint(Vector2 origin, double radians, Vector2 offset) {
    offset = { origin.x + offset.x, origin.y + offset.y };

    float s = sin(radians);
    float c = cos(radians);

    offset.x -= origin.x;
    offset.y -= origin.y;

    float xnew = offset.x * c - offset.y * s;
    float ynew = offset.x * s + offset.y * c;

    offset.x = xnew + origin.x;
    offset.y = ynew + origin.y;

    return offset;

}


int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    int fps = 0;

    Vector2 playerPos = {screenWidth/2,screenHeight/2};
    float rotate = 0; //rotation in degrees
    float rotateConv = 0; //converted rotation from degrees to radians

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        fps = (int)(1 / GetFrameTime());
        

        if (IsKeyDown(KEY_D)) {
            rotate += 100 * GetFrameTime();
        }
        if (IsKeyDown(KEY_A)) {
            rotate -= 100 * GetFrameTime();
        }
        rotateConv = rotate * DEG2RAD;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText(TextFormat("FPS: %i", fps), 10, 10, 16, RED);
        //DrawText(TextFormat("ROTATE: %e", rotate), 10, 26, 16, RED);
        //DrawText(TextFormat("ROTATE CONV: %i", rotateConv), 10, 42, 16, RED);

        DrawTriangleLines(rotatePoint(playerPos, (double)rotateConv, {0, -20}),
            rotatePoint(playerPos, (double)rotateConv, { 10, 0 }),
            rotatePoint(playerPos, (double)rotateConv, { -10, 0 }), RAYWHITE);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

