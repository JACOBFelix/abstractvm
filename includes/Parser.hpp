#ifndef PARSER_HPP_
# define PARSER_HPP_

# include "IOperand.hpp"
# include <string>

# define IS_NB(c)	(c >= '0' && c <= '9')

class Parser {
private:
  static IOperand*	createInt8(const std::string& value);
  static IOperand*	createInt16(const std::string& value);
  static IOperand*	createInt32(const std::string& value);
  static IOperand*	createFloat(const std::string& value);
  static IOperand*	createDouble(const std::string& value);

public:
  static void		check(char c);
  static std::string*	line(std::string const& line);
  static IOperand*	operand(std::string const& str);
  static IOperand*	createOperand(eOperandType type, std::string const& value);
  static IOperand*	createOperand(eOperandType type, long double value);
# ifdef BONUS
  static IOperand*	createAutoOperand(std::string const& value);
# endif
};

#endif
