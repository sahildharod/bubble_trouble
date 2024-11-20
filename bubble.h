#include "game_vars.h"

class Bubble
{
private:
    Circle circle;  // the circle representing the bubble
    double vx, vy;  // velocity in x and y direction
    Color color;    // color of the bubble

public:
    Bubble(double cx, double cy, double r, double vx_, double vy_, Color color_)
    {
        // Bubble constructor
        color = color_;
        circle = Circle(cx, cy, r);
        circle.setColor(color);
        circle.setFill(true);

        vx = vx_;
        vy = vy_;
    }

    void nextStep(const double &t)
    {
        //update velocity - I have tested various functions
        //to find a trajectory I liked
        vy+= t*40 + pow(circle.getY(),0.5);
        
        // move the bubble
        double new_x = circle.getX() + vx*t;
        double new_y = circle.getY() + vy*t;

        if ((vx < 0 && new_x < (0 + circle.getRadius())) // bounce along X direction at left border
            ||
            (vx > 0 && new_x > (WINDOW_X - circle.getRadius()))) // bounce along X direction at right border
        {
            
            vx = -vx;
            new_x = circle.getX() + vx*t;
            
        }

        if(new_y + circle.getRadius()> PLAY_Y_HEIGHT)// bounce on the ground
        {
            vy = -vy;
            new_y += vy*t;
        }

        if(new_y < circle.getRadius())// bounce on the ceiling
        {
            vy = -vy;
            new_y += vy*t;
        }

        circle.moveTo(new_x, new_y);
    }

    //returns score for popping bubble
    int collide(vector<Bubble> &bubbles){


        Color color = COLOR(255,105,180);
        int vel = BUBBLE_DEFAULT_VX + 50;

        //checking which kind of circle was destroyed
        if(abs(circle.getRadius() - BASE_BUBBLE_RADIUS*1.5) < 0.05)
        {
            color = COLOR(255, 165, 0);
            vel += 50;
        }

        //add new bubbles if large bubble popped
        if(abs(circle.getRadius() - BASE_BUBBLE_RADIUS) > 0.05){
            bubbles.push_back(Bubble(circle.getX() +5, circle.getY(), 
                            2*circle.getRadius()/3, vel, vy, color));
            bubbles.push_back(Bubble(circle.getX()-5, circle.getY(),
                            2*circle.getRadius()/3, -vel, vy, color));
        }

        //bubbles shot higher should give more points
        return circle.getRadius()*2 + (BOTTOM_MARGIN - circle.getY())/10;
    }

    double get_radius()
    {
        // return the radius of the bubble
        return circle.getRadius();
    }

    double get_center_x()
    {
        // return the x coordinate of the center of the bubble
        return circle.getX();
    }

    double get_center_y()
    {
        // return the y coordinate of the center of the bubble
        return circle.getY();
    }

    double get_vx()
    {
        // return the x velocity of the bubble
        return vx;
    }
    double get_vy()
    {
        // return the y velocity of the bubble
        return vy;
    }

    Color get_color()
    {
        // return the color of the bubble
        return color;
    }
};
