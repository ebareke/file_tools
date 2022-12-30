#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <vector>

class FileMerger {
public:
    FileMerger(const std::vector<std::string>& files, const std::vector<int>& key_columns, const std::vector<char>& separators)
        : files_(files), key_columns_(key_columns), separators_(separators) {}

    void ReadData() {
        data_.clear();
        for (size_t i = 0; i < files_.size(); ++i) {
            std::ifstream file(files_[i]);
            std::string line;
            while (std::getline(file, line)) {
                std::vector<std::string> row;
                size_t start = 0;
                size_t end = line.find(separators_[i]);
                while (end != std::string::npos) {
                    row.emplace_back(line.substr(start, end - start));
                    start = end + 1;
                    end = line.find(separators_[i], start);
                }
                row.emplace_back(line.substr(start));
                data_[files_[i]][row[key_columns_[i]]] = row;
            }
        }
    }

    std::vector<std::vector<std::string>> MergeData() {
        std::set<std::string> keys;
        for (const auto& [file, rows] : data_) {
            std::set<std::string> file_keys;
            for (const auto& [key, row] : rows) {
                file_keys.insert(key);
            }
            if (keys.empty()) {
                keys = std::move(file_keys);
            } else {
                std::set<std::string> new_keys;
                std::set_intersection(keys.begin(), keys.end(), file_keys.begin(), file_keys.end(),
                                      std::inserter(new_keys, new_keys.begin()));
                keys = std::move(new_keys);
            }
        }

        std::vector<std::vector<std::string>> merged_rows;
        for (const auto& key : keys) {
            std::vector<std::string> merged_row;
            for (size_t i = 0; i < files_.size(); ++i) {
                const auto& rows = data_[files_[i]];
                const auto it = rows.find(key);
                if (it != rows.end()) {
                    merged_row.insert(merged_row.end(), it->second.begin(), it->second.end());
                } else {
                    merged_row.emplace_back("-");
                }
            }
            merged_rows.emplace_back(std::move(merged_row));
        }
        return merged_rows;
    }

    void WriteToFile(const std::string& output_file) {
        std::ofstream file(output_file);
       
