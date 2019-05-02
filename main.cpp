#include <iostream>

#include "boost/graph/adjacency_list.hpp"
#include "VertexData.h"
#include "EdgeData.h"

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, // Define adjecency list properties
                            VertexData, EdgeData> 
                            GraphType;
    typedef boost::graph_traits<GraphType>::vertex_descriptor VertexData_t;
    typedef boost::graph_traits<GraphType>::edge_descriptor EdgeData_t;
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

    auto renoToSanFran = boost::add_edge(reno, sanFran, {218.4}, Cities);
    auto renoToLasVegas = boost::add_edge(reno, lasVegas, {438.2}, Cities);

    auto seattleToSaltLake = boost::add_edge(seattle, saltLake, {831.9}, Cities);
    auto seattleToReno = boost::add_edge(seattle, reno, {704.6}, Cities);
    auto seattleToSanFran = boost::add_edge(seattle, sanFran, {807.6}, Cities);

    auto saltLakeToLasVegas = boost::add_edge(saltLake, lasVegas, {421.1}, Cities);
    auto saltLakeToReno = boost::add_edge(saltLake, reno, {518.2}, Cities);

    auto sanFranToLasVegas = boost::add_edge(sanFran, lasVegas, {569.0}, Cities);

    std::cout << "Cities has : " << (Cities.m_vertices.size()) << " vertices.\n";
    std::cout << "Welcome to the city of " << (Cities[sanFran].name) << "!\n";
    std::cout << "That was a " << (Cities[renoToSanFran.first].distance) << " mile drive from " << (Cities[renoToSanFran.second].name) << ".\n";
}