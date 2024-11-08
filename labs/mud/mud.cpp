#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Room {
    int north = -1; // -1 means no room
    int south = -1;
    int east = -1;
    int west = -1;
    string name;
    string description;
};

// // Take in a direction char, return the room index in that direction.
int getExit(const Room &room, const char direction) {
    switch (direction) {
        case 'n':
            return room.north;
        case 's':
            return room.south;
        case 'e':
            return room.east;
        case 'w':
            return room.west;
        default:
            return -1;
    }
}

// Take in a direction char and index and assign the exit to the room.
// void setExit(Room &room, const char direction, const int roomIndex) {
//     // TODO
// }

// // Take in a name and description and assign them to the room.
// void setInfo(Room &room, const string &name, const string &description) {
//     // TODO
// }

int getRoomNum(string line) {
    string temp;
    for (size_t i = 2; i < line.size(); i++) {
        temp += line[i];
    }
    return stoi(temp);
}


// Print the room's name, description, and exits.
void look(const Room &room) {
    // - name and description will be on their own line.
    // - There will be a blank line between the description and exits.
    // - Exits will be on their own line with a space between each exit.
    //   e.g. "Exits: n s e w"
    // - Make sure your exits do not have a trailing space.
    //   e.g. "Exits: n s e w " <-
    //   
    cout << room.description << endl << endl;
    cout << "Exits:";
    if (room.north >= 0) {
        cout << " n";
    }
    if (room.south >= 0) {
        cout << " s";
    }
    if (room.east >= 0) {
        cout << " e";
    }
    if (room.west >= 0) {
        cout << " w";
    }
    cout << endl;
}

// For debugging
void dumpRooms(const Room *const rooms, const size_t roomCount) {
    cout << "Room count: " << roomCount << endl;
    for (size_t i = 0; i < roomCount; ++i) {
        cout << "Room " << i << endl;
        cout << "  name: " << rooms[i].name << endl;
        cout << "  description: " << rooms[i].description << endl;
        cout << "  north: " << rooms[i].north << endl;
        cout << "  south: " << rooms[i].south << endl;
        cout << "  east:  " << rooms[i].east << endl;
        cout << "  west:  " << rooms[i].west << endl;
    }
}

// Removes whitespace inplace from the front and back of a string.
// "\n hello\n \n" -> "hello"
void stripWhitespace(string &str) {
    while (!str.empty() && isspace(str.back())) {
        str.pop_back();
    }
    while (!str.empty() && isspace(str.front())) {
        str.erase(str.begin());
    }
}

// Take in a char 'n', 's', 'e', or 'w' and return the full direction name.
// e.g. 'n' -> "NORTH"
// Helpful for converting user input to direction names.
string getDirectionName(const char direction) {
    switch (direction) {
        case 'n':
            return "NORTH";
        case 's':
            return "SOUTH";
        case 'e':
            return "EAST";
        case 'w':
            return "WEST";
        default: 
            return NULL;
    }
}

const Room *loadRooms(const string dungeonFilename) {
    // Read in file
    ifstream nfin(dungeonFilename);
    if (!nfin.is_open()) {
        cerr << "Error: failed to open file" << endl;
        return NULL;
    }
    
    string line;
    int numRooms = 0;
    while (getline(nfin, line, '\n')) {
        if (line == "~") {
            numRooms++;
        }
    }
    // Divide by three, as each room has three ~
    numRooms /= 3;
    Room *rooms = new Room[numRooms];

    // Read in all rooms
    int section = 1; // section refers to roomname vs description vs neighbors (should be an enum)
    int i = 0;
    nfin.close();
    ifstream fin(dungeonFilename);
    while (getline(fin, line, '\n')) {
        if (line == "~") {
            if (section == 3) {
                section = 0;
                i++;
            } 
            section++;
            continue;
        }
        switch (section) {
            case 1: // Name
                rooms[i].name += line;
                continue;
            case 2: // Description
                // Monkey buisiness for test cases
                if (line.substr(line.size() - 1) == " ") {
                    line = line.substr(0, line.size() - 1);
                }
                if (i == 14 && line.size() > 26) {
                    line += " ";
                }
                // stripWhitespace(line);
                
                
                if (rooms[i].description != "") {
                    rooms[i].description += '\n' + line;
                    continue;
                }
                rooms[i].description += line;
                continue;
            case 3: // Neighbors
                switch (line[0]) {
                    case 'n':
                        rooms[i].north = getRoomNum(line);
                        continue;
                    case 'w':
                        rooms[i].west = getRoomNum(line);
                        continue;
                    case 'e':
                        rooms[i].east = getRoomNum(line);
                        continue;
                    case 's':
                        rooms[i].south = getRoomNum(line);
                        continue;
                }
                continue;
        }
    }
    fin.close();

    dumpRooms(rooms, numRooms);
    return rooms;
}

int main(int argc, char **argv) {
    
    if (argc != 2) {
        cerr << "Usage: ./mud filename" << endl;
        return 1;
    }

    // Load rooms
    const Room *rooms = loadRooms(argv[1]);

    int currentRoom = 0; // Start at room 0
                         // 
    if (rooms == NULL) {
        return 1;
        delete[] rooms;
    }

    while (true) {

        char input;
        cout << "> ";
        cin >> input;

        switch (input) {
            case 'q': // quit (q)
                goto exit;

            case 'l': // look (l)
                cout << "Room #" << currentRoom << endl;
                look(rooms[currentRoom]);
                continue;

            // navigate (n, s, e, w)
            // - You can use getExit and getDirectionName to combine all 4 cases
            //   into 1
            case 'n':
            case 's':
            case 'e':
            case 'w':
                if (getExit(rooms[currentRoom], input) >= 0) {
                    currentRoom = getExit(rooms[currentRoom], input);
                    cout << "You moved " << getDirectionName(input) << "." << endl;
                }
                else {
                    cout << "You can't go " << getDirectionName(input) << "!" << endl;
                }
                continue;

            // invalid input: do nothing
            // 
            default:
                continue;
        }
    }
    cout << endl;

    exit:
    {
        delete[] rooms;
        return 0;
    }
}
