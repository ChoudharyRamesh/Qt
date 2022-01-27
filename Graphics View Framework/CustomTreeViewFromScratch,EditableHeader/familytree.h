#ifndef FAMILYTREE_H
#define FAMILYTREE_H
#include<QString>
#include<QObject>
#include<QVariant>
#include<QDebug>

class FamilyTree : public QObject
{
    Q_OBJECT
 // you can use QStandardItem class to make you item class more easier
public:
    explicit FamilyTree(const QVariant & rootFamilyTreeValue \
                        =QVariant(),FamilyTree * parentNode =nullptr ,QObject * parent=nullptr);
    void setData(const QVariant & data );
    QVariant data()const;
    void addChild(const QVariant & data);
    void addChildrens(QVector<QVariant> datalist);
    void removeChild(int row);
    void removeChildrens(QVector<int> rowList);
    bool hasChildern()const ;
    int rowCount()const;
    int row()const;
    FamilyTree * Parent()const;
    QVector <FamilyTree*> getChildrens()const;
    FamilyTree * childAt(int row) const;
    ~FamilyTree();

private:
    QVariant name;
    QVector<FamilyTree * > ChildrenNodes;
    FamilyTree * parent;
};

#endif // FAMILYTREE_H
