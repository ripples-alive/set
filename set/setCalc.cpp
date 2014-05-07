#include "stdafx.h"

#include <stack>

#include "setCalc.h"
#include "setElement.h"

static stack<CSetElement> eleStack;
static stack<TCHAR> opStack;
static vector<CSetElement> varSet(26, CSetElement(ELE_SET));

//判断是否不可能为一个集合的开始字符
//inline static bool IsNotEleBegin(const TCHAR &c)
//{
//    return IsBinocularOperator(c) || (c == OP_RIGHT_BRACE) || (c == OP_RIGHT_PARENTHESIS)
//        || (c == OP_RIGHT_BRACKET);
//}

//判断是否是数字
inline static bool IsNumber(const TCHAR &c)
{
    return (c >= '0') && (c <= '9');
}

//判断是否为~A
inline static bool IsUnaryOperator1(const TCHAR &c)
{
    return c == OP_NEGATIVE;
}

//判断是否为P(A),r(R),s(R),t(R)
inline static bool IsUnaryOperator2(const TCHAR &c)
{
    return (c == OP_POWER_SET) || (c == OP_REFLEXIVE_CLOSURE) 
        || (c == OP_SYMMETRIC_CLOSURE) || (c == OP_TRANSITIVE_CLOSURE);
}

//判断是否为domR,ranR,fldR
inline static bool IsUnaryOperator3(const CString &s)
{
    return (s == OP_DOMAIN) || (s == OP_RANGE) || (s == OP_FIELD);
}

//判断是否为双目运算符
inline static bool IsBinocularOperator(const TCHAR &c)
{
    return (c == OP_UNION) || (c == OP_INTERSECTION) || (c == OP_DIFFERENCE) 
        || (c == OP_SYMMETRIC_DIFFERENCE) || (c == OP_DESCARTES)
        || (c == OP_COMPOUND) || (c == OP_QUOTIENT) || (c == OP_LIMIT);
}

//判断是否为运算符
inline static bool IsOperator(const TCHAR &c)
{
    for (int i = 0; i < OP_TABLE_LENGTH; i++)
    {
        if (c == OP_TABLE[i])
        {
            return true;
        }
    }
    return false;
}

//判断是否为集合变量
inline static bool IsVariable(const TCHAR &c)
{
    return (c >= TCHAR('A')) && (c <= TCHAR('Z'));
}

//判断是否可能为一个集合的结束字符
inline static bool IsEleEnd(const TCHAR &c)
{
    return IsVariable(c) || IsNumber(c) || (c == OP_EMPTY_SET) || (c == OP_RIGHT_BRACE) 
        || (c == OP_RIGHT_PARENTHESIS) || (c == OP_RIGHT_BRACKET);
}

inline static int GetPriority(const TCHAR &c)
{
    //分隔符
    if (c == OP_CUT_OFF)
    {
        return PRI_CUT_OFF;
    }
    //集合并
    else if (c == OP_UNION)
    {
        return PRI_UNION;
    }
    //集合交
    else if (c == OP_INTERSECTION)
    {
        return PRI_INTERSECTION;
    }
    //集合相对补
    else if (c == OP_DIFFERENCE)
    {
        return PRI_DIFFERENCE;
    }
    //集合对称差
    else if (c == OP_SYMMETRIC_DIFFERENCE)
    {
        return PRI_SYMMETRIC_DIFFERENCE;
    }
    //笛卡尔积
    else if (c == OP_DESCARTES)
    {
        return PRI_DESCARTES;
    }
    //二元关系右复合
    else if (c == OP_COMPOUND)
    {
        return PRI_COMPOUND;
    }
    //商集
    else if (c == OP_QUOTIENT)
    {
        return PRI_QUOTIENT;
    }
    //关系在集合上的限制
    else if (c == OP_LIMIT)
    {
        return PRI_LIMIT;
    }
    //集合的绝对补集
    else if (c == OP_NEGATIVE)
    {
        return PRI_NEGATIVE;
    }
    //幂集
    else if (c == OP_POWER_SET)
    {
        return PRI_POWER_SET;
    }
    //自反闭包
    else if (c == OP_REFLEXIVE_CLOSURE)
    {
        return PRI_REFLEXIVE_CLOSURE;
    }
    //对称闭包
    else if (c == OP_SYMMETRIC_CLOSURE)
    {
        return PRI_SYMMETRIC_CLOSURE;
    }
    //传递闭包
    else if (c == OP_TRANSITIVE_CLOSURE)
    {
        return PRI_TRANSITIVE_CLOSURE;
    }
    //关系的定义域
    else if (c == OP_DOMAIN[2])
    {
        return PRI_DOMAIN;
    }
    //关系的值域
    else if (c == OP_RANGE[2])
    {
        return PRI_RANGE;
    }
    //关系的域
    else if (c == OP_FIELD[2])
    {
        return PRI_FIELD;
    }
    //次方符号
    else if (c == OP_POWER)
    {
        return PRI_POWER;
    }
    //R[A]
    else if (c == OP_LEFT_BRACKET)
    {
        return PRI_LEFT_BRACKET;
    }
    //[x]R
    else if (c == OP_RIGHT_BRACKET)
    {
        return PRI_RIGHT_BRACKET;
    }
    //广义并
    else if (c == OP_REG_GEN_UNION)
    {
        return PRI_GEN_UNION;
    }
    //广义交
    else if (c == OP_REG_GEN_INTERSECTION)
    {
        return PRI_GEN_INTERSECTION;
    }
    return -1;
}

