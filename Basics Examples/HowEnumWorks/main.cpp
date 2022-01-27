#include <iostream>

using namespace std;

class MClass
{
public:
    MClass(){}
    enum MEnum
    {
        one=1,two=2,three=4,four=8
    };
    MEnum menum;
    bool hasFlag(MEnum flags,MEnum flag)
    {
        return flags & flag;
    }
};

int main()
{
    MClass mobj;
    mobj.menum = MClass::MEnum(
                MClass::MEnum::one | MClass::MEnum::two |
                 MClass::MEnum::four);
    cout<<mobj.menum<<"\n";
    cout<<mobj.hasFlag(mobj.menum ,MClass::MEnum::three)<<"\n";
}
