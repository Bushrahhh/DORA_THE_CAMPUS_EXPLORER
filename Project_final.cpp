//Comments have been added in the code to increase code clarity at some points
//our "Teammates' part" comments are already added to separate each group members' code just for the sake of understanding for us
//To make the main NOT JUNKED, we created separate function for all parts and then call in main in menu
//At some places, Emojis are used to make it Dora themed more, emojis aren't shown in most older terminals
//they work pretty well in Windows powershell terminal but even if the emojis aren't shown in YOUR TERMINAL
//random ascii characters are shown which also don't look bad.
#include <iostream>
#include <string>
#include<deque>
using namespace std;
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//MASOOOOOMAAA PARTTTT 
//CAMPUS mAP WITH GRAPHS
#define MAX_VERTICES 20
class Graph {
private:
    struct Node {
        string building;
        int weight; // path length
        Node* next;
    };

    Node* adjacencyList[MAX_VERTICES]; 
    string buildings[MAX_VERTICES];    
    int vertexCount;                   

public:
    Graph() {
        vertexCount=0;

        for (int i = 0; i < MAX_VERTICES; i++) {
            adjacencyList[i] = NULL;
        }
    }

    int getBuildingIndex(string building) {
        for (int i = 0; i < vertexCount; i++) {
            if (buildings[i] == building) {
                return i; 
            }
        }
        return -1; // Building not found
    }

    int addBuilding( string building) {
        if (vertexCount < MAX_VERTICES) {
            buildings[vertexCount] = building; 
            return vertexCount++; 
        } else {
            cout << "Graph is full, cannot add more buildings!" << endl;
            return -1;
        }
    }

 
    void addEdge(string source,string destination, int weight) {
        int sourceIndex = getBuildingIndex(source);
        if (sourceIndex == -1) {
            sourceIndex = addBuilding(source);
        }
        

  
        Node* newNode = new Node;
        newNode->building = destination;
        newNode->weight = weight;
        newNode->next = NULL;

  
        newNode->next = adjacencyList[sourceIndex];
        adjacencyList[sourceIndex] = newNode;
    }

    void printGraph() {
        for (int i = 0; i < vertexCount; i++) {
            cout << "Adjacency list for building " << buildings[i] << ": ";
            Node* currentNode = adjacencyList[i];
            while (currentNode != NULL) {
                cout << " (" << currentNode->building << ", Path Length: " << currentNode->weight << ")";
                currentNode = currentNode->next;
            }
            cout << endl;
        }
        cout << endl;
    }
    //-------------------------------------------------------------------------------
//RUMAISA BFS DFS PART
//------------------------------------------------------------------------------
void bfsTraversal(string startBuilding, string destination) {
    int startVertex = getBuildingIndex(startBuilding);
    if (startVertex == -1) {
        cout << "Building \"" << startBuilding << "\" not found in the graph!" << endl;
        return;
    }
    int destinationVertex = getBuildingIndex(destination);
    if (destinationVertex == -1) {
        cout << "Destination building \"" << destination << "\" does not exist." << endl;
        return;
    }

    bool visited[MAX_VERTICES] = {false};
    int parent[MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++) {
        parent[i] = -1;
    }

    deque<int> q;
    visited[startVertex] = true;
    q.push_back(startVertex);

    cout << "BFS Traversal starting from \"" << startBuilding << "\": ";

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop_front();

        cout << buildings[currentVertex] << " ";

        if (currentVertex == destinationVertex) {
            cout << "\nReached the destination building \"" << destination << "\"." << endl;

            deque<string> path;
            int temp = destinationVertex;
            while (temp != -1) {
                path.push_front(buildings[temp]);
                temp = parent[temp];
            }

            cout << "Shortest Path: ";
            for (const string& building : path) {
                cout << building << " ";
            }
            cout << endl;
            return;
        }

        Node* currentNode = adjacencyList[currentVertex];
        while (currentNode != NULL) {
            int neighborVertex = getBuildingIndex(currentNode->building);
            if (neighborVertex == -1 || neighborVertex >= MAX_VERTICES) {
                cout << "Invalid neighbor vertex: " << currentNode->building << endl;
                currentNode = currentNode->next;
                continue;
            }

            if (!visited[neighborVertex]) {
                visited[neighborVertex] = true;
                parent[neighborVertex] = currentVertex;
                q.push_back(neighborVertex);
            }

            currentNode = currentNode->next;
        }
    }

    cout << "\nDestination \"" << destination << "\" not reachable from \"" << startBuilding << "\"." << endl;
}


void dfsHelper(int vertex, bool visited[], int destinationVertex, int parent[]) {
    visited[vertex] = true;
    if (vertex == destinationVertex) {
        cout << "You have reached your destination \"" << buildings[destinationVertex] << "\"." << endl;
        return;
    }
    Node* currentNode = adjacencyList[vertex];
    while (currentNode != NULL) {
        int neighborVertex = getBuildingIndex(currentNode->building);
        if (!visited[neighborVertex]) {
            parent[neighborVertex] = vertex;
            dfsHelper(neighborVertex, visited, destinationVertex, parent);
        if (visited[destinationVertex]) return;
        }

        currentNode = currentNode->next;
    }
}

void dfsTraversal(string startBuilding, string destination) {
    int startVertex = getBuildingIndex(startBuilding);
    int destinationVertex = getBuildingIndex(destination);
    if (startVertex == -1) {
        cout << "Building \"" << startBuilding << "\" not found in the graph!" << endl;
        return;
    }
    if (destinationVertex == -1) {
        cout << "Building \"" << destination << "\" not found in the graph!" << endl;
        return;
    }
    bool visited[MAX_VERTICES] = {false};
    int parent[MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++) {
        parent[i] = -1;
    }

    cout << "DFS Traversal starting from \"" << startBuilding << "\": ";
    dfsHelper(startVertex, visited, destinationVertex, parent);
    if (visited[destinationVertex]) {
        cout << "Shortest Path: ";
        deque<string> path;
        int temp = destinationVertex;
        while (temp != -1) {
            path.push_front(buildings[temp]);
            temp = parent[temp];
        }
        for (const string& building : path) {
            cout << building;
            if (building != destination) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "Destination \"" << destination << "\" is not reachable from \"" << startBuilding << "\"." << endl;
    }

    cout << endl;
}
};
//-----------------------------------------------------------------------
//----------------------------------------------------------------------
//BUSHRAHHHH TREE PARTTT EHHHHHHH
//I created a FOREST where each building is a tree
//each building has child nodes as floors (which are levels as well), classes and lecture halls
struct BuildingNode {
    string name;           
    string description;     
    string location;        

