#include "customtreemodel.h"

CustomTreeModel::CustomTreeModel(QObject * parent ):QAbstractItemModel(parent)
{
    familyname<<"Samuel Grayson(Barber)"<<
                "Jeremy R. Ontiveros(Doctor)"<<
                "Timothy K. Howard(Party planner)"<<
                "Israel C. Rowe(Shop assistant)"<<
                "William S. Stlaurent(Professor)"<<
                "Eugene K. Kirk(Flower arranger)"<<
                "Michael M. Greene(Councillor)"<<
                "Don S. Elsass(Labourer)"<<
                "Nelson A. James(Domestic cleaner)"<<
                "Tyron M. Travis(Carpet fitter)"<<
                "Felipe J. Ramirez(Genealogist)"<<
                "Cameron E. Koehn(Cleric)"<<
                "John L. Rodriguez(Hairdresser)"<<
                "Jeff R. Olsen(Electrician)"<<
                "Robert K. Dansby(Gas fitter)"<<
                "Matthew C. Spence(Researcher)"<<
                "Clinton K. McCaleb(Plasterer)"<<
                "Marvin S. Gomez(Careers advisor)"<<
                "Joseph N. Nichols(Pharmacist)"<<
                "James S. Brazier(Museum Curator)"<<
                "John K. Jeter(Musician)"<<
                "Harry M. Forbes(Farmer)"<<
                "John A. Allen(Jockey)"<<
                "Jesse W. Joachim(Coastguard)"<<
                "Vince T. Delacruz(Engineer)"<<
                "Samuel B. Lopez (Librarian)"<<
                "Edward S. Shea(Health visitor)"<<
                "Reginald C. Smith (Sailor)"<<
                "Brian J. Oppenheim(Mechanic)"<<
                "Louis D. Hodges(Inventor)"<<
                "George L. Wolak(Carpenter)"<<
                "Kenneth L. Gonzalez(Fork-lift driver)"<<
                "Jeff C. Wolff(Gardener)"<<
                "Michael H. Pals(Diplomat)"<<
                "Eddie G. Calloway(Physiotherapist)"<<
                "Larry D. Monger(Governor)"<<
                "Nicholas M. Rembert(Chiropractor)"<<
                "Henry J. Skipworth (Financial advisor)";

    rootNode = new FamilyTree("Root");

    for(int i=0,j=0;i<familyname.size();i++,j++)
    {
        rootNode->addChild(familyname.at(i)); i++;
        for(int k=0;k<3 && i<familyname.size();k++,i++)
        {
            rootNode->childAt(j)->addChild(familyname.at(i));
        }
    }

    HeaderDataStorage<<"c1"<<"c2";

}
int CustomTreeModel::rowCount(const QModelIndex &parent) const
{
    //qDebug()<<"rowCount "<<parent<<","<<parent.isValid();
    // sapbse phle yh root se call  hogs fir child se ando so on
    // to jab rooot se call hoga to hum root wali rows ki value return karege nhi to us internal pointer ki
    FamilyTree * ParentNode;
    if(!parent.isValid())
        ParentNode = rootNode;
    else
        ParentNode = static_cast<FamilyTree*>(parent.internalPointer());
    return ParentNode->rowCount();
}

int CustomTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // qDebug()<<"columnCount "<<parent<<","<<parent.isValid();
    return 5;
}

QModelIndex CustomTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    /*
     * this function return the modelIndex under the parent at row and column
     * this function is binding all three parameters into one.
     * we need to check either these three property points any item in model or
     * not bcz index can be invalid when data is moved or deleted
 * */
    // qDebug()<<"Index "<<parent<<","<<parent.isValid();

    // has index function yh check karta hai ki model mai vo index exist karti hai ya nhi
    // Note::- keval index ko check karta hai ,usme data hai ya nhi usko nhi .
    // generally eis function ka use tab hota hai jab hum koi item delete kar dete hai or view
    // jab update hota hai to us index ko call karta hai but waha se item delete ho chuki hai to
    // hum view ko imaginary index send karte hai eis se view samaj jata hai
    // eis place se data move ya delete ho chuka hai
    if(hasIndex(row,column,parent)==false){return QModelIndex(); }


    // ab agar model mai vo index jo view mang raha hai to
    //hum us index ke parennt ko check karege
    // agar parent rootnode hai to hum uske hisaab se us item pe data attach karege
    // or agar child hai uske hisaab se
    FamilyTree * parentNode;
    if(parent.isValid()==false)
    {
        //first time yh chalege usek badd ....
        parentNode = rootNode;
    }
    else
    {
        // ... yh chalega or jab second time yh chalega to yh family ke rootNode
        // ko return karge jo ki humne first time mai createIndex method ke through
        // rootnode ko assign kiya tha ,same for second and third , and so on
        parentNode = static_cast<FamilyTree*>(parent.internalPointer());
    }

    FamilyTree * childNode = parentNode->childAt(row);
    if(childNode!=nullptr)
        return createIndex(row,column,childNode);  // this is were we assigning data to indexses
    else return QModelIndex();

}

QModelIndex CustomTreeModel::parent(const QModelIndex &child) const
{
    // this function return parent of model Index(item)
    /*
     * if child is invalid means first level data in model so simply return
     * root ( ModelIndex() ) as  a parent
  * */

    //qDebug()<<"parent "<<child<<","<<child.isValid();

    if(!child.isValid())  return QModelIndex();

    FamilyTree * childNode = static_cast<FamilyTree *>(child.internalPointer());
    FamilyTree * ParentNode = childNode->Parent();
    if(ParentNode==rootNode) return QModelIndex();
    else return createIndex(ParentNode->row(),0,ParentNode);
}



QVariant CustomTreeModel::data(const QModelIndex &index, int role) const
{
    //  qDebug()<<"data "<<index<<","<<index.isValid();

    if(!index.isValid()) return  QVariant();
    FamilyTree * Node = static_cast<FamilyTree*>(index.internalPointer());
    if(role==Qt::DisplayRole || role==Qt::EditRole)
    {
        return Node->data();
    }
    else return QVariant();
}

// for header

QVariant CustomTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole && role!=Qt::EditRole )  return QVariant();
    // above code is neccessary in order to build HeaderView
    //actuall code goes here
    if(orientation==Qt::Horizontal)
    {
        if(role==Qt::DisplayRole || role==Qt::EditRole)
        {
            if(HeaderDataStorage.size()>section)
                return QVariant(HeaderDataStorage.at(section));
        }
    }
    return QVariant();
}

bool CustomTreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(orientation==Qt::Horizontal)
    {
//        if(role==Qt::EditRole)
//        {  QInputDialog d;
//            d.setTextValue(HeaderDataStorage.at(section));
//            d.setLabelText("Header");
//            d.setWindowTitle("Input");
//            d.exec();
//            if(HeaderDataStorage.size()>section)
//                HeaderDataStorage[section]= d.textValue();
//        }
                if(role==Qt::EditRole)
                {
                    if(HeaderDataStorage.size()>section)
                        HeaderDataStorage[section]= value.toString();
                }
    }
    return QAbstractItemModel::setHeaderData(section,orientation,value,role);
}

Qt::ItemFlags CustomTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CustomTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid())
    {
        if(role==Qt::EditRole)
        {
            FamilyTree * temp = static_cast<FamilyTree *>(index.internalPointer());
            temp->setData(value);
            emit dataChanged(index,index);
            return true;
        }
        return true;
    }
    else return QAbstractItemModel::setData(index,value,role);
}
