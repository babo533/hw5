#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Add prototypes of helper functions here
void fillWords(std::set<std::string>& words, 
             std::string currentWord, 
             const std::string& floating,
             const std::set<std::string>& dict, 
             size_t index = 0);


// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict) {
  // Add your code here
  std::set<std::string> validWords;
  fillWords(validWords, in, floating, dict);  
  return validWords;
}

// Define any helper functions here
void fillWords(std::set<std::string>& words,
             std::string currentWord,
             const std::string& floating,
             const std::set<std::string>& dict,
             size_t index) {
  if (index == currentWord.size()) {
    if (dict.find(currentWord) != dict.end()) {
      words.insert(currentWord);
    }
    return;
  }

  if (currentWord[index] != '-') {
    fillWords(words, currentWord, floating, dict, index + 1);
  } 
  else {
    // use floating letters first if available
    if (!floating.empty()) {
      for (size_t i = 0; i < floating.size(); ++i) {
        string newWord = currentWord;
        newWord[index] = floating[i];
        string newFloating = floating;
        newFloating.erase(i, 1);
        fillWords(words, newWord, newFloating, dict, index + 1);
      }
    }

      // check if we should fillusing the alphabet
    int numLetters = 0;
    for (char c : currentWord) {
      if (c != '-') {
        numLetters++;
      }
    }

    // use alphabet if not all holders can be filled by floating letters
    unsigned int temp = numLetters + floating.size();
    if (temp < currentWord.size()) {
      for (char ch = 'a'; ch <= 'z'; ++ch) {
        currentWord[index] = ch;
        fillWords(words, currentWord, floating, dict, index + 1);
        currentWord[index] = '-'; // change the placeholder back
      }
    }
  }
}