#include "VertexData.h"

static int ID;

VertexData::VertexData()
{
    this->id = ID;
    ID++;
}

bool VertexData::operator==(const VertexData & other)
{
    return (this->id == other.id);
}