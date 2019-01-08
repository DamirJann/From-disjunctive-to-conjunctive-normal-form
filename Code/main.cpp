#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
using namespace std;

void Print_expression(set<set<char>> & expression ){
    ofstream cout("..\\..\\output.txt");

    int cont1 = 1;
    for (auto it1 = expression.begin(); it1 != expression.end(); it1++, cont1++){
        int count = 1;
        for (auto it2 = (*it1).begin(); it2 != (*it1).end(); it2++, count++) {
            cout << (*it2);
            if (count != (*it1).size()){
                cout << "*";
            }
        }
        if (cont1 != expression.size()) {
            cout << "+";
        }
    }
    cout.close();
}


void Reduce_expression(set<set<char>> & expression ){

    vector<set<set<char>> :: iterator> v;

    for (auto it1 = expression.begin(); it1 != expression.end(); it1++){
        for (auto it2 = expression.begin(); it2 != expression.end(); it2++){
            if ((*it1).size() == (*it2).size() -1){
                bool flag = true;
                for (auto i = (*it1).begin(); i != (*it1).end(); i++){
                    if ((*it2).find((*i)) == (*it2).end()){
                        flag = false;
                    }
                }
                if (flag == true) {
                    flag = true;
                    for (int i = 0; i < v.size(); i++){
                        if (it2 == v[i]){
                            flag = false;
                        }
                    }
                    if (flag == true) {
                        v.push_back(it2);
                    }
                }
            }
        }
    }
    for (int i = 0; i < v.size(); i++)
        expression.erase(v[i]);

}

int main(){

    ifstream cin("..\\..\\input.txt");
    char a, b;


    cin.ignore(1);
    cin >> a;
    cin.ignore(1);
    cin >> b;
    cin.ignore(2);

    set<set<char>> expression = {{a}, {b}};

    while(cin){
        char operand1, operand2;

        cin.ignore(1);
        cin >> operand1;
        cin.ignore(1);
        cin >> operand2;
        cin.ignore(1);
        if (cin) cin.ignore(1);

        int set_size = expression.size();
        int count = 0;
        set<set<char>> tmp;
        tmp = expression;
        expression.clear();

        for (auto it = tmp.begin(); it != tmp.end(); it++){
            set<char>tmp0 = (*it);
            tmp0.insert(operand1);
            expression.insert(tmp0);

            tmp0 = (*it);
            tmp0.insert(operand2);
            expression.insert(tmp0);
        }
        if (operand1 == '!')  break;
    }



    Reduce_expression(expression);

    Print_expression(expression);



    cin.close();



}
