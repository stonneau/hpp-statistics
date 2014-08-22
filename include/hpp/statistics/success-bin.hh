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


#ifndef HPP_MANIPULATION_GRAPH_STATISTICS_HH
# define HPP_MANIPULATION_GRAPH_STATISTICS_HH

# include <ostream>

# include <hpp/statistics/config.hh>
# include "hpp/statistics/bin.hh"

namespace hpp {
  namespace statistics {
    /// This class count the number of success and failure.
    class HPP_STATISTICS_DLLAPI SuccessBin : public Bin
    {
      public:
        /// Constructor
        SuccessBin (const bool success);

        /// Value of the bin.
        /// \return True is it counts "success", False otherwise.
        bool isSuccess () const;

        /// Add an occurence
        /// \return The frequency after increment;
        size_t operator ++();

        /// Add an occurence
        /// \return The frequency before increment;
        size_t operator ++(int);

        /// \return The number of element in the bin.
        size_t freq () const;

      private:
        bool success_;
        size_t freq_;

        std::ostream& printValue (std::ostream& os) const;
    };
  } // namespace statistics
} // namespace hpp

#endif // HPP_MANIPULATION_GRAPH_STATISTICS_HH
