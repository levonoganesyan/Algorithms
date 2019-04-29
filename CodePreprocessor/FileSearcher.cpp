
#include "FileSearcher.h"
#include <algorithm>
bool FileSearcher::CheckFileValidity(const std::wstring& filename)
{
    std::ifstream ifs;
    ifs.open(filename);
    return ifs.is_open();
}
FileSearcher::FileSearcher(const std::vector<std::wstring>& folder_paths)
    : m_folder_paths(folder_paths)
{
    for (auto& folder_path : m_folder_paths)
    {
        // Replacing all slashes by backslashes
        std::replace(std::begin(folder_path), 
                     std::end(folder_path), 
                     L'\\', L'/');

        if (folder_path == L"/") // case of root in POSIX
        {
            continue;
        }
        while (folder_path.size() && folder_path.back() == L'/')
        {
            folder_path.pop_back();
        }
    }
}

std::wstring FileSearcher::CheckForFile(const std::wstring & file_name) const
{
    for (auto& folder_path : m_folder_paths)
    {
        std::wstring full_file_path = folder_path + L"/" + file_name;
        if (CheckFileValidity(full_file_path))
        {
            return full_file_path;
        }
    }
    return L"";
}



