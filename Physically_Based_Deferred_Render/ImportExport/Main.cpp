#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    char choice = '0';
    while(choice == '0')
    {
        cout << "1. New Shader:";
        cin >> choice;
    }
    if(choice == '1')
    {
        string Name, Base = "..\\Shaders\\", Mgr = "..\\Shaders.mgr";
        cout << "What Name?";
        cin >> Name;

        ofstream File;

        File.open(Base+Name+".sha");
        if(!File)
            return -1;
        string Vert = Name + "Vert.sha";
        string Frag = Name + "Frag.sha";
        File << Name << " ";
        File << "Shaders\\"+Vert << " ";
        File << "Shaders\\"+Frag;
        File.close();

        File.open(Base+Vert);
        File.close();
        File.open(Base+Frag);
        File.close();

        fstream MgrFile;
        MgrFile.open(Mgr,ios::app | ios::out);
        if(!MgrFile)
        {
            cout << "Mgr Failed to open";
            return -1;
        }
        cout << "MgrFile::" << Mgr << endl;
        cout << Base << Name << ".sha" << endl;
        MgrFile<<" " << "Shaders\\" << Name+".sha";
        MgrFile.close();
    }

    return 1;
}