    BuildingNode* left;     //like left on same floor wala
    BuildingNode* right;    //right node on same floor

    // Constructor
    BuildingNode(string n, string desc, string loc = "")
        : name(n), description(desc), location(loc), left(nullptr), right(nullptr) {}
};

//this function is goonna add child to the current node
BuildingNode* addChild(BuildingNode* parent, string name, string description, string location) {
    BuildingNode* child = new BuildingNode(name, description, location);
    if (!parent->left) {
        parent->left = child; // Add as first childdd
    } else {
        BuildingNode* sibling = parent->left;
        while (sibling->right) {
            sibling = sibling->right; // Traverse to the lasttt sibling
        }
        sibling->right = child; // Add as the next sibling
    }
    return child;
}

// Function to display the tree hierarchy for a building
void displayBuildingTree(BuildingNode* root, int level = 0) {
    if (!root) return;

    // Indentation for hierarchy levels
    for (int i = 0; i < level; i++) cout << "  ";
    cout << "- " << root->name << " (" << root->location << "): " << root->description << endl;

    // Recursively display child nodes
    if (root->left) {
        displayBuildingTree(root->left, level + 1); // Display child sections
    }

    // Display sibling nodes
    if (root->right) {
        displayBuildingTree(root->right, level); // Display siblings at the same level
    }
}

// Function to create the Auditorium tree
BuildingNode* createAuditoriumTree() {

    // Root node for the Auditorium
    BuildingNode* auditorium = new BuildingNode(
        "Agha Hasan Abedi AHA Auditorium",
        "The heart of university events, seminars, and celebrations. 🎤 It's where all the magic happens!",
        "First Floor"
    );

    // Ground Floor: GIKafe and Bathrooms
    BuildingNode* gikafe = addChild(auditorium, 
        "GIKafe", 
        "The ultimate chill zone serving snacks, meals, and GIKI’s famous chai ☕. A crowd favorite!", 
        "Ground Floor"
    );

    addChild(gikafe, 
        "Left-Side Bathroom", 
        "Quick stop for explorers on the go 🚻. Located left of GIKafe.", 
        "Ground Floor"
    );

    addChild(gikafe, 
        "Right-Side Bathroom", 
        "Mirror image of the left bathroom – same vibes, opposite direction 🚻.", 
        "Ground Floor"
    );

    cout << "🌟 GRAND AUDITORIUM TREE LOADED: Ready for exploration! 🌟\n";
    return auditorium;
}


