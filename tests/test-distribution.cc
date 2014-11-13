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
#include <cfloat>
#include <time.h>

#include "hpp/statistics/distribution.hh"

int main ()
{
  /* initialize random seed: */
  srand (time(NULL));

  std::cout.precision(15);

  using namespace hpp::statistics;
  typedef int Value;
  typedef DiscreteDistribution <Value> Distrib;
  Distrib dd;
  const int nbValues = 4;
  const Value values[] = {1, 3, 2, 4};
  const Distrib::Weight_t weight[] =
    {1, 23, 99, 6};
  Distrib::Weight_t total_weight = 0;
  dd.insert (values[0], 9.0);
  for (int i = 0; i < nbValues; i++) {
    dd.insert (values[i], weight[i]);
    total_weight += weight[i];
  }

  std::vector < Proba_t > p = dd.probabilities ();

  for (size_t i = 0; i < p.size (); i++)
    if (p[i] - (double)(weight[i] / (double)total_weight) > DBL_EPSILON
        || - p[i] + (double)(weight[i] / (double)total_weight) > DBL_EPSILON) {
      std::cout << "p[" << i << "] = " << p[i] << std::endl
        << "weight[" << i << "] = " << weight[i] << std::endl
        << "Total weight = " << total_weight << std::endl
        << "Difference = " << p[i] - (double)(weight[i] / (double)total_weight) << std::endl;
      return EXIT_FAILURE;
    }

  if (dd ((Distrib::Weight_t)  0) != values[0]) {
    std::cout << "dichotomy (" << 0 << ") returns " << dd ((Distrib::Weight_t)  0) << std::endl;
    return EXIT_FAILURE;
  }
  if (dd ((Distrib::Weight_t) 21) != values[1]) {
    std::cout << "dichotomy (" << 21 << ") returns " << dd ((Distrib::Weight_t)  21) << std::endl;
    return EXIT_FAILURE;
  }
  if (dd ((Distrib::Weight_t) 50) != values[2]) {
    std::cout << "dichotomy (" << 50 << ") returns " << dd ((Distrib::Weight_t)  50) << std::endl;
    return EXIT_FAILURE;
  }
  if (dd ((Distrib::Weight_t)125) != values[3]) {
    std::cout << "dichotomy (" << 125 << ") returns " << dd ((Distrib::Weight_t)  125) << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
