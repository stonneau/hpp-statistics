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

#include "hpp/statistics/bin.hh"

namespace hpp {
  namespace statistics {
    std::ostream& Bin::print (std::ostream& os) const
    {
      return printValue (os << freq () << " - ");
    }

    std::ostream& operator<< (std::ostream& os, const hpp::statistics::Bin& b)
    {
      return b.print (os);
    }
  } // namespace statistics
} // namespace hpp
