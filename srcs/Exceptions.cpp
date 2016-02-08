#include "Exceptions.hpp"

VMException::VMException(std::string const& msg) : std::exception() {
  _msg = msg;
  _type = "";
}

VMException::~VMException() throw() {}

const char	*VMException::what() const throw() {
  return (_type + _msg).data();
}

IOError::IOError(std::string const& msg) : VMException(msg) {
  _type = "Input/Output error : ";
}

ParseError::ParseError(std::string const& msg) : VMException(msg) {
  _type = "Parse error : ";
}

MathError::MathError(std::string const& msg) : VMException(msg) {
  _type = "Math error : ";
}

LogicError::LogicError(std::string const& msg) : VMException(msg) {
  _type = "Logic error : ";
}

AssertError::AssertError(std::string const& msg) : VMException(msg) {
  _type = "Assertion failed : ";
}
