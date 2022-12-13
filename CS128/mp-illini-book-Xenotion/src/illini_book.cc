#include "illini_book.hpp"

#include "utilities.hpp"

// void IlliniBook::PrintGraph() {
//   for (auto it = graph_.begin(); it != graph_.end(); ++it) {
//     std::cout << it->first << ": ";
//     for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
//       std::cout << it2->first << " ";
//       for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3) {
//         std::cout << *it3 << " ";
//       }
//       std::cout << std::endl;
//     }
//     std::cout << std::endl;
//   }
// }

IlliniBook::IlliniBook(const std::string& people_fpath, const std::string& relations_fpath) {
  std::ifstream people_file(people_fpath);

  if (!people_file.is_open()) {
    throw std::runtime_error("Could not open file: " + people_fpath);
  }

  std::string line;

  while (std::getline(people_file, line)) {
    graph_[std::stoi(line)];
  }

  people_file.close();

  std::ifstream relations_file(relations_fpath);

  if (!relations_file.is_open()) {
    throw std::runtime_error("Could not open file: " + relations_fpath);
  }

  while (std::getline(relations_file, line)) {
    std::vector<std::string> tokens = utilities::Split(line, ',');

    int uin_1 = std::stoi(tokens[0]);
    int uin_2 = std::stoi(tokens[1]);
    std::string relationship = tokens[2];

    graph_[uin_1][relationship].push_back(uin_2);
    graph_[uin_2][relationship].push_back(uin_1);
  }

  relations_file.close();
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  std::set<int> visited;
  std::queue<int> q;

  q.push(uin_1);

  while (!q.empty()) {
    int uin = q.front();
    q.pop();

    if (uin == uin_2) {
      return true;
    }

    visited.insert(uin);

    for (auto it = graph_.at(uin).begin(); it != graph_.at(uin).end(); ++it) {
      for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
        if (visited.find(*it2) == visited.end()) {
          q.push(*it2);
        }
      }
    }
  }

  return false;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string& relationship) const {
  std::set<int> visited;
  std::queue<int> q;

  q.push(uin_1);

  while (!q.empty()) {
    int uin = q.front();
    q.pop();

    if (uin == uin_2) {
      return true;
    }

    visited.insert(uin);

    for (auto it = graph_.at(uin).begin(); it != graph_.at(uin).end(); ++it) {
      if (it->first == relationship) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
          if (visited.find(*it2) == visited.end()) {
            q.push(*it2);
          }
        }
      }
    }
  }

  return false;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  std::set<int> visited; std::map<int, int> dist; std::map<int, int> prev;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    dist[it->first] = kMaxUin;
    prev[it->first] = -1;
  }
  dist[uin_1] = 0;
  pq.push(std::make_pair(0, uin_1));

  while (!pq.empty()) {
    int uin = pq.top().second;
    pq.pop();

    if (uin == uin_2) {
      int count = 0;
      while (prev[uin] != -1) {
        count++;
        uin = prev[uin];
      }
      return count;
    }
    visited.insert(uin);
    for (auto it = graph_.at(uin).begin(); it != graph_.at(uin).end(); ++it) {
      for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
        if (visited.find(*it2) == visited.end()) {
          int alt = dist[uin] + 1;
          if (alt < dist[*it2]) {
            dist[*it2] = alt;
            prev[*it2] = uin;
            pq.push(std::make_pair(alt, *it2));
          }
        }
      }
    }
  }
  return -1;
}

int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string& relationship) const {
  std::set<int> visited; std::map<int, int> dist; std::map<int, int> prev;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    dist[it->first] = kMaxUin;
    prev[it->first] = -1;
  }
  dist[uin_1] = 0;
  pq.push(std::make_pair(0, uin_1));

  while (!pq.empty()) {
    int uin = pq.top().second;
    pq.pop();
    if (uin == uin_2) {
      int count = 0;
      while (prev[uin] != -1) {
        count++;
        uin = prev[uin];
      }
      return count;
    }
    visited.insert(uin);
    for (auto it = graph_.at(uin).begin(); it != graph_.at(uin).end(); ++it) {
      if (it->first == relationship) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
          if (visited.find(*it2) == visited.end()) {
            int alt = dist[uin] + 1;
            if (alt < dist[*it2]) {
              dist[*it2] = alt;
              prev[*it2] = uin;
              pq.push(std::make_pair(alt, *it2));
            }
          }
        }
      }
    }
  }
  return -1;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::set<int> visited; std::map<int, int> dist; std::map<int, int> prev;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
 
  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    dist[it->first] = kMaxUin;
    prev[it->first] = -1;
  }
  dist[uin] = 0;
  pq.push(std::make_pair(0, uin));
 
  while (!pq.empty()) {
    int uin = pq.top().second;
    pq.pop();
    visited.insert(uin);
    for (auto it = graph_.at(uin).begin(); it != graph_.at(uin).end(); ++it) {
      for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
        if (visited.find(*it2) == visited.end()) {
          int alt = dist[uin] + 1;
          if (alt < dist[*it2]) {
            dist[*it2] = alt;
            prev[*it2] = uin;
            pq.push(std::make_pair(alt, *it2));
          }
        }
      }
    }
  }
 
  std::vector<int> result;
  for (auto it = dist.begin(); it != dist.end(); ++it) {
    if (it->second == n) {
      result.push_back(it->first);
    }
  }
  return result;
}

size_t IlliniBook::CountGroups() const {
  std::set<int> visited;
  std::queue<int> q;
  size_t count = 0;

  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    if (visited.find(it->first) == visited.end()) {
      q.push(it->first);
      count++;
    }

    while (!q.empty()) {
      int uin = q.front();
      q.pop();

      visited.insert(uin);

      for (auto it = graph_.at(uin).begin(); it != graph_.at(uin).end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
          if (visited.find(*it2) == visited.end()) {
            q.push(*it2);
          }
        }
      }
    }
  }

  return count;
}

size_t IlliniBook::CountGroups(const std::string& relationship) const {
  std::set<int> visited;
  std::queue<int> q;
  size_t count = 0;

  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    if (visited.find(it->first) == visited.end()) {
      q.push(it->first);
      count++;
    }

    while (!q.empty()) {
      int uin = q.front();
      q.pop();

      visited.insert(uin);

      for (auto it = graph_.at(uin).begin(); it != graph_.at(uin).end(); ++it) {
        if (it->first == relationship) {
          for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if (visited.find(*it2) == visited.end()) {
              q.push(*it2);
            }
          }
        }
      }
    }
  }

  return count;
}

size_t IlliniBook::CountGroups(const std::vector<std::string>& relationships) const {
  std::set<int> visited;
  std::queue<int> q;
  size_t count = 0;

  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    if (visited.find(it->first) == visited.end()) {
      q.push(it->first);
      count++;
    }

    while (!q.empty()) {
      int uin = q.front();
      q.pop();

      visited.insert(uin);

      for (auto it = graph_.at(uin).begin(); it != graph_.at(uin).end(); ++it) {
        for (auto it2 = relationships.begin(); it2 != relationships.end();
             ++it2) {
          if (it->first == *it2) {
            for (auto it3 = it->second.begin(); it3 != it->second.end();
                 ++it3) {
              if (visited.find(*it3) == visited.end()) {
                q.push(*it3);
              }
            }
          }
        }
      }
    }
  }

  return count;
}