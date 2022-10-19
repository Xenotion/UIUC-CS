#include "functions.hpp"

// Your function definitions should go in this source file.
const char *quote = "'";

int CheckStr(std::string& s) {
  std::vector<char> arr = {
      'b', 'c', 'd', 'f', 'g', 'j', 'q', 'r', 's', 't', 'v', 'x', 'y', 'z'};

  for (unsigned int i = 0; i < s.length(); i++) {
    for (unsigned int j = 0; j < arr.size(); j++) {
      if (s[i] == arr.at(j)) {
        return 1;  // found illegal char
      }
    }
  }

  return 0;
}

int CheckVow(char s) {
  std::vector<char> arr = {
      'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

  for (unsigned int i = 0; i < arr.size(); i++) {
    if (s == arr.at(i)) {
      return 1;  // found illegal char
    }
  }

  return 0;
}

int CheckCons(char s) {
  std::vector<char> arr = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

  for (unsigned int i = 0; i < arr.size(); i++) {
    if (s == arr.at(i)) {
      return 1; // found illegal char
    }
  }

  return 0;
}

std::string ConvStr(char c) {
  if (c == 'a' || c == 'A') {
    return "ah";
  }

  if (c == 'e' || c == 'E') {
    return "eh";
  }

  if (c == 'i' || c == 'I') {
    return "ee";
  }

  if (c == 'o' || c == 'O') {
    return "oh";
  }

  if (c == 'u' || c == 'U') {
    return "oo";
  }

  std::string s(1, static_cast<char>(tolower(c)));
  return s;
}

void Helper(const std::string& word, std::string& s, unsigned int& i) {
  if (static_cast<char>(tolower(word[i])) == 'a') {
    if ((static_cast<char>(tolower(word[i + 1])) == 'i' || static_cast<char>(tolower(word[i + 1])) == 'e')) {
      s += "eye";
      i++;
    } else if ((static_cast<char>(tolower(word[i + 1])) == 'o' || static_cast<char>(tolower(word[i + 1])) == 'u')) {
      s += "ow";
      i++;
    } else {
      s += ConvStr(word[i])[0];
      s += ConvStr(word[i])[1];
    }
  }
  else if (static_cast<char>(tolower(word[i])) == 'e' && static_cast<char>(tolower(word[i + 1])) == 'i') {
    s += "ay";
    i++;
  } else if (static_cast<char>(tolower(word[i])) == 'e' && static_cast<char>(tolower(word[i + 1])) == 'u') {
    s += "eh-oo";
    i++;
  } else if (static_cast<char>(tolower(word[i])) == 'i' && static_cast<char>(tolower(word[i + 1])) == 'u') {
    s += "ew";
    i++;
  } else if (static_cast<char>(tolower(word[i])) == 'o' && static_cast<char>(tolower(word[i + 1])) == 'i') {
    s += "oy";
    i++;
  } else if (static_cast<char>(tolower(word[i])) == 'o' && static_cast<char>(tolower(word[i + 1])) == 'u') {
    s += "ow";
    i++;
  } else if (static_cast<char>(tolower(word[i])) == 'u' && static_cast<char>(tolower(word[i + 1])) == 'i') {
    s += "ooey";
    i++;
  } else {
    s += ConvStr(word[i])[0];
    s += ConvStr(word[i])[1];
  }
}

std::string Solve(std::string word) {
  std::string s, s2, phonetics;
  for (unsigned int i = 0; i < word.length(); i++) {
    if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') || word[i] == *quote) {
      if (CheckCons(word[i]) == 1 && CheckCons((word[i + 1])) == 1) {
        if (CheckCons(word[i]) == 1 && CheckCons((word[i + 1])) == 1) {
          Helper(word, s, i);
        }
      } else if (i != 0 && (static_cast<char>(tolower(word[i])) == 'w' && (static_cast<char>(tolower(word[i-1])) == 'i' || static_cast<char>(tolower(word[i-1])) == 'e'))) {
        s += 'v';
      } else {
        s += ConvStr(word[i])[0];
        s += ConvStr(word[i])[1];
      }
      s2.push_back(word[i]);
      if (word[i + 1] != '\0' && word[i + 1] != ' ' && CheckVow(static_cast<char>(tolower(word[i]))) == 0 && word[i] != *quote && word[i + 1] != *quote) {  
        s += '-'; 
      } 
    } else if (word[i] == ' ') {
      if (CheckStr(s2) == 1) {
        return (s2 +  " contains a character not a part of the Hawaiian language.");
      }
      phonetics += (s + ' ');
      s = "";
    }
  }
  if (CheckStr(s2) == 1) {
    return (s2 + " contains a character not a part of the Hawaiian language.");
  }
  phonetics += s;
  return phonetics;
}