#include <iostream>
#include "CampusMap.h"
#include <fstream>  //allows istream/ostream
#include <string>
#include <stdlib.h> //allows atoi
#include <json/json.h>
#include <vector>
#include <sstream>      // std::stringstream, std::stringbuf

using namespace std;

void displayMenu();
void readFileIntoGraph(Graph & g, char* fileName);

int main(int argc, char*argv[])
{
    // Create a graph
    Graph g;
    Graph g2;

    // Read file into graph
    //readFileIntoGraph(g, "zombieCities.txt");
    //readFileIntoGraph(g, "bestPlaces.txt");
    readFileIntoGraph(g, argv[1]);

    // Flag used for exiting menu
    bool quit = false;

    // Used for input
    string inputString1;
    string inputString2;
    int input;

    while(quit != true)
    {
        displayMenu();
        cin >> input;

        //clear out cin
        cin.clear();
        cin.ignore(10000,'\n');

        switch (input)
        {
            // Print Vertices
            case 1:
                g.displayEdges();
                break;
            // Find districts
            case 2:
                g.assignDistricts();
                break;
            // Find shortest path
            case 3:
                cout << "Enter a starting place:" << endl;
                getline(cin,inputString1);
                cout << "Enter an ending place:" << endl;
                getline(cin,inputString2);
                g.shortestPath(inputString1,inputString2);
                break;
            // Find shortest distance
            case 4:
                cout << "Enter a starting place:" << endl;
                getline(cin,inputString1);
                cout << "Enter an ending place:" << endl;
                getline(cin,inputString2);
                g.shortestDistance(inputString1,inputString2);
                break;
            // Extra Credit
            case 5:
                cout << "Enter a starting place:" << endl;
                getline(cin,inputString1);
                g.shortestDistanceRoundTrip(inputString1);
                break;
            // Quit
            case 6:
                readFileIntoGraph(g2, argv[2]);
                g2.displayBus();
                break;
            case 7:
                cout << "Goodbye!" << endl;
                quit = true;
                break;
            // invalid input
            default:
                cout << "Invalid Input" << endl;
                cin.clear();
                cin.ignore(10000,'\n');
                break;
        }
    }

    return 0;
}

/*displays a menu with options to enqueue and dequeue a message and transmit the entire message and quit*/
void displayMenu()
{
    cout << "======Main Menu======" << endl;
    //cout << "1. Find a movie" << endl;
    cout << "1. Show me the buildings" << endl;
    cout << "2. Find districts" << endl;
    cout << "3. Find shortest path" << endl;
    cout << "4. Find shortest distance" << endl;
    cout << "5. Road trip" << endl;
    cout << "6. Show me the bus trip" <<endl;
    cout << "7. Quit" << endl;
    return;
}

/* reads file into graph */
void readFileIntoGraph(Graph & g, char* fileName)
{
    vector<string> cities;
    ifstream in_stream;
    //cout << fileName << endl;
    in_stream.open(fileName);
    if (!in_stream)
    {
        cout << "Could not open file\n";
        return;
    }

    string city;
    string line;
    getline(in_stream,line);
    std::stringstream ss(line);
    int y = 0;

    while (getline(ss,city,','))
    {
        if (city != "buildings")
        {
            g.addVertex(city);
            cities.push_back(city);
        }
    }

    int i = 0;
    string in;
    while (!in_stream.eof())
    {
        i = -1;
        getline(in_stream,line);
        stringstream ss(line);

        while (getline(ss,in,','))
        {
            if (i == -1)
            {
                city = in;
            }
            else
            {
                if (in != "-1" && in != "0")
                {
                    g.addEdge(city,cities[i],atoi(in.c_str()));
                }
            }
            i++;
        }
    }

}

