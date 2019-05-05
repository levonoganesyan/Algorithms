#include<iostream>
#include"FileProcessor.h"

int wmain(int argc, wchar_t** argv) try
{
    std::wstring file_path = argv[1];
    std::vector<std::wstring> folder_paths;
    for (int i = 2; i < argc; ++i)
    {
        folder_paths.push_back(argv[i]);
    }
    FileProcessor file_processor(file_path, folder_paths);
    file_processor.Process();
    std::cout << "Code preprocessing is "
                << "successfully finished!"
                << std::endl;
}
catch (const std::exception& ex)
{
    std::cout << ex.what() << std::endl;
}




