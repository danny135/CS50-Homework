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
#define COLS 8

//size of the bricks
#define BWIDTH 36
#define BHEIGHT 15

#define BPADDING 12

// radius of ball in pixels
#define RADIUS 10

//size of the paddle
#define PWIDTH 75
#define PHEIGHT 10

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

	double x, y, dx = drand48() * 0.04 - 0.02, dy = 0.02;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
    	GEvent event = getNextEvent(MOUSE_EVENT);
    	
    	if (event != NULL)
    	{
    		if (getEventType(event) == MOUSE_MOVED)
            {
                setLocation(paddle, getX(event) - PWIDTH / 2, getY(paddle));
            }
    	}
    
    	move(ball, dx, dy);
    	
    	x = getX(ball);
    	y = getY(ball);
        GObject object = detectCollision(window, ball);
        
        if (object != NULL) //If collided
        {
		    if (strcmp(getType(object), "GRect") == 0) //Hitting a GRect
		    {
		    	if (getY(ball) > HEIGHT/2 - RADIUS*3) //Hitting the paddle
		    	{
		    		dy = -dy;
		    		dx = (getX(ball) + RADIUS) - (getX(paddle) + PWIDTH/2);
		    		dx /= 2000;
		    		//dx = -dx;
		    	}
		    	else //Hitting a brick
		    	{
		    		dy = -dy;
		    		bricks--;
		    		points++;
		    		updateScoreboard(window, label, points);
		    		removeGWindow(window, object);
		    	}
		    }
		}
		
		if (x < 0) //Hits left side of screen
        {
        	x = 0;
        	if (dx < 0)
        	{
        		dx = -dx;
        	}
        }
        else if (x + 2*RADIUS > WIDTH) //Hits the right side of screen
        {
        	x = WIDTH - 2*RADIUS;
        	if (dx > 0)
        	{
        		dx = -dx;
        	}
        }
        
        if (y < 0) //Hit top of screen
        {
        	y = 0;
        	if (dy < 0)
        	{
        		dy = -dy;
        	}
        }
        else if (y + 2*RADIUS > HEIGHT) //Hits bottom of screen
        {
        	removeGWindow(window, ball);
        	lives--;
        	
        	if (lives > 0)
        	{
		    	ball = initBall(window);
		    	dx = drand48() * 0.04 - 0.02;
		    	waitForClick();
		    	if (dy < 0)
		    	{
		    		dy = -dy;
		    	}
		    }
        }
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
	int pX, pY;
    for (int y = 0; y < ROWS; y++)
    {
    	for (int x = 0; x < COLS; x++)
    	{
    		if (x == 0)
    		{
    			pX = BPADDING;
    		}
    		else
    		{
    			pX = x*BPADDING+BPADDING;
    		}
    		
    		if (y == 0)
    		{
    			pY = BPADDING;
    		}
    		else
    		{
    			pY = y*BPADDING+BPADDING;
    		}
    		
    		GRect brick = newGRect(x*BWIDTH+pX, y*BHEIGHT+pY, BWIDTH, BHEIGHT);
    		setFilled(brick, true);
    		
    		//Make it a random color
    		switch((int) (drand48() * 3))
    		{
    			case 0:
    				setColor(brick, "RED");
    				break;
    			case 1:
    				setColor(brick, "GREEN");
    				break;
    			case 2:
    				setColor(brick, "BLUE");
    				break;
    			default:
    				setColor(brick, "RED");
    				break;
    		}
    		add(window, brick);
    	}
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
	GOval ball = newGOval(WIDTH/2-RADIUS, HEIGHT/2-RADIUS, RADIUS*2, RADIUS*2);
	setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect rect = newGRect(WIDTH/2 - PWIDTH/2, HEIGHT - PHEIGHT * 2, PWIDTH, PHEIGHT);
	setFilled(rect, true);
    setColor(rect, "BLACK");
    add(window, rect);
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-40");
    
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    add(window, label);
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
