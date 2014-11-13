// Copyright (c) 2014, LAAS-CNRS
// Authors: Joseph Mirabel (joseph.mirabel@laas.fr)
//
// This file is part of hpp-statistics.
// hpp-statistics is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp-statistics is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp-statistics. If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <list>

#include "hpp/statistics/bin.hh"

using hpp::statistics::Bin;
using hpp::statistics::Statistics;

class TestBin : public Bin {
  public:
    int val;
    std::list < double > l;

    TestBin (int i) : val (i) {}

    std::ostream& printValue (std::ostream& os) const 
    {
      os << val << " has :";
      for (std::list <double>::const_iterator it = l.begin ();
          it != l.end (); ++it)
        os << "   " << *it << std::endl;
      return os << std::endl;
    }

    bool operator< (const TestBin& rhs) const {
      return val < rhs.val;
    }

    bool operator== (const TestBin& rhs) const {
      return val == rhs.val;
    }
};

class TestStatistics : public Statistics <TestBin> {
  public:
    void add (int n, double d) {
      TestBin b(n);
      TestStatistics::iterator it = insert (b);
      it->l.push_back (d);
    }
};

int main ()
{
  srand (time(NULL));

  TestStatistics t;
  double *check = new double [100];
  int status = EXIT_SUCCESS;
  for (int i = 0; i < 100; i++) {
    check[i] = ((double)(rand())/(double)rand());
    t.add (i, check[i]);
  }
  for (int i = 0; i < 100; i++) {
    TestStatistics::const_iterator it = t.find (i);
    if (it == t.end ()) {
      status = EXIT_FAILURE;
      break;
    }
    if (it->l.size () != 1 && check[i] != it->l.front()) {
      status = EXIT_FAILURE;
      break;
    }
  }
  delete[] check;
  return status;
}
