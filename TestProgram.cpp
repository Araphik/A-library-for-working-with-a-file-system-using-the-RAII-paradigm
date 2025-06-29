#include <iostream>
#include "FileRAII.h"

void demonstrateFileOperations() {
    try {
        // 1. Создание и запись в файл
        {
            std::cout << "Creating and writing to test.txt...\n";
            FileRAII file("test.txt", std::ios::out);
            file.writeLine("Hello, RAII!");
            file.writeLine("This is a test file.");
            file.writeLine("Goodbye!");
        }
        
        // 2. Чтение из файла
        {
            std::cout << "\nReading from test.txt...\n";
            FileRAII file("test.txt", std::ios::in);
            
            try {
                while (true) {
                    std::string line = file.readLine();
                    std::cout << "Read line: " << line << std::endl;
                }
            } catch (const std::runtime_error& e) {
                if (std::string(e.what()).find("End of file") != std::string::npos) {
                    std::cout << "Finished reading file normally.\n";
                } else {
                    throw;
                }
            }
        }
        
        // 3. Попытка открыть несуществующий файл (должно вызвать исключение)
        std::cout << "\nTrying to open non-existent file...\n";
        FileRAII nonexistent("nonexistent.txt", std::ios::in);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

     // 5. Тестирование метода isOpen()

    {
        std::cout << "\nTesting isOpen() method...\n";
        FileRAII file("test_for_isopen.txt", std::ios::out);
        std::cout << "File is open: " << (file.isOpen() ? "true" : "false") << std::endl;
        file.close();
        std::cout << "File is open after close: " << (file.isOpen() ? "true" : "false") << std::endl;
    }

     // 6. Тестирование режима добавления (append)

    {
        std::cout << "\nTesting append mode...\n";
        FileRAII file("test.txt", std::ios::out | std::ios::app);
        file.writeLine("Appended line");
        FileRAII readFile("test.txt", std::ios::in);
        try {
            while (true) {
                std::string line = readFile.readLine();
                std::cout << "Read line: " << line << std::endl;
            }
        } catch (const std::runtime_error& e) {
            if (std::string(e.what()).find("End of file") != std::string::npos) {
                std::cout << "Finished reading appended file normally.\n";
            } else {
                throw;
            }
        }
    }

    // 6. Тестирование чтения и записи в одном файле
    {
        std::cout << "\nTesting read and write in the same file...\n";
        FileRAII file("readwrite.txt", std::ios::in | std::ios::out | std::ios::trunc);
        file.writeLine("Read/Write test line");
        file.writeLine("Second line");
        file.close();
        FileRAII readFile("readwrite.txt", std::ios::in);
        try {
            while (true) {
                std::string line = readFile.readLine();
                std::cout << "Read line: " << line << std::endl;
            }
        } catch (const std::runtime_error& e) {
            if (std::string(e.what()).find("End of file") != std::string::npos) {
                std::cout << "Finished reading read/write file normally.\n";
            } else {
                throw;
            }
        }
    }

    // 7. Тестирование обработки пустого файла
    {
        std::cout << "\nTesting empty file handling...\n";
        FileRAII file("empty.txt", std::ios::out | std::ios::trunc);
        file.close();
        FileRAII readFile("empty.txt", std::ios::in);
        try {
            readFile.readLine();
        } catch (const std::runtime_error& e) {
            if (std::string(e.what()).find("End of file") != std::string::npos) {
                std::cout << "Correctly caught EOF on empty file.\n";
            } else {
                throw;
            }
        }
    }
}

int main() {
    demonstrateFileOperations();
    return 0;
}