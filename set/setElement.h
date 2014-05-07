#pragma once

#include <set>
#include <vector>
//#include <utility>

using namespace std;

enum MarkType
{
    ELE_STRING, ELE_PAIR, ELE_SET
};

class CSetElement;

typedef set<CSetElement> MySet;
typedef set<CSetElement>::iterator SetIter;
//typedef pair<CSetElement, CSetElement> MyPair;
typedef vector<CSetElement> MyPair;

//集合元素类，集合元素可为普通元素、有序对、集合
//所有的集合，都被视作一个类型为集合的集合元素存在
class CSetElement
{
public:
    CSetElement();
    CSetElement(const MarkType &tMark);
    CSetElement(const CSetElement &tEle);
    CSetElement(const CString &tString);
    CSetElement(const MyPair &tPair);
    CSetElement(const MySet &tSet);
    ~CSetElement();

    CSetElement & operator=(const CSetElement &tEle);

    friend bool operator==(const CSetElement &eleA, const CSetElement &eleB);
    friend bool operator!=(const CSetElement &eleA, const CSetElement &eleB);
    friend bool operator<(const CSetElement &eleA, const CSetElement &eleB);
    friend bool operator>(const CSetElement &eleA, const CSetElement &eleB);

    MarkType GetMark(void) const;
    CString GetEleString(void) const;
    MyPair GetElePair(void) const;
    MySet GetEleSet(void) const;
    void SetMark(const MarkType &tMark);
    void SetEleString(const CString &tString);
    void SetElePair(const MyPair &tPair);
    void SetEleSet(const MySet &tSet);

    bool IsSet(void) const;//判断是否为集合
    bool IsRelation(void) const;//判断是否为二元关系
    bool IsReflexiveRelation(const MySet &rangeSet) const;//判断是否为自反关系
    bool IsSymmetricRelation(void) const;//判断是否为对称关系
    bool IsTransitiveRelation(void) const;//判断是否为传递关系
    bool IsEquivalenceRelation(const MySet &rangeSet) const;//判断是否为等价关系

    CSetElement GetOppositePair(void) const;//返回逆有序对，即对于<x,y>，返回<y,x>

    bool SetUnion(const CSetElement &eleA, const CSetElement &eleB);//集合并
    bool SetIntersection(const CSetElement &eleA, const CSetElement &eleB);//集合交
    bool SetDifference(const CSetElement &eleA, const CSetElement &eleB);//集合相对补
    bool SetSymmetricDifference(const CSetElement &eleA, const CSetElement &eleB);//集合对称差
    bool SetDescartes(const CSetElement &eleA, const CSetElement &eleB);//笛卡尔积
    bool SetCompound(const CSetElement &eleA, const CSetElement &eleB);//二元关系右复合
    bool SetQuotient(const CSetElement &eleA, const CSetElement &eleB);//商集
    bool SetLimit(const CSetElement &eleA, const CSetElement &eleB);//关系在集合上的限制
    bool SetPowerSet(const CSetElement &eleA);//幂集
    bool SetReflexiveClosure(const CSetElement &eleA, const CSetElement &eleB);//自反闭包
    bool SetSymmetricClosure(const CSetElement &eleA);//对称闭包
    bool SetTransitiveClosure(const CSetElement &eleA);//传递闭包
    bool SetDomain(const CSetElement &eleA);//集合的定义域
    bool SetRange(const CSetElement &eleA);//集合的值域
    bool SetField(const CSetElement &eleA);//集合的域
    bool SetReverse(const CSetElement &eleA);//关系的逆
    bool SetQuickPower(CSetElement eleA, int n);//关系的n次幂（快速幂）
    bool SetMapping(const CSetElement &eleA, const CSetElement &eleB);//求B上A
    bool SetEquivalenceClass(const CSetElement &eleA, const CSetElement &eleB, const MySet &rangeSet);//等价类
    bool SetGenUnion(const CSetElement &eleA);//广义并
    bool SetGenIntersection(const CSetElement &eleB);//广义交

private:
    MarkType mark;
    CString dataString;
    MyPair dataPair;
    MySet dataSet;

    void SubSetDfs(MySet &subSet, SetIter &iter, const SetIter &endIter);//递归生成所有子集
    void SetMappingDfs(MySet &subMapping, SetIter &iter, const SetIter &endIter, const CSetElement &eleB);//递归生成所有A到B的函数
};
