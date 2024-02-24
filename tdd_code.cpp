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


Graph::Graph() {

    graphNodes.clear();
    graphEdges.clear();

}

Graph::~Graph() {
    clear();
}

std::vector<Node*> Graph::nodes() {
    return graphNodes;
}

std::vector<Edge> Graph::edges() const {
    return graphEdges;
}

Node* Graph::addNode(size_t nodeId) {

    for (auto node : graphNodes) {
    
        if (node->id == nodeId) {
            return nullptr;
        }
    
    }

    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode != nullptr) {

        newNode->id = nodeId;
        graphNodes.push_back(newNode);

        return newNode;
    
    }
    
    return nullptr;
}

bool Graph::addEdge(const Edge& edge) {

    if(edge.a == edge.b) {

        return false;
    
    }

    for(auto graphEdge : graphEdges) {

        if(graphEdge == edge) {
            
            return false;

        }

    }    

    addNode(edge.a);
    addNode(edge.b);
    graphEdges.push_back(edge);

    return true;

}

void Graph::addMultipleEdges(const std::vector<Edge>& edges) {

    for(auto newEdge : edges) {

        addEdge(newEdge);
    
    }

}

Node* Graph::getNode(size_t nodeId) {

    for (auto node : graphNodes) {

        if (node->id == nodeId) {
            return node;
        }
    
    }
    
    return nullptr;

}


bool Graph::containsEdge(const Edge& edge) const {

    for(auto graphEdge : graphEdges) {

        if(graphEdge == edge) {
            
            return true;

        }

    }  

    return false;

}

void Graph::removeNode(size_t nodeId) {
    
    auto i = std::remove_if(graphEdges.begin(), graphEdges.end(), 
        [nodeId](const Edge& edge) { 
            return edge.a == nodeId || edge.b == nodeId; 
        });
    graphEdges.erase(i, graphEdges.end());

    auto nodeIt = std::find_if(graphNodes.begin(), graphNodes.end(), 
        [nodeId](const Node* node) { 
            return node->id == nodeId; 
        });

    if (nodeIt != graphNodes.end()) {
        delete *nodeIt;
        graphNodes.erase(nodeIt);
    } else {
        throw std::out_of_range("Node doesn't exist!\n");
    }
}

void Graph::removeEdge(const Edge& edge) {

    auto i = std::find(graphEdges.begin(), graphEdges.end(), edge);
   
    if (i != graphEdges.end()) {
        graphEdges.erase(i);
    } else {
        throw std::out_of_range("Edge doesn't exist!\n");
    }

}

size_t Graph::nodeCount() const{
    return graphNodes.size();
}

size_t Graph::edgeCount() const{
    return graphEdges.size();
}

size_t Graph::nodeDegree(size_t nodeId) const{
    return 42;
}

size_t Graph::graphDegree() const{
    return 42;
}

void Graph::coloring(){
}

void Graph::clear() {

    graphEdges.clear();

    for(auto node : graphNodes) {
        delete node; 
    }
    graphNodes.clear();

}

/*** Konec souboru tdd_code.cpp ***/
