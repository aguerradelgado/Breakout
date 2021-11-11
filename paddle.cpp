// file: paddle.h
//  lab: 11
//   by: A. Guerra
//  org: COP 2001, 10410/10409
// desc: implementation of a player paddle block class object
// --------------------------------------------------------
#include <math.h>   // for velocity checking
#include "paddle.h"

// global constants for paddle only
const float ACCEL_SPEED = 6.0;
const float MAX_SPEED = 300.0;

// constructors
// --------------------------------------------------------

/**
 * default constructor - initialize empty block
 */
Paddle::Paddle()
{
    paddle = Block();
    currentX = 0.0;
    currentY = 0.0;
    velocity = 0.0;
}


/**
 * property constructor - initialize to parameter values
 */
Paddle::Paddle(int x, int y, int width, int height, fgcugl::Color color)
{
    paddle = Block(x, y, width, height, color );
    currentX = x;
    currentY = y;
    velocity = 0.0;

}

// accessors
// --------------------------------------------------------
// getters (to get the private properties)
Block Paddle::getPaddle() {return paddle; }           // READ ONLY
float Paddle::getXCoordinate() { return currentX; }
float Paddle::getYCoordinate() { return currentY; }
int Paddle::getWidth() { return paddle.getWidth(); }
int Paddle::getHeight() { return paddle.getHeight(); }
fgcugl::Color Paddle::getColor() { return paddle.getColor(); }
float Paddle::getVelocity() { return velocity;}

// setters
void Paddle::setXCoordinate(float value)
{
    currentX = value;
    paddle.setXCoordinate(value);
}
void Paddle::setYCoordinate(float value)
{
    currentY = value;
    paddle.setYCoordinate(value);
}
void Paddle::setWidth(int value) { paddle.setWidth(value); }
void Paddle::setHeight(int value ) { paddle.setHeight(value); }
void Paddle::setColor(fgcugl::Color value) { paddle.setColor(value); }
void Paddle::setVelocity(float value) { velocity = value; }

// member methods
// --------------------------------------------------------
int Paddle::top() { return paddle.top(); }
int Paddle::bottom() { return paddle.bottom(); }
int Paddle::left() { return paddle.left(); }
int Paddle::right() { return paddle.right(); }

/**
 * return true if paddle is empty (will not ever be empty in current breakout but can be in future mods)
 */
bool Paddle::isEmpty() { return paddle. isEmpty(); }


/**
 * determine paddle direction from its velocity
 * (None = 0, Left = neg, Right = pos)
 *
 * Returns:
 * PaddleDirection - paddle is moving
 */
Paddle::PaddleDirection Paddle::currentDirection()
{
    PaddleDirection direction;

    if (fpclassify(velocity) == FP_ZERO)
    {
        direction = None;
    }
    else if (signbit(velocity))
    {
        direction = Left;
    }
    else
    {
        direction = Right;
    }

    return direction;
}


/**
 * update the location of the paddle each frame relative
 * to lag and perform collision checking with the left and right walls
 *
 * Parameters:
 * next       - user keyboard input
 * leftWall   - location of left wall
 * rightWall  - location of right wall
 * lag        - current frame lag
 */
void Paddle::update(PaddleDirection next, Block leftWall, Block rightWall, float lag)
{
    PaddleDirection curDir = currentDirection();

    // is player not holding a direction key
    if (next == None)
    {
        // if paddle is moving
        if (curDir != None)
        {
            // slow paddle to an eventual stop
            if (curDir == Left)
            {
                velocity += ACCEL_SPEED;
            }
            else {
                velocity -= ACCEL_SPEED;
            }
        } // paddle is moving
    }
    // player is holding a direction key down
    else
    {
        // accelerate paddle in usr direction
        if (next == Left)
        {
            velocity -= ACCEL_SPEED;
        }
        else
        {
            velocity += ACCEL_SPEED;
        } // accel

        // keep speed at or below max
        if (abs(velocity) > MAX_SPEED)
        {
            if (next == Left)
            {
                velocity = -MAX_SPEED;
            }
            else
            {
                velocity = MAX_SPEED;
            } // accel
        } // max speed

    } // holding direction

    // adjust paddle position
    currentX += velocity * lag;
    paddle.setXCoordinate(currentX);

    // check for collision with walls
    if (paddle.left() < leftWall.right())
    {
        velocity = 0.0;
        setXCoordinate(leftWall.right() + 1 );
    }
    else if (paddle.right() > rightWall.left())
    {
        velocity = 0.0;
        setXCoordinate(rightWall.left() - getWidth());
    }

} // update


/**
 * draw the paddle on the OpenGL window relative
 * to current x/y with lag
*/
void Paddle::draw(float lag)
{
    float x = currentX + velocity * lag;   // new x coord
    Block currentPos(paddle);  // direct initialization, similar to = paddle
    currentPos.setXCoordinate(x);
    currentPos.draw();
}


/**
 * Draw the paddle with a border by drawing the block passed in on
 * top of a background
 *
 * Parameters:
 * borderColor   color of the border block
 * borderSize    size of border in pixels
 */
void Paddle::drawWithBorder(float lag, fgcugl::Color borderColor, int borderSize)
{
    // temporary variables
    float x = currentX + velocity * lag;
    int y = currentY;
    int width = paddle.getWidth();
    int height = paddle.getHeight();
    fgcugl::Color color = paddle.getColor();

// draw background block
    Block background = Block(x, y, width, height, borderColor);
    background.draw();

    // draw inner block
    Block foreground = Block(x + borderSize, y + borderSize,
                             width - 2 * borderSize, height - 2 * borderSize,
                             color);
    foreground.draw();

}
