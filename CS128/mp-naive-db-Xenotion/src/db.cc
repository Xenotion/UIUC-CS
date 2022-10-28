#include "db.hpp"

void Database::CreateTable(const std::string& table_name) {
  tables_[table_name] = new DbTable();
}

void Database::DropTable(const std::string& table_name) {
  if (tables_.find(table_name) == tables_.end()) {
    throw std::invalid_argument("Table does not exist");
  }
  delete tables_[table_name];
  tables_.erase(table_name);
}

DbTable& Database::GetTable(const std::string& table_name) {
  if (tables_.find(table_name) == tables_.end()) {
    throw std::invalid_argument("Table does not exist");
  }
  return *tables_[table_name];
}

Database::Database(const Database& rhs) {
  for (const auto& table : rhs.tables_) {
    tables_[table.first] = new DbTable(*table.second);
  }
}

Database& Database::operator=(const Database& rhs) {
  if (this != &rhs) {
    for (const auto& table : tables_) {
      delete table.second;
    }
    tables_.clear();
    for (const auto& table : rhs.tables_) {
      tables_[table.first] = new DbTable(*table.second);
    }
  }
  return *this;
}

Database::~Database() {
  for (const auto& table : tables_) {
    delete table.second;
  }
  tables_.clear();
}

std::ostream& operator<<(std::ostream& os, const Database& db) {
  for (const auto& table : db.tables_) {
    os << *table.second << std::endl;
  }
  return os;
}