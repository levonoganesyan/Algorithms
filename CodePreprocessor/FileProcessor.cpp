#include "FileProcessor.h"
#include "FileSearcher.h"
#include <regex>
#include <iostream>
#include <stack>
#include <set>
FileProcessor::FileProcessor(const std::wstring& file_path, 
                             const std::vector<std::wstring>& folder_paths)
    : mp_file_searcher(new FileSearcher(folder_paths))
    , m_file_path(file_path)
{
    if (!FileSearcher::CheckFileValidity(m_file_path))
    {
        throw std::logic_error("Source file failed to open");
    }
}

void FileProcessor::Process() const
{
    std::wstring output_file_name = m_file_path;
    std::size_t pos_of_last_dot = output_file_name.find_last_of(L'.');
    output_file_name.insert(pos_of_last_dot, L"_processed");
    std::wofstream out_file(output_file_name);

    std::stack<std::wifstream> files_to_process;
    files_to_process.emplace(m_file_path);
    std::wregex e(L"#include\\s*[<\"](.*)[\">].*");

    std::set<std::wstring> processed_files;
    processed_files.insert(m_file_path);

    while (!files_to_process.empty())
    {
        std::wifstream& ifs = files_to_process.top();
        std::wstring line;
        if (!std::getline(ifs, line))
        {
            files_to_process.pop();
            continue;
        }
        std::wsmatch sm;
        std::regex_match(line, sm, e);
        if (sm.empty())
        {
            out_file << line << std::endl;
            continue;
        }
        std::wstring h_name = sm[1];
        std::wstring h_path = mp_file_searcher->CheckForFile(h_name);
        if (!h_path.empty())
        {
            
            if (h_path.back() == L'h')
            {
                std::wstring cpp_name = h_name;
                cpp_name.pop_back();
                cpp_name += L"cpp";
                std::wstring cpp_path = 
                            mp_file_searcher->CheckForFile(cpp_name);

                if (!cpp_path.empty())
                {
                    auto file_processed_it = processed_files.find(cpp_path);
                    if (file_processed_it == processed_files.end())
                    {
                        files_to_process.emplace(cpp_path);
                        processed_files.insert(cpp_path);
                    }
                }
            }
            if (processed_files.find(h_path) == processed_files.end())
            {
                files_to_process.emplace(h_path);
                processed_files.insert(h_path);
            }
        }
    }
}
