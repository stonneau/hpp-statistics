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

#include "hpp/statistics/success-bin.hh"

namespace hpp {
  namespace statistics {
    SuccessBin::SuccessBin (const bool success) :
      success_ (success), freq_ (0)
    {}

    bool SuccessBin::isSuccess () const
    {
      return success_;
    }

    size_t SuccessBin::freq () const
    {
      return freq_;
    }

    size_t SuccessBin::operator ++()
    {
      return ++freq_;
    }

    size_t SuccessBin::operator ++(int)
    {
      return freq_++;
    }

    std::ostream& SuccessBin::printValue (std::ostream& os) const
    {
      os << "Event ";
      if (success_) os << "'Success'";
      else          os << "'Failure'";
      return os;
    }
  } // namespace statistics
} // namespace hpp
