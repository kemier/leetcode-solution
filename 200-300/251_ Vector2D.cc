#include <vector>

using namespace std;

class Vector2D
{
public:
    vector<vector<int>>::iterator outerIter;
    vector<vector<int>>::iterator outerEnd;
    vector<int>::iterator innerIter;

    Vector2D(vector<vector<int>> &v)
    {
        //因为第一个next要返回第一个元素，所以只能在一开始添加一个工具dummy元素
        v.insert(v.begin(), vector<int>(1, 0));
        outerEnd = v.end();
        outerIter = v.begin();
        innerIter = v[0].begin();
    }

    int next()
    {
        ++innerIter;
        //直到找到一个非空vector为止
        while (innerIter == outerIter->end())
        {
            ++outerIter;
            innerIter = outerIter->begin();
        }
        return (*innerIter);
    }

    bool hasNext()
    {
        auto tempInner = innerIter;
        auto tempOuter = outerIter;

        ++tempInner;
        if (tempInner != outerIter->end())
            return true; //如果直接在第二维找到

        ++tempOuter;
        if (tempOuter == outerEnd)
            return false; //第一维已经搜索完还没有搜索到，失败
        tempInner = tempOuter->begin();

        while (tempInner == tempOuter->end())
        { //如果第二维的vector为空，持续搜索
            ++tempOuter;
            if (tempOuter == outerEnd)
                return false;
            tempInner = tempOuter->begin();
        }

        if (tempInner != tempOuter->end())
            return true; //最后检查第二维的vector是不是空的
        return true;
    }
};
