#pragma once
#include <vector>

#include "temporary_file.hpp"

class Test
{
public:
    Test();



    double seq1m_write(temporary_file &file, std::size_t write_bytes, std::size_t repeat);
    double seq512k_write(temporary_file &file, std::size_t write_bytes, std::size_t repeat);
    double seq1G_write(temporary_file &file, std::size_t write_bytes, std::size_t repeat);



    std::vector<std::pair<std::string, std::string>> seq_write_test(temporary_file &file, std::size_t write_bytes, std::size_t repeat);

private:
    double _seq_wrtie_test(temporary_file &file, std::size_t write_bytes, const std::size_t chunk_bytes);


};

