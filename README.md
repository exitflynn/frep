# FREP-(GREP Command Clone)

The grep command searches for the pattern specified by the Pattern parameter and writes each matching line to standard output. The patterns are limited regular expressions in the style of the ed or egrep command. The grep command uses a compact non-deterministic algorithm.The pattern that is searched in the file is referred to as the regular expression (grep stands for global search for regular expression and print out).

# About The Project

This system is developed keeping in view the general need required by the user while requiring searching and/or closest-record searching while using any given data. For example, a phone directory book or a database of movies. The users will have the ability to efficiently store and retrieve information with these functionalities.

This command works on the Boyer-Moore search Algorithm.The algorithm preprocesses the string being searched for (the pattern), but not the string being searched in (the text). It is thus well-suited for applications in which the pattern is much shorter than the text or where it persists across multiple searches. The Boyer–Moore algorithm uses information gathered during the preprocess step to skip sections of the text, resulting in a lower constant factor than many other string search algorithms. In general, the algorithm runs faster as the pattern length increases. The key features of the algorithm are to match on the tail of the pattern rather than the head, and to skip along the text in jumps of multiple characters rather than searching every single character in the text.

# Dataset Description

The dataset can be as large as the phonebook of a city or a directory containing a large number of research papers. To provide a demonstration for a general case, we have implemented in-file searching for any given files. The files can be given in the form of a directory path and more than one files can be added (not necessarily in the same directory).

# Key Features

The grep command is a powerful tool used in Unix-based operating systems for searching and filtering text files.Here are some of its key features:
* Inverse Matching: Using the -v option, grep can perform inverse matching, i.e., it displays lines that do not match the specified pattern. This is useful for excluding certain patterns from the search results.
* Case insensitive search : The -i option enables to search for a string case insensitively in the given file. It matches the words like “UNIX”, “Unix”, “unix”. 
* Help : The -h option displays how to use the frep command . Frep is a clone of grep, which uses the Boyer-Moore algorithm to search for objects in files.\n To use simply run it as: \n frep [-i] [-v] pattern filename \n It can also take stdin as input so there's also support for piping.

# Boyer-Moore search Algorithm

Given a text txt[0..n-1] and a pattern pat[0..m-1] where n is the length of the text and m is the length of the pattern, write a function search(char pat[], char txt[]) that prints all occurrences of pat[] in txt[]. You may assume that n > m. 

Examples:<br>
Input:<br>
txt[] = "THIS IS A TEST TEXT"<br>
pat[] = "TEST"<br>
Output: Pattern found at index 10<br>
Input:  txt[] =  "AABAACAADAABAABA"<br>
        pat[] =  "AABA"<br>
Output: Pattern found at index 0<br>
        Pattern found at index 9<br>
        Pattern found at index 12<br>

![img-660x438](https://github.com/exitflynn/frep/assets/97532274/9bb97520-95f0-4ce0-89c1-8c8dcd12a243)

Boyer Moore is a combination of the following two approaches:

* Bad Character Heuristic 
* Good Suffix Heuristic

Both of the above heuristics can also be used independently to search a pattern in a text. Let us first understand how two independent approaches work together in the Boyer Moore algorithm.
It processes the pattern and creates different arrays for each of the two heuristics. At every step, it slides the pattern by the max of the slides suggested by each of the two heuristics. So it uses greatest offset suggested by the two heuristics at every step.Unlike the previous pattern searching algorithms, the Boyer Moore algorithm starts matching from the last character of the pattern.

### Bad Character Heuristic

The idea of bad character heuristic is simple. The character of the text which doesn’t match with the current character of the pattern is called the Bad Character. Upon mismatch, we shift the pattern until – 

1. The mismatch becomes a match.
2. Pattern P moves past the mismatched character.

Case 1 – Mismatch become match 
We will lookup the position of the last occurrence of the mismatched character in the pattern, and if the mismatched character exists in the pattern, then we’ll shift the pattern such that it becomes aligned to the mismatched character in the text T.

![bad_match_heuristic_case_1](https://github.com/exitflynn/frep/assets/97532274/89c1e277-c083-4376-b193-421052cfec10)

Explanation: 

In the above example, we got a mismatch at position 3. Here our mismatching character is “A”. Now we will search for last occurrence of “A” in pattern. We got “A” at position 1 in pattern (displayed in Blue) and this is the last occurrence of it. Now we will shift pattern 2 times so that “A” in pattern get aligned with “A” in text.

Case 2 – Pattern move past the mismatch character 
We’ll lookup the position of last occurrence of mismatching character in pattern and if character does not exist we will shift pattern past the mismatching character.

![bad_match_heuristic_case_2](https://github.com/exitflynn/frep/assets/97532274/a88684d4-d63b-400e-a1a4-75a074fda6cc)

Explanation: 

Here we have a mismatch at position 7. The mismatching character “C” does not exist in pattern before position 7 so we’ll shift pattern past to the position 7 and eventually in above example we have got a perfect match of pattern (displayed in Green). We are doing this because “C” does not exist in the pattern so at every shift before position 7 we will get mismatch and our search will be fruitless.
In the following implementation, we preprocess the pattern and store the last occurrence of every possible character in an array of size equal to alphabet size. If the character is not present at all, then it may result in a shift by m (length of pattern). Therefore, the bad character heuristic takes O(n/m) time in the best case.

