#include "temporary_file.hpp"
#include <filesystem>
#include <exception>
#include <random>

namespace fs = std::filesystem;


temporary_file::temporary_file(const std::string &device) : _device(device) , _file(nullptr){

    if(!_device.ends_with("/")){
        _device += "/";
    }

}

temporary_file::~temporary_file(){
    close();
}

void temporary_file::open(){

    if(is_open()){
        close();
    }


    std::string name(24, 0);

    std::mt19937_64 rg(std::random_device{}());

    std::uniform_int_distribution<char> uid('a','z');


    while(fs::exists(_device + name)){
        std::generate(name.begin(), name.end(),[&rg, &uid]()mutable{return uid(rg); });
    }


    const auto path = _device + name;

    _file = std::fopen(path.c_str(), "w");

    if(!_file){
        throw std::system_error(errno, std::generic_category(), path);
    }

    _path = path;

}

void temporary_file::close(){
    if(_file){
        std::fclose(_file);
    }

    if(std::filesystem::exists(_path)){
        std::filesystem::remove(_path);
    }
}

bool temporary_file::is_open() const{
    return _file;
}

void temporary_file::seek(){
    std::fseek(_file, 0, SEEK_SET);
}

std::size_t temporary_file::write(const std::string_view string){
    return std::fwrite(string.data(), sizeof (std::string_view::value_type), string.size(), _file);
}

std::size_t temporary_file::write(const std::span<const char> buf){
    return std::fwrite(buf.data(), sizeof (char), buf.size(),  _file);
}

std::string temporary_file::path() const{
    return _path;
}

void temporary_file::flush(){
    std::fflush(_file);
}

std::string temporary_file::device() const{
    return _device;
}
