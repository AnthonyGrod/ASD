#include <string>
#include <iostream>
#include <vector>

using namespace std;

// Musimy sprawdzić, jaka jest minimalna odległość między dwoma różnymi literami
int main() {
    string pattern;
    getline(cin, pattern);

    int minDistance = -1;
    int currentIndex = 0;
    int currentDistance = 0;
    char begChar;
    
    // Omijamy pierwsze gwiazdki (przyjmujemy, że mamy poprawny napis na wejściu)
    while (currentIndex < pattern.size() && pattern[currentIndex] == '*') {
        currentIndex++;
    }
    if (currentIndex == pattern.size() - 1) {
        cout << "1\n";
        return 0; 
    }

    begChar = pattern[currentIndex];
    bool areDiffChars = false;
    while (currentIndex < pattern.size()) {
        if (pattern[currentIndex] != begChar && pattern[currentIndex] != '*') {
            areDiffChars = true;
            if (currentDistance < minDistance || minDistance == -1) {
                minDistance = currentDistance;
            }
            currentDistance = 0;
            begChar = pattern[currentIndex];
        }
        else if (pattern[currentIndex] == begChar) {
            currentDistance = 0;
        }

        currentDistance++;
        currentIndex++;
    }

    if (!areDiffChars) {
        minDistance = pattern.size();
    }

    cout << pattern.size() - minDistance + 1 << endl;

}