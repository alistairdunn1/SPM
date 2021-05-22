//============================================================================
// Name        : CError.cpp
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CError.h"
#include "CConvertor.h"
#include "../Translations/Translations.h"

//**********************************************************************
// void CError::error(string value)
// Throw a basic error
//**********************************************************************
void CError::error(string value)
{
  throw value;
}

//**********************************************************************
// void CError::errorMissing(string value)
// Throw an error parameter missing
//**********************************************************************
void CError::errorMissing(string value)
{
  string sException = ERROR_MISSING;
  sException += value;
  throw sException;
}

//**********************************************************************
// void CError::errorLessThan(string less, string more)
// Throw an error less than
//**********************************************************************
void CError::errorLessThan(string less, string more)
{
  string sException = less;
  sException += ERROR_LESS_THAN;
  sException += more;
  throw sException;
}

//**********************************************************************
// void CError::errorNotLessThan(string less, string more)
// Throw an error if not less than
//**********************************************************************
void CError::errorNotLessThan(string less, string more)
{
  string sException = less;
  sException += ERROR_NOT_LESS_THAN;
  sException += more;
  throw sException;
}

//**********************************************************************
// void CError::errorLessThanEqualTo(string less, string more)
// Throw error less than or equal to
//**********************************************************************
void CError::errorLessThanEqualTo(string less, string more)
{
  string sException = less;
  sException += ERROR_LESS_EQUAL_TO;
  sException += more;
  throw sException;
}

//**********************************************************************
// void CError::errorGreaterThan(string more, string less)
// Throw error greater than
//**********************************************************************
void CError::errorGreaterThan(string more, string less)
{
  string sException = more;
  sException += ERROR_GREATER_THAN;
  sException += less;
  throw sException;
}

//**********************************************************************
// void CError::errorGreaterThanEqualTo(string more, string less)
// Throw error greater than or equal to
//**********************************************************************
void CError::errorGreaterThanEqualTo(string more, string less)
{
  string sException = more;
  sException += ERROR_GREATER_EQUAL_TO;
  sException += less;
  throw sException;
}

//**********************************************************************
// void CError::errorNotEqual(string value1, string value2)
// Throw error not equal
//**********************************************************************
void CError::errorNotEqual(string value1, string value2)
{
  string sException = value1;
  sException += ERROR_EQUAL_NOT;
  sException += value2;
  throw sException;
}

//**********************************************************************
// void CError::errorEqualTo(string value1, string value2)
// Throw error equal to
//**********************************************************************
void CError::errorEqualTo(string value1, string value2)
{
  string sException = value1;
  sException += ERROR_EQUAL_TO;
  sException += value2;
  throw sException;
}

//**********************************************************************
// void CError::errorSupported(string value)
// Throw error not supported
//**********************************************************************
void CError::errorSupported(string value)
{
  string sException = value;
  sException += ERROR_SUPPORTED;
  throw sException;
}

//**********************************************************************
// void CError::errorTypeNotSupported(string type string label)
// Throw error not supported
//**********************************************************************
void CError::errorTypeNotSupported(string type, string label)
{
  string sException = type + ERROR_TYPE_NOT_SUPPORTED + label;
  throw sException;
}

//**********************************************************************
// void CError::errorUnknown(string type, string label)
// Throw Unknown Error
//**********************************************************************
void CError::errorUnknown(string type, string label)
{
  string sException = ERROR_UNKNOWN + type + ERROR_SEPARATOR + label;
  throw sException;
}

//**********************************************************************
// void CError::errorPairs(string value)
// Throw "Must be in pairs" exception
//**********************************************************************
void CError::errorPairs(string value)
{
  string sException = value + ERROR_MUST_BE_PAIRED;
  throw sException;
}

//**********************************************************************
// void CError::errorNoMatch(string type, string value, string type2)
// Throw "No matching X for Y" exception
//**********************************************************************
void CError::errorNoMatch(string type, string value, string type2)
{
  string sException = type + ERROR_SEPARATOR + value + ERROR_NO_MATCHING + type;
  throw sException;
}

