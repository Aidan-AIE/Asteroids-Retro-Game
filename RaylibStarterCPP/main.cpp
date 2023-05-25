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
#include "BulletObject.h"
#include "AsteroidObject.h"
#include <iostream> //remove later
#include <vector>


/*struct Bullet
{
    float PosX;//x position of bullet
    float PosY;//y position of bullet
    float Angle;// angle bullet is facing
    float Time;// how long bullet has before expiring
    float momentX; //extra momentum provided by the player on x
    float momentY; //extra momentum provided by the player on y
};*/

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
    int screenWidth = 1080; //the play area for x coordinates
    int screenHeight = 1080;//the play area for y coordinates

    int score = 0;

    int fps = 0;

    Vector2 playerPos = {screenWidth/2,screenHeight/2}; //current position of the player
    Vector2 playerMomentum = { 0,0 }; //current momentum of the player
    float rotate = 0; //current rotation of player in degrees
    float rotateConv = 0; //converted rotation from degrees to radians

    std::vector<BulletObject> bulletHolder; //holds all current bullets
    std::vector<AsteroidObject> asteroidHolder; //holds all current asteroids
    

    bool hitboxes = true; //used to display hitboxes for debug purposes
    
    InitWindow(1920, 1080, "raylib [core] example - basic window");

    SetWindowMinSize(screenWidth, screenHeight);
    
    ToggleFullscreen();

    Camera2D camera = { 0 };

    camera.target = { 0,0 };
    camera.offset = { 1920/5, 0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Font fontTtf = LoadFontEx("resources/pixantiqua.ttf", 32, NULL, 0);

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        if (asteroidHolder.size() == 0) {
            for (int i = 0; i < 10; i++) {

                float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

                int side = GetRandomValue(0, 3);

                Vector2 spawnpoint = { 0,0 };

                switch (side) {
                case 0:
                    spawnpoint = { (float)GetRandomValue(0,screenWidth), 0 };
                    break;
                case 1:
                    spawnpoint = { (float)GetRandomValue(0.0f,screenWidth), (float)screenHeight };
                    break;
                case 2:
                    spawnpoint = { 0,  (float)GetRandomValue(0,screenHeight) };
                    break;
                case 3:
                    spawnpoint = { (float)screenWidth, (float)GetRandomValue(0, screenHeight) };
                default:
                    spawnpoint = { (float)GetRandomValue(0,screenWidth), 0 };
                    break;
                }

                AsteroidObject newAsteroid;
                newAsteroid.Initialize(spawnpoint, r * (PI * 2), newAsteroid.generateSpeed(), 2);
                asteroidHolder.push_back(newAsteroid);

            }
        }
        
        //Gets the input for player rotation
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            rotate += 200 * GetFrameTime();
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            rotate -= 200 * GetFrameTime();
        }

        //debug purposes
        if (IsKeyPressed(KEY_H)) {
            hitboxes = !hitboxes;
        }

        //makes a new variable by converting rotation from degrees to radians
        rotateConv = rotate * DEG2RAD;
        
        //adds momentum based on player direction
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
            playerMomentum = { Lerp(playerMomentum.x , 500 * (float)cos(rotateConv - 1.5708), 1 * GetFrameTime()),
                Lerp(playerMomentum.y , 500 * (float)sin(rotateConv - 1.5708), 1 * GetFrameTime()) };
            playerMomentum = { Clamp(playerMomentum.x, -400, 400), Clamp(playerMomentum.y, -400, 400) };//clamps the player to a max speed
        }
        else {
            playerMomentum = { changeGrad(playerMomentum.x, 0, 1), changeGrad(playerMomentum.y, 0, 1) };//gradually lowers the speed of the player
        }

        //player shoot
        if (IsKeyPressed(KEY_SPACE)) {
            BulletObject newBullet;
             newBullet.Initialize(rotatePoint(playerPos, rotateConv, {0,-15}), rotateConv, 1, playerMomentum);
            bulletHolder.push_back(newBullet);
        }

        //moves player using current momentum
        playerPos = { playerPos.x + (playerMomentum.x * GetFrameTime()), playerPos.y + (playerMomentum.y * GetFrameTime()) };
        //goes through all bullets and then moves them accordingly || TODO: MAKE BULLETS SHOOT ACCORDING TO VELOCITY
        for (BulletObject &bullet : bulletHolder) {
            //sets up a variable for the change in the x position based on speed and direction
            float positionX = bullet.xPos() + ((500 + abs(bullet.momentum().x)) * (float)cos(bullet.angle() - 1.5708) * GetFrameTime());
            //if the bullet is off the screen it will correct accordingly
            if (positionX > screenWidth) {
                positionX = 0;
            }
            else if (positionX < 0) {
                positionX = screenWidth;
            }
            //sets up a variable for the change in the y position based on speed and direction
            float positionY = bullet.yPos() + ((500 + abs(bullet.momentum().y)) * (float)sin(bullet.angle() - 1.5708) * GetFrameTime());
            //if the bullet is off the screen it will correct accordingly
            if (positionY > screenHeight) {
                positionY = 0;
            }
            else if (positionY < 0) {
                positionY = screenHeight;
            }
            
            bullet.ChangePos({ positionX, positionY });

            bullet.SubTime(1);

        }
        //deletes bullets that have expired
        int bulletno = 0;
        for (BulletObject &bullet : bulletHolder) {
            if (bullet.time() < 0) {
                bulletHolder.erase(bulletHolder.begin() + bulletno);
            }
            bulletno += 1;
        }
        //moves the asteroids in the game
        int asteroidCount = 0;
        for (AsteroidObject& asteroid : asteroidHolder) {
            //sets up a variable for the change in the x position based on speed and direction
            float positionX = asteroid.xPos() + asteroid.speed() * (float)cos(asteroid.angle() - 1.5708) * GetFrameTime();
            //if the asteroid is off the screen it will correct accordingly
            if (positionX > screenWidth) {
                positionX = 0;
            }
            else if (positionX < 0) {
                positionX = screenWidth;
            }
            //sets up a variable for the change in the y position based on speed and direction
            float positionY = asteroid.yPos() + asteroid.speed() * (float)sin(asteroid.angle() - 1.5708) * GetFrameTime();
            //if the asteroid is off the screen it will correct accordingly
            if (positionY > screenHeight) {
                positionY = 0;
            }
            else if (positionY < 0) {
                positionY = screenHeight;
            }
            //moves the asteroid after all calculations are finished
            asteroid.ChangePos({ positionX, positionY });
            //this section handles collisions with bullets
            int count = 0;
            for (BulletObject& bullet : bulletHolder) {
                if (CheckCollisionCircles({ asteroid.xPos(), asteroid.yPos() }, asteroid.size(), { bullet.xPos(), bullet.yPos() }, 5)) {
                    bulletHolder.erase(bulletHolder.begin() + count);

                    switch (asteroid.sizeI()) {
                    case 0:
                        score += 100;
                        break;
                    case 1:
                        score += 50;
                        break;
                    case 2:
                        score += 20;
                        break;
                    }

                    //decreases size by 1
                    asteroid.Break();
                    //if on smallest size, destroys asteroid and finishes current iteration
                    if (asteroid.sizeI() == -1) {
                        asteroidHolder.erase(asteroidHolder.begin() + asteroidCount);
                        continue;
                    }
                    //generates random number between 0.0 and 1.0
                    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                    //changes the values of the asteroid to new random ones
                    asteroid.Initialize({ asteroid.xPos(), asteroid.yPos() }, r * (PI*2),asteroid.generateSpeed(),asteroid.sizeI());
                    
                    r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                    //creates a clone which undergoes the same process
                    AsteroidObject clone;
                    clone.Initialize({ asteroid.xPos(), asteroid.yPos() }, r* (PI * 2), asteroid.generateSpeed(), asteroid.sizeI());
                    //adds the clone to the asteroid holder
                    asteroidHolder.push_back(clone);

                }
                count++;
            }
            asteroidCount++;
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

        BeginMode2D(camera);

        BeginScissorMode(1920 / 5.0f, 0, screenWidth, screenHeight);

        DrawTextEx(fontTtf, TextFormat("%i", score), { 10.0f, 5.0f }, 35, 5, RAYWHITE);
        
                
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


        for (BulletObject bullet : bulletHolder) {
            bullet.Draw();
        }
        for (AsteroidObject asteroid : asteroidHolder) {
            asteroid.Draw(screenWidth, screenHeight);
        }

        if (hitboxes) {
            DrawCircleV(playerPos, 10, Fade(RED, 0.5)); //could save some lines by making this a function
            DrawCircleLines(playerPos.x, playerPos.y, 10, RED);

            for (BulletObject bullet : bulletHolder) {
                DrawCircle(bullet.xPos(), bullet.yPos(), 5, Fade(RED, 0.5));
                DrawCircleLines(bullet.xPos(), bullet.yPos(), 5, RED);
            }

            for (AsteroidObject asteroid : asteroidHolder) {
                DrawCircle(asteroid.xPos(), asteroid.yPos(), asteroid.size(), Fade(RED, 0.5));
                DrawCircleLines(asteroid.xPos(), asteroid.yPos(), asteroid.size(), RED);
            }

        }
        
        EndScissorMode();
        EndMode2D();
        EndDrawing();

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

