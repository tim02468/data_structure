#include <iostream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;

struct node{
    int coef;
    int epx;
    int epy;
    int epz;
};

class polyno {
public:
    std::vector<node> polylist;
    void add_item(int coef, int ex, int ey, int ez);
    bool retCoeff(int ex,int ey,int ez);
    void Mulf (int ex,int ey,int ez);
};

void polyno::Mulf(int ex, int ey, int ez){
    for(int i = 0; i < polylist.size(); i ++){
        polylist[i].epx += ex;
        polylist[i].epy += ey;
        polylist[i].epz += ez;
    }

}


bool polyno::retCoeff(int ex, int ey, int ez){
    for(int i=0; i < polylist.size(); i ++){
        if(polylist[i].epx == ex && polylist[i].epy == ey && polylist[i].epz == ez){
            cout << polylist[i].coef << endl;
            return true;
        }
    }

    cout << "No Match!" << endl;
    return false;
}

void polyno::add_item(int coef, int ex, int ey, int ez){
    node tmp = {coef, ex, ey, ez};
    polylist.push_back(tmp);

}


int main()
{
    polyno tmp;
    string inputs, pattern;
    int action, ex, ey, ez;

    while(true){
        cout << "Please construct the polynomial input (coff ex ey ez): (if done then input 0)" << endl;
        getline(cin, inputs);
        if(inputs == "0"){
            break;
        }

        stringstream stream(inputs);
        while(true) {
           int coef, ex, ey, ez;
           stream >> coef >> ex >> ey >> ez;
           tmp.add_item(coef, ex, ey, ez);
           if(!stream)
              break;
        }
    }


    // find pattern
    while(true){
        cin.clear();
        fflush(stdin);
        int action;
        cout << "Please select action: (1: retCoeff (), 2: Mulf ())" << endl;
        cin >> action;

        if(action == 1){
            cin.clear();
            fflush(stdin);

            cout << "To find coeff, Please input polynomial term (ex ey ez):" << endl;

            getline(cin, pattern);
            stringstream patternStream(pattern);

            while(true){
                patternStream >> ex >> ey >> ez;
                tmp.retCoeff(ex, ey, ez);
                if(!patternStream){
                    break;
                }
                break;
            }



        }
        else if(action == 2){
            cin.clear();
            fflush(stdin);

            cout << "To update, Please input polynomial term (ex ey ez):" << endl;
            getline(cin, pattern);
            stringstream patternStream(pattern);

            while(true){
                patternStream >> ex >> ey >> ez;
                tmp.Mulf(ex, ey, ez);
                if(!patternStream){
                    break;
                }
                break;
            }

        }
        else{
            cout << "Action not found!" << endl;
        }
    }

    system("pause");
    return 0;
}
