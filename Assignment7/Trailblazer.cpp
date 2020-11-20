/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "pqueue.h"
#include "random.h"
using namespace std;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
struct Node {
    Loc location;
    double distance;
    Node* parent;
};

Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
             double heuristic(Loc from, Loc to, Grid<double>& world)) {
    // Set up data structures to hold information about grid
    TrailblazerPQueue<Loc> tpq;
    Map<Loc, Node*> visited;
    
    // Configure start node
    Node* startNode = new Node;
    startNode->location = start;
    startNode->distance = 0;
    startNode->parent = NULL;
    colorCell(world, start, YELLOW);
    
    // Dijkstra's algorithm
    visited.put(start, startNode);
    tpq.enqueue(start, heuristic(start, end, world));
    
    while (!tpq.isEmpty()) {
        Loc currLoc = tpq.dequeueMin();
        Node* currNode = visited.get(currLoc);
        colorCell(world, currLoc, GREEN);
        
        // found shortest path from start to end
        if (currNode->location == end) {
            Stack<Loc> pathStack;
            Vector<Loc> path;
            pathStack.push(currLoc);
            
            while ((currNode = currNode->parent) != NULL) {
                pathStack.push(currNode->location);
            }
            
            while (!pathStack.isEmpty()) {
                path.add(pathStack.pop());
            }
            
            return path;
        }
        
        for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
            for (int colOffset = -1; colOffset <= 1; colOffset++) {
                Loc adjacent;
                adjacent.row = currLoc.row + rowOffset;
                adjacent.col = currLoc.col + colOffset;
                
                if (world.inBounds(adjacent.row, adjacent.col)) {
                    double length = costFn(currLoc, adjacent, world);
                    double candidateDistance = currNode->distance + length;
                    
                    if (!visited.containsKey(adjacent)) {
                        colorCell(world, adjacent, YELLOW);
                        Node* v = new Node;
                        v->location = adjacent;
                        v->distance = candidateDistance;
                        v->parent = currNode;
                        visited.put(adjacent, v);
                        tpq.enqueue(adjacent, candidateDistance + heuristic(adjacent, end, world));
                    } else if (candidateDistance < visited.get(adjacent)->distance) {
                        Node* v = visited.get(adjacent);
                        v->distance = candidateDistance;
                        v->parent = currNode;
                        tpq.decreaseKey(adjacent, candidateDistance + heuristic(adjacent, end, world));
                    }
                }
            }
        }
    }
    
    return Vector<Loc>();
}

Set<Edge> createMaze(int numRows, int numCols) {
    // Setup data structures to hold information about maze
    Grid<bool> world(numRows, numCols);
    Vector<Loc> nodes;
    PriorityQueue<Edge> pq;
    Set<Edge> edges;
    Map<Loc, Set<Loc>*> clusterMap;
    
    // Create Loc nodes
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            Loc node = makeLoc(i, j);
            Set<Loc>* initSet = new Set<Loc>;
            initSet->add(node);
            nodes.add(node);
            clusterMap.put(node, initSet);
        }
    }
    
    // Enqueue edges with random priority
    for (int i = 0; i < nodes.size(); i++) {
        Vector<Loc> neighbors;
        neighbors.add(makeLoc(nodes[i].row + 1, nodes[i].col)); // top
        neighbors.add(makeLoc(nodes[i].row - 1, nodes[i].col)); // bottom
        neighbors.add(makeLoc(nodes[i].row, nodes[i].col - 1)); // left
        neighbors.add(makeLoc(nodes[i].row, nodes[i].col + 1)); // right
        
        foreach (Loc adjacent in neighbors) {
            if (world.inBounds(adjacent.row, adjacent.col)) {
                Edge e = makeEdge(nodes[i], adjacent);
                pq.enqueue(e, randomReal(0, 1));
            }
        }
    }
    
    // Merge clusters
    while (!pq.isEmpty()) {
        Edge path = pq.dequeue();
        if (clusterMap[path.start] != clusterMap[path.end]) {
            Set<Loc>* cluster1 = clusterMap[path.start];
            Set<Loc>* cluster2 = clusterMap[path.end];
            Set<Loc>* mergedCluster = new Set<Loc>;
            
            // Add nodes in each cluster to new merged cluster
            foreach (Loc node in *cluster1) {
                mergedCluster->add(node);
            }
            
            foreach (Loc node in *cluster2) {
                mergedCluster->add(node);
            }
            
            // Update clusterMap with new key-value pairs
            foreach (Loc node in *mergedCluster) {
                clusterMap.put(node, mergedCluster);
            }
            
            // Delete old clusters
            delete cluster1;
            delete cluster2;
            
            // Add path to list of edges
            edges.add(path);
        }
    }
    
    // Free space used up by final cluster
    delete clusterMap[makeLoc(0, 0)];
    
    return edges;
}



//Set<Edge> createMaze(int numRows, int numCols) {
//    Grid<bool> world(numRows, numCols);
//    Vector<Loc> nodes;
//    PriorityQueue<Edge> pq;
//    Set<Edge> edges;
//    Map<Loc, Set<Loc> > clusterMap;
//    
//    // Create Loc nodes
//    for (int i = 0; i < numRows; i++) {
//        for (int j = 0; j < numCols; j++) {
//            Loc node = makeLoc(i, j);
//            Set<Loc> initSet;
//            initSet.add(node);
//            nodes.add(node);
//            clusterMap.put(node, initSet);
//        }
//    }
//    
//    // Enqueue edges with random priority
//    for (int i = 0; i < nodes.size(); i++) {
//        Vector<Loc> neighbors;
//        neighbors.add(makeLoc(nodes[i].row + 1, nodes[i].col)); // top
//        neighbors.add(makeLoc(nodes[i].row - 1, nodes[i].col)); // bottom
//        neighbors.add(makeLoc(nodes[i].row, nodes[i].col - 1)); // left
//        neighbors.add(makeLoc(nodes[i].row, nodes[i].col + 1)); // right
//        
//        foreach (Loc adjacent in neighbors) {
//            if (world.inBounds(adjacent.row, adjacent.col)) {
//                Edge e = makeEdge(nodes[i], adjacent);
//                pq.enqueue(e, randomReal(0, 1));
//            }
//        }
//    }
//    
//    // Merge clusters
//    while (!pq.isEmpty()) {
//        Edge path = pq.dequeue();
//        if (clusterMap[path.start] != clusterMap[path.end]) {
//            clusterMap[path.start] += clusterMap[path.end];
//            clusterMap[path.end] += clusterMap[path.start];
//            
//            foreach(Loc node in clusterMap[path.start]) {
//                clusterMap[node] += clusterMap[path.start];
//            }
//            
//            edges.add(path);
//        }
//    }
//    
//    return edges;
//}
