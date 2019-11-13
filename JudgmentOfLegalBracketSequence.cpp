/*
对于一个字符串，请设计一个算法，判断其是否为一个合法的括号串。

给定一个字符串A和它的长度n，请返回一个bool值代表它是否为一个合法的括号串。

测试样例：
"(()())",6
返回：true
测试样例：
"()a()()",7
返回：false
测试样例：
"()(()()",7
返回：false
*/
class Parenthesis {
public:
    bool chkParenthesis(string A, int n) {
        // write code here
        if(n%2==1)//先排除奇数情况
            return false;
        stack<char> s1;
        for(int i=0;i<A.size();i++)
        {
            if(A[i]=='(')
                s1.push(A[i]);
            else if(A[i]==')')
            {
                if(s1.empty())
                    return false;
                s1.top();
            }
            else 
                return false;
        }
        if(s1.empty())
            return true;
    }
};