#pragma once
#include <math.h>
#include <stdio.h>
using namespace std;


//Function Prototypes
double scale (double val, double a_max, double a_min, double b_max, double b_min);

//To Storage converted screenposition;
typedef struct sl_screen_position {
    
    double x;
    double y;
    
} sl_screen;

//To Storage Scaled position from -1.0 - 1.0
typedef struct sl_scaled_position {
    
    float x;
    float y;
    
} sl_eudlid_position;


double scale (double val, double a_max, double a_min, double b_max, double b_min){
    
    double ra = a_max - a_min;
    double rb = b_max - b_min;
    double ratio = rb/ra;
    
    return ( ((val-a_min)*ratio)+b_min );
}


class slEuclid {
    
    
    public:
 
        sl_screen_position screen;
        sl_scaled_position position;

        slEuclid(){
            
            //Set Screen Size
            screen_width = 1024;
            screen_height = 768;
            
            //Init Variables
            screen.x = 0.;
            screen.y = 0.;
            position.x = 0.;
            position.y = 0.;
            
        }        
    
        slEuclid(double x , double y){

            //Set Screen Size
            screen_width = x;
            screen_height = y;
            
            //Init Variables
            screen.x = 0.;
            screen.y = 0.;
            position.x = 0.;
            position.y = 0.;
            
        }
    
        double getScreenX (float scaled_x){
        
            //Convert scaled position to screen position
            return ( 0.5*(screen_width+(screen_width*scaled_x)) );
            
        }
    
        double getScreenY (float scaled_y){

            //Convert scaled position to screen position
            return ( screen_height - ( 0.5*(screen_height+(screen_height*scaled_y)) ) );
        }
    
        float getX (double got_screen_x){
            
            float half = screen_width*0.5;
            return ( (got_screen_x - half)/half );
        }
    
        float getY (double got_screen_y){
            
            float half = screen_height*0.5;
            return ( ((got_screen_y - half)/half) * -1 );
        }
    
    
    
        double setX (float scaled_x){
         
            return screen.x = getScreenX(scaled_x);
            
        }

        double setY (float scaled_y){
            
            return screen.y = getScreenY(scaled_y);
            
        }

        float setScreenX (double screen_x){

            return position.x = getX(screen_x);
            
        }
        
        float setScreenY (double screen_y){
            
            return position.y = getX(screen_y);
            
        }
    
    
      sl_screen_position getScreenPosition (sl_scaled_position got_position){

            sl_screen_position tmp_sc;
            tmp_sc.x = getScreenX(got_position.x);
            tmp_sc.y = getScreenY(got_position.y);
            return tmp_sc;
        }


       sl_screen_position getScreenPosition (float scaled_x, float scaled_y){

            sl_screen_position tmp_screen;
            sl_scaled_position tmp_position;
            tmp_position.x = scaled_x;
            tmp_position.y = scaled_y;
            tmp_screen = getScreenPosition(tmp_position);
            return tmp_screen;
        }

        sl_scaled_position getPosition (sl_screen_position sc){

            sl_scaled_position scaled;
            scaled.x = getX(sc.x);
            scaled.y = getY(sc.y);

            return scaled;

        }

        sl_scaled_position getPosition (double screen_x , double screen_y){

            sl_scaled_position scaled = getPosition(screen_x, screen_y);
            return scaled;

        }


        sl_screen_position setPositon (sl_scaled_position got_position){
            
            //Set is storage version of getPosition
            position = got_position;
            screen = getScreenPosition(position);
            return screen;
        }


        sl_scaled_position setScreenPosition (sl_screen_position got_screen_position){

            //Set is storage version of getScreenPosition
            screen = got_screen_position;
            position = getPosition(screen);
            return position;
            
        }

        int getLengthForScreen(float length)
        {
            if (length<0.) length = length * -1.; //Avoid minus param because it is length.
            return (int)((screen_height * length)*0.5);
        }

        bool intersect(sl_scaled_position a, sl_scaled_position b, sl_scaled_position c, sl_scaled_position d){

            // Check the intersect or not with two lines.
            // http://www.smipple.net/snippet/sparkon/%5BC%2B%2B%5D%202D%20lines%20segment%20intersection%20

            // Example of cast the struct (the member type must be same. this case, each struc has two float members.)
            // sl_scaled_position *a_st = (struct sl_scaled_position *)&target->center;

            float den = ((d.y-c.y)*(b.x-a.x)-(d.x-c.x)*(b.y-a.y));
            float num1 = ((d.x - c.x)*(a.y-c.y) - (d.y- c.y)*(a.x-c.x));
            float num2 = ((b.x-a.x)*(a.y-c.y)-(b.y-a.y)*(a.x-c.x));
            float u1 = num1/den;
            float u2 = num2/den;
            // std::cout << u1 << ":" << u2 << std::endl;
            if (den == 0 && num1  == 0 && num2 == 0)
                /* The two lines are coincidents */
                return false;
            if (den == 0)
                /* The two lines are parallel */
                return false;
            if (u1 <0 || u1 > 1 || u2 < 0 || u2 > 1)
                /* Lines do not collide */
                return false;
            /* Lines DO collide */
            return true;
        }
    
    
        float distance(sl_scaled_position a, sl_scaled_position b){
            
            float diff_x = a.x - b.x;
            float diff_y = a.y - b.y;
            
            
            diff_x *= diff_x;
            diff_y *= diff_y;
            
            float dist = (float)sqrt((double)diff_x+diff_y);
            return dist;
            
        }
    
    
        int whoisNearest(){
                cout << "test" << endl;
            
        }
    
        int whoisNearest(sl_scaled_position node , sl_scaled_position *others, int index_num){
    
            int id_shortest = 0;
            float shortest_dist = 999.9f;

            
            for(int i = 0; i<index_num;i++){
            
                float dist = this->distance(node, others[i]);
                if(dist < shortest_dist){
                    
                    id_shortest = i;
                    shortest_dist = dist;
                }
                
            }
            
            return id_shortest;
            
        }
 
    int whoisNearest(sl_scaled_position node , sl_scaled_position *others, int index_num, int node_id){
        
        int id_shortest = 0;
        float shortest_dist = 999.9f;
        
        
        for(int i = 0; i<index_num;i++){
            
            if(i == node_id)continue;
            
            float dist = this->distance(node, others[i]);
            if(dist < shortest_dist){
                
                id_shortest = i;
                shortest_dist = dist;
            }
            
        }
        
        return id_shortest;
        
    }
    
    
    private:
        double screen_width;
        double screen_height;
    
};