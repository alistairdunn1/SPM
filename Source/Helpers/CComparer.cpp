//============================================================================
// Name        : CComparer.cpp
// Author      : S.Rasmussen
// Date        : 7/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CComparer.h"
#include "../Translations/Translations.h"

//**********************************************************************
// bool CComparer::isSame(string one, string two, bool useWildCards)
//
//**********************************************************************
bool CComparer::isSame(string one, string two, bool useWildCards)
{

  // Vars
  int i1CardIndex = one.find_first_of(CONFIG_WILDCARD_SINGLE);
  int iNCardIndex = one.find_first_of(CONFIG_WILDCARD_MULTIPLE);

  /* ? Wildcard
   * This one can be used to simulate 1 character
   * you can add more than length of the string just to be safe
   */
  if (i1CardIndex >= 0)
  {
    // Remove The ?'s From Both Strings
    while (i1CardIndex >= 0)
    {
      one = one.erase(i1CardIndex, 1);
      if (i1CardIndex < (int)two.length())
        two = two.erase(i1CardIndex, 1);

      i1CardIndex = one.find_first_of(CONFIG_WILDCARD_SINGLE);
    }
  }

  /*
   * * Wildcard
   * This allows for N-number of chars to be removed from that char
   * forward
   */
  if (iNCardIndex >= 0)
  {
    one = one.erase(iNCardIndex, (one.length() - iNCardIndex + 1));
    if (iNCardIndex <= (int)two.length())
      two = two.erase(iNCardIndex, (two.length() - iNCardIndex + 1));
  }

  // Check For Match Now
  if (two == one)
    return true;

  return false;
}

//**********************************************************************
// bool CComparer::hasDuplicates(std::vector<string>)
//
//**********************************************************************

bool CComparer::hasDuplicates(const std::vector<string> &vLabels)
{

  std::vector<std::string> vTemp = vLabels;
  std::sort(vTemp.begin(), vTemp.end());
  vTemp.erase(std::unique(vTemp.begin(), vTemp.end()), vTemp.end());
  if (vTemp.size() != vLabels.size())
    return 1;
  else
    return 0;
}
