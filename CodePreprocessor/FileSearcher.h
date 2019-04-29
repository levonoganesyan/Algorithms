#pragma once

#include<fstream>
#include<string>
#include<vector>

class FileSearcher
{
    std::vector<std::wstring> m_folder_paths;

public:
    static bool CheckFileValidity(const std::wstring& filename);

public:
    FileSearcher(const std::vector<std::wstring>& folder_paths);
    std::wstring CheckForFile(const std::wstring& file_name) const;
};