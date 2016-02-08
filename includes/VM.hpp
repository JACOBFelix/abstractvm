#ifndef VM_HPP_
# define VM_HPP_

# include <list>
# include <map>
# include <fstream>
# include "IOperand.hpp"

# ifndef UNUSED
#  define UNUSED __attribute__((unused))
# endif

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif

# ifdef BONUS
#  define BLACK		30
#  define RED		31
#  define GREEN		32
#  define YELLOW	33
#  define BLUE		34
#  define MAGENTA	35
#  define CYAN		36
#  define WHITE		37
# endif

# ifdef UNIT
void	unit_tests();
# endif

class VM {
private:
  bool								_end;
  std::string							_buf;
  std::list<IOperand *>						_stack;
  std::map<std::string, void (VM::*)(std::string const &)>	_fptr;

  void	push(std::string const &str);
  void	pop(std::string const &str);
  void	dump(std::string const &str);
  void	assert(std::string const &str);
  void	add(std::string const &str);
  void	sub(std::string const &str);
  void	mul(std::string const &str);
  void	div(std::string const &str);
  void	mod(std::string const &str);
  void	print(std::string const &str);
  void	exit(std::string const &str);

public:
  VM(const char* filename = NULL);
  ~VM();
  VM(const VM &);
  VM	&operator=(const VM &);

  void run();
};

#endif
