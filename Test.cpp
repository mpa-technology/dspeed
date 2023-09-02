#include "Test.hpp"


#include <chrono>

Test::Test()
{

}

double Test::_seq_wrtie_test(temporary_file &file, std::size_t write_bytes, const std::size_t chunk_bytes){
    std::vector<char> zero(chunk_bytes, 0);


    const auto start_time = std::chrono::high_resolution_clock::now();

    for(std::size_t i = 0; i <= write_bytes; i += chunk_bytes){
        file.write(zero);
    }

    file.flush();


    const auto end_time = std::chrono::high_resolution_clock::now();

    const auto work_time = end_time - start_time;

    const double sec = static_cast<double>(work_time.count()) / 1e+9;

    const double mb_sec = (static_cast<double>(write_bytes) / sec)/(1048576);

    return mb_sec;
}

double Test::seq1m_write(temporary_file &file, std::size_t write_bytes, std::size_t repeat){

    double sum = 0;

    for(std::size_t i = 0; i != repeat; ++i){
        file.open();
        sum += _seq_wrtie_test(file, write_bytes, 1048576);
    }




    return sum/static_cast<double>(repeat);
}

double Test::seq512k_write(temporary_file &file, std::size_t write_bytes, std::size_t repeat)
{
    double sum = 0;

    for(std::size_t i = 0; i != repeat; ++i){
        file.open();
        sum += _seq_wrtie_test(file, write_bytes, 524288);
    }



    return sum/static_cast<double>(repeat);
}

double Test::seq1G_write(temporary_file &file, std::size_t write_bytes, std::size_t repeat)
{
    double sum = 0;

    for(std::size_t i = 0; i != repeat; ++i){
        file.open();
        sum += _seq_wrtie_test(file, write_bytes, 1073741824);
    }


    return sum/static_cast<double>(repeat);
}

std::vector<std::pair<std::string, std::string> > Test::seq_write_test(temporary_file &file, std::size_t write_bytes, std::size_t repeat){


    const auto t1_result = seq1m_write(file,write_bytes, repeat);
    const auto t2_result = seq512k_write(file, write_bytes, repeat);
    const auto t3_result = seq1G_write(file,write_bytes, repeat);

    std::pair<std::string, std::string> seq1m;
    seq1m.first = "seq 1m";
    seq1m.second = std::to_string(t1_result) + " MB/s";


    std::pair<std::string, std::string> seq512k;
    seq512k.first = "seq 512k";
    seq512k.second = std::to_string(t2_result) + " MB/s";


    std::pair<std::string, std::string> seq1g;
    seq1g.first = "seq 1g";
    seq1g.second = std::to_string(t3_result) + " MB/s";


    return {seq1g, seq1m, seq512k};
}