// Function to create the Faculty of Mechanical Engineering (FME) tree
BuildingNode* createFMETree() {

    // Root node for FME
    BuildingNode* fme = new BuildingNode(
        "Faculty of Mechanical Engineering (FME)",
        "The hub of innovation, mechanical labs, and academic brilliance.",
        "Ground Floor"
    );

    // Ground Floor: Left Wing
    BuildingNode* fmeLeft = addChild(fme, 
        "Left Wing", 
        "Faculty offices and mechanical labs where concepts turn into reality.", 
        "Ground Floor"
    );

    addChild(fmeLeft, 
        "Faculty Offices Corridor", 
        "A corridor of faculty offices where academic discussions take shape.", 
        "Ground Floor"
    );

    addChild(fmeLeft, 
        "Mechanical Labs", 
        "Labs equipped with tools and engines to bring mechanical ideas to life.", 
        "Ground Floor"
    );

    // Ground Floor: Right Wing
    BuildingNode* fmeRight = addChild(fme, 
        "Right Wing", 
        "More labs and an FME cafe for students to recharge.", 
        "Ground Floor"
    );

    addChild(fmeRight, 
        "Mechanical Labs", 
        "Parallel labs with advanced tools for practical learning.", 
        "Ground Floor"
    );

    addChild(fmeRight, 
        "FME Cafe", 
        "A student-friendly space to relax and recharge with food and drinks.", 
        "Ground Floor"
    );

    // First Floor: Left Wing
    BuildingNode* firstFloorLeft = addChild(fmeLeft, 
        "Left Wing - First Floor", 
        "Lecture halls for learning fundamental and advanced mechanical concepts.", 
        "First Floor"
    );

    addChild(firstFloorLeft, 
        "Lecture Hall 1", 
        "Lecture space for introductory mechanical engineering courses.", 
        "First Floor"
    );

    addChild(firstFloorLeft, 
        "Lecture Hall 2", 
        "Another hall similar to Lecture Hall 1 for advanced classes.", 
        "First Floor"
    );

    // First Floor: Right Wing
    BuildingNode* firstFloorRight = addChild(fmeRight, 
        "Right Wing - First Floor", 
        "Main lecture hall for larger mechanical engineering classes.", 
        "First Floor"
    );

    addChild(firstFloorRight, 
        "Main Lecture Hall (MLH)", 
        "A large lecture hall designed for seminars and important academic sessions.", 
        "First Floor"
    );

    // Second Floor: Labs and Lecture Halls
    BuildingNode* secondFloor = addChild(fme, 
        "Second Floor", 
        "Specialized labs and additional lecture halls for advanced students.", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "FME Labs", 
        "Advanced laboratories for mechanical engineering research and experiments.", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "Automation Labs", 
        "Dedicated labs for automation, robotics, and mechanical programming.", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "Lecture Hall 3", 
        "A well-equipped lecture hall for focused academic discussions.", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "Lecture Hall 4", 
        "Quiet and organized lecture hall designed for advanced topics.", 
        "Second Floor"
    );

    cout << "\nExplore the Faculty of Mechanical Engineering (FME) – where theory meets practice and ideas take shape.\n";
    return fme;
}
// Function to create the Faculty of Computer Science and Electrical Engineering (FCSE) tree
BuildingNode* createFCSETree() {
    // Root node for FCSE
    BuildingNode* fcse = new BuildingNode(
        "FCSE - The Brainy Tech Hub",
        "Where code runs, circuits connect, and innovation thrives. Future tech leaders and engineers start here.",
        "Ground Floor"
    );

    // Ground Floor: Left Portion - Computer Science
    BuildingNode* fcseLeft = addChild(fcse, 
        "The LEFT WING - CODE HAVEN", 
        "Home of the Computer Science legends – offices, labs, and all things code. 💻", 
        "Ground Floor"
    );

    addChild(fcseLeft, 
        "CS Faculty Corridor", 
        "The brain trust of coders – where professors live, breathe, and debug life. 🧑‍💻📝", 
        "Ground Floor"
    );

    // Ground Floor: Right Portion - Electrical Engineering
    BuildingNode* fcseRight = addChild(fcse, 
        "The RIGHT WING - CIRCUIT ZONE", 
        "Electrical Engineering side – wizards with wires, tools, and pure energy ⚡.", 
        "Ground Floor"
    );

    addChild(fcseRight, 
        "EE Faculty Corridor", 
        "Faculty offices for Electrical Engineering – where equations turn into sparks. 🔌📐", 
        "Ground Floor"
    );

    addChild(fcseRight, 
        "EE Labs", 
        "Hands-on labs for circuits, robotics, and everything that GLOWS. ⚙️🔋", 
        "Ground Floor"
    );

    // First Floor: Left Portion - Computer Science
    BuildingNode* firstFloorLeft = addChild(fcseLeft, 
        "CS LECTURE HALLS - FIRST FLOOR", 
        "Where code warriors gather to learn the art of programming. 🎓💻", 
        "First Floor"
    );

    addChild(firstFloorLeft, 
        "Lecture Hall 1", 
        "Lecture hall on the left side – where Python, Java, and algorithms take flight. 🐍📊", 
        "First Floor"
    );

    addChild(firstFloorLeft, 
        "Lecture Hall 2", 
        "Another coding arena – packed with laptops, notebooks, and buzzing brains. 🧠💻", 
        "First Floor"
    );

    // First Floor: Right Portion - Electrical Engineering
    BuildingNode* firstFloorRight = addChild(fcseRight, 
        "EE MAIN LECTURE HALL", 
        "The BIG HALL where circuits meet theory. Come prepared to SPARK your brain. ⚡📚", 
        "First Floor"
    );

    addChild(firstFloorRight, 
        "Main Lecture Hall (MLH)", 
        "THE spot for Electrical Engineering – where calculations and diagrams rule. 📝🔋", 
        "First Floor"
    );

    // Second Floor: Labs and Lecture Halls
    BuildingNode* secondFloor = addChild(fcse, 
        "SECOND FLOOR - INNOVATION ZONE", 
        "Software labs, shared spaces, and lecture halls – a floor for FUTURE LEADERS. 🌐💡", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "FCSE Labs", 
        "Shared with ELECTRICAL Engineering – collaboration at its finest. 🛠️⚙️", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "Software Labs", 
        "The coding dojo. Workstations ready for projects, algorithms, and late-night bugs. 👨‍💻🔍", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "Lecture Hall 3", 
        "Lecture hall for focused learners and caffeine-driven dreamers. ☕📖", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "Lecture Hall 4", 
        "One last stop – where future tech meets curious minds. 🎓🔧", 
        "Second Floor"
    );

    cout << "\n⚡💻 THE FCSE TREE IS BUILT – READY TO CODE, CONNECT, AND INNOVATE! ⚡💻\n";
    return fcse;
}
// Function to create the Faculty of Engineering Sciences (FES) tree
BuildingNode* createFESTree() {
    // Root node for FES
    BuildingNode* fes = new BuildingNode(
        "FES - The Science Hub",
        "The epicenter of innovation, experiments, and engineering brilliance. 🧪⚙️",
        "Ground Floor"
    );

    // Ground Floor: Left Portion
    BuildingNode* fesLeft = addChild(fes, 
        "The LEFT WING - SCIENCE SANCTUARY", 
        "Faculty offices corridor – home of the science masterminds. 🧑‍🔬🔍", 
        "Ground Floor"
    );

    addChild(fesLeft, 
        "Faculty Offices Corridor (Left)", 
        "Where professors brainstorm, grade papers, and craft the next big lecture. 📚🧠", 
        "Ground Floor"
    );

    // Ground Floor: Right Portion
    BuildingNode* fesRight = addChild(fes, 
        "The RIGHT WING - SCIENCE HQ", 
        "More faculty offices – the heartbeat of FES knowledge. 💡📝", 
        "Ground Floor"
    );

    addChild(fesRight, 
        "Faculty Offices Corridor (Right)", 
        "Additional offices for faculty – quiet but loaded with science vibes. 📊", 
        "Ground Floor"
    );

    // First Floor: Left Portion
    BuildingNode* firstFloorLeft = addChild(fesLeft, 
        "FIRST FLOOR LEFT - LECTURE ZONE", 
        "The hall of theories – lecture halls for next-gen scientists. 📝🔭", 
        "First Floor"
    );

    addChild(firstFloorLeft, 
        "Lecture Hall 1", 
        "Where science enthusiasts take notes and scribble equations. ✍️🧪", 
        "First Floor"
    );

    addChild(firstFloorLeft, 
        "Lecture Hall 2", 
        "Another hall of knowledge – whiteboards FULL of formulas. 🔎📐", 
        "First Floor"
    );

    // First Floor: Right Portion
    BuildingNode* firstFloorRight = addChild(fesRight, 
        "FIRST FLOOR RIGHT - MLH", 
        "The **Main Lecture Hall** – the BIG stage of knowledge-sharing. 🎓🔊", 
        "First Floor"
    );

    addChild(firstFloorRight, 
        "Main Lecture Hall (MLH)", 
        "The GRAND hall for large classes, guest lectures, and major brain upgrades. 🧠🎤", 
        "First Floor"
    );

    // Second Floor: Labs and Lecture Halls
    BuildingNode* secondFloor = addChild(fes, 
        "SECOND FLOOR - THE INNOVATION DECK", 
        "Labs, PCs, and more lecture halls – a place for serious SCIENCE ACTION. 💻🔬", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "FES Labs", 
        "Where science experiments are born – Bunsen burners, test tubes, and all things STEM. 🔥🧪", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "PC Labs", 
        "State-of-the-art computer labs ready for coding, projects, and research. 💻📊", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "Lecture Hall 3", 
        "Focus mode ON – equations, projects, and quiet concentration. 📏✏️", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "Lecture Hall 4", 
        "Final stop for knowledge seekers – theories, notes, and caffeine-fueled genius. ☕🎓", 
        "Second Floor"
    );

    cout << "\n🧪⚙️ THE FES TREE IS BUILT – SCIENCE IS HAPPENING, KNOWLEDGE IS FLOWING, AND MINDS ARE GLOWING! ⚙️🧪\n";
    return fes;
}
// Function to create the New Academic Block (ACB) tree
BuildingNode* createACBTree() {
    // Root node for ACB
    BuildingNode* acb = new BuildingNode(
        "ACB - THE INNOVATION BLOCK",
        "Home to labs, lecture halls, and offices for departments shaping the FUTURE. 🌐🔬",
        "Ground Floor"
    );

    // Ground Floor: Left Portion
    BuildingNode* acbLeftGround = addChild(acb, 
        "GROUND FLOOR LEFT WING", 
        "Where students GRIND in labs and classrooms. 💻⚙️", 
        "Ground Floor"
    );

    addChild(acbLeftGround, 
        "ACB Cafe", 
        "The fuel station for brains – coffee, chai, and quick bites to keep the hustle alive. ☕🥪", 
        "Ground Floor"
    );

    addChild(acbLeftGround, 
        "Cyber Lab", 
        "Where cybersecurity ninjas learn to outsmart hackers. Digital vault vibes. 🔐💻", 
        "Ground Floor"
    );

    addChild(acbLeftGround, 
        "Civil Lab", 
        "Engineers test the strength of buildings and bridges here. Concrete dreams! 🏗️🛠️", 
        "Ground Floor"
    );

    // Ground Floor: Right Portion
    BuildingNode* acbRightGround = addChild(acb, 
        "GROUND FLOOR RIGHT WING", 
        "Main Lecture Hall and the BIG brains – the staff offices. 🎤📚", 
        "Ground Floor"
    );

    addChild(acbRightGround, 
        "Main Lecture Hall (MLH)", 
        "The spotlight is ON. Major classes, guest lectures, and brain fuel drops happen here. 🎓🎙️", 
        "Ground Floor"
    );

    addChild(acbRightGround, 
        "Staff Offices (Ground Floor)", 
        "Where the professors brainstorm, plan, and grade (tough luck). 📑💡", 
        "Ground Floor"
    );

    // First Floor: Civil Engineering
    BuildingNode* firstFloor = addChild(acb, 
        "FIRST FLOOR - CIVIL HAVEN", 
        "Dedicated to Civil Engineering: labs, offices, and minds building the future. 🏗️📐", 
        "First Floor"
    );

    addChild(firstFloor, 
        "Civil Engineering Offices", 
        "Home base for Civil Engineering faculty – blueprints, hard hats, and all. 🛠️📝", 
        "First Floor"
    );

    addChild(firstFloor, 
        "AI Lab", 
        "Where machines get smarter and algorithms run wild. Code the future here! 🤖💻", 
        "First Floor"
    );

    // Second Floor: AI Focus
    BuildingNode* secondFloor = addChild(acb, 
        "SECOND FLOOR - AI ZONE", 
        "The hub of Artificial Intelligence – offices, labs, and data magic. 🌐🤖", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "AI Offices", 
        "The masterminds behind AI breakthroughs – where theory meets code. 🧠👩‍💻", 
        "Second Floor"
    );

    addChild(secondFloor, 
        "Data Analytics Lab", 
        "Data everywhere – graphs, trends, and predictive genius. Numbers tell stories here. 📊📈", 
        "Second Floor"
    );

    // Third Floor: Chemical Engineering
    BuildingNode* thirdFloor = addChild(acb, 
        "THIRD FLOOR - CHEMICAL ZONE", 
        "Dedicated to the Chemical Engineering department. 🧪🔬", 
        "Third Floor"
    );

    addChild(thirdFloor, 
        "Chemical Engineering Offices", 
        "Where experiments are designed, and solutions are cooked up. Bunsen burners forever! 🔥🧪", 
        "Third Floor"
    );

    cout << "\n✨ THE ACB TREE IS READY: LABS LOADED, CLASSES SET, AND BRAINS ACTIVATED! LET’S GOOO! 🚀✨\n";
    return acb;
}
// Function to create the Faculty of Management Sciences (Brabers) tree
BuildingNode* createBrabersTree() {
    // Root node for Brabers
    BuildingNode* brabers = new BuildingNode(
        "Brabers - The Blue Management Hub",
        "The iconic blue building of the Faculty of Management Sciences, located next to the library. 💼🔵",
        "Ground Floor"
    );

    // Main Entrance leading to faculty offices
    BuildingNode* mainEntrance = addChild(brabers, 
        "MAIN ENTRANCE - KNOWLEDGE PORTAL", 
        "Step in and you’ll find faculty offices bustling with strategies, meetings, and notes. 🗂️📚", 
        "Ground Floor"
    );

    addChild(mainEntrance, 
        "Faculty Offices", 
        "Home base for Management Sciences professors – planners, strategists, and grade-givers. 📊✏️", 
        "Ground Floor"
    );

    // Exam Halls on both sides
    BuildingNode* examHalls = addChild(brabers, 
        "EXAM ZONE - BATTLE ARENA", 
        "Exam halls on BOTH SIDES. The ultimate battleground for sleepy students with pens. 📝😴", 
        "Ground Floor"
    );

    addChild(examHalls, 
        "Left Exam Hall", 
        "Silent… until someone drops their calculator. Left-side exam hall for big challenges. 🧠📖", 
        "Ground Floor"
    );

    addChild(examHalls, 
        "Right Exam Hall", 
        "Identical to the left, but the vibes? Slightly better. Maybe. 🎓🖊️", 
        "Ground Floor"
    );

    // Conference Hall
    addChild(brabers, 
        "CONFERENCE HALL - THE THINK TANK", 
        "Meetings, seminars, and presentations happen here. Ideas turn into projects. 💼🗣️", 
        "Ground Floor"
    );

    // Emergency Exits on both sides
    BuildingNode* emergencyExits = addChild(brabers, 
        "EMERGENCY EXITS - ESCAPE ROUTES", 
        "Safety first! Exits on BOTH SIDES – because smart managers always plan ahead. 🛑🚪", 
        "Ground Floor"
    );

    addChild(emergencyExits, 
        "Left Emergency Exit", 
        "Quick getaway for left-wing explorers. Safety vibes only. 🚶‍♂️🛑", 
        "Ground Floor"
    );

    addChild(emergencyExits, 
        "Right Emergency Exit", 
        "Mirror exit – fast escape for right-wing champions. 🏃‍♀️🚪", 
        "Ground Floor"
    );

    cout << "\n💼 THE BRABERS TREE IS READY: OFFICES CHECKED, HALLS CLEARED, AND EXITS TESTED. STRATEGY MODE: ON! 💼🔵\n";
    return brabers;
}// Function to create the GIKI Clock Tower tree
BuildingNode* createClockTowerTree() {
    // Root node for the GIKI Clock Tower
    BuildingNode* clockTower = new BuildingNode(
        "GIKI Clock Tower",
        "Standing tall next to the main gate – a timeless symbol of GIKI’s greatness and innovation. 🕰️✨",
        "Ground Floor"
    );

    // Symbolic Feature
    addChild(clockTower, 
        "Symbolic Feature", 
        "More than just a tower – it represents academic excellence, innovation, and the spirit of GIKI. 🧠🏆", 
        "Ground Floor"
    );

    // Historical Significance
    addChild(clockTower, 
        "Historical Significance", 
        "A legendary landmark cherished by alumni and students alike – stories and memories live here. 📸🎓", 
        "Ground Floor"
    );

    // Viewpoint Feature
    addChild(clockTower, 
        "The Selfie Spot", 
        "THE place for a perfect photo-op. Snap it, share it, and let the world know you made it here. ", 
        "Ground Floor"
    );

    // Legacy Stone
    addChild(clockTower, 
        "The Legacy Stone", 
        "A plaque etched with GIKI’s milestones – a tribute to its journey and achievements. ", 
        "Ground Floor"
    );

    cout << "\n THE CLOCK TOWER TREE IS BUILT – A LANDMARK OF MEMORIES, SYMBOLISM, AND LEGACY! \n";
    return clockTower;
}


