#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <string>

struct VertexData
{
    VertexData();

    std::string name;
    bool visited = false;
    int id;

    bool operator==(const VertexData & other);
};

#endif