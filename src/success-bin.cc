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

#include <limits.h>

#include "hpp/statistics/success-bin.hh"

namespace hpp {
  namespace statistics {
    unsigned int SuccessBin::reasonID_last = 0;
    const SuccessBin::Reason SuccessBin::REASON_SUCCESS = SuccessBin::createReason ("Success");
    const SuccessBin::Reason SuccessBin::REASON_UNKNOWN = SuccessBin::createReason ("Unknown");

    SuccessBin::Reason SuccessBin::createReason (const std::string& what)
    {
      return Reason (reasonID_last++, what);
    }

    SuccessBin::SuccessBin (const bool success, const Reason& r) :
      Bin(), success_ (success), reason_(r)
    {
      if (success_)
        reason_ = REASON_SUCCESS;
    }

    bool SuccessBin::isSuccess () const
    {
      return success_;
    }

    std::ostream& SuccessBin::printValue (std::ostream& os) const
    {
      os << "Event ";
      if (success_) os << "'Success'";
      else          os << "'Failure': " << reason_.what;
      return os;
    }

    const SuccessBin::Reason& SuccessBin::reason () const
    {
      return reason_;
    }

    bool SuccessBin::operator == (const SuccessBin& other) const
    {
      return reason_.id == other.reason().id;
    }

    bool SuccessBin::operator < (const SuccessBin& other) const
    {
      return reason_.id < other.reason ().id;
    }

    SuccessStatistics::SuccessStatistics ()
    {}

    void SuccessStatistics::addFailure (const SuccessBin::Reason& r)
    {
      SuccessBin b = SuccessBin (false, r);
      increment (b);
    }

    void SuccessStatistics::addSuccess ()
    {
      SuccessBin b = SuccessBin (true);
      increment (b);
    }

    unsigned int SuccessStatistics::nbSuccess () const
    {
      return freq (SuccessBin(true));
    }

    unsigned int SuccessStatistics::nbFailure () const
    {
      return numberOfObservations() - nbSuccess();
    }

    unsigned int SuccessStatistics::nbFailure (const SuccessBin::Reason& r) const
    {
      return freq (SuccessBin (false, r));
    }
  } // namespace statistics
} // namespace hpp
