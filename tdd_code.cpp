//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     David Bujzaš <xbujzad00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"

// constructor
Graph::Graph() {
    graphNodes.clear(); // clears the vector containing nodes
    graphEdges.clear(); // clears the vector containing edges
}

// destructor
Graph::~Graph() {
    clear();
}

// returns a vector of nodes
std::vector<Node*> Graph::nodes() {
    return graphNodes;
}

// returns a vector of edges
std::vector<Edge> Graph::edges() const {
    return graphEdges;
}

// adds a node to the graph
Node* Graph::addNode(size_t nodeId) {
    // checks if the node already exists
    for (auto node : graphNodes) {
        // if the node exists return null pointer
        if (node->id == nodeId) {
            return nullptr;
        }
    }

    // creates node and adds it to the graphNode vector
    Node *newNode = new Node;
    if (newNode != nullptr) {
        newNode->id = nodeId;
        graphNodes.push_back(newNode);
        return newNode;
    }
    
    return nullptr;
}

// adds an edge to the graph
bool Graph::addEdge(const Edge& edge) {
    // checks if the edge connects to the same node
    if(edge.a == edge.b) {
        return false;
    }

    // checks if the edge already exists
    for(auto graphEdge : graphEdges) {
        if(graphEdge == edge) {
            return false;
        }
    }    

    // adds the edges to the graphEdges vector
    addNode(edge.a);
    addNode(edge.b);
    graphEdges.push_back(edge);

    return true;
}

// adds multiple edges to the graph
void Graph::addMultipleEdges(const std::vector<Edge>& edges) {
    for(auto newEdge : edges) {
        addEdge(newEdge);
    }
}

// returns a pointer to the node
Node* Graph::getNode(size_t nodeId) {
    for (auto node : graphNodes) {
        if (node->id == nodeId) {
            return node;
        }
    }
    return nullptr;
}

// checks if graph contains the given edge
bool Graph::containsEdge(const Edge& edge) const {
    for(auto graphEdge : graphEdges) {
        if(graphEdge == edge) {
            return true;
        }
    }  
    return false;
}

// removes the node from the graph
void Graph::removeNode(size_t nodeId) {
    // removes edges connected to the node
    auto i = std::remove_if(graphEdges.begin(), graphEdges.end(), 
        [nodeId](const Edge& edge) { 
            return edge.a == nodeId || edge.b == nodeId; 
        });
    graphEdges.erase(i, graphEdges.end());

    // removes the node from the node vectors and deallocates memory
    auto nodeIt = std::find_if(graphNodes.begin(), graphNodes.end(), 
        [nodeId](const Node* node) { 
            return node->id == nodeId; 
        });


    if (nodeIt != graphNodes.end()) {
        delete *nodeIt;
        graphNodes.erase(nodeIt);
    } else {
        throw std::out_of_range("Node does not exist!\n");
    }
}

// removes the edge from the graph
void Graph::removeEdge(const Edge& edge) {
    // iterates through edges and erases the given edge
    auto i = std::find(graphEdges.begin(), graphEdges.end(), edge);
    if (i != graphEdges.end()) {
        graphEdges.erase(i);
    } else {
        throw std::out_of_range("Edge does not exist!\n");
    }
}

// returns the node count
size_t Graph::nodeCount() const{
    return graphNodes.size();
}

// returns the edge count
size_t Graph::edgeCount() const{
    return graphEdges.size();
}

// returns the degree of a node
size_t Graph::nodeDegree(size_t nodeId) const {
    // checks if the node exists
    if (std::find_if(graphNodes.begin(), graphNodes.end(), 
        [nodeId](const Node* node) { return node->id == nodeId; }) == graphNodes.end()) {
        throw std::out_of_range("Node does not exist!\n");
    }

    // counts the number of edges connected to the node
    size_t degree = 0;
    for (auto node : graphNodes) {
        if (containsEdge({nodeId, node->id})) {
            degree++;
        }
    }

    return degree;
}

// returns the maximum degree of any node in the graph
size_t Graph::graphDegree() const{
    size_t maxDegree = 0;

    // iterates through all nodes and find the max degree
    for(auto node : graphNodes) {
        size_t currentDegree = nodeDegree(node->id);
        if(currentDegree > maxDegree) {
            maxDegree = currentDegree;
        }
    }

    return maxDegree;
}

void Graph::coloring() {
    // initializes all nodes with color -1
    for(auto node : graphNodes) {
        node->color = -1;
    }

    // generates a list of colors
    std::vector<size_t> colors;
    for(size_t i = 1; i <= graphDegree() + 1; i++) {
        colors.push_back(i);
    }

    // iterates through all nodes and assign colors
    for(auto nodeI : graphNodes) {
        std::vector<size_t> tempColors = colors;

        for(auto nodeJ : graphNodes) {
            if(containsEdge({nodeI->id, nodeJ->id})) {
                auto i = std::find(tempColors.begin(), tempColors.end(), nodeJ->color);
                if(i != tempColors.end()) {
                    tempColors.erase(i);
                }
            }
        }
        
        nodeI->color = tempColors[0];
    }
}

// clears graph
void Graph::clear() {
graphEdges.clear();         // clears edges vector
    for(auto node : graphNodes) {
        delete node;            // deallocates memory for each node            
    }
    graphNodes.clear();         // clears nodes vector
}
/*** Konec souboru tdd_code.cpp ***/
