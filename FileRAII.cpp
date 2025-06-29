#include "FileRAII.h"

FileRAII::FileRAII(const std::string& filename, std::ios_base::openmode mode) 
    : filename(filename) {
    auto* raw_file = new std::fstream();
    raw_file->open(filename, mode);
    if (!raw_file->is_open()) {
        delete raw_file;
        throw std::runtime_error("Failed to open file: " + filename);
    }
    file.reset(raw_file);
}

std::string FileRAII::readLine() {
    if (!file || !file->is_open()) {
        throw std::runtime_error("File is not open for reading: " + filename);
    }
    
    std::string line;
    if (!std::getline(*file, line)) {
        if (file->eof()) {
            throw std::runtime_error("End of file reached: " + filename);
        } else {
            throw std::runtime_error("Error reading from file: " + filename);
        }
    }
    return line;
}

void FileRAII::writeLine(const std::string& line) {
    if (!file || !file->is_open()) {
        throw std::runtime_error("File is not open for writing: " + filename);
    }
    
    *file << line << std::endl;
    if (file->fail()) {
        throw std::runtime_error("Error writing to file: " + filename);
    }
}

bool FileRAII::isOpen() const {
    return file && file->is_open();
}

void FileRAII::close() {
    if (file && file->is_open()) {
        file->close();
    }
}