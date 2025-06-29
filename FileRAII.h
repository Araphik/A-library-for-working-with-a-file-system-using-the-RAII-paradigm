#ifndef FILE_RAII_H
#define FILE_RAII_H

#include <string>
#include <fstream>
#include <memory>
#include <stdexcept>

#define FILE_RAII_API

class FileRAII {
public:
    FILE_RAII_API FileRAII(const std::string& filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out);
    FILE_RAII_API ~FileRAII() = default;
    FILE_RAII_API std::string readLine();
    FILE_RAII_API void writeLine(const std::string& line);
    FILE_RAII_API bool isOpen() const;
    FILE_RAII_API void close();

private:
    struct FileDeleter {
        void operator()(std::fstream* file) const {
            if (file && file->is_open()) {
                file->close();
            }
            delete file;
        }
    };

    std::unique_ptr<std::fstream, FileDeleter> file;
    std::string filename;
};

#endif