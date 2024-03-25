#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include "shape.h"
#include "Quad.h"
#include "Button.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
//https://github.com/mikepoirier/clion-glfw
GLdouble width, height;
int wd;
const int SIDE_LENGTH = 20;
dimensions dimensions1(45, 20);
const color white(1, 1, 1);
const color red(1, 0, 0);
const qColor skyBlue{77/255.0, 213/255.0, 240/255.0};
const qColor grassGreen{26/255.0, 176/255.0, 56/255.0};
const qColor brickRed{201/255.0, 20/255.0, 20/255.0};
const color green(0, 1, 0);
const color black(0, 0, 0);
const color cyan (0, 1, 1);

Button mButton({0.2, 1.5, 1}, {200, 500}, 100, 45, "Maze");
Button pButton({0.2, 1.5, 1}, {400, 500}, 100, 45, "Ping Pong");
Button dButton({0.2, 1.5, 1}, {600, 500}, 100, 45, "Dodge");
const color back(.2, .6, .9);

Rect base;
Rect goal;
Rect user;
vector<Rect> block1;
vector<Rect> block2;
vector<Rect> block3;
vector<Circle> snow;
vector<Rect> objects;
vector<Rect> maze;
enum screens{first = 1, middleMaze = 2, middleDodge = 3, middlePing = 4, pingGame = 5, pingEnd = 6, lastWin = 7, lastLost =8};
screens screen = first;
string startScreen = "Welcome to Gill and Carols Arcade, Please choose a game below.";
string endScreenLose = "You lost!";
string endScreenWin = "You Won!";
string endScreenWrong = "Something went wrong!";

//pong variables
string pongTitle = "Table Tennis/ Ping Pong!";
string pong1 = "In this game you can either play yourself,";
string pong2 = "or play a friend.";
string pong3 = "The goal of the game is to not let the";
string pong4 = "ball past your racket.";
string pong5 = "The green racket is controlled with the";
string pong6 = "'q' and 'a' keys, while the red racket";
string pong7 = "uses the up and down arrows.";
string pong8 = "First to 5 points wins!";

string pongEnd = "Game Over!";
string player1Win = "Player 1 has won.";
string player2Win = "Player 2 has won.";
string pong9 = "Thanks for playing. Press the ESC key";
string pong10 = "to exit.";

string playerLPointsLabel = "P1 Points:";
string playerRPointsLabel = "P2 Points:";
Button startPong(grassGreen,{400,370},150,50,"Start Game");
Quad leftRacket;
Quad rightRacket;
Quad ball;
int playerLPoints = 0;
int playerRPoints = 0;
//
//Ping pong inits
void initRacket() {
    // TODO: Create rackets for pong game (should border edges of screen)
    leftRacket.qresize(10,100);
    leftRacket.qsetColor(grassGreen);
    leftRacket.qsetCenter(30,height/2);

    rightRacket.qresize(10,100);
    rightRacket.qsetColor(brickRed);
    rightRacket.qsetCenter(width-30,height/2);
}

void initBall() {
    // TODO : Create ball for pong game
    /*ball.setCenterX(width/2);
    ball.setCenterY(height/2);
    ball.setHeight(30);
    ball.setWidth(30);
    ball.setColor(skyBlue);*/
    ball.qsetVelocity(10,10);
    ball.qsetCenter(width/2,height/2);
    ball.qresize(30,30);
    ball.qsetColor(skyBlue);
}

void initUser() {
    // centered in the top left corner of the graphics window
    user.setCenter(390, 250);
    user.setSize(10, 10);
    user.setColor(cyan);

}

void initSnow() {
    for (int i = 0; i < 150; ++i) {
        snow.push_back(Circle(1, 1, 1, 1, rand() % int(width), -(rand() % int(height)), rand() % 5 + 1));
    }
}

