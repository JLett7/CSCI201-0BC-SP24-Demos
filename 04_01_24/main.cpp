#include <iostream>
#include <limits>
#include <cctype>
#include "drink.h"

// lecture activity comment lines 25 - 30, 32, 46, 50, 59, 61, 74 - 80
void resetStream();
sizeType inputDrinkSize();
baseType inputDrinkBase();
tempType inputDrinkTemperature();
std::string inputDrinkFlavor();
std::string inputDrinkDairy();
int *newArray();

bool numInRange(int num, int lower, int upper);
bool numGT0(int num, int = 0, int = 0);
bool negNum(int num, int = 0, int = 0);

int inputInt(std::string prompt, bool (*func)(int, int, int), int lower = 0, int upper = 0); // the function pointer returns a true if the data is valid

int main()
{
    int x = 79;
    int *p = nullptr;
    p = &x; //set a pointer variable p at the memory location of variable x
    std::cout << &x << std::endl; //Output the memory address
    std::cout << *p << std::endl; // Output the contents of the memory address for x using pointer p
    p = newArray(); //sets p equal to the returned result of the newArray function
    delete[] p; //delete the array in order to free up memory for potential reallocation
    drink **drinks; //Creates a double pointer variable called drinks in order to create the drink class without a constructor.

    sizeType drinkSize;
    baseType drinkBase;
    tempType drinkTemp;
    std::string dairy;
    std::string flavor;
    char yN = 'Y';
    drink *myDrink;
    drinkSize = inputDrinkSize();
    drinkBase = inputDrinkBase();
    drinkTemp = inputDrinkTemperature();
    flavor = inputDrinkFlavor();
    dairy = inputDrinkDairy();
    //line 46
    myDrink = new drink(drinkBase, drinkTemp, drinkSize, dairy, flavor);//Set a new pointer with a drink class called myDrink with parameters drinkBase drinkTemp,drinkSize, dairy and flavor

    // int numDrinks = inputInt("How many drinks do you want? ", numGT0);
    int numDrinks = 1; //initialize the numDrinks integer to 1
    drinks = new drink *[numDrinks]; // Create a dynamic array of drink class variables with the index of numDrinks

    while (yN == 'Y')
    {
        drinkSize = inputDrinkSize();
        drinkBase = inputDrinkBase();
        drinkTemp = inputDrinkTemperature();
        flavor = inputDrinkFlavor(); sets the variable flavor by calling the input drink flavor function
        dairy = inputDrinkDairy();
        drinks[numDrinks - 1] = new drink(drinkBase, drinkTemp, drinkSize, dairy, flavor);//fills the memory of the drinks array with the result of creating a new drink class variable with the parameters
        // drink d(bases[drinkBase - 1], temps[drinkTemp - 1], sizes[drinkSize - 1], dairy, flavor);
        std::cout << drinks[numDrinks - 1]->tostring() << std::endl;
        std::cout << "Would you like another drink? ";
        std::cin >> yN;
        yN = toupper(yN);
        while (yN != 'Y' && yN != 'N')
        {
            std::cout << "You did not enter y or n." << std::endl;
            std::cout << "Would you like another drink? ";
            std::cin >> yN;
            yN = toupper(yN);
        }
        if (yN == 'Y')
        {
            drink **d = drinks; //constructs class drink using a pointer
            drinks = new drink *[++numDrinks]; //Adds a new drink to the array storing the drink class variables
            for (int i = 0; i < numDrinks - 1; i++) // Sets up a for loop to access the array
            {
                drinks[i] = d[i]; //sets the value in the d array at index i to the value in the drinks array at index i
            }
            delete[] d; //delete array d to free up memory
        } //close for loop
    }

    std::cout << "The list of drinks is:" << std::endl;
    std::cout << myDrink->tostring() << std::endl;

    delete myDrink;
    for (int i = 0; i < numDrinks; i++)
    {
        std::cout << drinks[i]->tostring() << std::endl;
        delete drinks[i];
    }
    delete[] drinks;
    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

sizeType inputDrinkSize()
{
    std::ostringstream out;

    out << "Please choose the drink size:" << std::endl;
    for (int i = 0; i < ENUM_NUM; i++)
    {
        out << i + 1 << ": " << sizeStr[i] << std::endl;
    }
    int drinkSize = inputInt(out.str(), numInRange, 1, 3);

    return sizes[drinkSize - 1];
}

baseType inputDrinkBase()
{
    std::ostringstream out;
    out << "Please choose the drink base:" << std::endl;
    for (int i = 0; i < ENUM_NUM; i++)
    {
        out << i + 1 << ": " << baseStr[i] << std::endl;
    }
    int drinkBase = inputInt(out.str(), numInRange, 1, 3);

    return bases[drinkBase - 1];
}

tempType inputDrinkTemperature()
{
    std::ostringstream out;
    int drinkTemp;
    out << "Please choose the drink temperature:" << std::endl;
    for (int i = 0; i < ENUM_NUM; i++)
    {
        out << i + 1 << ": " << tempStr[i] << std::endl;
    }
    drinkTemp = inputInt(out.str(), numInRange, 1, 3);

    return temps[drinkTemp - 1];
}

std::string inputDrinkFlavor()
{
    std::string flavor;
    std::cout << "Please enter a flavor for your drink: ";
    std::cin >> std::ws;
    std::getline(std::cin, flavor);
    return flavor;
}

std::string inputDrinkDairy()
{
    std::string dairy;
    std::cout << "What kind of dairy would you like? ";
    std::cin >> std::ws;
    std::getline(std::cin, dairy);
    return dairy;
}

int *newArray()
{
    int *list = new int[15];
    return list;
}

bool numInRange(int num, int lower, int upper)
{
    return lower <= num && num <= upper;
}

bool numGT0(int num, int, int)
{

    return num > 0;
}

bool negNum(int num, int, int)
{
    return num < 0;
}

int inputInt(std::string prompt, bool (*func)(int, int, int), int lower, int upper)
{
    int theNum;
    std::cout << prompt;
    std::cin >> theNum;

    while (!std::cin || !func(theNum, lower, upper))
    {
        if (!std::cin)
        {
            std::cout << "You entered something that is not a number!" << std::endl;
            resetStream();
        }
        std::cout << "You have entered invalid data." << std::endl;
        std::cout << prompt;
        std::cin >> theNum;
    }

    return theNum;
}
