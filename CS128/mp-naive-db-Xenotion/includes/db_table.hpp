#ifndef TABLE_HPP
#define TABLE_HPP

#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

enum class DataType { kString, kDouble, kInt };

class DbTable {
public:
  DbTable() = default;
  
  void CheckAddColumn(auto& row, const std::pair<std::string, DataType>& col_desc);
  void CheckDeleteColumnByIdx(auto& row, unsigned int col_idx);
  void CheckAddRow(unsigned int i, const std::initializer_list<std::string>& col_data);
  void CheckDeleteRowById(unsigned int i, unsigned int id);
  void CheckDbTable(unsigned int i, void** new_row, auto& row);
  void CheckOperator(unsigned int i, auto& row, void** new_row, int option);
  void CheckDestruct(auto& row, unsigned int i);

  void AddColumn(const std::pair<std::string, DataType>& col_desc);
  void DeleteColumnByIdx(unsigned int col_idx);

  void AddRow(const std::initializer_list<std::string>& col_data);
  void DeleteRowById(unsigned int id);

  DbTable(const DbTable& rhs);
  DbTable& operator=(const DbTable& rhs);
  ~DbTable();

  friend std::ostream& operator<<(std::ostream& os, const DbTable& table);

private:
  unsigned int next_unique_id_ = 0;
  unsigned int row_col_capacity_ = 2;
  std::map<unsigned int, void**> rows_;
  std::vector<std::pair<std::string, DataType>> col_descs_;
};

// std::ostream& operator<<(std::ostream& os, const DbTable& table);

#endif