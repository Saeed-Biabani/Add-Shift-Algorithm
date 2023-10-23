#include <iostream>

#include "AddShift.hxx"

using namespace std;

int main(int argc, const char** argv) {
    const char *b = "100101";
    const char *q = "110110";
    AddShift table = AddShift(q, b, 6);


    cout<<"Init  :  ";
    table.Print();
    cout<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<endl;

    while (true) {
        if (table.Q0 == 1) {
            table.A = table.BitSum(table.B, table.A);
            cout<<"BitSum : ";
            table.Print();
        }

        cout<<"shift  : ";
        table.ShiftToRightEAQ();
        table.Print();
        cout<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<endl;

        if (table.SC == 0) {
            break;
        }
    }
    cout<<'('<<table.BitToDec(b, 6)<<'*'<<table.BitToDec(q, 6)<<')'<<endl;
    cout<<"Binary : "<<table.BitString()<<endl;
    cout<<"Decimal : "<<table.ResInDec()<<endl;

    return 0;
}