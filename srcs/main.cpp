#include <iostream>
#include "VM.hpp"
#include "Exceptions.hpp"

int	main(int argc UNUSED, char **argv UNUSED) {
#ifdef UNIT
  try {
    unit_tests();
  } catch (VMException const& e) {
    std::cerr << "\033[31mUncaught error\033[0m" << std::endl << e.what() << std::endl << "\033[31mExiting.\033[0m" << std::endl;
  }
#else
  try {
    VM	vm(argv[1]);
    vm.run();
  } catch (VMException const& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
#endif
  return EXIT_SUCCESS;
}