//**********************************************************************
// void CError::errorDuplicate(string type, string label)
// Duplicate Error
//**********************************************************************
void CError::errorDuplicate(string type, string label)
{
  string sException = ERROR_DUPLICATE + type + ERROR_SEPARATOR + label;
  throw sException;
}

//**********************************************************************
// void CError::errorListSameSize(string type, string type2)
// Throw " list must be same size as" exception
//**********************************************************************
void CError::errorListSameSize(string type, string type2)
{
  string sException = type + ERROR_LIST_EQUAL_SIZE + type2;
  throw sException;
}

//**********************************************************************
// void CError::errorListNotSize(string type, int size)
// List mush have size of 'size'
//**********************************************************************
void CError::errorListNotSize(string type, int size)
{
  string sException = type + ERROR_LIST_NOT_SIZE + boost::lexical_cast<string>(size);
  throw sException;
}

//**********************************************************************
// void CError::errorTooHigh(string type)
// Throw type is too high exception
//**********************************************************************
void CError::errorTooHigh(string type)
{
  string sException = type + ERROR_TOO_HIGH;
  throw sException;
}

//**********************************************************************
// void CError::errorTooMuch(string type)
// Too Much of Something
//**********************************************************************
void CError::errorTooMuch(string type)
{
  string sException = ERROR_TOO_MUCH + type;
  throw sException;
}

//**********************************************************************
// void CError::errorNotEnough(string type)
// Not Enough of Something
//**********************************************************************
void CError::errorNotEnough(string type)
{
  string sException = ERROR_NOT_ENOUGH + type;
  throw sException;
}

//**********************************************************************
// void CError::errorNotBetween(string middle, string low, string high)
// Value middle is not between low and high
//**********************************************************************
void CError::errorNotBetween(string middle, string low, string high)
{
  string Ex = middle + ERROR_BETWEEN + low + CONFIG_COMMA_SEPERATOR + string(" ") + high;
  throw Ex;
}

//**********************************************************************
// void CError::errorElementLessThan(string type, int lessIndex, int moreIndex)
// Element less is less than element more
//**********************************************************************
void CError::errorElementLessThan(string type, int lessIndex, int moreIndex)
{
  string sException = type + string(" ") + PARAM_VALUE + string(" ") + boost::lexical_cast<string>(lessIndex);
  sException += ERROR_LESS_THAN;
  sException += boost::lexical_cast<string>(moreIndex);
  throw sException;
}

//**********************************************************************
// void CError::errorSumGreaterThanEqualTo(string val1, string val2, string less)
// A + B is less than more
//**********************************************************************
void CError::errorSumGreaterThanEqualTo(string val1, string val2, string less)
{
  string sException = val1 + " + " + val2;
  sException += ERROR_GREATER_EQUAL_TO;
  sException += less;
  throw sException;
}

//**********************************************************************
// void CError::errorSumGreaterThan(string val1, string val2, string less)
// A + B is less than more
//**********************************************************************
void CError::errorSumGreaterThan(string val1, string val2, string less)
{
  string sException = val1 + " + " + val2;
  sException += ERROR_GREATER_THAN;
  sException += less;
  throw sException;
}

//**********************************************************************
// void CError::errorInvalidCharacter(string val1, char val2)
// A + B is less than more
//**********************************************************************
void CError::errorInvalidCharacter(string val1, string val2)
{
  string sException = ERROR_INVALID_CHAR + string("'") + val1 + string("' in ") + val2;
  throw sException;
}

//**********************************************************************
// void CError::errorNotIncreasing(string val1)
// A is not increasing
//**********************************************************************
void CError::errorNotIncreasing(string val1)
{
  string sException = ERROR_INVALID_CHAR + string("'") + val1 + string("' is not monotonically increasing when compared to the next value");
  throw sException;
}
