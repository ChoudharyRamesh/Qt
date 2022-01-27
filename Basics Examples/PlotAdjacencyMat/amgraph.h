#ifndef AMGRAPH_H
#define AMGRAPH_H

#include<QList>
#include<QBitArray>
#include<QMultiMap>

//Adjacency-Matrix-Graph
class AMGraph
{
public:
    AMGraph(const QList<QList<int>> & adjacencyMatrix);
    int getEgdeCount()const;
    int getNodeCount()const;
    bool hasEdge(int source,int destination)const;
    QList<QList<int>>  getSortedNodes();

private:
    uint nodes=0;
    uint edges=0;
    QList<QBitArray> adjacencyMatrix;

};
#endif // AMGRAPH_H
