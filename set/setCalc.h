#pragma once

//定义符号表
//备用符号: ╳×°─
const CString OP_TABLE = _T("${}<>,[]()∪∩|&⊕#-×*○.Ф/「@~^∨∧?｛｝《》，【】（）。？");
const int OP_TABLE_LENGTH = OP_TABLE.GetLength();
const TCHAR OP_CUT_OFF = OP_TABLE[0];//分隔符
const TCHAR OP_LEFT_BRACE = OP_TABLE[1];//左大括号
const TCHAR OP_RIGHT_BRACE = OP_TABLE[2];//右大括号
const TCHAR OP_LEFT_ANGLE_BKT = OP_TABLE[3];//左尖括号
const TCHAR OP_RIGHT_ANGLE_BKT = OP_TABLE[4];//右尖括号
const TCHAR OP_COMMA = OP_TABLE[5];//逗号
const TCHAR OP_LEFT_BRACKET = OP_TABLE[6];//左方括号
const TCHAR OP_RIGHT_BRACKET = OP_TABLE[7];//右方括号
const TCHAR OP_LEFT_PARENTHESIS = OP_TABLE[8];//左小括号
const TCHAR OP_RIGHT_PARENTHESIS = OP_TABLE[9];//右小括号
const TCHAR OP_UNION = OP_TABLE[10];//集合并
const TCHAR OP_INTERSECTION = OP_TABLE[11];//集合交
const TCHAR OP_INPUT_UNION = OP_TABLE[12];//集合并的输入代替
const TCHAR OP_INPUT_INTERSECTION = OP_TABLE[13];//集合交的输入代替
const TCHAR OP_SYMMETRIC_DIFFERENCE = OP_TABLE[14];//集合对称差
const TCHAR OP_INPUT_SYM_DIFFERENCE = OP_TABLE[15];//集合对称差的输入代替
const TCHAR OP_DIFFERENCE = OP_TABLE[16];//集合相对补
const TCHAR OP_DESCARTES = OP_TABLE[17];//笛卡尔积
const TCHAR OP_INPUT_DESCARTES = OP_TABLE[18];//笛卡尔积的输入代替
const TCHAR OP_COMPOUND = OP_TABLE[19];//二元关系右复合
const TCHAR OP_INPUT_COMPOUND = OP_TABLE[20];//二元关系右复合的输入代替
const TCHAR OP_EMPTY_SET = OP_TABLE[21];//空集符号
const TCHAR OP_QUOTIENT = OP_TABLE[22];//商集
const TCHAR OP_LIMIT = OP_TABLE[23];//关系在集合上的限制
const TCHAR OP_INPUT_LIMIT = OP_TABLE[24];//关系在集合上的限制的输入代替
const TCHAR OP_NEGATIVE = OP_TABLE[25];//集合的绝对补集
const TCHAR OP_POWER = OP_TABLE[26];//次方符号
const TCHAR OP_REG_GEN_UNION = OP_TABLE[27];//广义并（存储时使用，与并区别）
const TCHAR OP_REG_GEN_INTERSECTION = OP_TABLE[28];//广义交（存储时使用，与交区别）
const TCHAR OP_INPUT_EMPTY_SET = OP_TABLE[29];//空集符号的输入代替
//const TCHAR OP_DIFFERENCE = OP_TABLE[30];//集合相对补
const TCHAR OP_FULL_LEFT_BRACE = OP_TABLE[30];//左大括号(全角)
const TCHAR OP_FULL_RIGHT_BRACE = OP_TABLE[31];//右大括号(全角)
const TCHAR OP_FULL_LEFT_ANGLE_BKT = OP_TABLE[32];//左尖括号(全角)
const TCHAR OP_FULL_RIGHT_ANGLE_BKT = OP_TABLE[33];//右尖括号(全角)
const TCHAR OP_FULL_COMMA = OP_TABLE[34];//逗号(全角)
const TCHAR OP_FULL_LEFT_BRACKET = OP_TABLE[35];//左方括号(全角)
const TCHAR OP_FULL_RIGHT_BRACKET = OP_TABLE[36];//右方括号(全角)
const TCHAR OP_FULL_LEFT_PARENTHESIS = OP_TABLE[37];//左小括号(全角)
const TCHAR OP_FULL_RIGHT_PARENTHESIS = OP_TABLE[38];//右小括号(全角)
const TCHAR OP_FULL_COMPOUND = OP_TABLE[39];//二元关系右复合(全角)
const TCHAR OP_FULL_EMPTY_SET = OP_TABLE[40];//空集符号(全角)

const TCHAR OP_POWER_SET = TCHAR('P');//幂集
const TCHAR OP_REFLEXIVE_CLOSURE = TCHAR('r');//自反闭包
const TCHAR OP_SYMMETRIC_CLOSURE = TCHAR('s');//对称闭包
const TCHAR OP_TRANSITIVE_CLOSURE = TCHAR('t');//传递闭包

const CString OP_DOMAIN = _T("dom");//关系的定义域
const CString OP_RANGE = _T("ran");//关系的值域
const CString OP_FIELD = _T("fld");//关系的域

//定义运算符优先级
const int PRI_CUT_OFF = 0;//分隔符
const int PRI_UNION = 10;//集合并
const int PRI_INTERSECTION = 10;//集合交
const int PRI_DIFFERENCE = 10;//集合相对补
const int PRI_SYMMETRIC_DIFFERENCE = 10;//集合对称差
const int PRI_DESCARTES = 20;//笛卡尔积
const int PRI_COMPOUND = 30;//二元关系右复合
const int PRI_QUOTIENT = 15;//商集
const int PRI_LIMIT = 15;//关系在集合上的限制
const int PRI_NEGATIVE = 50;//集合的绝对补集
const int PRI_POWER_SET = 50;//幂集
const int PRI_REFLEXIVE_CLOSURE = 50;//自反闭包
const int PRI_SYMMETRIC_CLOSURE = 50;//对称闭包
const int PRI_TRANSITIVE_CLOSURE = 50;//传递闭包
const int PRI_DOMAIN = 50;//关系的定义域
const int PRI_RANGE = 50;//关系的值域
const int PRI_FIELD = 50;//关系的域
const int PRI_POWER = 60;//次方符号
const int PRI_LEFT_BRACKET = 50;//R[A]
const int PRI_RIGHT_BRACKET = 50;//[x]R
const int PRI_GEN_UNION = 50;//广义并
const int PRI_GEN_INTERSECTION = 50;//广义交

bool CalcExpression(CString sInput, CString &sResult, const TCHAR &cChoose);