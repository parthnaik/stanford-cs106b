/*
 * File: DepthFirstSearch.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "vector.h"
#include "map.h"
#include "console.h"
using namespace std;

Vector<string> depthFirstSearch(string start, string end,
                                Vector<string> edgeFunction(string nodeName));
bool dfsRec(string curr, string parent, string end,
            Map<string, string>& parentMap,
            Vector<string> edgeFunction(string nodeName));
Vector<string> flattenPath(Map<string, string>& parentMap, string endpoint);


int main() {
    
    return 0;
}

Vector<string> depthFirstSearch(string start, string end,
                                Map<string, string> parentMap,
                                Vector<string> edgeFunction(string nodeName)) {
    if (dfsRec(start, start, end, parentMap, edgeFunction)) {
        return flattenPath(parentMap, end);
    }
    
    /* Otherwise, return an empty Vector. */
    return Vector<string>();
}

bool dfsRec(string curr, string parent, string end,
            Map<string, string>& parentMap,
            Vector<string> edgeFunction(string nodeName)) {
    if (parentMap.containsKey(curr)) return false;
    parentMap[curr] = parent;
    if (curr == end) return true;
    foreach (string child in edgeFunction(curr)) {
        if (dfsRec(child, curr, end, parentMap, edgeFunction)) {
            return true;
        }
    }
    return false;
}

Vector<string> flattenPath(Map<string, string>& parentMap, string endpoint) {
    /* The parent map traces the path back to the starting node, so we have to
     * reverse it before returning it. To do so, we'll throw everything in a Stack
     * before putting it into the Vector.
     */
    Stack<string> reverseResult;
    while (true) {
        reverseResult.push(endpoint);
        if (parentMap[endpoint] == endpoint) break;
        endpoint = parentMap[endpoint];
    }
    Vector<string> result;
    while (!reverseResult.isEmpty()) {
        result += reverseResult.pop();
    }
    return result;
}