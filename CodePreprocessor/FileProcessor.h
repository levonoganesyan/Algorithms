#pragma once
#include<memory>
#include<string>
#include<vector>
class FileSearcher;

class FileProcessor
{
    std::shared_ptr<FileSearcher> mp_file_searcher;
    std::wstring m_file_path;
public:

    FileProcessor(const std::wstring& file_name,
                  const std::vector<std::wstring>& folder_paths);
    void Process() const;
};

