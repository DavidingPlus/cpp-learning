#include <vector>
#include <iostream>
using namespace std;

//ÈÝÆ÷Ç¶Ì×ÈÝÆ÷
void test01()
{

    vector<vector<int>> v;

    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;

    for (int i = 0; i < 4; i++)
    {
        v1.push_back(i + 1);
        v2.push_back(i + 2);
        v3.push_back(i + 3);
        v4.push_back(i + 4);
    }

    //½«ÈÝÆ÷ÔªËØ²åÈëµ½vector vÖÐ
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);

    for (vector<vector<int>>::iterator iter = v.begin(); iter < v.end(); iter++)
    {
        for (vector<int>::iterator iter2 = iter->begin(); iter2 < iter->end(); iter2++)
            cout << *iter2 << ' ';
        cout << endl;
    }
}

int main()
{
    test01();

    return 0;
}
