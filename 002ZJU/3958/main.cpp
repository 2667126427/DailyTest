#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main(void){
    int cases = 0;
    int N = 0;
    int i, j;
    int k = 0, t = 0, choise = 0;
    string K = "Kobayashi";
    string T = "Tohru";
    string D = "Draw";
    cin >> cases;
    for(i = 0; i < cases; ++i){
        cin >> N;
        k = t = 0;
        for (j = 0; j < N; ++j){
            cin >> choise;
            switch(choise){
            case 1:
                ++k;
                break;
            case 2:
                ++t;
                break;
            }
        }
        if (k>t){
            cout << K << endl;
        }
        else if (k < t){
            cout << T << endl;
        }
        else{
            cout << D << endl;
        }
    }
    return 0;
}
