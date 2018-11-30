#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

struct client{
    int arrive_t;
    int service_t;
    int allow_wait_t;
};

struct result{
    bool served;
    int served_t;
    int leave_t;
};

int main()
{
    int arrival, service, allow, wait_t, next_serve_t=0, input_counts = 0;
    bool served;
    string tag;
    vector <client> lines;
    vector <result> outputs;
    result tmp;


    while(lines.size() < 10){
        cout << "Please input client " << ++input_counts << " Arrival time, Service time, Allowable waiting time: " << endl;
        cin >> arrival >> service >> allow;
        client tmp = {arrival, service, allow};
        lines.insert(lines.end(), tmp);
    }

    for(int i = 0; i < lines.size(); i++) {
        if(i == 0){
            served = true;
            next_serve_t = lines[i].arrive_t + lines[i].service_t;
            tmp = {served, lines[i].arrive_t, next_serve_t};
        }
        else{
            if(next_serve_t < lines[i].arrive_t){
                served = true;
                next_serve_t = lines[i].arrive_t + lines[i].service_t;
                tmp = {served, lines[i].arrive_t, next_serve_t};
            }
            else{
                wait_t = next_serve_t - lines[i].arrive_t;
                if(wait_t <= lines[i].allow_wait_t){
                    served = true;
                    tmp = {served, next_serve_t, next_serve_t + lines[i].service_t};
                    next_serve_t = next_serve_t + lines[i].service_t;
                }
                else{
                    // check whether cutting in or not
                    if(lines[i].arrive_t <= outputs[i-1].served_t){
                        int expect = outputs[i-1].served_t + lines[i].service_t;
                        if(expect <= lines[i-1].arrive_t + lines[i-1].allow_wait_t){
                            served = true;
                            tmp = {served, outputs[i-1].served_t, expect};
                            outputs[i-1].served_t = expect;
                            outputs[i-1].leave_t = expect + lines[i-1].service_t;
                            next_serve_t = outputs[i-1].leave_t;
                        }
                        else{
                            served = false;
                            tmp = {served, next_serve_t, next_serve_t};
                        }
                    }
                    else{
                        served = false;
                        tmp = {served, next_serve_t, next_serve_t};
                    }
                }
            }
        }

        outputs.insert(outputs.end(), tmp);
    }

    for(int i = 0; i < outputs.size(); i++){
        cout << "            Served or not?            Departure time" << endl;
        if(outputs[i].served){
            tag = "Yes";
            cout << "Client " << i+1 << ":        " << tag << "                         " << outputs[i].leave_t << endl;
        }
        else{
            tag = "No";
            cout << "Client " << i+1 << ":        " << tag << "                       " << endl;
        }

    }

    system("pause");
    return 0;
}
