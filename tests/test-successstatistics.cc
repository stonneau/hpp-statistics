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

#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "hpp/statistics/success-bin.hh"

HPP_DEFINE_REASON_FAILURE (REASON_TEST, "Fake reason for testing purpose");

using namespace hpp;

int main ()
{
  /* initialize random seed: */
    srand (static_cast<unsigned int> (time(NULL)));

  using namespace hpp::statistics;
  SuccessStatistics ss;
  unsigned int counter[3];
  counter[0]=0; counter[1]=0; counter[2]=0;
  for (int i = 0; i < 100; i++) {
    unsigned int nb = rand() % 3;
    counter[nb]++;
    switch (nb) {
      case 0:
        ss.addSuccess ();
        break;
      case 1:
        ss.addFailure ();
        break;
      case 2:
        ss.addFailure (REASON_TEST);
        break;
    }
  }
  if (   ss.nbSuccess () != counter[0]
      || ss.nbFailure (SuccessBin::REASON_UNKNOWN) != counter[1]
      || ss.nbFailure (REASON_TEST) != counter[2]) {
    std::cout << ss << std::endl;
    std::cout << "Real frequencies are: ( " << counter[0] << ", " << counter[1]
      << ", " << counter [2] << ")" << std::endl;
    return EXIT_FAILURE;
  }
  if (ss.nbFailure () != counter[1] + counter[2])
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
