// SNAKE GAME
#include <queue>
#include <iostream>
using namespace std;

class Snake{
    public:
        int x, y;
        bool endGame;
        queue <pair<int, int>> coordinate;

        Snake(int n): x(0),y(0){
            for(int i = 0; i < n; i++){
                coordinate.push(pair<int, int>(0, n-i));
            }
            endGame = false;
        }
        void Up(){
            y+=1;
            coordinate.push(pair<int, int>(x, y));
            coordinate.pop();
            if(checkEnd()) cout << "X";
        };
        void Down(){
            y -= 1;
            coordinate.push(pair<int, int>(x, y));
            coordinate.pop();
            if(checkEnd()) cout << "X";
        };
        void Left(){
            x -= 1;
            coordinate.push(pair<int, int>(x, y));
            coordinate.pop();
            if(checkEnd()) cout << "X";
        };
        void Right(){
            x += 1;
            coordinate.push(pair<int, int>(x, y));
            coordinate.pop();
            if(checkEnd()) cout << "X";
        };
        
        bool checkEnd(){
            queue <pair<int, int>> Q;
            while(!coordinate.empty()){
		        Q.push(coordinate.front());
		        coordinate.pop();
            }
            while(Q.size() != 1){
                if((x == Q.front().first) && (y == Q.front().second)){
                    endGame = true;
                    cout << "End: " << endGame << endl;
                    return true;
                }
		        coordinate.push(Q.front());
		        Q.pop();
            }
            coordinate.push(Q.front());
		    Q.pop();

            return false;
        }
};

int main(){
    cout << "duljina zmije i kretanja, control C prekida :)" << ;
    int size;
    cin >> size;
    Snake S(size);

    for(char c;cin >> c;){
        if(c == 'U') {
            S.Up();

        }else if(c == 'D'){
            S.Down();

        }else if(c == 'R'){
            S.Right();

        }else if(c == 'L'){
            S.Left();

        }
    }

    if(S.endGame == 0){cout << "OK";}else{cout << "Game over";};
    cout << endl;
    
    return 0;
}