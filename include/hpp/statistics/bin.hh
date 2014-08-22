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


#ifndef HPP_STATISTICS_HH
# define HPP_STATISTICS_HH

# include <ostream>

# include <hpp/statistics/config.hh>

namespace hpp {
  namespace statistics {
    class Bin;
    static std::ostream& operator<< (std::ostream& os, const Bin& b);

    /// Abstract class representing a bin.
    ///
    /// Bins are use for statistics. They keep the number of
    /// of apparition of a given value.
    class HPP_STATISTICS_DLLAPI Bin
    {
      public:
        /// Return the number of element in the bin.
        virtual size_t freq () const = 0;

      private:
        /// Print the inner value of the bin.
        virtual std::ostream& printValue (std::ostream& os) const = 0;

        friend std::ostream& operator<< (std::ostream&, const Bin&);
    };
  } // namespace statistics
} // namespace hpp

#endif // HPP_STATISTICS_HH
