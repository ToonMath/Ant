echo "Give number of searches"
read Nsearches
echo "----------------------------------------------------------------------"
echo "--------------------------circle boundary-----------------------------"
echo "----------------------------------------------------------------------"

g++ -O2 -Wall -Werror -Dcircle=1  -pedantic -std=c++14 -o ant_food ant_food.cpp -lm
./ant_food $Nsearches

echo "----------------------------------------------------------------------"
echo "---------------------------box boundary-------------------------------"
echo "----------------------------------------------------------------------"

g++ -O2 -Wall -Werror -Dbox=1  -pedantic -std=c++14 -o ant_food ant_food.cpp -lm
./ant_food $Nsearches

echo "----------------------------------------------------------------------"
echo "------------------------Line boundary---------------------------------"
echo "----------------------------------------------------------------------"

g++ -O2 -Wall -Werror -Dline=1  -pedantic -std=c++14 -o ant_food ant_food.cpp -lm
./ant_food $Nsearches
