#include <iostream>
#include <fstream>
using namespace std;

int main() {
  // Create and open a text file
  ofstream MyFile("filename.txt");

  // Write to the file
  for(int i{0};i<=20;i++)
  {
    MyFile << "Files can be tricky, but it is fun enough!";
  }

  // Close the file
  MyFile.close();
  return 0;
}
