// this program is an interpreter for the language known as brainfuck.  the only characters that mean anything are <>_+[],.
// it recieves the program input from the command line at the beginning, then data input and output occur on the commandline afterwards.

#include <iostream>
using namespace std;

// cpu class for modular structure
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

// actual interpreter
int main()
{
    // allocate cpu memory and stack for loops
    cpu * c = new cpu();
    c->allocateMemory(1000, 30000);

    int myStack[1000]{ 0 };
    int myStackIndex = 1;

    // for every character in the program
    while (c->pc < c->programSize)
    {
        // get the character
        char input = c->programMemory[c->pc];
        
        // determine what we should do
        switch (input)
        {
            // increment the current value
            case '+':
                ++(c->dataMemory[c->dc]);
                break;
            // decrement the current value
            case '-':
                --(c->dataMemory[c->dc]);
                break;
            // move left one space
            case '<':
                c->dc--;
                break;
            // move right one space
            case '>':
                c->dc++;
                break;
            // print output
            case '.':
                cout << (char)c->dataMemory[c->dc];
                break;
            // recieve input
            case ',':
                char inchar;
                cin >> inchar;
                c->dataMemory[c->dc] = (int)inchar;
                break;
            // begin loop
            case '[':
                myStackIndex++;
                myStack[myStackIndex] = c->pc;
                break;
            // end loop
            case ']':
                if (c->dataMemory[c->dc] > 0 && myStackIndex >= 0)
                {
                    c->pc = myStack[myStackIndex];
                }
                else
                    myStackIndex--;
                break;
        }
        // move to next instruction
        c->pc++;
    }

    // deallocate memory allocated using (new)
    c->deallocateMemory();
    delete(c);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu