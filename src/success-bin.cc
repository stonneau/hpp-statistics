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
    unsigned int reasonID_last = 0;
    SuccessBin::Reason SuccessBin::REASON_SUCCESS = SuccessBin::createReason ("Success");
    SuccessBin::Reason SuccessBin::REASON_UNKNOWN = SuccessBin::createReason ("Unknown");

    DEFINE_REASON_FAILURE (REASON_MAX_ITERATION, "Max iteration reached");

    SuccessBin::Reason SuccessBin::createReason (const std::string& what)
    {
      return Reason (reasonID_last++, what);
    }

    SuccessBin::SuccessBin (const bool success, Reason r) :
      success_ (success), freq_ (0), reason_(r)
    {
      if (success_)
        r = REASON_SUCCESS;
    }

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

    void SuccessStatistics::addFailure (const SuccessBin::Reason& r)
    {
      SuccessBin b (false, r);
      std::set<SuccessBin>::iterator it = bins.find (b);
      if (it == bins.end())
        bins.insert (b);
      ((SuccessBin)(*it))++;
    }

    void SuccessStatistics::addSuccess ()
    {
      SuccessBin b (true);
      std::set<SuccessBin>::iterator it = bins.find (b);
      if (it == bins.end())
        bins.insert (b);
      ((SuccessBin)(*it))++;
    }

    std::ostream& SuccessStatistics::print (std::ostream& os) const
    {
      std::set <SuccessBin>::const_iterator it;
      for (it = bins.begin(); it != bins.end(); it++)
        os << (*it);
      return os;
    }

    static std::ostream& operator<< (std::ostream& os, const SuccessStatistics& ss)
    {
      return ss.print (os);
    }
  } // namespace statistics
} // namespace hpp
