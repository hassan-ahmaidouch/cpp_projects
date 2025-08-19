#include <iostream>
#include "clsBankClient.h"

using namespace std;


int main()
{
    clsBankClient Client = clsBankClient::Find("A101");
    Client.Print();
    


    return 0;
}