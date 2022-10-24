#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <time.h>


/*by performing random walks the object should be able to reach any position. For this case the object is an ant that start from an initial position (mostly the ant hill) ant searches for food to grow the colony.
 */

class Ant{
private:
    // save the initial location, the possible moves, the current location and the amount of steps the ant takes to find the food
    std::array <double,2> init_loc;
    std::vector<std::array<double,2>> moves;
    std::array <double,2> current_loc;
    std::vector<int> nsteps;
public:
    //create the prototype function that are defined outside of the class
    Ant()=default;
    //constructor that initializes the position of an ant
    Ant(double x0,double y0, bool food);
    void setMoves(std::vector<std::array<double,2>> hops);
    void setFood(std::vector<std::array <double,2>> boundary_points);
    void Move(void);
    bool foodChecker();
    void goForage(int nsearches);
    void getAverage(void);
    ~Ant()=default;
    
};

//define an ant at initial position (x0,y0)
Ant::Ant(double x0,double y0, bool food){
    init_loc[0] = x0;
    init_loc[1] = y0;
    current_loc[0]=x0;
    current_loc[1]=y0;
    
}

//define the direction the ant can take at each point
void Ant::setMoves(std::vector<std::array<double,2>> hops){
    for (std::array <double,2> hop: hops)
        moves.push_back(hop);
        //print the moves to test they are correctly saved
        //printf("moves are: (%g,%g)\n",hop[0],hop[1]);
    
    
}
//define the location of the food
void Ant::setFood(std::vector<std::array <double,2>> boundary_points){
    for(std::array <double,2> temp: boundary_points)
        boundary_points.push_back(temp);
}

//randomly select a direction the ant will move and update the current position
void Ant::Move(void){
    int getrand = rand()%4;
    current_loc[0] += moves[getrand][0];
    current_loc[1] += moves[getrand][1];
    //printf("next location is (%g,%g)\n",current_loc[0],current_loc[1]);
    
}



bool Ant::foodChecker(){
    bool food = 0;
    //define the function that describes the food region:
    //for a box of 4x4 centered at (0,0)
#ifdef box
    double xmin=-2,xmax=2,ymin=-2,ymax=2;
    
        if((current_loc[0] == xmin || current_loc[0]==xmax) && (current_loc[1]>=ymin || current_loc[1]<=ymax))
            food = 1;
        if((current_loc[0] >= xmin || current_loc[0]<=xmax) && (current_loc[1]==ymin || current_loc[1]==ymax))
            food = 1;
#endif
#ifdef line
    // if the boundarie is a line going through (0,1) and (1,0)
    double rc=0,y0=0;
    rc = -1; y0=1;
    double y = y0+rc*current_loc[0];
     if(y==current_loc[1])
         food = 1;
#endif
#if circle
    // if there is food located outside the circle ( (x – 2.5cm) / 30cm )2 + ( (y – 2.5cm) / 40cm )^2=1
    double xcenter,ycenter;
    xcenter=ycenter=0.25;
    double radius = pow(((current_loc[0]+xcenter)-xcenter) / 3 ,2) + pow( ((current_loc[1]+ycenter)-ycenter) / 4 ,2);
    double R = 1;
    
    if(radius>R)
        food=1;
#endif
    
    return food;
}




void Ant::goForage(int nsearches){
    printf("\nsearching for food");
    int steps = 0;
    srand(time(0));
    bool food=0;
    for(int n=0;n<nsearches;n++){
        food=0;
        steps=0;
//        printf("search %d\n",n);
        while(!food){
            Move();
            food = foodChecker();
            steps++;
            if(food || steps>100){
                food = 1;
                if(food && steps<100){
//                    printf("food located!!\n");
                    nsteps.push_back(steps);
                }
//                if(steps>100)
//                    printf("To far from hill, going back!!\n");
            }
        }
        current_loc[0] = init_loc[0];
        current_loc[1] = init_loc[1];
//        printf("number of steps = %d\n",steps);
    }
        
}

void Ant::getAverage(void){
    int total_steps=0;
    for(double x: nsteps)
        total_steps +=x;
#ifdef box
    printf("\nAverage steps box boundary = %d\n",(int)(total_steps/nsteps.size()));
#endif
    
#ifdef circle
    printf("\nAverage steps circle boundary = %d\n",(int)(total_steps/nsteps.size()));
#endif
    
#ifdef line
    printf("\nAverage steps line boundary = %d\n",(int)(total_steps/nsteps.size()));
#endif
}
int main(int a, char *argv[]){
    Ant ant1(0,0,0);
    ant1.setMoves({{1,0},{0,-1},{-1,0},{0,1}});
    ant1.setFood({{0,0}});
    ant1.goForage(atoi(argv[1]));
    ant1.getAverage();
}
