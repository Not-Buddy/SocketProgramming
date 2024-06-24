
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Open the file
    std::ifstream file("filename.txt");

    // Check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    int LineCount = 0;

    // Read the file word by word
    //while (file >> word) {
    while(std::getline(file,line)){
          LineCount++;
        //std::cout << "Read word: " << line << std::endl; // Diagnostic output
    }

    // Close the file
    file.close();

    // Output the word count
    std::cout << "The file contains " << LineCount << " lines" << std::endl;

    return 0;
}

