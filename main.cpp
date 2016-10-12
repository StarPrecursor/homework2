#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAXVALUE 2038074743

using namespace std;

const int maxRemainLoop = MAXVALUE>>1;
const int maxPrimeLoop = (int)(sqrt(MAXVALUE * 1.0) / 2.0);
int primeSeperateRecord[10001];
bool prime[maxRemainLoop];

int IsPrime(void);
int PrimeSeperate(void);
int Primenum(int);
int InputNumber(int &);

int main()
{
    cout << "Preprocessing..\n";
    IsPrime();
    PrimeSeperate();
    cout << "Done\n";
    int input = 0;
    int output = 0;

    while(true)
    {
        if(-1 != InputNumber(input))
        {
            output = Primenum(input);
            cout << output << endl;
        }
        else
        {
            cout << endl;
        }
    }

    return 0;
}

int IsPrime()
{
     memset(prime,true,sizeof(prime));
     for(int i = 0; i <= maxPrimeLoop; i++)
     {
        if(prime[i])
        {
            for(int j = 2*i*i + 6*i + 3; j < maxRemainLoop; j += 2*i + 3)
            {
                prime[j] = false;
            }
        }
     }

    return 0;
}

int PrimeSeperate()
{
    int blockCount = 1;
    int blockNum = 1;

    primeSeperateRecord[0] = 0;

    for(int i = 0; i < maxRemainLoop && blockNum <= 10000; i++)
    {
        if(prime[i])
        {
            blockCount++;
            if (10000 == blockCount)
            {
                primeSeperateRecord[blockNum] = i;
                blockNum++;
                blockCount = 0;
            }
        }
    }

    return 0;
}

int Primenum(int input)
{
    int blockNum = input / 10000;
    int sortNum = input % 10000;
    int primeCount = 0;

    if(1 == input)
    {
        return 2;
    }

    if(0 == blockNum)
    {
        primeCount = 1;
        for(int i = 0; i < maxRemainLoop; i++)
        {
            if(prime[i])
            {
                primeCount++;
                if(sortNum == primeCount)
                {
                    return 2*i + 3;
                }
            }
        }
    }
    else
    {
        primeCount = 0;
        for(int i = primeSeperateRecord[blockNum]; i < maxRemainLoop; i++)
        {
            if(prime[i])
            {
                if(sortNum == primeCount)
                {
                    return 2*i + 3;
                }
                primeCount++;
            }
        }
    }
}

int InputNumber(int &inputNumber)
{
    inputNumber = 0;
    char inputString[100];
    char *inputStringPointer = inputString;
    int positionValue = 0;
    int countDownNum = 10;

    if(nullptr != gets(inputString))
    {
        if('+' == *inputStringPointer)
        {
            inputStringPointer++;
        }

        while('\0' != *inputStringPointer)
        {
            if('0' == *inputStringPointer)
            {
                inputStringPointer++;
                continue;
            }
            else
            {
                break;
            }
        }

        while(('\0' != *inputStringPointer) && (0 != countDownNum))
        {
            positionValue = (*inputStringPointer) - '0';
            if(0 <= positionValue && 9 >= positionValue)
            {
                inputNumber = inputNumber * 10 + positionValue;
                countDownNum --;
            }
            else
            {
                cout << "Error input.";
                return -1;
            }

            inputStringPointer++;
        }
    }
    else
    {
        cout << "Fail to input.";
        return -1;
    }

    if((0 <= inputNumber) && (1000000000 >= inputNumber))
    {
        return inputNumber;
    }
    else
    {
        cout << "Error input.";
        return -1;
    }
}
