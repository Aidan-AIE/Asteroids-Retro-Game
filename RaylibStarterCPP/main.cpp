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
#include "raymath.h"
#include "raygui.h"
#include <iostream> //remove later

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

//changes a number towards a target gradually, made independent of framerate
float changeGrad(float input, float desiredNumber, float amount) {
    
    input = Lerp(input, desiredNumber, amount * GetFrameTime());
    
    //if (input > desiredNumber) {
    //    input -= amount * GetFrameTime();
    //    if (input < desiredNumber) input = desiredNumber;
    //}
    //else {
    //    input += amount * GetFrameTime();
    //    if (input > desiredNumber) input = desiredNumber;
    //}

    return input;
}


int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    int fps = 0;

    Vector2 playerPos = {screenWidth/2,screenHeight/2}; //current position of the player
    Vector2 playerMomentum = { 0,0 }; //current momentum of the player
    float rotate = 0; //current rotation of player in degrees
    float rotateConv = 0; //converted rotation from degrees to radians
    
    float speedX = 0; //Speed of player along X axis for testing
    float speedY = 0; //Speed of player along Y axis for testing

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        

        //for fps counter
        fps = (int)(1 / GetFrameTime());
        

        //Gets the input for player rotation
        if (IsKeyDown(KEY_D)) {
            rotate += 200 * GetFrameTime();
        }
        if (IsKeyDown(KEY_A)) {
            rotate -= 200 * GetFrameTime();
        }
        //makes a new variable by converting rotation from degrees to radians
        rotateConv = rotate * DEG2RAD;

        //temporary movement
        /*if (IsKeyDown(KEY_W)) {
            playerPos = {playerPos.x + (100 * GetFrameTime() * (float)cos(rotateConv - 1.5708)), playerPos.y + (100 * GetFrameTime() * (float)sin(rotateConv - 1.5708)) };
        }
        if (IsKeyDown(KEY_S)) {
            playerPos = { playerPos.x - (100 * GetFrameTime() * (float)cos(rotateConv - 1.5708)), playerPos.y - (100 * GetFrameTime() * (float)sin(rotateConv - 1.5708)) };
        }*/
        
        //adds momentum based on player direction
        /*if (IsKeyDown(KEY_W)) {
            playerMomentum = { playerMomentum.x + (500 * GetFrameTime() * (float)cos(rotateConv - 1.5708)), 
                playerMomentum.y + (500 * GetFrameTime() * (float)sin(rotateConv - 1.5708)) };
            playerMomentum = { Clamp(playerMomentum.x, -300, 300), Clamp(playerMomentum.y, -400, 400) };//clamps the player to a max speed
        }*/
        if (IsKeyDown(KEY_W)) {
            playerMomentum = { Lerp(playerMomentum.x , 500 * (float)cos(rotateConv - 1.5708), 1 * GetFrameTime()),
                Lerp(playerMomentum.y , 500 * (float)sin(rotateConv - 1.5708), 1 * GetFrameTime()) };
            playerMomentum = { Clamp(playerMomentum.x, -400, 400), Clamp(playerMomentum.y, -400, 400) };//clamps the player to a max speed
        }
        else {
            playerMomentum = { changeGrad(playerMomentum.x, 0, 0.5), changeGrad(playerMomentum.y, 0, 0.75) };//to do: gradually slow down speed 
        }

        //moves player using current momentum
        playerPos = { playerPos.x + (playerMomentum.x * GetFrameTime()), playerPos.y + (playerMomentum.y * GetFrameTime()) };

        //checks if the player has gone past the left and right borders and moves them to the oposite side
        if (playerPos.x > screenWidth) {
            playerPos.x = 0;
        }
        else if (playerPos.x < 0) { 
            playerPos.x = screenWidth; 
        }
        //checks if the player has gone on the top and bottom borders and moves them to the oposite side
        if (playerPos.y > screenHeight) {
            playerPos.y = 0;
        }
        else if (playerPos.y < 0) {
            playerPos.y = screenHeight;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText(TextFormat("FPS: %i", fps), 10, 10, 16, RED);
        DrawText(TextFormat("SPEED X: %a", abs((int)(playerPos.x - speedX))), 10, 26, 16, RED);
        DrawText(TextFormat("SPEED Y: %a", abs((int)(playerPos.y - speedY))), 10, 42, 16, RED);
        //DrawText(TextFormat("ROTATE: %e", rotate), 10, 26, 16, RED);
        //DrawText(TextFormat("ROTATE CONV: %i", rotateConv), 10, 42, 16, RED);

        DrawTriangleLines(rotatePoint(playerPos, (double)rotateConv, {0, -20}),
            rotatePoint(playerPos, (double)rotateConv, { 10, 10 }),
            rotatePoint(playerPos, (double)rotateConv, { -10, 10 }), RAYWHITE);


        EndDrawing();
        //----------------------------------------------------------------------------------
        speedX = playerPos.x;
        speedY = playerPos.y;

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

