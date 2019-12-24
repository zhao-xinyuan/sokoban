#include "state.h"
void Search::printLevel(std::vector< std::vector<char> > &map)
{
    for (int i = 0; i < map.size(); i++)
    {
        std::vector<char> vec = map[i];
        std::vector<char>::iterator itr;
        for (itr = vec.begin(); itr != vec.end(); itr++)
            std::cout << *itr;
        std::cout << std::endl;
    }
}
State Search::breadthFirst(State initial_state)
{
    std::deque<State> unSearched;
    std::vector<State> Searched;
    State currentState;
    State goalState;
    unSearched.push_back(initial_state);
    while(!unSearched.empty())
    {
        currentState=unSearched.front();
        unSearched.pop_front();
        Searched.push_back(currentState);
        if (isGoal(currentState))
        {
            goalState=currentState;
            unSearched.pop_front();
            break;
        }
        std::queue<State>validStates=genStates(currentState);
        while(!validStates.empty())
        {
            bool seen=false;
            State tempState=validStates.front();
            for(std::vector<State>::iterator iter=Searched.begin();iter!=Searched.end();iter++)
            {
                if(iter->state_str==tempState.state_str)
                {
                    seen=true;
                    break;
                }
            }
            for(std::deque<State>::iterator iter=unSearched.begin();iter!=unSearched.end();iter++)
            {
                if(iter->state_str==tempState.state_str)
                {
                    seen=true;
                    break;
                }
            }
            if(!seen)
            {
                unSearched.push_back(tempState);
            }
            validStates.pop();
        }
    }
    return goalState;
}


bool Search::isGoal(State &cur_state)
{
   bool goal = false;
   if ((cur_state.state_str.find_first_of('.')) == std::string::npos)
   {
       if ((cur_state.state_str.find_first_of('+')) == std::string::npos)
       {
           if ((cur_state.state_str.find_first_of('$')) == std::string::npos)
               goal = true;
       }
   }
   return goal;
}

