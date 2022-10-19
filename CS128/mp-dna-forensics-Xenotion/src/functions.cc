#include "functions.hpp"

int MostFreq(std::string& str, std::string& sequence) {
  int max = 0, curr = 0;
  std::string temp;

  for (unsigned int i = 0; i <= (sequence.length() - str.length()); i++) {
    if (sequence.at(i) == str.at(0)) {
      
      for (unsigned int j = i; j < i + str.length(); j++) {
        temp += sequence.at(j);
      }

      if (temp == str) {
        curr++;
        i += (str.length() - 1);
        temp.clear();
      } else {
        temp.clear();
        curr = 0;
      }

      if (curr > max) {
        max = curr;
      }
    } else {
      if (curr > max) {
        max = curr;
      }
      curr = 0;
      continue;
    }
  }
  
  return max;
}

void HelperTwo(std::string& sequence, std::string& line, std::string& s, std::vector<std::string>& lookup2, std::vector<int>& lookup3) {

  for (unsigned int i = 0; i < line.length(); i++) {
    if ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z')) {
      s += line[i];
    } else if (line[i] == ',' || line[i] == '\0') {
      if (s[0] == 'A' || s[0] == 'T' || s[0] == 'G' || s[0] == 'C') {
        lookup2.push_back(s);
        s.clear();
      } else {
        s.clear();
      }
    }
  }

  lookup2.push_back(s);

  for(unsigned int i=0; i < lookup2.size(); i++) {
    int temp = MostFreq(lookup2.at(i), sequence);
    lookup3.push_back(temp);
  } 
}

int Helper(std::string& file, std::string& sequence) {
  std::vector<std::string> lookup2;
  std::vector<int> lookup3;
  std::ifstream ifs{file};
  std::string line;
  std::getline(ifs, line);
  std::string s;
  
  HelperTwo(sequence, line, s, lookup2, lookup3);

  for(std::string line; std::getline(ifs, line); line = "") {
    std::vector<int> temp;
    for (unsigned int i = 0; i < line.length(); i++) {
      std::string stemp;
      if (!((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z') || line[i] == ',')) {
        stemp += line[i];
        temp.push_back(std::stoi(stemp));
        stemp.clear();
      } else {
        continue;
      }
    }

    if (lookup3 == temp) {
      std::string temp;
      for (unsigned int i = 0; i < line.length(); i++) {
        if ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z')) {
          temp += line[i];
        } else if (line[i] == ',') {
          break;
        }
      }
      std::cout << temp << std::endl;
      return 0;
    } 
  }
  std::cout << "No Match" << std::endl;
  return 0;
}