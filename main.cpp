#include <iostream>
#include <windows.h>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

int pos1x(){
    //gets x coordinate of the click
    POINT point;
    if (GetCursorPos(&point)) {
    }
    int x = point.x;

    return(x);
}

int pos1y(){
    //gets y coordinate of the click
    POINT point;
    if (GetCursorPos(&point)) {
    }
    int y = point.y;

    return(y);
}

int keyPressed(int key){
    //returns which button pressed. If left the program continues
    return (GetAsyncKeyState(key) & 0x8000 != 0);
}

void printArr(vector<int>xArr,vector<int>yArr){
    //prints x and y arrays
    for(int i=0;i<xArr.size();i++){
        cout << i <<  " X: " << xArr[i] << "--- Y: " << yArr[i] << endl;
        }
}

void positionLooper(vector<int>xArr,vector<int>yArr){
    //loops through both arrays - setting cursor to each inputted position!
    while(1){
        for(int i=0;i<xArr.size();i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            cout << i << endl;
            SetCursorPos(xArr[i],yArr[i]);

            //left click is weird investigate why it disrupts the positioning in the game browser
            //for(int x = 0;x<10;x++){
            //    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            //}
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

            if(GetKeyState('P')){
                cout << "end program";
                exit(EXIT_FAILURE);
            }
            else{
                cout << "continue" << endl;
            }
        }
    }
}

int main(){
    bool click;
    string endMessage = "";
    vector<int>xArr;
    vector<int>yArr;
    int totalArrSize = 0;
    int x = 999;
    int y = 999;
    char continueQuestion = 'x';
    char areYouReadyKids = 'x';
    //boolean first click so that the weird bug you get when you start the program goes away!

    cout << "enter x into console when you are ready to start" << endl;
    cin >> areYouReadyKids;
    if(areYouReadyKids == 'x'){
        cout << "next left click will be recorded" << endl;
        while(1){
            if(keyPressed(VK_LBUTTON)){
                x = pos1x();
                y = pos1y();
                cout << x << " --- " << y << " " << endl;

                xArr.push_back(x);
                yArr.push_back(y);

                if(GetKeyState('C')){
                    cout << "Print array (you pressed X)" << endl;
                    xArr.pop_back();
                    yArr.pop_back();
                    printArr(xArr,yArr);

                    cout << "Do you want to loop this array?" << endl;
                    cin >> continueQuestion;
                    if(continueQuestion=='y'){
                        positionLooper(xArr,yArr);
                    }
                }

                if(GetKeyState('E')){
                    cout << "You have ended the system" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}