void initMaze() {
    string filename = "../maze2.txt";
    ifstream inFile(filename);
    inFile >> noskipws;
    int xCoord = 0, yCoord = 0;
    char letter;
    color blockColor;
    bool draw;
    while (inFile >> letter) {
        draw = true;
        switch (letter) {
            case 'b':
                blockColor = black;
                break;
            case 'r':
                blockColor = red;
                break;
            case 'g':
                blockColor = green;
                break;
            case 'w':
                blockColor = white;
                break;
            case ' ':
                draw = false;
                xCoord += SIDE_LENGTH;
                yCoord += 0;
                break;

            default: // newline
                draw = false;
                xCoord = 0;
                yCoord += SIDE_LENGTH;
        }
        if (draw) {
            //create rectangle object
            //stores x and y cord
            maze.push_back(Rect(blockColor, xCoord + (SIDE_LENGTH / 2), yCoord + (SIDE_LENGTH / 2)));
            maze[maze.size() - 1].setSize(SIDE_LENGTH, SIDE_LENGTH);
            xCoord += SIDE_LENGTH;
        }
    }
    inFile.close();
}

void determineWin() {
    ////TODO: ISOVERLAPPING
    //GET FROM RUNNER determine if user rectangle is not overlapping with the maze
    //detect if user
    bool lost = true;
    for (int i = 0; i < maze.size(); ++i) {
        if ((maze[i].isOverlapping(user))) {
            lost = false;
        }
        if(user.getTopY()== 705 && user.getLeftX()== 85){
            screen = lastWin;
            user.setColor(0, 1, 0, 1);
        }
    }
    if (lost) {
        screen = lastLost;
    }
}

void initDodge() {
//    for (int i = 0; i < 150; ++i) {
//        objects.push_back(Rect(1, 0, 0,1, rand() % int(width), -(rand() % int(height)), dimensions));
//    }
// First vector is for closest buildings
    int totalBuildingWidth = 0;
    dimensions blockSize(10, 10);
    while (totalBuildingWidth < width + 50) {
        // Building height between 50-100
        blockSize.height = rand() % 51 + 50;

        // Building width between 30-50
        blockSize.width = rand() % 70 + 80;
        block1.push_back(Rect(black,
                              totalBuildingWidth+((blockSize.width/2)+rand() % 100),
                              height-((blockSize.height/2)+ rand() % 900 + 450),
                              blockSize));
        totalBuildingWidth += blockSize.width + 5;
    }

    // Populate second set of buildings
    totalBuildingWidth = 0;
    while (totalBuildingWidth < width + 100) {
        // Building height between 100-200
        blockSize.height = rand() % 15 + 30;
        // Building width between 50-100
        blockSize.width = rand() % 30 + 50;
        block2.push_back(Rect(black,totalBuildingWidth+((blockSize.width/2)+ rand() % 70),
                              height-((blockSize.height/2)+ rand() % 900 + 300),
                              blockSize));

        totalBuildingWidth += blockSize.width + 5; // Placeholder line to avoid infinite loop
    }

    // Populate third set of buildings
    totalBuildingWidth = 0;
    while (totalBuildingWidth < width + 200) {
        // TODO: Populate this vector of purple buildings
        // Building height between 200-400
        blockSize.height = rand() % 10 + 20;
        // Building width between 100-200
        blockSize.width = rand() % 21 + 30;
        block3.push_back(Rect(black,totalBuildingWidth+(blockSize.width/2)+10,
                              height-((blockSize.height/2)+ rand() % 900 + 100),
                              blockSize));
        totalBuildingWidth += blockSize.width + 5; // Placeholder line to avoid infinite loop
    }
}
void initBase() {
    base.setCenter(400, 800);
    base.setSize(width, height/3);
    base.setColor(white);
}

void initGoal() {
    base.setCenter(400, 2);
    base.setSize(100, 100);
    base.setColor(green);
}

