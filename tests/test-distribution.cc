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
  typedef DiscreteDistribution <double> Distrib;
  Distrib dd;
  const int nbValues = 4;
  const double values[] = {1.0, 3.0, 2.0, 4.5};
  const Distrib::Weight_t weight[] =
    {1, 23, 99, 6};
  Distrib::Weight_t total_weight = 0;
  dd.insert (values[0], 9.0);
  for (int i = 0; i < nbValues; i++) {
    dd.insert (values[i], weight[i]);
    total_weight += weight[i];
  }

  std::vector < Distrib::Proba_t > p = dd.probabilities ();

  for (size_t i = 0; i < p.size (); i++)
    if (p[i] - (double)(weight[i] / (double)total_weight) > DBL_EPSILON
        || p[i] - (double)(weight[i] / (double)total_weight) > DBL_EPSILON) {
      std::cout << "p[" << i << "] = " << p[i] << std::endl
        << "weight[" << i << "] = " << weight[i] << std::endl
        << "Total weight = " << total_weight << std::endl
        << "Difference = " << p[i] - (double)(weight[i] / (double)total_weight) << std::endl;
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
