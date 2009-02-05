// Copyright (C) 2004 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// As a special exception, you may use this file as part of a free software
// library without restriction.  Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License.  This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.

#include <sstream>
#include <locale>
#include <iomanip>
#include <testsuite_hooks.h>

struct MyNP : std::numpunct<wchar_t>
{
  std::wstring do_truename() const;
  std::wstring do_falsename() const;
};

std::wstring
MyNP::do_truename() const 
{ 
  std::wstring s(L"yea"); 
  return s; 
}

std::wstring
MyNP::do_falsename() const 
{ 
  std::wstring s(L"nay"); 
  return s; 
}

void
test01()
{
  bool test __attribute__((unused)) = true;
  const wchar_t lit[] = L"1 0\n"
                        L"true false\n"
                        L":  true:\n"
                        L":true  :\n"
                        L": false:\n"
                        L":  1:\n"
                        L":1  :\n"
                        L":  0:\n"
                        L"yea nay\n"
                        L":   yea:\n"
                        L":yea   :\n"
                        L":   nay:\n";

  std::wostringstream oss;
  oss << true << L" " << false << std::endl;
  oss << std::boolalpha;
  oss << true << L" " << false << std::endl;

  oss << L":" << std::setw(6) << std::internal << true << L":" << std::endl;
  oss << L":" << std::setw(6) << std::left << true << L":" << std::endl;
  oss << L":" << std::setw(6) << std::right << false << L":" << std::endl;
  oss << std::noboolalpha;
  oss << L":" << std::setw(3) << std::internal << true << L":" << std::endl;
  oss << L":" << std::setw(3) << std::left << true << L":" << std::endl;
  oss << L":" << std::setw(3) << std::right << false << L":" << std::endl;

  std::locale loc = std::locale(std::locale::classic(), new MyNP);
  oss.imbue(loc);

  oss << std::boolalpha;
  oss << true << L" " << false << std::endl;

  oss << L":" << std::setw(6) << std::internal << true << L":" << std::endl;
  oss << L":" << std::setw(6) << std::left << true << L":" << std::endl;
  oss << L":" << std::setw(6) << std::right << false << L":" << std::endl;

  VERIFY( oss.good() );
  VERIFY( oss.str() == lit );
}

int 
main() 
{
  test01();
  return 0;
}
