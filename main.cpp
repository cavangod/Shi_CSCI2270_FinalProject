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
void addbuildingdescription(Graph & g,char* fileName);

int main(int argc, char*argv[])
{
    Graph g;
    Graph g2;
    readFileIntoGraph(g, argv[1]);

    bool quit = false;

    string inputString1;
    string inputString2;
    string num;
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
            case 1:
                g.displayEdges();
                break;

            case 2:
                g.assignDistricts();
                break;
            
            case 3:
                cout << "Enter a starting place:" << endl;
                getline(cin,inputString1);
                cout << "Enter an ending place:" << endl;
                getline(cin,inputString2);
                g.shortestPath(inputString1,inputString2);
                break;
            
            case 4:
                cout << "Enter a starting place:" << endl;
                getline(cin,inputString1);
                g.addmyownbuilding(inputString1);
                cout << "Enter an ending place:" << endl;
                getline(cin,inputString2);
                cout << "Enter the distances between these two buildings:" << endl;
                getline(cin,num);
                g.addmyownedge(inputString1,inputString2,atoi(num.c_str()));
                break;

            case 5:
                addbuildingdescription(g,argv[3]);
                break;
            
            case 6:
				g.showmetheinfo();
				break;
            
            case 7:
                readFileIntoGraph(g2, argv[2]);
                g2.displayBus();
                
            case 8:
                cout << "Goodbye!" << endl;
                quit = true;
                break;

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
    cout << "1. Show me the buildings" << endl;
    cout << "2. Find districts" << endl;
    cout << "3. Find shortest path" << endl;
    cout << "4. Add my own building" << endl;
    cout << "5. Add building description" << endl;
    cout << "6. Show me the building description" << endl;
    cout << "7. Show me the bus trip" <<endl;
    cout << "8. Quit" << endl;
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
void addbuildingdescription(Graph & g,char* fileName){
	std::ifstream stream;
    string city;
    string line;
    string in;
    stream.open(fileName);
    if (!stream)
    {
        cout << "Could not open file\n";
        return;
    }
    while (!stream.eof())
    {
        getline(stream,line);
        stringstream ss(line);

        getline(ss,in,',');
        city = in;
        getline(ss,in);
        g.addbuildingdescription(city,in);
    }
}

