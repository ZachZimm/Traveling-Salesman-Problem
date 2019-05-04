#include <iostream>
#include <iterator>
#include <algorithm>
#include <tuple>

#include "boost/graph/adjacency_list.hpp"
#include "VertexData.h"
#include "EdgeData.h"
#include "Visitor.h"
/*
    TODO
    Make Visitor::chooseVertex do something
*/

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, // Define adjecency list properties
                            VertexData, EdgeData>
                            GraphType;
typedef boost::graph_traits<GraphType>::vertex_descriptor VertexData_t;
typedef boost::graph_traits<GraphType>::edge_descriptor EdgeData_t;

void testRoute(VertexData_t startCity, GraphType & graph);

/*
    Cities :
    Reno
    San Francisco
    Salt Lake City
    Seattle
    Las Vegas
 */

int main()
{
    GraphType Cities;

    VertexData_t reno = boost::add_vertex(Cities);
    Cities[reno].name = "Reno";

    VertexData_t sanFran = boost::add_vertex(Cities);
    Cities[sanFran].name = "San Francisco";

    VertexData_t saltLake = boost::add_vertex(Cities);
    Cities[saltLake].name = "Salt Lake City";
    
    VertexData_t seattle = boost::add_vertex(Cities);
    Cities[seattle].name = "Seattle";
    
    VertexData_t lasVegas = boost::add_vertex(Cities);
    Cities[lasVegas].name = "Las Vegas";


    EdgeData_t renoToSanFran = boost::add_edge(reno, sanFran, {218.4}, Cities).first;
    EdgeData_t renoToLasVegas = boost::add_edge(reno, lasVegas, {438.2}, Cities).first;

    EdgeData_t seattleToSaltLake = boost::add_edge(seattle, saltLake, {831.9}, Cities).first;
    EdgeData_t seattleToReno = boost::add_edge(seattle, reno, {704.6}, Cities).first;
    EdgeData_t seattleToSanFran = boost::add_edge(seattle, sanFran, {807.6}, Cities).first;

    EdgeData_t saltLakeToLasVegas = boost::add_edge(saltLake, lasVegas, {421.1}, Cities).first;
    EdgeData_t saltLakeToReno = boost::add_edge(saltLake, reno, {518.2}, Cities).first;

    EdgeData_t sanFranToLasVegas = boost::add_edge(sanFran, lasVegas, {569.0}, Cities).first;

    testRoute(reno, Cities);
}

void testRoute(VertexData_t startCity, GraphType & graph)
{
    // Get Cities
    // Need a 'visitor'?
    // Based on adjacent cities, find unvisited cities
    // Traverse to a city and mark as visited
    // Repeat until all cities are visited

    // Declare and initialize nessecary variables
    std::vector<VertexData_t> adjUnvisited;
    std::vector<VertexData_t> citiesVisited;
    Visitor visitor;
    graph[startCity].visited = true;
    visitor.currCity = startCity;
    bool unfinished = true;

    // Get an iterator range of adjacent and unvisited cities
    std::cout << "Starting City : " << graph[startCity].name << "\n\n";
    while(unfinished)
    {
        auto currAdj = boost::adjacent_vertices(visitor.currCity, graph);
        for(currAdj; currAdj.first != currAdj.second; ++currAdj.first)
        {
            if(!(graph[*currAdj.first].visited))
            {
                adjUnvisited.push_back(*currAdj.first);
            }
        }

        // Visit city
        if(adjUnvisited.size() > 0)
        {
            VertexData_t prevVertex = visitor.currCity; // Save previously visited city so the correct edge can be determined
            EdgeData targetEdge;

            visitor.currCity = adjUnvisited[visitor.chooseVertex(adjUnvisited.size())]; // Currently just outputs 0, as far as I can tell, this function is the bulk of the work I still
            graph[visitor.currCity].visited = true;                                     // have to do
            std::cout << "Visiting " << graph[visitor.currCity].name << "\n";

            auto currAdjEdg = boost::out_edges(visitor.currCity, graph); // Get an iterator range of connecting edges
            for(currAdjEdg.first; currAdjEdg.first != currAdjEdg.second; ++currAdjEdg.first) // And check whether any of those edges have the previous and current cities as source/target
            {
                if((graph[prevVertex] == graph[boost::target(*currAdjEdg.first, graph)] && graph[visitor.currCity] == graph[boost::source(*currAdjEdg.first, graph)] ||
                    (graph[prevVertex] == graph[boost::source(*currAdjEdg.first, graph)] && graph[visitor.currCity] == graph[boost::target(*currAdjEdg.first, graph)])))
                    {
                        targetEdge = graph[*currAdjEdg.first];
                        visitor.addDistance(targetEdge.distance);
                        std::cout << targetEdge.distance << " miles traveled\n\n";
                    }
            }
        }

        // std::cout << "\n\tDEBUG Contents of adjUnvisited : \n";
        // for(int i = 0; i < adjUnvisited.size(); i++)
        // {
        //     std::cout << "\t\t" << graph[adjUnvisited[i]].name << "\n";
        // }
        // std::cout << "\n";

        unfinished = false;
        for(auto allV = boost::vertices(graph); allV.first != allV.second; ++allV.first) // Check whether all vertices in the graph
        {
            if(!graph[*allV.first].visited)
            {
                unfinished = true;
                break;
            }
        }

        adjUnvisited.clear(); // Clear list of adjacent vertices because visitor is at a new city
    }
    std::cout << visitor.getDistance() << " miles traveled in total\n";
}