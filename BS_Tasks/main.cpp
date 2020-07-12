#include <iostream>
#include <string>

using namespace std;
void outputtypes()
{
    bool ob{true};
    char oc{'s'};
    int oi{888};
    double od{88.8888};
    string ostr{"C++ skills improving!"};
    cout << ob << "\t" << oc << "\t" << oi << "\t" << od << "\n\r" ;
    cout << ostr << std::endl;
}
void inputtypes()
{
    bool ob{0};
    char oc{'\0'};
    int oi{0};
    double od{0};
    string ostr{""};
    cout << "Input a bool:\n";
    cin >> ob;
    cout << "Input a char:\n";
    cin >> oc;
    cout << "Input a int:\n";
    cin >> oi;
    cout << "Input a double:\n";
    cin >> od;
    ws(cin);
    cout << "Input a string:\n";
    getline( cin, ostr );

    cout << ob << "\t" << oc << "\t" << oi << "\t" << od << "\n\r" ;
    cout << ostr << std::endl;
}
int main()
{
    cout << "Hello World!" << endl;
    outputtypes();
    inputtypes();
    return 0;
}
