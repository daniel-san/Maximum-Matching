#include "graph.h"

double weight(struct vertex v1, struct vertex v2)
{
    double w = sqrt(pow(v1.x - v2.x,2) + pow(v1.y - v2.y,2));
    return w;
}
