#include <iostream>
#include <fstream>
#include <vector>


std::vector<int> computePrefixFunction(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> pi(m);
    pi[0] = 0;
    int k = 0;

    for (int q = 1; q < m; q++) {
        while (k > 0 && pattern[k] != pattern[q]) {
            k = pi[k-1];
        }
        if (pattern[k] == pattern[q]) {
            k++;
        }
        pi[q] = k;
    }

    return pi;
}

std::vector<int> KMPMatcher(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    std::vector<int> result;
    auto pi = computePrefixFunction(pattern);
    int q = 0;
    for (int i = 0; i < n; i++) {
        while (q > 0 && pattern[q] != text[i]) {
            q = pi[q-1];
        }
        if (pattern[q] == text[i]) {
            q++;
        }
        if (q == m) {
            result.push_back(i - m + 1);
            q = pi[q-1];
        }
    }
    return result;
}

void outputAnswer(std::ostream& os, const std::vector<int>& ans) {
    if (ans.empty()) {
        os << 0;
    }
    else {
        os << ans.size() << std::endl;
        for (auto i : ans) {
            os << i + 1 << " ";
        }
    }
}

void formatAnswer(const std::vector<int>& ans, bool toFile)
{
    if (toFile) {
        std::ofstream outfile("output.txt");
        if (!outfile.is_open()) {
            std::cerr << "Error opening file for writing" << std::endl;
            return;
        }
        outputAnswer(outfile, ans);
        outfile.close();
    }
    else {
        outputAnswer(std::cout, ans);
    }
}

std::pair<std::string, std::string> readInput(std::istream& is) {
    std::string text, pattern;
    is >> text >> pattern;
    return std::make_pair(text, pattern);
}

std::pair<std::string, std::string> readFromFile(const std::string& path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return std::make_pair("", "");
    }
    auto input = readInput(input_file);
    input_file.close();
    return input;
}



int main()
{   // Test KMPMatcher function
    std::cout << "Wprowadz sciezke do pliku testowego" << std::endl;
    std::string path;
    std::cin >> path;

    auto input = readFromFile(path);
    auto ans = KMPMatcher(input.first, input.second);
    formatAnswer(ans, true);

    return 0;
}