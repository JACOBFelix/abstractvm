#ifndef OPERAND_HPP_
# define OPERAND_HPP_

# include <sstream>
# include "Parser.hpp"
# include "IOperand.hpp"
# include "Exceptions.hpp"

template<typename T>
class Operand : public IOperand {
private:
  eOperandType	_type;
  T		_value;
  std::string	_str;

public:
  Operand(eOperandType type, std::string const& str) {
    std::stringstream ss;

    ss.str(str);
    _type = type;
    ss >> _value;
    _str = str;
  }

  Operand(Operand const& o) {
    _type = o._type;
    _value = o._value;
    _str = o._str;
  };

  ~Operand() {}

  Operand &operator=(Operand const& o) {
    if (this != &o) {
      _type = o._type;
      _value = o._value;
      _str = o._str;
    }
    return *this;
  }

  // GETTERS

  std::string const	&toString() const {
    return _str;
  }

  int			getPrecision() const {
    return static_cast<int>(_type);
  }

  eOperandType		getType() const {
    return _type;
  }

  // OPERATORS

  IOperand		*operator+(const IOperand &rhs) const {
    std::stringstream	ss;
    eOperandType	precise;
    long double		value;

    ss << rhs.toString();
    precise = _type >= rhs.getType() ? _type : rhs.getType();
    ss >> value;
    return Parser::createOperand(precise, _value + value);
  }

  IOperand		*operator-(const IOperand &rhs) const {
    std::stringstream	ss;
    eOperandType	precise;
    long double		value;

    ss << rhs.toString();
    precise = _type >= rhs.getType() ? _type : rhs.getType();
    ss >> value;
    return Parser::createOperand(precise, _value - value);
  }

  IOperand		*operator*(const IOperand &rhs) const {
    std::stringstream	ss;
    eOperandType	precise;
    long double		value;

    ss << rhs.toString();
    precise = _type >= rhs.getType() ? _type : rhs.getType();
    ss >> value;
    return Parser::createOperand(precise, _value * value);
  }

  IOperand		*operator/(const IOperand &rhs) const {
    std::stringstream	ss;
    eOperandType	precise;
    long double		value;

    ss << rhs.toString();
    precise = _type >= rhs.getType() ? _type : rhs.getType();
    ss >> value;
    if (!value)
      throw MathError("Division by 0");
    return Parser::createOperand(precise, _value / value);
 }

  IOperand		*operator%(const IOperand &rhs) const {
    std::stringstream	ss;
    eOperandType	precise;
    long long		value;

    if (rhs.getType() >= Float || _type >= Float)
      throw MathError("Error : can't process modulo on decimal types");
    ss << rhs.toString();
    precise = _type >= rhs.getType() ? _type : rhs.getType();
    ss >> value;
    if (!value)
      throw MathError("Modulo by 0");
    value = static_cast<long long>(_value) % static_cast<long long>(value);
    return Parser::createOperand(precise, value);
  }
};
#endif
