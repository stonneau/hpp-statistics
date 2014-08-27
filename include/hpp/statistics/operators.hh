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

#ifndef HPP_STATISTICS_OPERATORS_HH
# define HPP_STATISTICS_OPERATORS_HH

# include <iosfwd>

# include "hpp/statistics/bin.hh"
# include "hpp/statistics/success-bin.hh"
# include "hpp/statistics/config.hh"

namespace hpp {
  HPP_STATISTICS_DLLAPI std::ostream&
    operator<< (std::ostream& os, const hpp::statistics::Bin& b);
  HPP_STATISTICS_DLLAPI std::ostream&
    operator<< (std::ostream& os, const hpp::statistics::SuccessBin& b);
  template < typename T > HPP_STATISTICS_DLLAPI std::ostream&
    operator<< (std::ostream& os, const hpp::statistics::Statistics <T>& ss);
  HPP_STATISTICS_DLLAPI std::ostream&
    operator<< (std::ostream& os, const hpp::statistics::SuccessStatistics& ss);
} // namespace hpp

#endif // HPP_STATISTICS_OPERATORS_HH
