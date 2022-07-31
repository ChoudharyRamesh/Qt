#include "amgraph.h"
#include<QDebug>

AMGraph::AMGraph(const QList<QList<int> > &adjacencyMatrix)
{

    for(int i=0;i<adjacencyMatrix.size();i++)
    {
        this->adjacencyMatrix.append(QBitArray(adjacencyMatrix.size(),0));
        for(int j=0;j<adjacencyMatrix.at(i).size();j++)
            this->adjacencyMatrix[i].setBit(j,adjacencyMatrix.at(i).at(j));
    }

    for(uint toDown=0;toDown<nodes;toDown++)
        for(uint toLeft=toDown;toLeft<nodes;toLeft++)
            if(toLeft!=toDown)
            {
                if(this->adjacencyMatrix.at(toDown).at(toLeft)==1 ||
                        this->adjacencyMatrix.at(toLeft).at(toDown)==1 )
                    edges++;
            }
    this->nodes = this->adjacencyMatrix.size();
}

int AMGraph::getEgdeCount() const
{
    return edges;
}

int AMGraph::getNodeCount() const
{
    return nodes;
}

bool AMGraph::hasEdge(int source, int destination) const
{
    if(source==destination)return false;
    return adjacencyMatrix.at(source).at(destination);
}

QList<QList<int> > AMGraph::getSortedNodes()
{
    QMultiMap<int,int> map ;
    QList<QList<int>> list ;

    for(int i=0;i<adjacencyMatrix.size();i++)
    {
        int sum=0;
        for(int j=0;j<adjacencyMatrix.at(i).size();j++)
        {
            if(i==j)continue;
            sum+=adjacencyMatrix.at(i).at(j);
        }
        map.insert(sum,i);
    }

    QList<int> temp;
    int currentPriority= map.begin().key();
    for(auto item :map)
    {
        if(map.key(item)!=currentPriority)
        {
            currentPriority=map.key(item);
            list.prepend(temp);
            temp.clear();
        }
        temp.prepend(item);
    }
    list.prepend(temp);

    return list;
}
