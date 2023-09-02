#include "Test.hpp"
#include "temporary_file.hpp"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char **argv) {

  std::size_t file_size;
  std::size_t test_repeat;

  po::options_description desc("General options");
  desc.add_options()("help,h", "show help")(
      "size,s", po::value<std::size_t>(&file_size)->default_value(1073741824),
      "file test size")("repeat,r",
                        po::value<std::size_t>(&test_repeat)->default_value(5),
                        "repeat test");
  po::variables_map vm;
  po::parsed_options parsed = po::command_line_parser(argc, argv)
                                  .options(desc)
                                  .allow_unregistered()
                                  .run();
  po::store(parsed, vm);
  po::notify(vm);

  auto list = po::collect_unrecognized(
      parsed.options,
      boost::program_options::collect_unrecognized_mode::include_positional);

  if (vm.contains("help") || argc == 1 || list.empty()) {
    std::cout << desc << '\n';
    return EXIT_SUCCESS;
  }

  Test test;
  temporary_file file(list[0]);
  file.open();

  std::cout << "start test: "
            << "file size: " << file_size << "  repeat: " << test_repeat
            << std::endl;

  for (const auto &it : test.seq_write_test(file, file_size, test_repeat)) {
    std::cout << it.first << ": " << it.second << '\n';
  }

  return EXIT_SUCCESS;
}
