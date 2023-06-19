#include <iostream>
using namespace std;

// grid size
int N = 4;
int M = 5;
class Robot{
    protected:
    int _x;
    int _y;
    public:
        Robot(int x, int y): _x(x), _y(y){}

        void Up();
        void Down();
        void Left();
        void Right();

        void PrintMesh() const;   
        void PrintPath(int, int) const; 

};
void Robot::PrintPath(int x,int y) const{
	if(_x < x){
		for(int i =0; i<x-_x; i++){
			cout<<"Right"<<endl;
		}
	}else{
		for(int i =0; i<x-_x; i++){
			cout<<"Left"<<endl;
		}
	}
	if(_y < y){
		for(int i =0; i<y-_y; i++){
			cout<<"Down"<<endl;
		}
	}else{
		for(int i =0; i<y-_y; i++){
			cout<<"Up"<<endl;
		}
	}

}

void Robot::Left(){
    if (_y == 0){
        _y = M - 1;
    }else{
        _y = _y - 1;   
    }
}
void Robot::Right(){
    if (_y == 3){
        _y = 0;
    }else{
        _y += 1;
    }   
}
void Robot::Up(){
    if (_x == 0){
        _x = N - 1;
    }else{
        _x -= 1;
    }   
}
void Robot::Down(){
    if (_x == 4){
        _x = 0;
    }else{
        _x += 1;
    }   
}
void Robot::PrintMesh() const{
    // cout << _x << " i " << _y << endl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(i == _x && j == _y){
                cout << "X ";
            }else{
                cout << "O ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    Robot r(1,2);
    // r.PrintMesh();
    r.Left();
    
    r.PrintMesh();
    r.PrintPath(2,3);
    return 0;
}