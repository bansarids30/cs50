//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 15

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    double velocityx=drand48()+2, velocityy=drand48()+2;
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        GEvent event = getNextEvent(MOUSE_EVENT);
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure circle follows top cursor
                double x = getX(event) - getWidth(paddle) / 2;
                double y = 550;
                setLocation(paddle,x,y);
            }
        }
        
        move(ball, velocityx, velocityy);
        
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocityx = -velocityx;
        }
        else if (getX(ball) <= 0)
        {
            velocityx = -velocityx;
        }
        else if(getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            pause(30);
            setLocation(ball,200,300);
            waitForClick();
        }
        else if(getY(ball)<=0)
        {
            velocityy=-velocityy;
        }
        pause(10);
        GObject object = detectCollision(window, ball);
        if(object!=NULL)
        {
            if(object == paddle)
            {
                velocityy=-velocityy;
            } 
              
            else if((strcmp(getType(object), "GRect") == 0))
            {
                points++;
                bricks--;
                velocityy=-velocityy;
                updateScoreboard(window,label,points);
                removeGWindow(window,object);
            }
        }
        
    }
    if(lives<=0)
    {
        GLabel lose=newGLabel("GAME OVER!!");
        setColor(lose, "GRAY");
        setFont(lose, "SansSerif-48");
        setLocation(lose, 100, 250);
        add(window,lose);
    }
    if(bricks<=0)
    {
        GLabel win=newGLabel("YOU WIN!!");
        setColor(win, "GRAY");
        setFont(win, "SansSerif-48");
        setLocation(win, 100, 250);
        add(window,win);
    }
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int span=40, y=40;
    char* colors[5]={"RED","ORANGE","YELLOW","GREEN","BLUE"}; 
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<WIDTH;j=j+span)
        {
            GRect rect = newGRect(j+2,y,36,10);
            setColor(rect, colors[i]);
            setFilled(rect,true);
            add(window,rect);
        }
        y=y+14;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval circle = newGOval(getWidth(window)/2-RADIUS/2, getHeight(window)/2-RADIUS/2, RADIUS, RADIUS);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    add(window, circle);
    return circle;
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect rect=newGRect(getWidth(window)/2-30, 550, 60, 10);
    setColor(rect, "BLACK");
    setFilled(rect,true);
    add(window,rect);
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label=newGLabel("0");
    double x = (getWidth(window)-getWidth(label) ) / 2;//
    double y = (getHeight(window) + getFontAscent(label)) / 2;
    setColor(label, "GRAY");
    setFont(label, "SansSerif-48");
    setLocation(label, x, y-20);
    add(window,label);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
