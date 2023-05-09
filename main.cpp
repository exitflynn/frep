#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <getopt.h>

using namespace std;

// Define the maximum line length
const int MAX_LINE_LEN = 1024;

// Define the maximum pattern length
const int MAX_PATTERN_LEN = 256;

// Define the Boyer-Moore search function
int boyer_moore(const char* text, int n, const char* pattern, int m)
{
    // Initialize the jump table
    int jump[256];
    for (int i = 0; i < 256; i++) {
        jump[i] = m;
    }
    for (int i = 0; i < m - 1; i++) {
        jump[pattern[i]] = m - 1 - i;
    }

    // Perform the search
    int i = m - 1;
    while (i < n) {
        int j = m - 1;
        while (j >= 0 && text[i] == pattern[j]) {
            i--;
            j--;
        }
        if (j < 0) {
            return i + 1;
        }
        i += max(jump[text[i]], m - 1 - j);
    }

    // Pattern not found
    return -1;
}

// Define the main function
int main(int argc, char* argv[])
{
    // Define the program options
    struct option long_options[] = {
        {"ignore-case", no_argument, NULL, 'i'},
        {"invert-match", no_argument, NULL, 'v'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}
    };

    // Parse the program options
    int c;
    bool ignore_case = false;
    bool invert_match = false;
    bool word_regexp = false;
    while ((c = getopt_long(argc, argv, "ivh", long_options, NULL)) != -1) {
        switch (c) {
            case 'i':
                ignore_case = true;
                break;
            case 'v':
                invert_match = true;
                break;
            case 'h':
                cout << "frep is a clone of grep, which uses the Boyer-Moore algorithm to search for objects in files.\n To use simply run it as: \n frep [-i] [-v] pattern filename \n It can also take stdin as input so there's also support for piping." << endl;
            default:
                cout << "Usage should look like: frep [-i][-v] pattern filename" << endl;
                return 1;
        }
    }

    // Parse the search pattern
    if (optind >= argc) {
        cerr << "Error: search pattern not specified" << endl;
        return 1;
    }
    const char* pattern = argv[optind];

    // Convert the search pattern to lowercase if ignore-case is set
    char lowercase_pattern[MAX_PATTERN_LEN];
    if (ignore_case) {
        transform(pattern, pattern + strlen(pattern), lowercase_pattern, ::tolower);
        lowercase_pattern[strlen(pattern)] = '\0';
        pattern = lowercase_pattern;
    }

    // Parse the input files or read from stdin
    vector<string> files;
    if (optind + 1 < argc) {
        for (int i = optind + 1; i < argc; i++) {
            files.push_back(argv[i]);
        }
    } else {
        files.push_back("-");
    }

    // Search for the pattern in each file or stdin
    bool match_found = false;
    for (const string& filename : files) {
        // Open the file or stdin
        istream* input;
        ifstream file_input;
        if (filename == "-") {
            input = &cin;
        }
            else {
        file_input.open(filename);
        if (!file_input.is_open()) {
            cerr << "Error: cannot open file " << filename << endl;
            return 1;
        }
        input = &file_input;
    }

    // Search for the pattern in each line
    char line[MAX_LINE_LEN];
    while (input->getline(line, MAX_LINE_LEN)) {
        // Convert the line to lowercase if ignore-case is set
        char lowercase_line[MAX_LINE_LEN];
        if (ignore_case) {
            transform(line, line + strlen(line), lowercase_line, ::tolower);
            lowercase_line[strlen(line)] = '\0';
        }

        // Perform the search
        int pos;
        if (ignore_case) {
            pos = boyer_moore(lowercase_line, strlen(lowercase_line), pattern, strlen(pattern));
        } else {
            pos = boyer_moore(line, strlen(line), pattern, strlen(pattern));
        }

        // Check if the pattern was found
        bool found = (pos != -1);
        if (invert_match) {
            found = !found;
        }
        if (found) {
            cout << line << endl;
            match_found = true;
        }
    }

    // Close the file or stdin
    file_input.close();
    }
    // Exit with the appropriate status code
    return (match_found ? 0 : 1);
}
