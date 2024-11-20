#include "shooter.h"

//distance between two points
double distance(double x_1, double y_1, double x_2, double y_2)
{
    return (sqrt((x_1-x_2)*(x_1-x_2) + (y_1-y_2)*(y_1-y_2)));
}

//checks all collisions of bubbles
int collisions(vector<Bubble> &bubbles, vector<Bullet> &bullets, Shooter &shooter){

    int score_update = 0;

    for (unsigned int i = 0; i< bubbles.size(); i++){

        //bullet collisions
        for (unsigned int j = 0; j < bullets.size(); j++){

            if(abs(bullets[j].get_center_x() - bubbles[i].get_center_x()) < bubbles[i].get_radius() + 2.5
                &&
                abs(bubbles[i].get_center_y() - bullets[j].get_center_y()) < bubbles[i].get_radius() +  5)
            {                
                Bubble bub = bubbles[i];
                bubbles.erase(bubbles.begin() + i);

                //for some reason, directly using bubbles[i].collide is crashing the
                //program in some cases.
                score_update += bub.collide(bubbles);
                bullets.erase(bullets.begin() + j);
            }
        }

        //shooter collision
        if( //body
            (abs(shooter.get_body_center_x() - bubbles[i].get_center_x()) < bubbles[i].get_radius() + SHOOTER_WIDTH
            &&
            shooter.get_body_center_y() - bubbles[i].get_center_y() < bubbles[i].get_radius() +  SHOOTER_HEIGHT/2)
            ||
            //head
        distance(shooter.get_head_center_x(),shooter.get_head_center_y(),bubbles[i].get_center_x(),bubbles[i].get_center_y()) 
                        < bubbles[i].get_radius() + HEAD_RADIUS
        ) shooter.hit();
    }

    return score_update;
}

void move_bullets(vector<Bullet> &bullets){
    // move all bullets
    for(unsigned int i=0; i<bullets.size(); i++){
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
        bubbles[i].nextStep(STEP_TIME);
    }
}

vector<Bubble> create_bubbles()
{
    // create larger bubbles in the game
    vector<Bubble> bubbles;
    bubbles.push_back(Bubble(WINDOW_X/4.0, 2.25 * BASE_BUBBLE_RADIUS + 50, 2.25 * BASE_BUBBLE_RADIUS, -BUBBLE_DEFAULT_VX, -100, COLOR(127,0,255)));
    bubbles.push_back(Bubble(0.75 * WINDOW_X, 2.25 * BASE_BUBBLE_RADIUS , 2.25 * BASE_BUBBLE_RADIUS, BUBBLE_DEFAULT_VX, 50, COLOR(127,0,255)));
    bubbles.push_back(Bubble(0.5 * WINDOW_X, 2.25 * BASE_BUBBLE_RADIUS , 2.25 * BASE_BUBBLE_RADIUS, 0, -100, COLOR(127,0,255)));
    return bubbles;
}

//return true if player wants to quit
bool quit(XEvent &event)
{
    char c;

    while(true)
    {
        nextEvent(event);
        c = charFromEvent(event);

        if(keyPressEvent(event))
        {
            if(c == 'p')
                return false;
            else if(c == 'q')
                return true;
        }
    }
}

bool pause_menu(XEvent &event)
{
    Text pauseMessage(WINDOW_X/2, WINDOW_Y/2-20, "Press q if you want to quit current game (Score will be lost)");
    Text startMessage_2(WINDOW_X/2, WINDOW_Y/2+20, "Press p to continue game");

    return quit(event);
}

string int_to_str(int a)
{
    if(a == 0)
        return "0";
    
    string s = "";

    while(a != 0)
    {
        char c = (a%10) + 48;//ASCII coding
        s = c + s;
        a/=10;
    }

    return s;
}