// Function to create the Guest House tree
BuildingNode* createGuestHouseTree() {
    // Root node for the Guest House
    BuildingNode* guestHouse = new BuildingNode(
        "GIKI Guest House",
        "A cozy haven near the Clock Tower – perfect for visitors to unwind, relax, and enjoy their stay. ",
        "Ground Floor"
    );

    // Living Room
    addChild(guestHouse, 
        "The Living Room", 
        "The heart of the Guest House – comfy sofas, warm vibes, and quiet corners to chill. ", 
        "Ground Floor"
    );

    // Guest Rooms
    addChild(guestHouse, 
        "Guest Rooms", 
        "Rooms for guests to stay comfortably. Soft beds, fresh linen, and peaceful nights guaranteed. ", 
        "Ground Floor"
    );

    // Courtyard Feature
    addChild(guestHouse, 
        "The Courtyard", 
        "A peaceful outdoor space with fresh air and greenery – the ultimate spot for a morning coffee. ", 
        "Ground Floor"
    );

    // Dining Area
    addChild(guestHouse, 
        "Dining Area", 
        "Where meals are served fresh and vibes are as warm as the food. ", 
        "Ground Floor"
    );

    cout << "\n THE GUEST HOUSE TREE IS READY: COZY VIBES, RELAXED SPACES, AND PEACEFUL STAYS GUARANTEED! \n";
    return guestHouse;
}


