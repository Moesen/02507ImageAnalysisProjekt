// #include <iostream>
// #include <vector>
// #include <string>

// using namespace std;

// int main()
// {
//     vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

//     for (const string& word : msg)
//     {
//         cout << word << " ";
//     }
//     cout << endl;
// }

#include <iostream>
#include <future>

int addNumbers(int a, int b) {
    return a + b;
}

int main() {
    std::cout << "Start of the program \n";
    auto fut = std::async(addNumbers, 1, 2);
    std::cout << "Calculating sum asynchrinously\n";
    std::cout << "The result is: " << fut.get() << "\n";
    std::cout << "End of the program \n";
}