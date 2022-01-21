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

    //create a restart button to sidestep the issue of the clicking turning to non clicking
    while(1){
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        for(int i=0;i<xArr.size();i++){
            //edit time here

            cout << i << endl;
            SetCursorPos(xArr[i],yArr[i]);


            for(int x = 0;x<40;x++){
                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            if(GetKeyState('E') & 0x8000){
                cout << "end program";
                exit(EXIT_FAILURE);
            }
            else if(GetKeyState('R') & 0x8000){
                cout << "*****\nTemporary hold please enter y to continue\nenter y: ";
                string enterToContinue = "";
                cin >> enterToContinue;
                if(enterToContinue=="y"){
                    SetCursorPos(1145,803);
                    SetCursorPos(1145,802);
                    continue;
                }

            }
            else{
                cout << "Hold the E button to exit the program" << endl;
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

    cout << "enter y into console when you are ready to start" << endl;
    cin >> areYouReadyKids;
    if(areYouReadyKids == 'y'){
        cout << "Hold the C button and click to indicate you are done with mouse positions" << endl;
        cout << "next left click will be recorded" << endl;

        if(keyPressed(VK_LBUTTON)){
            cout << "you left clicked too early! - click not recorded!" << endl;
        }

        while(1){
            if(keyPressed(VK_LBUTTON)){

                x = pos1x();
                y = pos1y();
                cout << x << " --- " << y << " " << endl;

                xArr.push_back(x);
                yArr.push_back(y);

                if(GetKeyState('C')){
                    cout << "Print array (you pressed C)" << endl;
                    if(xArr.size() != 0){
                        xArr.pop_back();
                        yArr.pop_back();
                        printArr(xArr,yArr);
                    }
                    else{
                        cout << "--- your array is nothing! --- \n";
                    }

                    cout << "Do you want to loop this array (y/n)?" << endl;
                    cin >> continueQuestion;
                    if(continueQuestion=='y'){
                        positionLooper(xArr,yArr);
                    }
                    else if(continueQuestion = 'n'){
                        exit(EXIT_FAILURE);
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
