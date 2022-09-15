#include <iostream>
#include <fstream>
#include <string>

int32_t main(int32_t argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "Se requiere un argumento\n";
    return EXIT_FAILURE;
  }

  std::cout << "Proyecto usando YML" << std::endl;

  for (int32_t i = 0; i < argc; ++i)
  {
    std::cout << "[" << i << "]: " << argv[i] << std::endl;
  }

  std::ifstream file{argv[1]};

  if (!file.is_open())
  {
    std::cerr << "Error when trying to open file.\n";
    return EXIT_FAILURE;
  }

  while (!file.eof())
  {
    std::string output_text;
    getline(file, output_text);
    std::cout << output_text << std::endl;
  }

  return EXIT_SUCCESS;
}