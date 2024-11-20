//contains, by the end, all files needed.
#include "main_functions.h"
#include <time.h>

void gameLoop(int &score, bool &win, XEvent &event)
{   
    //frame_Rate
    double t;

    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(0, 0, 255));

    string msg_cmd("Movement: _");
    Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);

    // Intialize the shooter
    Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);

    // Initialize the bubbles
    vector<Bubble> bubbles = create_bubbles();

    // Initialize the bullets (empty)
    vector<Bullet> bullets;
    
    //health bar border
    Rectangle r = Rectangle(WINDOW_X -70, WINDOW_Y - 30, 110, 20);

    //Timer set up
    int One_sec_frames = 1/STEP_TIME , frame_since_second = 0; //to track whether 1 second has passed
    int time_left = TOTAL_TIME;
    Text timer(LEFT_MARGIN + 200, BOTTOM_MARGIN, "Time left : ");

    //Scoring set up
    int score_update;
    Text scoreBoard(LEFT_MARGIN + 90, BOTTOM_MARGIN,"Score : 0");

    //stop bullet spam
    short int stop_gun_frames = 0;
    short int no_frames = 0.1/STEP_TIME;
    
    //slippery movement settings
    bool go_right = false, go_left = false;

    // Main game loop
    while (true)
    {
        t = clock();

        beginFrame();
        bool pendingEvent = checkEvent(event);
        
        if (pendingEvent)
        {
            // Get the key pressed
            char c = charFromEvent(event);

            //update if movement
            if(c == 'a' || c == 'd' || c == 's'){
                msg_cmd[msg_cmd.length() - 1] = c;
                charPressed.setMessage(msg_cmd);
            };

            // Update the shooter movement
            if(c == 'a'){
                go_left = true; go_right = false;
            }

            else if(c == 'd'){
                go_left = false; go_right = true;                
            }

            else if(c == 's'){
                go_right = go_left = false;
            }

            else if(c == 'w'){
                //stop if shoot
                go_right = go_left = false;
                msg_cmd[msg_cmd.length() - 1] = 's';
                charPressed.setMessage(msg_cmd);

                //wait for 0.1 seconds for next bullet
                if(stop_gun_frames > 0)
                    stop_gun_frames--;

                else
                {
                    bullets.push_back(shooter.shoot());
                    stop_gun_frames = no_frames;
                }
            }

            else if(c == 'q')
            {    
                endFrame();

                //pause_menu returns true if player wants to quit
                bool quit = pause_menu(event);
                if(quit){
                    score = -1; return;
                }
                else
                {
                    //reset time and drawing
                    beginFrame();
                    t = clock();
                }
            }
        }

        if(go_left)
            shooter.move(STEP_TIME, true);

        if(go_right)
            shooter.move(STEP_TIME, false);

        if(stop_gun_frames > 0)
            stop_gun_frames--;

        // Update the bubbles
        move_bubbles(bubbles);

        // Update the bullets
        move_bullets(bullets);

        //update score
        score_update = collisions(bubbles, bullets, shooter);
        if(score_update != 0)
        {
            score += score_update;
            scoreBoard.setMessage("Score : " + int_to_str(score));
        }

        //timer update
        if(frame_since_second == 0)
        {
            time_left --;
            timer.setMessage("Time left : " + int_to_str(time_left));
        }
        frame_since_second = (1 + frame_since_second)%(One_sec_frames);

        //win condition
        if(bubbles.size() == 0){
            score += 5*time_left;
            win = true;
            break;
        }

        //lose condition
        if(shooter.is_dead()|| time_left == 0){
            win = false;
            break;
        }

        endFrame();
        wait(STEP_TIME - (clock() - t)/double(CLOCKS_PER_SEC));
    }
}

int main()
{
    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);

    //String messages
    {
        Text startMessage_1(WINDOW_X/2, WINDOW_Y/2 - 100, "Welcome to Bubble Trouble - Slippery Edition!");
        
        Text startMessage_2_1(WINDOW_X/2, WINDOW_Y/2 - 40, "Avoid and shoot the bubbles.");
        Text startMessage_2_2(WINDOW_X/2, WINDOW_Y/2 - 20, "Popping them faster and while they are higher gives more points!");
        
        Text startMessage_3(WINDOW_X/2, WINDOW_Y/2 , 
                    "Press w to shoot, d to go right, a to go left, s to stop slipping or q to pause");
        startMessage_3.setColor(COLOR("red"));
        
        Text startMessage_4(WINDOW_X/2, WINDOW_Y/2 + 50, "Click anywhere to start");

        getClick();
    }

    short int no_wins = 0, no_losses = 0, best_score = 0;
    XEvent event;

    while(true){

        bool win; int score = 0;
        
        //modifies score and win
        gameLoop(score, win, event);
        Text game_status(WINDOW_X/2, WINDOW_Y/2 - 50, "");
        endFrame();

        //player quit
        if(score == -1)
            game_status.setMessage("You quit the last game");

        //player won
        else if(win){
            game_status.setMessage("You won! Score: " + int_to_str(score));
            no_wins ++;
            best_score = best_score > score ? best_score : score;
        }

        //player lost
        else{
            game_status.setMessage("You lost. Better luck next time!");
            no_losses ++;
        }
        
        Text stats(WINDOW_X/2, WINDOW_Y/2 , 
            "Best score: " + int_to_str(best_score) + " Wins: " + int_to_str(no_wins) + " Losses: " + int_to_str(no_losses));        
        Text options(WINDOW_X/2, WINDOW_Y/2 + 20,"Press p to play another game, or q to quit game window");
        Text game_controls(WINDOW_X/2, WINDOW_Y/2 + 50, 
            "Press w to shoot, d to go right, a to go left, s to stop slipping or q to pause");
        game_controls.setColor(COLOR("red"));

        if(quit(event))
            break;
    }
}
