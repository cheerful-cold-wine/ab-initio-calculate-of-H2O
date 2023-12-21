#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> readFileAndStoreInArray(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> messages;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            messages.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return messages;
}

int main() {
    std::string filename = "your_file.txt"; // Replace 'your_file.txt' with your file's name

    std::vector<std::string> messages = readFileAndStoreInArray(filename);

    // Printing the messages stored in the array
    for (const auto& message : messages) {
        std::cout << message << std::endl;
    }

    return 0;
}

