Dora the Campus Explorer
Dora the Campus Explorer is a comprehensive application designed to navigate and explore the GIKI campus with ease and efficiency. By leveraging the power of advanced data structures such as graphs, trees, and queues, this system provides an interactive and user-friendly platform to assist users in finding routes between buildings, accessing detailed information about rooms and lecture halls, and managing campus events effectively.

The project serves as a practical demonstration of how fundamental data structures can be utilized to solve real-world problems, specifically within the domain of campus navigation and organization. The intuitive interface and structured approach make it a valuable tool for students, faculty, and visitors.

🏢 About the Project
The Dora the Campus Explorer application is designed to address the complexities of navigating a large campus, like GIKI, by combining data structure algorithms with an intuitive design. Users can easily find their way around the campus, retrieve information about specific buildings and rooms, and stay updated on events and notifications.

The system uses a combination of:

Graphs for mapping and connectivity.
Trees for hierarchical data representation.
Queues for efficiently handling notifications and event management.
This project demonstrates a holistic approach to software development by integrating both theoretical concepts and practical application, making it an excellent educational tool and a functional campus resource.

🌟 Features

The application includes the following features:

Campus Building Information:

Displays hierarchical information about buildings, including rooms, lecture halls, and facilities.
Allows structured access to building details through tree-based data structures.
Campus Notifications:

Real-time notifications handled using a queue-based system.
Notifications are displayed in a First-In-First-Out (FIFO) order to ensure timely updates.
Mapping of Campus Buildings:

Connects campus buildings using graph data structures.
Weighted edges represent distances between buildings for realistic navigation.
Building Traversal:

Users can explore buildings using graph traversal algorithms such as:
BFS (Breadth-First Search) for level-order traversal.
DFS (Depth-First Search)for depth-oriented exploration.

Campus Event Management:


Efficiently manages campus events using queue-based notifications and scheduling.
📚 Data Structures and Algorithms Used
This project stands out for its innovative use of data structures and algorithms to solve real-world challenges:

Graphs:

Buildings are represented as vertices.
Edges connect these vertices and are weighted based on distances between buildings.
Adjacency lists are used for efficient memory usage and easy visualization of connections.
Algorithms like BFS and DFS are applied to traverse and explore the campus graph.

Trees:

Campus buildings are represented as hierarchical binary search trees.
The root node represents the building, while child nodes represent lecture halls, rooms, and other facilities.
Trees provide a structured and intuitive way to store and retrieve building information.

Queues:

Notifications and events are managed using FIFO queues.
Implemented using linked lists to allow dynamic and efficient handling of notification data.

Linked Lists:

Used in the implementation of adjacency lists for graphs.
Facilitate dynamic data management in queues and tree structures.

Graph Traversal Algorithms:

Breadth-First Search (BFS) ensures a level-by-level exploration of connected buildings.
Depth-First Search (DFS) allows for a deeper dive into campus connectivity.

🔧 Implementation Details

Adjacency Matrix for Graphs:
A 2D array represents connections between buildings.
Weighted edges signify the distance between connected buildings.
Forest of Trees for Buildings:
Each building is represented as a tree with rooms and lecture halls as child nodes.
The hierarchical structure ensures clarity and organization.
Notification System:
Queues ensure notifications are displayed in the order they are received.
Each notification is a node in a linked list, allowing for seamless transitions.

📂 Project Structure

Main Application: Integrates all features into a cohesive system.
Data Structures: Custom implementations of graphs, trees, and queues.
Navigation System: Traversal algorithms for efficient campus exploration.
Event Management System: Queue-based scheduling and notifications.
🛠️ Getting Started
Prerequisites
A C++ compiler (e.g., GCC)
A terminal or IDE (e.g., Visual Studio Code)
Installation Steps
Clone the repository:

git clone https://github.com/your-username/dora-campus-explorer.git
cd dora-campus-explorer
Compile the program:

g++ main.cpp -o dora_explorer
Run the program:

./dora_explorer
🌟 Example Output
Graph Connections:

Vertex 0 connections: 1(1) 2(1) 3(1) 4(1)
Vertex 1 connections: 0(1) 3(1)
Vertex 2 connections: 0(1) 4(1)
...
BFS Traversal:

BFS Traversal: 0 1 2 3 4
📊 Key Benefits
Efficient Navigation: Traversal algorithms provide optimal routes and exploration paths.
Structured Data Management: Trees and queues offer logical organization and seamless data handling.
Real-Time Notifications: Queue-based notifications ensure timely and organized updates.

🤝 Contributing
We welcome contributions to improve the project! To contribute:

Fork the repository.
Create a new branch for your feature:

git checkout -b feature-name
Commit your changes and push the branch:

git push origin feature-name
Submit a pull request for review.


🏆 Acknowledgments
This project demonstrates the potential of data structures and algorithms to solve real-world problems. It was inspired by the challenges faced in navigating and organizing large campus environments, specifically at GIKI. We would like to thank the GIKI community for their invaluable feedback and support.

