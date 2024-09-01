#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Test{
    public:
        int a = 0;
        int b = 1;
        string name;

        Test(int a, int b) {
            this->a = a;
            this->b = b;
        };

        bool operator==(Test t){
            return t.a == this->a && t.b == this->b;
        }

        
};

string to_string(Test t){ return to_string(t.a) + " - " + to_string(t.b);}

int main(){
    Test ab(1, 2);
    Test ab2(1, 2);
    cout << (ab == ab2 ? "funfa" : "N funfa") << endl ;
    // testar vetor
    vector<Test> v1{ab, ab2};
    vector<Test> v2{ab, Test(32, 2)};
    pair<vector<Test>::iterator, vector<Test>::iterator> p = mismatch(v1.begin(), v1.end(), v2.begin());
    cout << (p.first == v1.end() ? "sem diferenca" : "diferente") << endl;
    return 0;
}