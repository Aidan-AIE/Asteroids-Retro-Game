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
#include <vector>


struct Bullet
{
    float PosX;//x position of bullet
    float PosY;//y position of bullet
    float Angle;// angle bullet is facing
    float Time;// how long bullet has before expiring
    float momentX; //extra momentum provided by the player on x
    float momentY; //extra momentum provided by the player on y
};

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


float changeGrad(float input, float desiredNumber, float amount) { // changes a number towards a target gradually, made independent of framerate
                                                                   // this was originally a different equation but I figured out that lerp works and dont want to change
                                                                   // everything else
    input = Lerp(input, desiredNumber, amount * GetFrameTime());
    
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
    
    std::vector<Bullet> bullets;

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
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            rotate += 200 * GetFrameTime();
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
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
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
            playerMomentum = { Lerp(playerMomentum.x , 500 * (float)cos(rotateConv - 1.5708), 1 * GetFrameTime()),
                Lerp(playerMomentum.y , 500 * (float)sin(rotateConv - 1.5708), 1 * GetFrameTime()) };
            playerMomentum = { Clamp(playerMomentum.x, -400, 400), Clamp(playerMomentum.y, -400, 400) };//clamps the player to a max speed
        }
        else {
            playerMomentum = { changeGrad(playerMomentum.x, 0, 0.5), changeGrad(playerMomentum.y, 0, 0.75) };//gradually lowers the speed of the player
        }

        //player shoot
        if (IsKeyPressed(KEY_SPACE)) {
            //creates a bullet at the location and rotation of the player
            Vector2 spawn = rotatePoint(playerPos, rotateConv, { 0,-20 });
            Bullet newBullet = {spawn.x, spawn.y, rotateConv, 1, playerMomentum.x, playerMomentum.y };
            bullets.push_back(newBullet); //adds the bullet to the bullet list

        }

        //moves player using current momentum
        playerPos = { playerPos.x + (playerMomentum.x * GetFrameTime()), playerPos.y + (playerMomentum.y * GetFrameTime()) };
        //goes through all bullets and then moves them accordingly || TODO: inherit player velocity
        for (int i = 0; i < bullets.size(); i++) {
            //sets up a variable for the change in the x position based on speed and direction
            float positionX = bullets[i].PosX + (500 * (float)cos(bullets[i].Angle - 1.5708) * GetFrameTime());
            //if the bullet is off the screen it will correct accordingly
            if (positionX > screenWidth) {
                positionX = 0;
            }
            else if (positionX < 0) {
                positionX = screenWidth;
            }
            //sets up a variable for the change in the y position based on speed and direction
            float positionY = bullets[i].PosY + (500 * (float)sin(bullets[i].Angle - 1.5708) * GetFrameTime());
            //if the bullet is off the screen it will correct accordingly
            if (positionY > screenHeight) {
                positionY = 0;
            }
            else if (positionY < 0) {
                positionY = screenHeight;
            }
            //sets up the replacement for the bullet that uses the changed x and y values
            Bullet replacement = { positionX, positionY, bullets[i].Angle, bullets[i].Time - (1 * GetFrameTime())};
            //inserts the new bullet behind the old one
            bullets.insert(bullets.begin() + i, replacement);
            //removes the old bullet (which is now one position ahead) functionally replacing it
            bullets.erase(bullets.begin() + i + 1);
        }
        //deletes bullets that have expired
        for (int i = 0; i < bullets.size(); i++) {
            if (bullets[i].Time < 0) {
                bullets.erase(bullets.begin() + i);
            }
        }

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
        //Draws the player
        DrawTriangleLines(rotatePoint(playerPos, (double)rotateConv, {0, -20}),
            rotatePoint(playerPos, (double)rotateConv, { 10, 10 }),
            rotatePoint(playerPos, (double)rotateConv, { -10, 10 }), RAYWHITE);
        //Just makes moving between screens smoother, doesn't provide anything useful (perhaps implement this into a function for further use)
        DrawTriangleLines(rotatePoint({playerPos.x + screenWidth, playerPos.y}, (double)rotateConv, {0, -20}),
            rotatePoint({ playerPos.x + screenWidth, playerPos.y }, (double)rotateConv, {10, 10 }),
            rotatePoint({ playerPos.x + screenWidth, playerPos.y }, (double)rotateConv, { -10, 10 }), RAYWHITE);

        DrawTriangleLines(rotatePoint({ playerPos.x - screenWidth, playerPos.y }, (double)rotateConv, { 0, -20 }),
            rotatePoint({ playerPos.x - screenWidth, playerPos.y }, (double)rotateConv, { 10, 10 }),
            rotatePoint({ playerPos.x - screenWidth, playerPos.y }, (double)rotateConv, { -10, 10 }), RAYWHITE);

        DrawTriangleLines(rotatePoint({ playerPos.x, playerPos.y + screenHeight}, (double)rotateConv, { 0, -20 }),
            rotatePoint({ playerPos.x, playerPos.y + screenHeight}, (double)rotateConv, { 10, 10 }),
            rotatePoint({ playerPos.x, playerPos.y + screenHeight}, (double)rotateConv, { -10, 10 }), RAYWHITE);

        DrawTriangleLines(rotatePoint({ playerPos.x, playerPos.y - screenHeight }, (double)rotateConv, { 0, -20 }),
            rotatePoint({ playerPos.x, playerPos.y - screenHeight }, (double)rotateConv, { 10, 10 }),
            rotatePoint({ playerPos.x, playerPos.y - screenHeight }, (double)rotateConv, { -10, 10 }), RAYWHITE);


        for (Bullet bullet : bullets) {
            DrawCircle(bullet.PosX, bullet.PosY, 1, RAYWHITE);
        }

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