// Function to create the TUC Area tree
BuildingNode* createTUCTree() {
    // Root node for TUC Area
    BuildingNode* tuc = new BuildingNode(
        "TUC Area",
        "The bustling center of GIKI – home to shops, eateries, and everything you need to keep life rolling. ",
        "Ground Floor"
    );

    // Shops Section
    BuildingNode* shops = addChild(tuc, 
        "Shops - THE ESSENTIALS HUB", 
        "From groceries to grooming, these shops have you covered. ", 
        "Ground Floor"
    );

    addChild(shops, 
        "PCO Shop", 
        "The go-to spot for calls, photocopies, and getting that last-minute printout done. ", 
        "Ground Floor"
    );

    addChild(shops, 
        "Barber's Shop", 
        "Fresh cuts and sharp looks – the barber’s here to keep you stylish. ", 
        "Ground Floor"
    );

    addChild(shops, 
        "Grocery Store 1", 
        "The ultimate grocery stop for snacks, essentials, and late-night cravings. ", 
        "Ground Floor"
    );

    addChild(shops, 
        "Grocery Store 2 (Asrarbucks)", 
        "Chai and coffee that rivals Starbucks – the legend of TUC. ", 
        "Ground Floor"
    );

    addChild(shops, 
        "Fruit Shop", 
        "Fresh fruits to fuel your day – from bananas to oranges, it’s all here. ", 
        "Ground Floor"
    );

    addChild(shops, 
        "Laundry Shop", 
        "Get your clothes fresh and clean – laundry made easy. ", 
        "Ground Floor"
    );

    // Restaurants Section
    BuildingNode* restaurants = addChild(tuc, 
        "Restaurants - FOOD HEAVEN", 
        "Cravings? Sorted. These spots serve up the best food on campus. ", 
        "Ground Floor"
    );

    addChild(restaurants, 
        "Raju", 
        "Local favorite known for serving hearty meals that hit the spot. ", 
        "Ground Floor"
    );

    addChild(restaurants, 
        "Hot N Spicy", 
        "A must-visit for spicy food lovers – bold flavors, big vibes. ", 
        "Ground Floor"
    );

    addChild(restaurants, 
        "Ayan Gardens", 
        "Relax, eat, and vibe at this chill spot with great ambiance and even better food. ", 
        "Ground Floor"
    );

    cout << "\n THE TUC TREE IS READY: SNACKS STOCKED, SHOPS LOADED, AND VIBES CHECKED. LET’S GO EXPLORE! \n";
    return tuc;
}
// Function to create the Girls Hostels tree
BuildingNode* createGirlsHostelsTree() {
    // Root node for Girls Hostels
    BuildingNode* girlsHostels = new BuildingNode(
        "Girls Hostels",
        "A welcoming and secure space for female students, complete with all the essentials for a vibrant campus life. ",
        "Ground Floor"
    );

    // Ground Floor
    BuildingNode* groundFloor = addChild(girlsHostels, 
        "GROUND FLOOR - THE COMMUNITY HUB", 
        "The heart of the hostels – dining, cooking, and connecting happen here. ", 
        "Ground Floor"
    );

    addChild(groundFloor, 
        "Mess Hall", 
        "The dining hall where food meets friendship – grab a plate and share stories! ", 
        "Ground Floor"
    );

    addChild(groundFloor, 
        "Kitchen", 
        "Where meals are crafted with love (and a sprinkle of midnight snacks). ", 
        "Ground Floor"
    );

    addChild(groundFloor, 
        "Staff Room", 
        "The HQ for the hostel staff – always ready to assist and keep things running smoothly. ", 
        "Ground Floor"
    );

    addChild(groundFloor, 
        "Warden's Room", 
        "The warden’s base – ensuring safety, guidance, and that no one skips curfew.", 
        "Ground Floor"
    );

    // Upper Floors
    addChild(girlsHostels, 
        "Student Rooms", 
        "Cozy rooms filled with dreams, study sessions, and late-night gossip. ", 
        "First, Second, and Third Floors"
    );

    cout << "\n THE GIRLS HOSTELS TREE IS READY: SAFE, COZY, AND BUILT FOR BRILLIANT STUDENTS! \n";
    return girlsHostels;
}

