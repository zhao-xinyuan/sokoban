#include <state.h>
std::string line;
std::ifstream fs;
std::string input_level = "";
int main(int argc,char** argv)
{
    State initialState;
    State currentState;
    if(argc!=2) {std::cerr <<" usage: "<<argv[0]<<std::endl;return 0;}
    fs.open(argv[1]);
    if(!fs) {std::cerr<<" can not open file"<<argv[1]<<std::endl;return 0;}
    while (std::getline(fs, line))
    {
        input_level.append(line) += "\n";
    }
    fs.close();
    initialState.state_str = input_level;
    initialState.move_list="";
    Search breadthfirst;
    currentState=breadthfirst.breadthFirst(initialState);
    std::cout<<currentState.move_list<<std::endl;
}

