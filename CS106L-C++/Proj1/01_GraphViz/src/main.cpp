#include <iostream>
#include "SimpleGraph.h"

using std::cout;	using std::endl;

void Welcome();

// Main method
int main() {
    Welcome();
    return 0;
}

/* Prints a message to the console welcoming the user and
 * describing the program. */
void Welcome() {
    cout << "Welcome to CS106L GraphViz!" << endl;
    cout << "This program uses a force-directed graph layout algorithm" << endl;
    cout << "to render sleek, snazzy pictures of various graphs." << endl;
    cout << endl;

    while(1)
    {
        std::string filename;
        double duration;
        SimpleGraph graph;

        cout << "Please enter the filename to visualize,quit for qiut" << endl;
        std::cin>>filename;
        if(filename=="qiut")
            break;
        cout<<"Please enter the Algorithm rumtime duration." << endl;
        std::cin >> duration;

        ReadGraph(filename,graph);

        InitGraph(graph);
        DrawGraph(graph);
    }
}
