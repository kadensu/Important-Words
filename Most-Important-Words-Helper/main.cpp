//
//  main.cpp
//  Most-Important-Words-Helper
//
//  Created by Kaden Sukachevin on 10/26/17.
//  Copyright © 2017 Kaden Sukachevin. All rights reserved.
//
//  Loads a word into a dictionary, and allows the user to search for a word in said dictionay.
//      The number of appearances of the word is returned.

#include <iostream>
#include <fstream>
#include <string>

struct Node {
    Node *children[26]; // Allows for 26 alphabetical characters + 14 punctuation characters
    int count = 0;
};

// Creates a node, ensuring all elemnts are 0 or NULL
struct Node *createNode() {
    
    struct Node * n = new Node;
    n -> count = 0;
    
    for (int i = 0; i < 26; i++) {
        n->children[i] = NULL;
    }
    
    return n;
}

void store(std::string word, Node *root);
int findWord(Node *root, std::string word);
void clear(Node * n);
void printWords(Node *root, std::string word);
char indexToCharConverter(int i);
int charToIndexConverter(char c);

int main(int argc, const char * argv[]) {
    
    std::ifstream test;
    test.open( "/Users/KadenSukachevin/Documents/Xcode/Personal-Projects/Most-Important-Words-Helper/Most-Important-Words-Helper/data2.txt" );
    std::string word;
    
    Node *root = createNode(); // Root node of the trie
    
    // Exit program if there is a probelem opening the file
    if (!test) {
        std::cout << "There was a problem opening the file. Exiting now.\n";
        return 1;
    }
    
    while (test.good()) {
        getline(test, word, ' ');
        
        if (word != "") {
            for (int i = 0; i < word.length(); i++) {
                if (!isalpha(word[i])) {
                    word = word.substr(0, i);
                    break;
                }
            }
            //std::cout << "Word: " << word << std::endl;
            store(word, root);
        }
    }
    
    bool isChar = true;
    
    while (true) {
        std::cout << "Enter word to find (to exit, \"q\"): ";
        std::string word_to_find = "";
        std::cin >> word_to_find;
        
        if (word_to_find == "q") {
            break;
        }
        
        for (int i = 0; i < word_to_find.length(); i++) {
            if (!isalpha(tolower(word_to_find[i]))) {
                isChar = false;
                std::cout << "ERR0R: Please enter an alphabetical word.\n";
                break;
            }
        }
        
        if (isChar) {
            int num_words = findWord(root, word_to_find);
            std::cout << "Appearances of " << word_to_find << ": " << num_words << std::endl;
        }
    }
    
    printWords(root, "");
    clear(root);
    
    // Function that prints out the results needed
    
    return 0;
}

// Adds words from the file to the trie that stores all the words
void store(std::string word, Node *root) {
    
    // Creates new pointer pointing at root pointer
    Node *ptr = createNode();
    ptr = root;
    int index = 0;
    
    for (int i = 0; i < word.length(); i++) {
        // for loop iterating through every character in word
        char c = std::tolower(word[i]); // Ensures all characters are lower case
        index = c - 'a';
        if (!ptr -> children[index]) {
            ptr -> children[index] = createNode();
        }
        ptr = ptr -> children[index];
    }
    
    ptr -> count++;
}

// Returns the instances of a
int findWord(Node *root, std::string word) {
    Node *ptr = createNode();
    ptr = root;
    
    for (int i = 0; i < word.length(); i++) {
        char c = std::tolower(word[i]);
        int index = c - 'a';
        
        if (!ptr -> children[index]) {
            return 0;
        }
        ptr = ptr -> children[index];
    }
    
    return ptr -> count;
}

// Lists the words and the number of times they appear in alphabetical order
void printWords(Node *root, std::string word) {
    Node *ptr = createNode();
    ptr = root;
    
    if (ptr -> count > 0) {
        word[0] = toupper(word[0]);
        std::cout << word << ":\t" << ptr->count << std::endl;
    }
    
    for (int i = 0; i < 26; i++) {
        if (ptr -> children[i]) {
            char c = i + 'a';
            printWords(ptr=ptr->children[i], word+c);
        }
        ptr = root;
    }
}

// TODO
// Not needed?
// Coverts index to corresponding char
char indexToCharConverter(int i) {
    
    if (i < 26) {
        return i + 'a';
    }
    
    return 0;
}

// TODO
// Not needed?
// Converts char to corresponding index
int charToIndexConverter(char c) {
    
    if ((0 <= c - 'a') && (c - 'a' <= 26)) {
        return c - 'a';
    }
    
    
    
    return 0;
}

// Frees memory from trie
void clear(Node* n) {
    for (int i = 0; i < 26; i++)
    {
        if (n->children[i])
        {
            clear(n->children[i]);
        }
    }
    
    delete n;
}