// Function to display the main menu and handle user selection
void handleSelection(BuildingNode* auditorium, BuildingNode* fme, BuildingNode* fcse, BuildingNode* fes, BuildingNode* acb, BuildingNode* brabers, BuildingNode* clockTower, BuildingNode* guestHouse, BuildingNode* tuc, BuildingNode* girlsHostels) {
     cout << "\n";
    cout << "=============================================\n";
    cout << " WELCOME TO THE GIKI ADVENTURE         \n";
    cout << "          LET'S EXPLORE TOGETHER!            \n";
    cout << "=============================================\n";
    cout << " Hola, Dora here! Ready to explore? \n";
    cout << "Grab your MAP and let's find the fastest way to explore GIKI! \n";
    cout << "Together, we'll navigate buildings, find shortcuts, and uncover exciting events! \n";
    cout << "Ready? Vamonos! Let’s GO! \n";


    while (true) {
        cout << "\nCHOOSE YOUR NEXT DESTINATION:\n";
        cout << "--------------------------------------------\n";
        cout << "   [1]  GRAND AUDITORIUM        - EVENTS CENTRAL\n";
        cout << "   [2]  MECHANICAL ENGINEERING  - GEARS & LABS\n";
        cout << "   [3]  CS & ELECTRICAL ENG.    - CODE N' CIRCUITS\n";
        cout << "   [4]  ENGINEERING SCIENCES    - SCIENCE CITY\n";
        cout << "   [5]  ACADEMIC BLOCK (ACB)    - FLOORS OF WONDERS\n";
        cout << "   [6]  BRABERS (MANAGEMENT)    - MANAGEMENT HUB\n";
        cout << "   [7]  GIKI CLOCK TOWER        - SYMBOL OF GREATNESS\n";
        cout << "   [8]  GUEST HOUSE             - REST 'N CHILL SPOT\n";
        cout << "   [9]  TUC AREA                - SNACKS & VIBES\n";
        cout << "   [10] GIRLS HOSTELS           - SAFE HAVEN\n";
        cout << "   [11] EXIT                    - BACK TO REALITY\n";
        cout << "--------------------------------------------\n";
        cout << "WHERE TO NEXT, DORA? ENTER YOUR CHOICE >> ";

        int choice;
        cin >> choice;
        cin.ignore(); // Ignore leftover newline

        cout << "\n=============================================\n";

        switch (choice) {
            case 1:
                cout << " STEPPING INTO THE **GRAND AUDITORIUM** \n";
                cout << "WHERE EVENTS TURN INTO MEMORIES. TAKE A LOOK AROUND!\n";
                displayBuildingTree(auditorium);
                break;
            case 2:
                cout << " WELCOME TO **MECHANICAL ENGINEERING** \n";
                cout << "THE REALM OF GEARS, LABS, AND FUTURE INNOVATORS.\n";
                displayBuildingTree(fme);
                break;
            case 3:
                cout << " ENTERING **CS & ELECTRICAL ENGINEERING** \n";
                cout << "CODES, CIRCUITS, AND ALL THE MAGIC BEHIND TECHNOLOGY.\n";
                displayBuildingTree(fcse);
                break;
            case 4:
                cout << " YOU'RE IN **ENGINEERING SCIENCES** \n";
                cout << "WHERE SCIENCE MEETS ENGINEERING – EXPLORE EVERYTHING!\n";
                displayBuildingTree(fes);
                break;
            case 5:
                cout << " TOURING THE **NEW ACADEMIC BLOCK (ACB)** \n";
                cout << "A BLOCK OF WONDERS, FLOORS FULL OF POSSIBILITIES!\n";
                displayBuildingTree(acb);
                break;
            case 6:
                cout << " VISITING **BRABERS - MANAGEMENT HUB** \n";
                cout << "OFFICES, EXAM HALLS, AND ALL THINGS BUSINESS.\n";
                displayBuildingTree(brabers);
                break;
            case 7:
                cout << " ADMIRING THE ICONIC **GIKI CLOCK TOWER** \n";
                cout << "A SYMBOL OF EXCELLENCE AND GREATNESS – STAND IN AWE.\n";
                displayBuildingTree(clockTower);
                break;
            case 8:
                cout << " RESTING UP AT THE **GUEST HOUSE** \n";
                cout << "COOL VIBES, COZY SPOTS, AND A PLACE TO RELAX.\n";
                displayBuildingTree(guestHouse);
                break;
            case 9:
                cout << " CHILLING AT THE **TUC AREA** \n";
                cout << "SNACKS, SHOPS, AND ALL THE CAMPUS VIBES YOU NEED.\n";
                displayBuildingTree(tuc);
                break;
            case 10:
                cout << " STEPPING INTO THE **GIRLS HOSTELS** \n";
                cout << "SAFE HAVEN FOR STUDENTS – HOME AWAY FROM HOME.\n";
                displayBuildingTree(girlsHostels);
                break;
            case 11:
                cout << " WRAPPING UP THE GIKI ADVENTURE, DORA! \n";
                cout << "TIME TO CLOSE THE MAP AND HEAD BACK TO REALITY.\n";
                cout << "THANKS FOR EXPLORING GIKI WITH ME! SEE YOU NEXT TIME! \n";
                return;
            default:
                cout << "UH-OH! THAT’S NOT ON THE MAP, DORA. TRY AGAIN. 💻\n";
        }

        cout << "=============================================\n";
    }
}
//I used linked list implementation of queues to handle campus notifications
///a student can also create a notification just like "lost and found" in giki
//Events scheduled will also be shown
//-----------------------------------------------------------------------------------
//BUSHRAH QUEUE PART EHHHHHHHHH
//-----------------------------------------------------------------------------------
//QUEUE PART IS FOR CAMPUS NOTIFICATIONS AND CAMPUS CAMPUS EVENTS
struct Node {
    string data;
    Node* next;

