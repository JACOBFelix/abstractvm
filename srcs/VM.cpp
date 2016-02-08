#include <iostream>
#include <sstream>
#include <algorithm>
#include "VM.hpp"
#include "Parser.hpp"
#include "Exceptions.hpp"

VM::VM(const char *filename) {
  std::ifstream file(filename);
  std::stringstream buf;
  std::string line;

  _end = false;
  if (filename) {
    if (!file.good())
      throw IOError(std::string("Invalid file : ") + filename);
    buf << file.rdbuf();
    _buf = buf.str();
    file.close();
  }
  else {
    while (line != ";;") {
      std::getline(std::cin, line);
      if (std::cin.eof())
	std::cin.clear();
      else if (line != ";;")
	buf << line << std::endl;
    }
    _buf = buf.str();
  }
  _fptr["push"] = &VM::push;
  _fptr["pop"] = &VM::pop;
  _fptr["dump"] = &VM::dump;
  _fptr["assert"] = &VM::assert;
  _fptr["add"] = &VM::add;
  _fptr["sub"] = &VM::sub;
  _fptr["mul"] = &VM::mul;
  _fptr["div"] = &VM::div;
  _fptr["mod"] = &VM::mod;
  _fptr["print"] = &VM::print;
  _fptr["exit"] = &VM::exit;
}

VM::~VM() {
  while (!_stack.empty()) {
    delete _stack.front();
    _stack.pop_front();
  }
}

VM::VM(const VM& vm) {
  _end = vm._end;
  _buf = vm._buf;
  _stack = vm._stack;
  _fptr = vm._fptr;
}

VM	&VM::operator=(const VM& vm) {
  if (this != &vm) {
    _end = vm._end;
    _buf = vm._buf;
    _stack = vm._stack;
    _fptr = vm._fptr;
  }
  return *this;
}

void	VM::push(std::string const &str) {
  _stack.push_front(Parser::operand(str));
}

void	VM::pop(std::string const &str UNUSED) {
  if (_stack.empty())
    throw LogicError("Error on pop : stack is empty");
  delete _stack.front();
  _stack.pop_front();
}

static void	display(IOperand *op) {
#ifdef BONUS
  int		colors[] = {YELLOW, RED, MAGENTA, GREEN, CYAN};
  std::string	types[] = {"int8", "int16", "int32", "float", "double"};

  std::cout << "\033[" << colors[op->getPrecision()] << "m" <<
    types[op->getPrecision()] << "(" << op->toString() << ")\033[0m" << std::endl;
#else
  std::cout << op->toString() << std::endl;
#endif
}

void	VM::dump(std::string const &str UNUSED) {
  std::for_each(_stack.begin(), _stack.end(), display);
}

void			VM::assert(std::string const &str) {
  IOperand		*cmp = Parser::operand(str);
  std::string		types[] = {"int8", "int16", "int32", "float", "double"};
#ifdef BONUS
  int			colors[] = {YELLOW, RED, MAGENTA, GREEN, CYAN};
  std::stringstream	ss;
#endif

  if (_stack.front()->toString() != cmp->toString()
      || _stack.front()->getType() != cmp->getType()) {
#ifdef BONUS
    ss << "\033[" << colors[_stack.front()->getPrecision()] << "m"
       << types[_stack.front()->getType()] << "(" << _stack.front()->toString()
       << ")\033[0m != \033[" << colors[cmp->getPrecision()] << "m"
       << types[cmp->getType()] << "(" << cmp->toString() << ")\033[0m";
    throw AssertError(ss.str());
#else
    throw AssertError(types[_stack.front()->getType()] + "(" + _stack.front()->toString()
		      + ") != "
		      + types[cmp->getType()] + "(" + cmp->toString() + ")");
#endif
  }
  delete cmp;
}

void		VM::add(std::string const &str UNUSED) {
  IOperand	*first, *second;

  if (_stack.size() < 2)
    throw LogicError("Trying to make an addition with a stack smaller than 2");
  first = _stack.front();
  _stack.pop_front();
  second = _stack.front();
  _stack.pop_front();
  _stack.push_front(*first + *second);
  delete first;
  delete second;
}

void		VM::sub(std::string const &str UNUSED) {
  IOperand	*first, *second;

  if (_stack.size() < 2)
    throw LogicError("Trying to make a substraction with a stack smaller than 2");
  first = _stack.front();
  _stack.pop_front();
  second = _stack.front();
  _stack.pop_front();
  _stack.push_front(*first - *second);
  delete first;
  delete second;
}

void		VM::mul(std::string const &str UNUSED) {
  IOperand	*first, *second;

  if (_stack.size() < 2)
    throw LogicError("Trying to make a multiplication with a stack smaller than 2");
  first = _stack.front();
  _stack.pop_front();
  second = _stack.front();
  _stack.pop_front();
  _stack.push_front(*first * *second);
  delete first;
  delete second;
}

void		VM::div(std::string const &str UNUSED) {
  IOperand	*first, *second;

  if (_stack.size() < 2)
    throw LogicError("Trying to make a division with a stack smaller than 2");
  first = _stack.front();
  _stack.pop_front();
  second = _stack.front();
  _stack.pop_front();
  _stack.push_front(*first / *second);
  delete first;
  delete second;
}

void	VM::mod(std::string const &str UNUSED) {
  IOperand	*first, *second;

  if (_stack.size() < 2)
    throw LogicError("Trying to make a modulo with a stack smaller than 2");
  first = _stack.front();
  _stack.pop_front();
  second = _stack.front();
  _stack.pop_front();
  _stack.push_front(*first % *second);
  delete first;
  delete second;
}

void			VM::print(std::string const &str UNUSED) {
  std::stringstream	ss;
  int			val;

  if (_stack.front()->getType() != Int8)
    throw LogicError("Trying to print a non-int8 value");
  ss << _stack.front()->toString();
  ss >> val;
  std::cout << static_cast<char>(val);
}

void	VM::exit(std::string const &str UNUSED) {
  _end = true;
}

void	VM::run() {
  std::stringstream	ss;
  std::string		line;
  std::string		*args;

  ss << _buf;
  while (std::getline(ss, line)) {
    if (line.empty())
      continue;
    args = Parser::line(line);
    if (args[0].empty())
      continue;
    if (!_fptr[args[0]])
      throw ParseError("Unknown instruction : " + args[0]);
    if (!args[0].empty())
      (this->*_fptr[args[0]])(args[1]);
    delete[] args;
    if (_end)
      return;
  }
  throw LogicError("No exit instruction found");
}
