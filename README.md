# Shi_CSCI2270_FinalProject
Shi_CSCI2270_FinalProject

This project is about building up a map application based on CU Boulder and find the shortest path for student. Also it contains the building info and bustrip info.

Use "g++ *.cpp -std=c++11 -o test" to compiling (I prefer test, you can use the original a.out)

Use "./test CampusMap.txt bustrip.txt buildingdescription.txt" to start

First the campus map would be read from the command line "CampusMap.txt"

User can choose the first three function to build up the map and find the shortest path between buildings.

It also provides a function to add users' own building to the map. And it takes a little time to create cause user have to input the connection information between every two existing buildings, otherwise the code would show the building's name is not found.

For function 5 and 6, it reads the information from "buildingdescription.txt". User can use function6 to display the building info.

For function 7, it reads the information from "bustrip.txt" and provides the bustrip info, if the user wants to take a bus to a building instead of walking.

System	Requirements
Any c++ compiler.

Group	Members
Jiachen Shi

Contributors
Jiachen Shi
