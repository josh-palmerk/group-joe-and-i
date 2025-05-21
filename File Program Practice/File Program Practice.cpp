/***********************************************************************
 * Program:
 *    Lab 06: File Round-Trip
 * Author:
 *    David Wells, Joe Allen
 * Summary:
 *    Reads a floating-point number from a file, updates it with user input,
 *    and writes it back to the file.
 ************************************************************************/

#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

/*************************************
 * READ BALANCE
 * Read the balance from data.txt.
 * If the file doesn't exist, set to 0.0
 *************************************/
double readBalance()
{
   ifstream fin("data.txt");
   double balance = 0.0;

   if (fin.fail())
   {
      cout << "Unable to open data.txt\n";
   }
   else
   {
      fin >> balance;
      fin.close();
   }

   return balance;
}

/*************************************
 * DISPLAY BALANCE
 * Show the balance to the user.
 *************************************/
void displayBalance(double balance)
{
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   cout << "Account balance: $" << balance << endl;
}

/*************************************
 * UPDATE BALANCE
 * Prompt user for a value to add.
 *************************************/
double updateBalance(double balance)
{
   double change;
   cout << "Change: $";
   cin >> change;
   return balance + change;
}

/*************************************
 * WRITE BALANCE
 * Write the updated balance to file.
 *************************************/
void writeBalance(double balance)
{
   ofstream fout("data.txt");

   if (fout.fail())
   {
      cout << "Unable to write balance to data.txt\n";
   }
   else
   {
      fout << balance << endl;
      fout.close();
      cout << "Balance successfully written to data.txt\n";
   }
}

/*************************************
 * SHOW WORKING DIRECTORY
 * Display current directory in a portable way
 *************************************/

void showWorkingDirectory()
{
   #ifdef _WIN32
      system("cd");
   #else
      system("pwd");
   #endif
}

/*************************************
 * MAIN
 * Program driver
 *************************************/
int main()
{
   // Show current working directory for verification
	showWorkingDirectory(); // Should work for any OS

   double balance = readBalance();
   displayBalance(balance);

   balance = updateBalance(balance);
   displayBalance(balance);

   writeBalance(balance);

   return 0;
}
