// Brainfuck_Interpreter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class cpu
{
    public:
        int programSize = 1;
        int dataSize = 1;
        char * programMemory = NULL;
        int * dataMemory = NULL;
        int pc = 0;
        int dc = 0;

        void allocateMemory(int programSize, int dataSize)
        {
            this->programSize = programSize;
            this->dataSize = dataSize;

            dc = dataSize / 2;

            programMemory = new char[programSize];
            cin.getline(programMemory, programSize, '\n');
            dataMemory = new int[dataSize] {0};
        }
        void deallocateMemory()
        {
            delete(programMemory);
            delete(dataMemory);
        }
};

int main()
{
    cpu * c = new cpu();
    c->allocateMemory(1000, 30000);

    int myStack[1000]{ 0 };
    int myStackIndex = 1;

    while (c->pc < c->programSize)
    {
        char input = c->programMemory[c->pc];
        
        switch (input)
        {
            case '+':
                ++(c->dataMemory[c->dc]);
                //cerr << c->dataMemory[c->dc] << endl;
                break;
            case '-':
                --(c->dataMemory[c->dc]);
                //cerr << c->dataMemory[c->dc] << endl;
                break;
            case '<':
                c->dc--;
                //cerr << c->dataMemory[c->dc] << endl;
                break;
            case '>':
                c->dc++;
                //cerr << c->dataMemory[c->dc] << endl;
                break;
            case '.':
                cout << (char)c->dataMemory[c->dc];
                break;
            case ',':
                char inchar;
                cin >> inchar;
                c->dataMemory[c->dc] = (int)inchar;
                break;
            case '[':
                myStackIndex++;
                myStack[myStackIndex] = c->pc;
                break;
            case ']':
                if (c->dataMemory[c->dc] > 0 && myStackIndex >= 0)
                {
                    c->pc = myStack[myStackIndex];
                }
                else
                    myStackIndex--;
                break;
        }
        c->pc++;
    }

    c->deallocateMemory();
    delete(c);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
