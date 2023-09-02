#pragma once
#include <string>
#include <span>

class temporary_file{
public:


    temporary_file(const std::string &device);

    ~temporary_file();

    void open();

    void close();

    bool is_open()const;

    void seek();

    std::size_t write(const std::string_view string);

    std::size_t write(const std::span<const char> buf);

    std::string path()const;

    void flush();

    std::string device()const;

private:
    std::string _device;
    std::string _path;
    std::FILE* _file;

};
