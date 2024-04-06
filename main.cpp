#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void renameAndPrint(const fs::path& directory, int num) {
    int count = num;
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            const fs::path& filePath = entry.path();
            if (filePath.extension() == ".jpg" || filePath.extension() == ".jpeg" ||
                filePath.extension() == ".png" || filePath.extension() == ".gif") {
                fs::path newFilePath = entry.path().parent_path() / (std::to_string(count) + filePath.extension().string());
                fs::rename(filePath, newFilePath);
                std::cout << "<span><img src=\"./imgs/" << newFilePath.filename().string() << "\"></span>" << std::endl;
                count++;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <directory_path>" << " <num>" << std::endl;
        return 1;
    }

    fs::path directoryPath = argv[1]; // 从命令行参数获取目录路径
    renameAndPrint(directoryPath, std::stoi(argv[2]));
    return 0;
}
