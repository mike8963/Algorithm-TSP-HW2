#include "tsp.hpp"

int main(int argc,char* argv[])
{
    try{
        TSP tsp(argv[1]);
        tsp.output();
    }
    catch(const char* fileError){
        cerr << "tsp: can't open file with file name \"" << fileError << "\"" << endl;
    }
    return 0;
}
