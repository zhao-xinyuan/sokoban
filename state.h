#ifndef STATE
#define STATE
#include <string>
#include <deque>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>
#include <iostream>
struct State
{
    std::string state_str;
    std::string move_list; 
};
class Search
{
    public:
        Search(){}
        State breadthFirst (State);
    private:
        void printLevel(std::vector< std::vector<char> > &map);
        bool isGoal(State &curState);
        void newStatestr(std::vector<std::vector<char>>,State& newState);
        std::queue<State> genStates (const State &cur_state);
};
#endif // STATE