inline static bool CmpPriority(const TCHAR &c1, const TCHAR &c2)
{
    return GetPriority(c1) <= GetPriority(c2);
}

//利用栈顶运算符进行一次运算
static bool CalcOnce(void)
{
    if (eleStack.empty())
    {
        return false;
    }
    TCHAR op = opStack.top();
    opStack.pop();
    //集合并
    if (op == OP_UNION)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetUnion(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //集合交
    else if (op == OP_INTERSECTION)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetIntersection(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //集合相对补
    else if (op == OP_DIFFERENCE)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetDifference(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //集合对称差
    else if (op == OP_SYMMETRIC_DIFFERENCE)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetSymmetricDifference(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //笛卡尔积
    else if (op == OP_DESCARTES)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetDescartes(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //二元关系右复合
    else if (op == OP_COMPOUND)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetCompound(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //商集
    else if (op == OP_QUOTIENT)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetQuotient(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //关系在集合上的限制
    else if (op == OP_LIMIT)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetLimit(eleA, eleB))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //B上A
    else if (op == OP_POWER)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetMapping(eleB, eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //处理R[A]
    else if (op == OP_LEFT_BRACKET)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetLimit(eleA, eleB))
        {
            return false;
        }
        if (!eleB.SetRange(eleC))
        {
            return false;
        }
        eleStack.push(eleB);
    }
    //处理[x]R
    else if (op == OP_RIGHT_BRACKET)
    {
        CSetElement eleB = eleStack.top();
        eleStack.pop();
        if (eleStack.empty())
        {
            return false;
        }
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetEquivalenceClass(eleA, eleB, varSet[TCHAR('E') - TCHAR('A')].GetEleSet()))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //集合的绝对补集
    else if (op == OP_NEGATIVE)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetDifference(varSet[TCHAR('E') - TCHAR('A')], eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //幂集
    else if (op == OP_POWER_SET)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetPowerSet(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //自反闭包
    else if (op == OP_REFLEXIVE_CLOSURE)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetReflexiveClosure(eleA, varSet[0]))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //对称闭包
    else if (op == OP_SYMMETRIC_CLOSURE)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetSymmetricClosure(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //传递闭包
    else if (op == OP_TRANSITIVE_CLOSURE)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetTransitiveClosure(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //关系的定义域
    else if (op == OP_DOMAIN[2])
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetDomain(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //关系的值域
    else if (op == OP_RANGE[2])
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetRange(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //关系的域
    else if (op == OP_FIELD[2])
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetField(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //广义并
    else if (op == OP_REG_GEN_UNION)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetGenUnion(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    //广义交
    else if (op == OP_REG_GEN_INTERSECTION)
    {
        CSetElement eleA = eleStack.top();
        eleStack.pop();
        CSetElement eleC;
        if (!eleC.SetGenIntersection(eleA))
        {
            return false;
        }
        eleStack.push(eleC);
    }
    return true;
}

//判断表达式括号是否匹配
static bool IsBracketMatch(const CString &sInput)
{
    stack<TCHAR> bracketStack;
    bracketStack.push(OP_CUT_OFF);
    for (int i = 0; i < sInput.GetLength(); i++)
    {
        const TCHAR &c = sInput[i];
        if ((c == OP_LEFT_PARENTHESIS) || (c == OP_LEFT_BRACE)
            || (c == OP_LEFT_BRACKET) || (c == OP_LEFT_ANGLE_BKT))
        {
            bracketStack.push(c);
        }
        else if (c == OP_RIGHT_PARENTHESIS)
        {
            if (bracketStack.top() != OP_LEFT_PARENTHESIS)
            {
                return false;
            }
            bracketStack.pop();
        }
        else if (c == OP_RIGHT_BRACE)
        {
            if (bracketStack.top() != OP_LEFT_BRACE)
            {
                return false;
            }
            bracketStack.pop();
        }
        else if (c == OP_RIGHT_BRACKET)
        {
            if (bracketStack.top() != OP_LEFT_BRACKET)
            {
                return false;
            }
            bracketStack.pop();
        }
        else if (c == OP_RIGHT_ANGLE_BKT)
        {
            if (bracketStack.top() != OP_LEFT_ANGLE_BKT)
            {
                return false;
            }
            bracketStack.pop();
        }
    }
    return bracketStack.top() == OP_CUT_OFF;
}

//运算符进栈（同时计算栈顶可以计算的运算符）
static bool CalcAndPush(const TCHAR &c)
{
    while (CmpPriority(c, opStack.top()))
    {
        if (!CalcOnce())
        {
            return false;
        }
    }
    opStack.push(c);
    return true;
}

//处理表达式
static bool DealInput(const CString &sInput, int &pos)
{
    int inEleStackSize = eleStack.size();

    opStack.push(OP_CUT_OFF);
    while ((sInput[pos] != OP_COMMA) && (sInput[pos] != OP_RIGHT_BRACE) 
        && (sInput[pos] != OP_RIGHT_ANGLE_BKT) && (sInput[pos] != OP_RIGHT_PARENTHESIS)
        && (sInput[pos] != OP_CUT_OFF) && (sInput[pos] != OP_RIGHT_BRACKET))
    {
        //处理为集合的情况
        if (sInput[pos] == OP_LEFT_BRACE)
        {
            MySet inputSet;
            pos++;
            if (sInput[pos] != OP_RIGHT_BRACE)
            {
                while (true)
                {
                    if (!DealInput(sInput, pos))
                    {
                        return false;
                    }
                    inputSet.insert(eleStack.top());
                    eleStack.pop();

                    if (sInput[pos] == OP_RIGHT_BRACE)
                    {
                        break;
                    }
                    else if (sInput[pos] == OP_COMMA)
                    {
                        pos++;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            pos++;

            eleStack.push(CSetElement(inputSet));
        }
        //处理为有序对的情况
        else if (sInput[pos] == OP_LEFT_ANGLE_BKT)
        {
            MyPair inputPair;

            pos++;
            if (!DealInput(sInput, pos))
            {
                return false;
            }
            inputPair.push_back(eleStack.top());
            eleStack.pop();

            if (sInput[pos] != OP_COMMA)
            {
                return false;
            }
            pos++;
            if(!DealInput(sInput, pos))
            {
                return false;
            }
            inputPair.push_back(eleStack.top());
            eleStack.pop();

            if (sInput[pos] != OP_RIGHT_ANGLE_BKT)
            {
                return false;
            }
            pos++;

            eleStack.push(CSetElement(inputPair));
        }
        //处理为(的情况
        else if (sInput[pos] == OP_LEFT_PARENTHESIS)
        {
            pos++;
            if (!DealInput(sInput, pos))
            {
                return false;
            }
            if (sInput[pos] != OP_RIGHT_PARENTHESIS)
            {
                return false;
            }
            pos++;
        }
        //处理为空集Ф的情况
        else if (sInput[pos] == OP_EMPTY_SET)
        {
            eleStack.push(CSetElement(ELE_SET));
            pos++;
        }
        //处理关系的逆
        else if ((sInput[pos] == OP_POWER) && (sInput[pos + 1] == TCHAR('-'))
            && (sInput[pos + 2] == TCHAR('1')))
        {
            CSetElement eleA = eleStack.top();
            eleStack.pop();
            CSetElement eleC;
            if (!eleC.SetReverse(eleA))
            {
                return false;
            }
            eleStack.push(eleC);
            pos += 3;
        }
        //处理关系的n次幂
        else if ((sInput[pos] == OP_POWER) && IsNumber(sInput[pos + 1]))
        {
            int n = 0;
            while (IsNumber(sInput[++pos]))
            {
                n = n * 10 + (int)(sInput[pos] - TCHAR('0'));
            }
            CSetElement eleA = eleStack.top();
            eleStack.pop();
            CSetElement eleC;
            if (!eleC.SetQuickPower(eleA, n))
            {
                return false;
            }
            eleStack.push(eleC);
        }
        //处理为B上A的情况
        else if (sInput[pos] == OP_POWER)
        {
            if ((sInput[pos + 1] != OP_UNION) && (sInput[pos + 1] != OP_INTERSECTION) 
                && IsBinocularOperator(sInput[pos + 1]))
            {
                return false;
            }
            opStack.push(sInput[pos++]);
        }
        //处理R[A]和[x]R
        else if (sInput[pos] == OP_LEFT_BRACKET)
        {
            bool flag = (pos > 0) && IsEleEnd(sInput[pos - 1]);
            if (flag)
            {
                if (!CalcAndPush(sInput[pos]))
                {
                    return false;
                }
            }
            if (!DealInput(sInput, ++pos))
            {
                return false;
            }
            if (sInput[pos] != OP_RIGHT_BRACKET)
            {
                return false;
            }
            if (!flag)
            {
                if (!CalcAndPush(sInput[pos]))
                {
                    return false;
                }
            }
            pos++;
        }
        //处理为广义并的情况
        else if ((sInput[pos] == OP_UNION) && ((pos == 0) || !IsEleEnd(sInput[pos - 1])))
        {
            opStack.push(OP_REG_GEN_UNION);
            pos++;
        }
        //处理为广义交的情况
        else if ((sInput[pos] == OP_INTERSECTION) && ((pos == 0) || !IsEleEnd(sInput[pos - 1])))
        {
            opStack.push(OP_REG_GEN_INTERSECTION);
            pos++;
        }
        //处理为双目运算符的情况
        else if (IsBinocularOperator(sInput[pos]))
        {
            if ((sInput[pos + 1] != OP_UNION) && (sInput[pos + 1] != OP_INTERSECTION) 
                && IsBinocularOperator(sInput[pos + 1]))
            {
                return false;
            }
            if (!CalcAndPush(sInput[pos++]))
            {
                return false;
            }
        }
        //处理为~的情况
        else if (IsUnaryOperator1(sInput[pos]))
        {
            opStack.push(sInput[pos++]);
        }
        //处理为P(A),r(R),s(R),t(R)的情况
        else if (IsUnaryOperator2(sInput[pos]) && (sInput[pos + 1] == OP_LEFT_PARENTHESIS))
        {
            opStack.push(sInput[pos++]);
        }
        //处理为domR,ranR,fldR的情况
        else if ((pos + 2 < sInput.GetLength()) && IsUnaryOperator3(sInput.Mid(pos, 3))
            && ((sInput[pos + 3] == OP_LEFT_PARENTHESIS) || (sInput[pos + 3] == OP_LEFT_BRACE)
            || (sInput[pos + 3] == OP_EMPTY_SET) || (IsVariable(sInput[pos + 3]) && IsOperator(sInput[pos + 4]))))
        {
            opStack.push(sInput[pos + 2]);
            pos += 3;
        }
        //处理为集合变量的情况
        else if (IsVariable(sInput[pos]) && IsOperator(sInput[pos + 1]))
        {
            eleStack.push(varSet[sInput[pos++] - TCHAR('A')]);
        }
        //处理为普通元素的情况
        else if (!IsOperator(sInput[pos]))
        {
            int i;
            for (i = pos + 1; !IsOperator(sInput[i]); i++)
            {
            }

            eleStack.push(CSetElement(sInput.Mid(pos, i - pos)));
            pos = i;
        }
        else
        {
            return false;
        }
    }

    while (opStack.top() != OP_CUT_OFF)
    {
        if (!CalcOnce())
        {
            return false;
        }
    }
    opStack.pop();

    return eleStack.size() == inEleStackSize + 1;
}

//将集合输出到字符串sResult
static void OutputElement(const CSetElement &outEle, CString &sResult)
{
    if (outEle.GetMark() == ELE_STRING)
    {
        sResult += outEle.GetEleString();
    }
    else if (outEle.GetMark() == ELE_PAIR)
    {
        MyPair outPair = outEle.GetElePair();
        sResult += OP_LEFT_ANGLE_BKT;
        OutputElement(outPair[0], sResult);
        sResult += OP_COMMA;
        OutputElement(outPair[1], sResult);
        sResult += OP_RIGHT_ANGLE_BKT;
    }
    else //if (outEle.GetMark() == ELE_SET)
    {
        MySet outSet = outEle.GetEleSet();
        if (outSet.empty())
        {
            sResult += OP_EMPTY_SET;
        } 
        else
        {
            sResult += OP_LEFT_BRACE;
            for (SetIter iter = outSet.begin(); iter != outSet.end(); iter++)
            {
                if (iter != outSet.begin())
                {
                    sResult += OP_COMMA;
                }
                OutputElement(*iter, sResult);
            }
            sResult += OP_RIGHT_BRACE;
        }
    }
}

//计算集合表达式对外的接口
bool CalcExpression(CString sInput, CString &sResult, const TCHAR &cChoose)
{
    //初始化栈
    while (!eleStack.empty())
    {
        eleStack.pop();
    }
    while (!opStack.empty())
    {
        opStack.pop();
    }

    //计算表达式
    int pos = 0;
    sInput += OP_CUT_OFF;
    if (!IsBracketMatch(sInput) || !DealInput(sInput, pos) || (pos < sInput.GetLength() - 1))
    {
        return false;
    }

    varSet[cChoose - TCHAR('A')] = eleStack.top();

    //将结果转换成字符串
    sResult = "";
    OutputElement(eleStack.top(), sResult);

    return true;
}
