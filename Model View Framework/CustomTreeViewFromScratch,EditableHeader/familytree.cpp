#include "familytree.h"

FamilyTree:: FamilyTree(const QVariant & Value, FamilyTree * parentNode ,QObject * parent ): QObject(parent)
{
   name = Value;
   this->parent=parentNode;
}

FamilyTree::~FamilyTree()
{
//   if(ChildrenNodes.isEmpty()==false)
//   {
//       for(int i=0;i<ChildrenNodes.size();i++)
//           delete  ChildrenNodes.at(i);  // its automatically calls destructor before delete
//   }
//  qDebug()<<name<<" deleted ";
  //or
  qDeleteAll(ChildrenNodes);
  qDebug()<<name<<" deleted ";
}

FamilyTree * FamilyTree::Parent()const
{
    return this->parent;
}

QVector<FamilyTree*> FamilyTree::getChildrens()const
{
   return ChildrenNodes;
}

void FamilyTree::setData(const QVariant & value)
{
   name=value;
}

QVariant FamilyTree::data()const
{
   return name;
}

void FamilyTree::addChild(const QVariant &value)
{
   ChildrenNodes.append(new FamilyTree(value,this));
}

void FamilyTree::addChildrens(QVector<QVariant> datalist )
{
    for(int i=0;i<datalist.size();i++)
     ChildrenNodes.append( new FamilyTree(datalist.at(i),this));
}

void FamilyTree::removeChild(int row)
{
    if(row>=0 && row<ChildrenNodes.size())
        ChildrenNodes.removeAt(row);
}

void FamilyTree::removeChildrens(QVector<int> rowList)
{
    for(int i=0;i<rowList.size();i++)
    {
        if(rowList.at(i)>=0 && rowList.at(i)<ChildrenNodes.size())
           ChildrenNodes.removeAt(rowList.at(i));
    }
}

bool FamilyTree::hasChildern()const
{
    if(ChildrenNodes.isEmpty()) return  false;
    else return true;
}

int FamilyTree::rowCount() const
{
  return ChildrenNodes.size();
}

int FamilyTree::row() const
{
   if(parent==nullptr)return -1;
   return parent->ChildrenNodes.indexOf(const_cast<FamilyTree*>(this));
}

FamilyTree *FamilyTree::childAt(int row) const
{
    if(row<ChildrenNodes.size() && row>=0)
        return ChildrenNodes.at(row);
    else return nullptr;
}
