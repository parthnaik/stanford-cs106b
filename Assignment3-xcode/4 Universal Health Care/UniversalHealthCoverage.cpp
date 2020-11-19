/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);
Set<string> getCoveredCities(Set<string>& cities, Set<string> location);

int main() {
    Set<string> cities;
    cities += "A", "B", "C", "D", "E", "F";
    
    Set<string> hospital1;
    hospital1 += "A", "B", "C";
    
    Set<string> hospital2;
    hospital2 += "A", "C", "D";
    
    Set<string> hospital3;
    hospital3 += "B", "F";
    
    Set<string> hospital4;
    hospital4 += "C", "E", "F";
    
    Vector<Set<string> > locations;
    locations += hospital1, hospital2, hospital3, hospital4;
    
    int numHospitals = 3;
    Vector<Set<string> > result;
    if (canOfferUniversalCoverage(cities, locations, numHospitals, result)) {
        cout << "Yes, it can offer universal coverage!" << endl;
    } else {
        cout << "No, it cannot offer universal coverage." << endl;
    }
    cout << "Result: " << result << endl;
    
    return 0;
}

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result) {
    // Base Case 0 (If all cities are covered return true):
    if (cities.isEmpty()) {
        return true;
    }
    
    // Base Case 1 (If cities are not covered and no hospital choices left return false):
    if (numHospitals == 0) {
        return false;
    }
    
    // Base Case 2 (If cities are not covered and there are no more hospitals return false):
    if (locations.isEmpty()) {
        return false;
    }
    
    for (int i = 0; i < locations.size(); i++) {
        Vector<Set<string> > currResult = result;
        Set<string> remainingCities = cities;
        Vector<Set<string> > remainingLocations = locations;
        
        Set<string> coveredCities = getCoveredCities(remainingCities, locations[i]);
        if (!coveredCities.isEmpty()) {
            remainingLocations.remove(i);
            currResult.add(locations[i]);
        }
        
        if (canOfferUniversalCoverage(remainingCities, remainingLocations, numHospitals - 1, currResult)) {
            result = currResult;
            return true;
        }
    }
    
    return false;
}

/* Determines any covered cities in hospital location and removes them from the cities set.
 * Returns the removed/covered cities.
 */
Set<string> getCoveredCities(Set<string>& cities, Set<string> location) {
    Set<string> coveredCities;
    
    foreach(string city in cities) {
        if (location.contains(city)) {
            coveredCities.add(city);
            cities.remove(city);
        }
    }
    
    return coveredCities;
}