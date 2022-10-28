#include "db_table.hpp"

const unsigned int kRowGrowthRate = 2;

void DbTable::CheckAddColumn(auto& row, const std::pair<std::string, DataType>& col_desc) {
  if (col_desc.second == DataType::kString) {
    row.second[col_descs_.size() - 1] = new std::string();
  } else if (col_desc.second == DataType::kInt) {
    row.second[col_descs_.size() - 1] = new int(0);
  } else if (col_desc.second == DataType::kDouble) {
    row.second[col_descs_.size() - 1] = new double(0.0);
  }
}

void DbTable::CheckDeleteColumnByIdx(auto& row, unsigned int col_idx) {
  if (col_descs_[col_idx].second == DataType::kString) {
    delete static_cast<std::string*>(row.second[col_idx]);
  } else if (col_descs_[col_idx].second == DataType::kInt) {
    delete static_cast<int*>(row.second[col_idx]);
  } else if (col_descs_[col_idx].second == DataType::kDouble) {
    delete static_cast<double*>(row.second[col_idx]);
  }
}

void DbTable::CheckAddRow(unsigned int i, const std::initializer_list<std::string>& col_data) {
  if (col_descs_[i].second == DataType::kString) {
    rows_[next_unique_id_ - 1][i] = new std::string(col_data.begin()[i]);
  } else if (col_descs_[i].second == DataType::kInt) {
    rows_[next_unique_id_ - 1][i] = new int(std::stoi(col_data.begin()[i]));
  } else if (col_descs_[i].second == DataType::kDouble) {
    rows_[next_unique_id_ - 1][i] = new double(std::stod(col_data.begin()[i]));
  }
}

void DbTable::CheckDeleteRowById(unsigned int i, unsigned int id) {
  if (col_descs_[i].second == DataType::kString) {
    delete static_cast<std::string*>(rows_[id][i]);
  } else if (col_descs_[i].second == DataType::kInt) {
    delete static_cast<int*>(rows_[id][i]);
  } else if (col_descs_[i].second == DataType::kDouble) {
    delete static_cast<double*>(rows_[id][i]);
  }
}

void DbTable::CheckDbTable(unsigned int i, void** new_row, auto& row) {
  if (col_descs_[i].second == DataType::kString) {
    new_row[i] = new std::string(*static_cast<std::string*>(row.second[i]));
  } else if (col_descs_[i].second == DataType::kInt) {
    new_row[i] = new int(*static_cast<int*>(row.second[i]));
  } else if (col_descs_[i].second == DataType::kDouble) {
    new_row[i] = new double(*static_cast<double*>(row.second[i]));
  }
}

void DbTable::CheckOperator(unsigned int i, auto& row, void** new_row, int option) {
  if (option == 0) {
    if (col_descs_[i].second == DataType::kString) {
      delete static_cast<std::string*>(row.second[i]);
    } else if (col_descs_[i].second == DataType::kInt) {
      delete static_cast<int*>(row.second[i]);
    } else if (col_descs_[i].second == DataType::kDouble) {
      delete static_cast<double*>(row.second[i]);
    }
  } else if (option == 1) {
    if (col_descs_[i].second == DataType::kString) {
      new_row[i] = new std::string(*static_cast<std::string*>(row.second[i]));
    } else if (col_descs_[i].second == DataType::kInt) {
      new_row[i] = new int(*static_cast<int*>(row.second[i]));
    } else if (col_descs_[i].second == DataType::kDouble) {
      new_row[i] = new double(*static_cast<double*>(row.second[i]));
    }
  }
}

