//Contestant - 02-0861-0001
//Coin Data program.
//Include Standard Library Packages.
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

const int       TWENTYDOLLAR_VALUE = 2000;
const int       TENDOLLAR_VALUE = 1000;
const int       FIVEDOLLAR_VALUE = 500;

const int       DOLLAR_VALUE = 100; //1
const int       QUARTER_VALUE = 25; //2
const int       DIME_VALUE = 10;    //3
const int       NICKEL_VALUE = 5;   //4
const int       PENNY_VALUE = 1;    //5

//uses this to pull the right results.
const int       VALUES[5] =
{
    DOLLAR_VALUE, QUARTER_VALUE, DIME_VALUE, NICKEL_VALUE, PENNY_VALUE
};

const int       CHANGE_VALUES[8] =
{
    TWENTYDOLLAR_VALUE, TENDOLLAR_VALUE, FIVEDOLLAR_VALUE, DOLLAR_VALUE,
    QUARTER_VALUE, DIME_VALUE, NICKEL_VALUE, PENNY_VALUE
};

class           ChangeMachine
{
private:

    //parses the input for the coin variables, and turns them into usable numbers.
    void parseInput(string input, int coinVariables[10])
    {
        int pos = 0;
        coinVariables[pos] = stoi(input.substr(0, input.find(' ')));    //gets the first number.
        int last = input.find(' ');
        pos++;

        while (pos < 10 && input.find(' ', last) != -1)                 //if the position is less than ten, and there is more to be parsed.
        {
            //parsing the string by spaces
            int begin = input.find(' ', last) + 1;

            if (input.find(' ', begin) != -1)
            {
                //theres more spaces, so parse in between them.
                //parses to a number
                int next = input.find(' ', begin);
                coinVariables[pos] = stoi(input.substr(begin, next - begin));
            }
            else
            {
                //theres not any more spaces. Just get the rest of the string.
                //parses the string to an int.
                coinVariables[pos] = stoi(input.substr(begin));
            }

            last = begin;
            pos++;
        }
    }

    //parses the best possible change amount.
    void parseBestChange(int sum, int amounts[8])
    {
        int pos = 0;

        while (sum != 0)
        {
            while (CHANGE_VALUES[pos] <= sum)   //checks if the value is less than the total money
            {
                amounts[pos] += 1;              //increases the type of currency
                sum -= CHANGE_VALUES[pos];      //subtracts from what's left.
            }

            pos++;
        }
    }

public:

    //gets the change.
    string getChange(string input)
    {
        int coinVariables[10];
        parseInput(input, coinVariables);

        int sum = 0;
        for (int i = 0; i < 10; i += 2) //goes through each position in the array
        {
            sum += VALUES[coinVariables[i] - 1] * coinVariables[i + 1];
        }

        int amounts[8];                 //create an amounts for each currency_type.
        for (int i = 0; i < 8; i++)
        {
            amounts[i] = 0;
        }   //set each value to zero.

        parseBestChange(sum, amounts);  //parses for the best change
        stringstream    ss;
        ss <<
            "This yields: " <<
            amounts[0] <<
            " twenty dollar bill(s), " <<
            amounts[1] <<
            " ten dollar bill(s), " <<
            amounts[2] <<
            " five dollar bill(s), " <<
            amounts[3] <<
            " one dollar bill(s), " <<
            amounts[4] <<
            " quarter(s), " <<
            amounts[5] <<
            " dime(s), " <<
            amounts[6] <<
            " nickel(s), " <<
            amounts[7] <<
            " penny(ies).";

        string  line;
        getline(ss, line);
        return line;
    }

    //gets the input line from the file.
    string getInput(ifstream &file)
    {
        string  line;
        getline(file, line);    //gets the line from the file, and allocates it the the variable "line"
        return line;
    }
};

void pause()
{
    //waits until the user presses enter.
    string  w;
    getline(cin, w);
}

//Main method that will be executed when the program is first run.
int main(int argC, const char *args)
{
    ifstream    coinDataFile("c++coinData.txt");    //this was the supplied file.
    ofstream    outFile("change.txt");
    if (coinDataFile.good())
    {
        //file exists and is all good.
        ChangeMachine   machine;

        bool            reading = true;
        while (reading)
        {
            string  line = machine.getInput(coinDataFile);
            if (line == "")
            {
                reading = false;
                break;
            }

            //cout << line << endl << endl;
            //outFile << line << endl << endl;
            string  change = machine.getChange(line);
            cout << change << endl << endl;
            outFile << change << endl << endl;
        }

        //Finished
    }
    else
    {
        //the file is not available.
        cout << "The input file is not available." << endl;
    }

    pause();                //allows judges to see the output
    outFile.close();        //closes the output file.
    coinDataFile.close();   //closes the input file.
}
