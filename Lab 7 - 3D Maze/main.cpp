#include "Maze.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int main(int argc, char* argv[]) {
    VS_MEM_CHECK            // enable memory leak check

    // set up input and output files and read them
    if (argc < 3) {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out) {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    // read in dimension size
    int height, width, layer, value = 0;
    in >> height >> width >> layer;

    // dynamically allocate array via constructor
    Maze maze(height, width, layer);

    // fill maze values
    for(int i = 0; i < layer; i++) {
        for(int j = 0; j < height; j++) {
            for(int k = 0; k < width; k++) {
                in >> value;
                maze.setValue(j, k, i, value);          
            }
        }
    }

    // solve maze
    out << "Solve Maze:" << endl;
    out << maze.toString();

    // find the path
    if (maze.find_maze_path()) {
        out << "Solution:" << endl;
        out << maze.toString();
    }
    else {
        out << "No Solution Exists!" << endl;
    }

    return 0;
}