void DbTable::CheckDestruct(auto& row, unsigned int i) {
  if (col_descs_[i].second == DataType::kString) {
    delete static_cast<std::string*>(row.second[i]);
  } else if (col_descs_[i].second == DataType::kInt) {
    delete static_cast<int*>(row.second[i]);
  } else if (col_descs_[i].second == DataType::kDouble) {
    delete static_cast<double*>(row.second[i]);
  }
}

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) {
    for (auto& row : rows_) {
      void** new_row = new void*[static_cast<unsigned int>(row_col_capacity_ * kRowGrowthRate)];
      for (unsigned int i = 0; i < row_col_capacity_; ++i) {
        new_row[i] = row.second[i];
      }
      delete[] row.second;
      row.second = new_row;
    }
    row_col_capacity_ *= kRowGrowthRate;
  }

  col_descs_.push_back(col_desc);

  for (auto& row : rows_) {
    CheckAddColumn(row, col_desc);
  }
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx >= col_descs_.size()) {
    throw std::out_of_range("nope");
  }

  if (col_descs_.size() == 1 && !rows_.empty()) {
    throw std::runtime_error("nope");
  }

  for (auto& row : rows_) {
    CheckDeleteColumnByIdx(row, col_idx);
    for (unsigned int i = col_idx; i < col_descs_.size() - 1; ++i) {
      row.second[i] = row.second[i + 1];
    }
  }

  col_descs_.erase(col_descs_.begin() + col_idx);
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size()) {
    throw std::invalid_argument("nope");
  }

  void** new_row = new void*[row_col_capacity_];
  rows_[next_unique_id_++] = new_row;

  for (unsigned int i = 0; i < col_descs_.size(); ++i) {
    CheckAddRow(i, col_data);
  }
}

void DbTable::DeleteRowById(unsigned int id) {
  if (rows_.find(id) == rows_.end()) {
    throw std::out_of_range("nope");
  }
  for (unsigned int i = 0; i < col_descs_.size(); ++i) {
    CheckDeleteRowById(i, id);
  }

  delete[] rows_[id];
  rows_.erase(id);
}

DbTable::DbTable(const DbTable& rhs) {
  col_descs_ = rhs.col_descs_;
  row_col_capacity_ = rhs.row_col_capacity_;
  next_unique_id_ = rhs.next_unique_id_;
  for (const auto& row : rhs.rows_) {
    void** new_row = new void*[row_col_capacity_];
    for (unsigned int i = 0; i < col_descs_.size(); ++i) {
      CheckDbTable(i, new_row, row);
    }
    rows_[row.first] = new_row;
  }
}

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this != &rhs) {
    for (auto& row : rows_) {
      for (unsigned int i = 0; i < col_descs_.size(); ++i) {
        CheckOperator(i, row, nullptr, 0);
      }
      delete[] row.second;
    }
    rows_.clear();
    col_descs_ = rhs.col_descs_;
    row_col_capacity_ = rhs.row_col_capacity_;
    next_unique_id_ = rhs.next_unique_id_;
    for (const auto& row : rhs.rows_) {
      void** new_row = new void*[row_col_capacity_];
      for (unsigned int i = 0; i < col_descs_.size(); ++i) {
        CheckOperator(i, row, new_row, 1);
      }
      rows_[row.first] = new_row;
    }
  }
  return *this;
}

DbTable::~DbTable() {
  for (auto& row : rows_) {
    for (unsigned int i = 0; i < col_descs_.size(); ++i) {
      CheckDestruct(row, i);
    }
    delete[] row.second;
  }
}

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  for (unsigned int i = 0; i < table.col_descs_.size(); ++i) {
    os << table.col_descs_[i].first << "(";
    switch (table.col_descs_[i].second) {
    case DataType::kString:
      os << "std::string";
      break;
    case DataType::kInt:
      os << "int";
      break;
    case DataType::kDouble:
      os << "double";
      break;
    }
    os << ")";
    if (i != table.col_descs_.size() - 1) {
      os << ", ";
    }
  }
  os << std::endl;
  for (const auto& row : table.rows_) {
    for (unsigned int i = 0; i < table.col_descs_.size(); ++i) {
      switch (table.col_descs_[i].second) {
      case DataType::kString:
        os << *static_cast<std::string*>(row.second[i]);
        break;
      case DataType::kInt:
        os << *static_cast<int*>(row.second[i]);
        break;
      case DataType::kDouble:
        os << *static_cast<double*>(row.second[i]);
        break;
      }
      if (i != table.col_descs_.size() - 1) {
        os << ", ";
      }
    }
    os << std::endl;
  }
  return os;
}