    Node(string value) : data(value), next(nullptr) {}
};
class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}
    void enqueue(string value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    void dequeue() {
        if (front == nullptr) {
            cout << "⚠️ The queue is empty! Nothing to dequeue.\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        cout << "✅ Processed the next item in the queue.\n";
    }
    bool isEmpty() const {
        return front == nullptr;
    }
    void display() const {
        if (isEmpty()) {
            cout << "⚠️ The queue is empty! No notifications or events to display.\n";
            return;
        }
        Node* temp = front;
        int count = 1;
        while (temp != nullptr) {
            cout << count++ << ". " << temp->data << endl;
            temp = temp->next;
        }
    }
};

// Function to manage campus notifications
void campusNotifications(Queue& notifications) {
    int choice;
    do {
        cout << "\n📢 CAMPUS NOTIFICATIONS:\n";
        cout << "1. View Notifications 👀\n";
        cout << "2. Add a Notification (Admin) ✍️\n";
        cout << "3. Go Back 🔙\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore trailing newline

        switch (choice) {
            case 1:
                cout << "\n📜 Current Notifications:\n";
                notifications.display();
                break;
            case 2: {
                string newNotification;
                cout << "Enter the notification: ";
                getline(cin, newNotification);
                notifications.enqueue(newNotification);
                cout << "✅ Notification added successfully!\n";
                break;
            }
            case 3:
                cout << "🔙 Going back to the main menu...\n";
                break;
            default:
                cout << "❌ Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

// Function to manage campus events
void campusEvents(Queue& events) {
    cout << "\n🎉 UPCOMING EVENTS:\n";
    if (events.isEmpty()) {
        cout << "⚠️ No upcoming events at the moment. Check back later! 🗓️\n";
    } else {
        events.display();
    }
    cout << "✨ Enjoy exploring these amazing events, Explorer Dora! 🚀\n";
}
// Main function for campus management
void campusManagement() {
    Queue notifications; // Queue for notifications
    Queue events;        // Queue for events
    cout << "\n🎒 LET'S LOAD UP OUR EVENT BACKPACK, EXPLORER DORA! 🎒\n";
    events.enqueue("🌟 FME Workshop at 10 AM - Let’s learn how gears and machines work!");
    events.enqueue("🤖 AI Seminar at 2 PM in FCSE - Meet the robots and algorithms shaping the future!");
    events.enqueue("🎭 Cultural Fest in the Auditorium at 6 PM - Dance, music, and fun all in one place!");
    events.enqueue("🛠️ PC Lab Maintenance - Closed for the Day - Time to rest those keyboards!");
    events.enqueue("✨ Automation Lab Showcase at 11 AM - Discover robots that build the future!");

    cout << "🎉 EVENTS ARE READY! Time to explore and manage campus like a pro! 🚀\n";

    int choice;
    do {
        cout << "\n🗺️ DORA'S CAMPUS MANAGEMENT SYSTEM 🗺️\n";
        cout << "1. Manage Campus Notifications 📢\n";
        cout << "2. View Campus Events 🎉\n";
        cout << "3. Exit 🚪\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore trailing newline

        switch (choice) {
            case 1:
                campusNotifications(notifications);
                break;
            case 2:
                campusEvents(events);
                break;
            case 3:
                cout << "🚪 Exiting the system. Thank you, Explorer Dora! See you next time! ✨\n";
                break;
            default:
                cout << "❌ Uh-oh! That’s not an option, Explorer. Try again! 🗺️\n";
        }
    } while (choice != 3);
}
void bushrah1()
{
   //BUSHRAHHHH PARTTTT
    // Create separate trees for each building
    BuildingNode* auditoriumTree = createAuditoriumTree();
    BuildingNode* fmeTree = createFMETree();
    BuildingNode* fcseTree = createFCSETree();
    BuildingNode* fesTree = createFESTree();
    BuildingNode* acbTree = createACBTree();
    BuildingNode* brabersTree = createBrabersTree();
    BuildingNode* clockTowerTree = createClockTowerTree();
    BuildingNode* guestHouseTree = createGuestHouseTree();
    BuildingNode* tucTree = createTUCTree();
    BuildingNode* girlsHostelsTree = createGirlsHostelsTree();

    // Interactive menu for the user
    handleSelection(auditoriumTree, fmeTree, fcseTree, fesTree, acbTree, brabersTree, clockTowerTree, guestHouseTree, tucTree, girlsHostelsTree);

}
void bushrah2()
{
    //BUSHRAHHH QUEUE PARTTTT
   campusManagement();
}

void masooma()
{//MASOOOOOOOMAAAA PART
    Graph campusGraph;
    cout<<"DORA: WHO DO WE ASK FOR HELP WHEN WE DONT KNOW WHICH WAY TO GO??"<<endl;
    cout<<"BOOTS:THE MAP, THE MAP!!"<<endl;
    cout<<"DORA:YOU HAVE TO SAY MAP"<<endl;
    cout<<"BOOTS:SAY MAP,SAY MAP!!"<<endl;
    cout<<endl;
    cout<<"=========MAP SONG=========="<<endl;
    cout<<endl;
    cout<<"IM THE MAP IM THE MAP IM THE MAP IM THE MAP IM THE MAPPPPPP!!!!"<<endl;
    cout<<endl;
    cout<<"I NOW SHOW PLACES AND THEIR DISTANCECS TO EACHOTHER IN THE FORM OF GRAPHS THROUGH ADJACENCY LISTS!!!"<<endl;
    cout<<endl;
    campusGraph.addEdge("Brabers Building", "Girls Hostel", 2);
    campusGraph.addEdge("Brabers Building", "Tuck", 3);
    campusGraph.addEdge("Brabers Building", "Library", 2);
    campusGraph.addEdge("Library", "Acb", 1);
    campusGraph.addEdge("Library", "Auditorium", 1);
    campusGraph.addEdge("Acb", "Boys Hostel", 1);
    campusGraph.addEdge("Acb", "Auditorium", 1);
    campusGraph.addEdge("FCSE", "Auditorium", 1);
    campusGraph.addEdge("FCSE", "FES", 1);
    campusGraph.addEdge("FCSE", "FME", 1);
    campusGraph.addEdge("FME", "FCSE", 1);
    campusGraph.addEdge("FMCE", "FCSE", 2);
    campusGraph.addEdge("FME", "Auditorium", 1);
    campusGraph.addEdge("FMCE", "Auditorium", 1);
    campusGraph.addEdge("Tuck", "Guest House", 1);
    campusGraph.addEdge("Auditorium", "Tuck", 3);
    campusGraph.addEdge("FMCE", "Tuck", 2);
    campusGraph.addEdge("Tuck", "Clock Tower", 2);
    campusGraph.addEdge("Clock Tower", "Entrance", 1);
    campusGraph.addEdge("Entrance", "Admin", 2);
    campusGraph.addEdge("Admin", "Sports Complex", 2);
    campusGraph.addEdge("Sports Complex ", "Boys Hostel", 1);

    // Print the graph
    campusGraph.printGraph();
    //RUMAISA
     cout<<"..................................................."<<endl;
    campusGraph.dfsTraversal("Brabers Building","Admin");
    cout<<"..................................................."<<endl;
    campusGraph.dfsTraversal("Brabers Building", "Tuck");
    cout<<"..................................................."<<endl;
    //campusGraph.dfsTraversal("Brabers Building", "FCSE");
    campusGraph.bfsTraversal("Library","Admin");
    cout<<"..................................................."<<endl;


}

void menu()
{
    //looked cringe so we commented out BUT WE MADE SO
    // cout << " EEEEE  X   X  PPPP   L      OOO   RRRR   EEEEE " << endl;
    // cout << " E       X X   P   P  L     O   O  R   R  E     " << endl;
    // cout << " EEEE     X    PPPP   L     O   O  RRRR   EEEE  " << endl;
    // cout << " E       X X   P      L     O   O  R  R   E     " << endl;
    // cout << " EEEEE  X   X  P      LLLLL  OOO   R   R  EEEEE " << endl;

cout<<"DORA:OLA SOI DORA!"<<endl;
cout<<"BOOTS:AND IM BOOTS"<<endl;
cout<<"DORA:WHAT WOULD YOU LIKE TO DO ON THE GIKI CAMPUS TODAY"<<endl;
 while (true){
    cout<<"IF YOU WOULD YOU LIKE TO VIEW CAMPUS BUILDINGS ANAD DETAILS PRESS 1"<<endl;
    cout<<"IF YOU WOULD LIKE TO VIEW NOTIFICATIONS,PRESS 2"<<endl;
    cout<<"IF YOU WOULD YOU LIKE TO EXPLORE THE MAP AND TRAVERSE IT PRESS 3"<<endl;
    cout<<"IF YOU WOULD YOU LIKE TO CALL IT A DAY PRESS 4"<<endl;
    cout<<"DORA:ME TOO"<<endl;
    int option;
    cin>>option;
   
    if (option==1)
    {
bushrah1();
    }
    else if (option==2)
    {
        bushrah2();
    }
    else if(option==3)
    {
        masooma();
    }
    else if (option==4){
        break;
    }
    else{
        cout<<"PLEASE ENTER A VALID OPTION"<<endl;
    }
}}
// Main Function
int main() {
 

    
menu();

    return 0;
}