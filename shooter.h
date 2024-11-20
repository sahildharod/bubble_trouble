#include "bullet.h"

class Shooter
{
private:
    Rectangle body; // The body of the shooter
    Circle head;    // The head of the shooter
    double vx;      // The x-velocity of the shooter
    Color color;    // The color of the shooter
    int health, length_bar;
    Rectangle health_bar;
    unsigned int Inv_frames; // no. of frames shooter remains unaffected after a single hit

public:
    Shooter(double position_x, double position_y, double vx_=SHOOTER_VX, Color color_=COLOR(0, 255, 0))
    {   
        // Shooter constructor
        color = color_;
        health = INITIAL_HEALTH;

        // body (represented by a rectangle)
        body = Rectangle(position_x, position_y, SHOOTER_WIDTH, SHOOTER_HEIGHT);                        
        body.setColor(color);
        body.setFill(true);

        // head (represented by a circle)
        head = Circle(position_x, position_y - (SHOOTER_HEIGHT/2.0) - HEAD_RADIUS, HEAD_RADIUS);   
        head.setColor(color);
        head.setFill(true);

        // initial velocity
        vx = vx_;

        //health bar
        length_bar = 100;
        health_bar = Rectangle(WINDOW_X -122 + (length_bar/2), WINDOW_Y - 30, length_bar, 12);
        health_bar.setFill(true);
        health_bar.setColor(COLOR("red"));

        Inv_frames = 0;
    }
    
    Bullet shoot()
    {
        // shoot a bullet
        return Bullet(head.getX(), head.getY());
    }

    void move(const double &t, bool is_moving_left)
    {   
        // move the shooter
        double vel = vx;
        if (is_moving_left)
        {
            vel = -vel;
        }

        double new_body_x = body.getX() + vel*t;
        double new_head_x = head.getX() + vel*t;

        if (vel < 0 && new_body_x < (0 + body.getWidth()/2.0)) // stop moving along X direction at left border (if pressed A)
        {
            new_body_x = 0 + body.getWidth()/2.0;
            new_head_x = 0 + body.getWidth()/2.0;
        }
        else if (vel > 0 && new_body_x > (WINDOW_X - body.getWidth()/2.0)) // stop moving along X direction at right border (if pressed D)
        {
            new_body_x = WINDOW_X - body.getWidth()/2.0;
            new_head_x = WINDOW_X - body.getWidth()/2.0;
        }

        body.moveTo(new_body_x, body.getY());
        head.moveTo(new_head_x, head.getY());
    }

    void hit()
    {   
        //check and set invulnerability frames
        if(!Inv_frames){
            health -=10;
            Inv_frames = 20;

            //body color = red
            body.setColor(COLOR(200, 0, 0));
            head.setColor(COLOR(200, 0, 0));

            //update health bar
            length_bar = health*100/INITIAL_HEALTH;
            health_bar = Rectangle(WINDOW_X - 122 + (length_bar/2), WINDOW_Y - 30, length_bar, 12);
            health_bar.setFill(true);
            health_bar.setColor(COLOR("red"));
        }
    }

    bool is_dead()
    {
        //reduce invulnerable frames if they are >0.
        if(Inv_frames == 0){}

        else if(Inv_frames>1)
            Inv_frames --;
        else if(Inv_frames == 1)
        {
            Inv_frames = 0;

            //reset body color
            body.setColor(COLOR(0, 255, 0));
            head.setColor(COLOR(0, 255, 0));
        }

        //true if dead
        if(health <= 0)
           return true;
        return false;
    }

    double get_head_center_x()
    {
        // return the x coordinate of the center of the head
        return head.getX();
    }
    
    double get_head_center_y()
    {
        // return the y coordinate of the center of the head
        return head.getY();
    }

    double get_body_center_x()
    {
        // return the x coordinate of the center of the body
        return body.getX();
    }

    double get_body_center_y()
    {
        // return the y coordinate of the center of the body
        return body.getY();
    }   
};
