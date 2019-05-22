//prompt user to enter a num 1-10 
//use the input to tell user's fortune

#include <iostream>
using namespace std;

int main()
{
    int num;
    bool bad;

    do
    {
        //reset flag variable
        bad = false;
        //get user's favorite number
        cout << "Enter your favorite number: ";
        cin >> num;

        //check if input is valid
        if((num < 1) || (num > 10)) //0.5 causes error
        {
            bad = true;
            cout << "Bad input..." << endl;
        }

    //if not valid, prompt again
    }while(bad);

    //if valid, print fortune
    switch(num)
    {
        case 1:
            cout << "Stop procrasting starting tomorrow." << endl;
            break;
        case 2:
            cout << "The end is near." << endl;
            break;
        case 3:
            cout << "*hug*" << endl;
            break;
        case 4:
            cout << "You can not be helped." << endl;
            break;
        case 5:
            cout << ";)" << endl;
            break;
        case 6:
            cout << "You will do something today." << endl;
            break;
        case 7:
            cout << "meh." << endl;
            break;
        case 8:
            cout << "404 Fortune Not Found." << endl;
            break;
        case 9:
            cout << "You are not illiterate." << endl;
            break;
        case 10:
            cout << "The fortune you seek is in another cookie." << endl;
            break;
    }

    //terminate program
    return 0;
}