void determineWinDodge() {
    bool lost = false;
    bool win = true;
    for (int i = 0; i < block1.size(); ++i) {
        if ((block1[i].isOverlapping(user))) {
            lost = true;
        }
    }
    for (int i = 0; i < block2.size(); ++i) {
        if ((block2[i].isOverlapping(user))) {
            lost = true;
        }
    }
    for (int i = 0; i < block3.size(); ++i) {
        if ((block3[i].isOverlapping(user))) {
            lost = true;
        }
    }
    if(user.getBottomY()<= 50 && user.getLeftX() >= 350  && user.getRightX()<= 450){
        screen = lastWin;
        //user.setColor(0, 1, 0, 1);
    }
    if (lost) {
        screen = lastLost;
    }
}




void mazeDraw() {
    for (int i = 0; i < maze.size(); ++i) {
        int xCoord = maze[i].getLeftX();
        int yCoord = maze[i].getTopY();
        //color drawColor = maze[i].getColor();
        //replay with rectangle draw
        glBegin(GL_QUADS);
        glColor3f(maze[i].getColor().red, maze[i].getColor().green, maze[i].getColor().blue);
        glVertex2i(xCoord, yCoord);
        glVertex2i(xCoord + SIDE_LENGTH, yCoord);
        glVertex2i(xCoord + SIDE_LENGTH, yCoord + SIDE_LENGTH);
        glVertex2i(xCoord, yCoord + SIDE_LENGTH);
        glEnd();

    }

}
void init() {
    width = 800;
    height = 800;
    srand(time(0));
    initSnow();
    initMaze();
    initRacket();
    initBall();
    initDodge();
    initUser();
    initBase();
    initGoal();

}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(back.red, back.green, back.blue, 1.0f);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    /*
     * Draw here
     */

    //Screen switch
    switch(screen) {
        case (first):
            for (Circle &flake: snow) {
                flake.draw();
            }
            glColor3f(0, 0, 0);
            glRasterPos2i((width / 5) - 55, (height / 2));
            for (const char &letter: startScreen) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            mButton.qdraw();
            pButton.qdraw();
            dButton.qdraw();

            glFlush();
            break;

        case (middleMaze):
            // Add logic to draw the clouds, mountain, the user, the maze.
            for (Circle &flake: snow) {
                flake.draw();
            }

            //draw mountain
            glBegin(GL_TRIANGLES);
            glClearColor(white.red, white.green, white.blue, 1.0f);
            glVertex2i(0, 800);
            glVertex2i(400, 200);
            glVertex2i(800, 800);
            glEnd();


            mazeDraw();
            user.draw();
            determineWin();

            glFlush();

            // Render now
            break;

            //maybe lastWin and lastLose

        case (middleDodge):
            base.draw();
            goal.draw();
            for (Circle &flake: snow) {
                flake.draw();
            }

            for (Rect &r : block1) {
                if (r.isOverlapping(user)) {
                    r.setColor(red);
                } else {
                    r.setColor(black);
                }
                r.draw();
            }

            for (Rect &r : block2) {
                if (r.isOverlapping(user)) {
                    r.setColor(red);
                } else {
                    r.setColor(black);
                }
                r.draw();
            }
            for (Rect &r : block3) {
                if (r.isOverlapping(user)) {
                    r.setColor(red);
                } else {
                    r.setColor(black);
                }
                r.draw();
            }


            user.draw();
            determineWinDodge();

            glFlush();
            break;
        case(middlePing):
            for (Circle &flake: snow) {
                flake.draw();
            }
            glColor3f(1,1,1);
            glRasterPos2i(width/2-80, 50);
            for (const char &letter : pongTitle) {
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15 , letter);
            }
            glRasterPos2i(width/2-150, 100);
            for (const char &letter : pong1) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13 , letter);
            }
            glRasterPos2i(width/2-50, 120);
            for (const char &letter : pong2) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13 , letter);
            }
            glRasterPos2i(width/2-150, 170);
            for (const char &letter : pong3) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13 , letter);
            }
            glRasterPos2i(width/2-60, 190);
            for (const char &letter : pong4) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13 , letter);
            }
            glRasterPos2i(width/2-150, 240);
            for (const char &letter : pong5) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13 , letter);
            }
            glRasterPos2i(width/2-150, 260);
            for (const char &letter : pong6) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13 , letter);
            }
            glRasterPos2i(width/2-100, 280);
            for (const char &letter : pong7) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13 , letter);
            }
            glRasterPos2i(width/2-90, 310);
            for (const char &letter : pong8) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13 , letter);
            }

            startPong.qdraw();
            glFlush();
            break;

        case(pingGame):
            glClear(GL_COLOR_BUFFER_BIT);
            leftRacket.qdraw();
            rightRacket.qdraw();
            ball.qdraw();

            glColor3f(1.0, 1.0, 1.0);
            glRasterPos2i(width / 2 - 200, height/4 - 15);
            for (const char &letter : playerLPointsLabel) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            glColor3f(1.0, 1.0, 1.0);
            glRasterPos2i(width / 2 - 200, height/4);
            for (const char &letter : to_string(playerLPoints)) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            glColor3f(1.0, 1.0, 1.0);
            glRasterPos2i(350, height/4 - 15);
            for (const char &letter : playerRPointsLabel) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            glColor3f(1.0, 1.0, 1.0);
            glRasterPos2i(350, height/4);
            for (const char &letter : to_string(playerRPoints)) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            if (playerLPoints == 5) {
                screen = pingEnd;
            }
            if (playerRPoints == 5) {
                screen = pingEnd;
            }

            for (Circle &flake: snow) {
                flake.draw();
            }

            glFlush();
            break;
        case (pingEnd):
            glClear(GL_COLOR_BUFFER_BIT);

            if (playerLPoints == 5) {
                glColor3f(1,1,1);
                glRasterPos2i(width/2-45, 10);
                for (const char &letter : pongEnd) {
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15 , letter);
                }

                glRasterPos2i(width/2-80, 50);
                for (const char &letter : player1Win) {
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
                }

                glRasterPos2i(width/2-150, 100);
                for (const char &letter : pong9) {
                    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
                }

                glRasterPos2i(width/2-30, 120);
                for (const char &letter : pong10) {
                    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
                }
            }

            if (playerRPoints == 5) {
                glColor3f(1,1,1);
                glRasterPos2i(width/2-45, 80);
                for (const char &letter : pongEnd) {
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15 , letter);
                }

                glRasterPos2i(width/2-80, 210);
                for (const char &letter : player2Win) {
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
                }

                glRasterPos2i(width/2-150, 300);
                for (const char &letter : pong9) {
                    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
                }

                glRasterPos2i(width/2-30, 320);
                for (const char &letter : pong10) {
                    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
                }
            }

            for (Circle &flake: snow) {
                flake.draw();
            }

            glFlush();
            break;

        case (lastWin):
            glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(1, 1, 1);
            glRasterPos2i(400, 400);

            for (const char &message: endScreenWin) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, message);
            }

            for (Circle &flake: snow) {
                flake.draw();
            }
            glFlush();
            break;

        case (lastLost):
            glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(1, 1, 1);
            glRasterPos2i(400, 400);
            for (const char &message: endScreenLose) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, message);
            }
            for (Circle &flake: snow) {
                flake.draw();
            }
            glFlush();
            break;
    }
}



// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    if (key == 'm') {
        screen = first;
    }
   /* if (key == 'm') {
        screen = middleMaze;
    }
    if (key == 'd') {
        user.setCenter(400,700);
        screen = middleDodge;
    }
    if (key == 'p') {
        screen = middlePing;
    }*/
    if (key == '119') {
        screen = lastLost;
    }
    if (screen == pingGame) {
        if (key == 'a') {
            if (leftRacket.qgetTopY() > 0) {
                leftRacket.qmove(0, -50);
            }
        }
        if (key == 'q') {
            if (leftRacket.qgetBottomY() < height) {
                leftRacket.qmove(0, 50);
            }
        }
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {

        case GLUT_KEY_DOWN:
            user.move(0, 5);
            if (screen == pingGame) {
                if (rightRacket.qgetBottomY() < height) {
                    rightRacket.qmove(0, 50);
                }
            }
            break;
        case GLUT_KEY_LEFT:
            user.move(-5, 0);
            break;
        case GLUT_KEY_RIGHT:
            user.move(5, 0);
            break;
        case GLUT_KEY_UP:
            user.move(0, -5);
                if (screen == pingGame) {
                    if (rightRacket.qgetTopY() > 0) {
                        rightRacket.qmove(0, -50);
                    }
                }
            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {
    // TODO: Set the user's center point to be the coordinates
    //Hover
    if(mButton.qisOverlapping(x, y)){
        mButton.qhover();
    }
    else{
        mButton.qrelease();
    }
    if(pButton.qisOverlapping(x, y)){
        pButton.qhover();
    }
    else{
        pButton.qrelease();
    }
    if(startPong.qisOverlapping(x, y)){
        startPong.qhover();
    }
    else{
        startPong.qrelease();
    }
    if(dButton.qisOverlapping(x, y)){
        dButton.qhover();
    }
    else{
        dButton.qrelease();
    }

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mButton.qisOverlapping(x, y)){
        mButton.qpressDown();
    }
    else{
        mButton.qrelease();
    }
    // TODO: If the left button is up and the cursor is overlapping with the Button, call spawnConfetti.
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && mButton.qisOverlapping(x, y)){
        screen = middleMaze;
    }
    //Ping pong
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && pButton.qisOverlapping(x, y)){
        pButton.qpressDown();
    }
    else{
        pButton.qrelease();
    }
    // TODO: If the left button is up and the cursor is overlapping with the Button, call spawnConfetti.
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && pButton.qisOverlapping(x, y)){
        screen = middlePing;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && startPong.qisOverlapping(x, y)){
        startPong.qpressDown();
    }
    else{
        startPong.qrelease();
    }
    // TODO: If the left button is up and the cursor is overlapping with the Button, call spawnConfetti.
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && startPong.qisOverlapping(x, y)){
        screen = pingGame;
    }
    //Dodge
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && dButton.qisOverlapping(x, y)){
        dButton.qpressDown();
    }
    else{
        dButton.qrelease();
    }
    // TODO: If the left button is up and the cursor is overlapping with the Button, call spawnConfetti.
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && dButton.qisOverlapping(x, y)){
        screen = middleDodge;
        user.setCenter(400,700);
    }

    glutPostRedisplay();
}
void timerSnow(int dummy) {
    for (Circle &flake : snow) {
        flake.moveY(flake.getRadius());
        if (flake.getTopY() > height) {
            flake.setCenter(rand() % int(width), -flake.getRadius());
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, timerSnow, dummy);
}
void pingTimer(int dummy) {
    if (screen == pingGame) {
        ball.qmove(ball.qgetXVelocity(), ball.qgetYVelocity());
        if (ball.qgetCenterX() < ball.qgetWidth() / 2) {
            ball.bounceX();
            ball.qsetCenter(width / 2, height / 2);
            ball.qsetVelocity((rand() % 50 - 25), (rand() % 50 - 25));
            playerRPoints++;
        } else if (ball.qgetCenterX() > (width - ball.qgetWidth() / 2)) {
            ball.bounceX();
            ball.qsetCenter(width / 2, height / 2);
            ball.qsetVelocity((rand() % 50 - 25), (rand() % 50 - 25));
            playerLPoints++;
        }
        if (ball.qgetCenterY() < ball.qgetHeight() / 2) {
            ball.bounceY();
            ball.qsetCenterY(ball.qgetHeight() / 2);
        } else if (ball.qgetCenterY() > (height - ball.qgetHeight() / 2)) {
            ball.bounceY();
            ball.qsetCenterY(height - ball.qgetHeight() / 2);
        }
        if (ball.qisOverlapping(leftRacket)) {
            ball.bounceY();
            ball.bounceX();
            ball.qsetXVelocity((rand() % 10 + 1));
            ball.qsetYVelocity((rand() % 10));
            while (ball.qgetYVelocity() == 0){
                ball.qsetYVelocity((rand() % 10));
            }
        }
        if (ball.qisOverlapping(rightRacket)) {
            ball.bounceY();
            ball.bounceX();
            ball.qsetXVelocity((rand() % 10 - 21));
            ball.qsetYVelocity((rand() % 10));
            while (ball.qgetYVelocity() == 0){
                ball.qsetYVelocity((rand() % 10));
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(10, pingTimer, dummy);
}
void timerDodge(int dummy) {
    for (Rect &object : objects) {
        object.moveY(object.getWidth());
        if (object.getTopY() > height) {
            object.setCenter(rand() % int(width), -object.getHeight());
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, timerSnow, dummy);
}

void blockTimer(int dummy) {
    // TODO: Make the other two vectors of buildings move.
    // The larger the buildings, the slower they should move.

    for (int i = 0; i < block1.size(); ++i) {
        // Move all the red buildings to the left
        block1[i].moveX(-3);
        block1[i].moveY(3);
        // If a shape has moved off the screen
        if (block1[i].getCenterX() < -(block1[i].getWidth()/2)) {
            // Set it to the right of the screen so that it passes through again
            int blockOnLeft = (i == 0) ? block1.size()-1 : i - 1;
            block1[i].setCenterX(block1[blockOnLeft].getCenterX() + block1[blockOnLeft].getWidth()/2 + block1[i].getWidth()/2 + 5);
        }
    }

//buildings 2
    for (int i = 0; i < block2.size(); ++i) {
        // Move all the red buildings to the left
        block2[i].moveY(-3);
        // If a shape has moved off the screen
        if (block2[i].getCenterX() < -(block2[i].getWidth()/2)) {
            // Set it to the right of the screen so that it passes through again
            int blockOnLeft = (i == 0) ? block2.size()-1 : i - 1;
            block2[i].setCenterX(block2[blockOnLeft].getCenterX() + block2[blockOnLeft].getWidth()/2 + block2[i].getWidth()/2 + 5);
        }
    }


//buildings 3
    for (int i = 0; i < block3.size(); ++i) {
        // Move all the red buildings to the left
        block3[i].moveX(-3);
        //block3[i].moveY(1);
        // If a shape has moved off the screen
        if (block3[i].getCenterX() < -(block3[i].getWidth()/2)) {
            // Set it to the right of the screen so that it passes through again
            int blockOnLeft = (i == 0) ? block3.size()-1 : i - 1;
            block3[i].setCenterX(block3[blockOnLeft].getCenterX() + block3[blockOnLeft].getWidth()/2 + block3[i].getWidth()/2 + 5);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(30, blockTimer, dummy);


}
void resetVariables() {
    leftRacket = Quad();
    rightRacket = Quad();
    ball = Quad();
    playerLPoints = 0;
    playerRPoints = 0;
}


/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv) {

        init();

        glutInit(&argc, argv);          // Initialize GLUT

        glutInitDisplayMode(GLUT_RGBA);

        glutInitWindowSize((int) width, (int) height);
        glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
        /* create the window and store the handle to it */
        wd = glutCreateWindow("Mountain Maze!");

        // Register callback handler for window re-paint event
        glutDisplayFunc(display);

        // Our own OpenGL initialization
        initGL();

        // register keyboard press event processing function
        // works for numbers, letters, spacebar, etc.
        glutKeyboardFunc(kbd);

        // register special event: function keys, arrows, etc.
        glutSpecialFunc(kbdS);


        // handles mouse movement
        glutPassiveMotionFunc(cursor);

        // handles mouse click
        glutMouseFunc(mouse);

        // handles timer
        glutTimerFunc(0, timerSnow, 0);
        glutTimerFunc(0, timerDodge, 0);
        glutTimerFunc(0, blockTimer, 0);
        glutTimerFunc(0, pingTimer, 0);


        // Enter the event-processing loop
        glutMainLoop();


        return 0;

}