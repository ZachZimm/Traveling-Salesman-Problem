#ifndef VISITTOR_H
#define VISITOR_H

#include "boost/graph/adjacency_list.hpp"
#include "VertexData.h"
#include "EdgeData.h"

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, // Define adjecency list properties
                            VertexData, EdgeData>
                            GraphType;
typedef boost::graph_traits<GraphType>::vertex_descriptor VertexData_t;

struct Visitor
{
    VertexData_t currCity;

    int chooseVertex(int range);
    void addDistance(float const distance);
    float getDistance();

private:
    float distanceTraveled = 0;
};

#endif