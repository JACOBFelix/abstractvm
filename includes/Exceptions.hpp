#ifndef EXCEPTIONS_HPP_
# define EXCEPTIONS_HPP_

# include <exception>
# include <string>

class VMException : public std::exception{
protected:
  std::string _msg;
  std::string _type;

public:
  VMException(std::string const& msg);
  ~VMException() throw();

  const char *what() const throw();
};

class IOError : public VMException {
public:
  IOError(std::string const& msg);
};

class ParseError : public VMException {
public:
  ParseError(std::string const& msg);
};

class MathError : public VMException {
public:
  MathError(std::string const& msg);
};

class LogicError : public VMException {
public:
  LogicError(std::string const& msg);
};

class AssertError : public VMException {
public:
  AssertError(std::string const& msg);
};

#endif