void Search::newStatestr(std::vector<std::vector<char> > newLevelmap, State& newState)
{
    for(int i = 0;i<newLevelmap.size();i++)
    {
        std::vector<char>::iterator iter;
        for(iter=newLevelmap[i].begin();iter!=newLevelmap[i].end();iter++)
        {
            newState.state_str.push_back(*iter);
        }
        newState.state_str.append("\n");
    }
}
std::queue<State> Search::genStates(const State &cur_state)
{
    std::queue<State> moves;
    std::stringstream ss(cur_state.state_str);
    std::vector< std::vector<char> > newLevelmap;
    State newState;
    std::string line;
    std::vector<std::vector<char>> levelMap;
    int x,y,counter=0;
    while(std::getline(ss,line,'\n'))
    {
        std::vector<char> temp;
        levelMap.push_back(temp);
        for(int i=0;i<line.length();i++)
        {
           if(line[i]=='@' | line[i]=='+')
           {
               x=i;
               y=counter;
           }
           levelMap[counter].push_back(line[i]);
        }
        counter++;
    }
    char north=levelMap[y-1][x];
    switch(north)
    {
        case' ':
            newLevelmap = levelMap;
            newLevelmap[y-1][x]='@';
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("u,");
            moves.push(newState);
            break;
        case'#':
            break;
        case'.':
            newLevelmap = levelMap;
            newLevelmap[y-1][x]='+';
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("u,");
            moves.push(newState);
            break;
        case'$':
            newLevelmap = levelMap;
            newLevelmap[y-1][x]='@';
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            if(newLevelmap[y-2][x]=='#')
                break;
            else if (newLevelmap[y-2][x]=='$')
                break;
            else if (newLevelmap[y-2][x]=='*')
                break;
            else if(newLevelmap[y-2][x]==' ')
                newLevelmap[y-2][x]='$';
            else if(newLevelmap[y-2][x]=='.')
                newLevelmap[y-2][x]='*';
            else
                break;
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("u,");
            moves.push(newState);
            break;
        case'*':
            newLevelmap = levelMap;
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            newLevelmap[y-1][x]='+';
            if(newLevelmap[y-2][x]=='#')
                break;
            else if (newLevelmap[y-2][x]=='$')
                break;
            else if (newLevelmap[y-2][x]=='*')
                break;
            else if(newLevelmap[y-2][x]==' ')
                newLevelmap[y-2][x]='$';
            else if(newLevelmap[y-2][x]=='.')
                newLevelmap[y-2][x]='*';
            else
                break;
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("u,");
            moves.push(newState);
            break;
        default:
            break;
    }
    char south=levelMap[y+1][x];
    switch(south)
    {
        case' ':
            newLevelmap = levelMap;
            newLevelmap[y+1][x]='@';
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("d,");
            moves.push(newState);
            break;
        case'#':
            break;
        case'.':
            newLevelmap = levelMap;
            newLevelmap[y+1][x]='+';
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("d,");
            moves.push(newState);
            break;
        case'$':
            newLevelmap = levelMap;
            newLevelmap[y+1][x]='@';
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            if(newLevelmap[y+2][x]=='#')
                break;
            else if (newLevelmap[y+2][x]=='$')
                break;
            else if (newLevelmap[y+2][x]=='*')
                break;
            else if(newLevelmap[y+2][x]==' ')
                newLevelmap[y+2][x]='$';
            else if(newLevelmap[y+2][x]=='.')
                newLevelmap[y+2][x]='*';
            else
                break;
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("d,");
            moves.push(newState);
            break;
        case'*':
            newLevelmap = levelMap;
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            newLevelmap[y+1][x]='+';
            if(newLevelmap[y+2][x]=='#')
                break;
            else if (newLevelmap[y+2][x]=='$')
                break;
            else if (newLevelmap[y+2][x]=='*')
                break;
            else if(newLevelmap[y+2][x]==' ')
                newLevelmap[y+2][x]='$';
            else if(newLevelmap[y+2][x]=='.')
                newLevelmap[y+2][x]='*';
            else
                break;
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("d,");
            moves.push(newState);
            break;
        default:
            break;
    }
    char east=levelMap[y][x+1];
    switch(east)
    {
        case' ':
            newLevelmap = levelMap;
            newLevelmap[y][x+1]='@';
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("r,");
            moves.push(newState);
            break;
        case'#':
            break;
        case'.':
            newLevelmap = levelMap;
            newLevelmap[y][x+1]='+';
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("r,");
            moves.push(newState);
            break;
        case'$':
            newLevelmap = levelMap;
            newLevelmap[y][x+1]='@';
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            if(newLevelmap[y][x+2]=='#')
                break;
            else if (newLevelmap[y][x+2]=='$')
                break;
            else if (newLevelmap[y][x+2]=='*')
                break;
            else if(newLevelmap[y][x+2]==' ')
                newLevelmap[y][x+2]='$';
            else if(newLevelmap[y][x+2]=='.')
                newLevelmap[y][x+2]='*';
            else
                break;
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("r,");
            moves.push(newState);
            break;
        case'*':
            newLevelmap = levelMap;
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            newLevelmap[y][x+1]='+';
            if(newLevelmap[y][x+2]=='#')
                break;
            else if (newLevelmap[y][x+2]=='$')
                break;
            else if (newLevelmap[y][x+2]=='*')
                break;
            else if(newLevelmap[y][x+2]==' ')
                newLevelmap[y][x+2]='$';
            else if(newLevelmap[y][x+2]=='.')
                newLevelmap[y][x+2]='*';
            else
                break;
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("r,");
            moves.push(newState);
            break;
        default:
            break;
    }
    char west=levelMap[y][x-1];
    switch(west)
    {
        case' ':
            newLevelmap = levelMap;
            newLevelmap[y][x-1]='@';
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("l,");
            moves.push(newState);
            break;
        case'#':
            break;
        case'.':
            newLevelmap = levelMap;
            newLevelmap[y][x-1]='+';
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("l,");
            moves.push(newState);
            break;
        case'$':
            newLevelmap = levelMap;
            newLevelmap[y][x-1]='@';
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            if(newLevelmap[y][x-2]=='#')
                break;
            else if (newLevelmap[y][x-2]=='$')
                break;
            else if (newLevelmap[y][x-2]=='*')
                break;
            else if(newLevelmap[y][x-2]==' ')
                newLevelmap[y][x-2]='$';
            else if(newLevelmap[y][x-2]=='.')
                newLevelmap[y][x-2]='*';
            else
                break;
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("l,");
            moves.push(newState);
            break;
        case'*':
            newLevelmap = levelMap;
            (newLevelmap[y][x]=='+')?newLevelmap[y][x]='.':newLevelmap[y][x]=' ';
            newLevelmap[y][x-1]='+';
            if(newLevelmap[y][x-2]=='#')
                break;
            else if (newLevelmap[y][x-2]=='$')
                break;
            else if (newLevelmap[y][x-2]=='*')
                break;
            else if(newLevelmap[y][x-2]==' ')
                newLevelmap[y][x-2]='$';
            else if(newLevelmap[y][x-2]=='.')
                newLevelmap[y][x-2]='*';
            else
                break;
            newState=cur_state;
            newState.state_str="";
            newStatestr(newLevelmap,newState);
            newState.move_list.append("l,");
            moves.push(newState);
            break;
        default:
            break;
    }
    return moves;
}
