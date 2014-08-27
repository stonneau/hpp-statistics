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


#ifndef HPP_STATISTICS_SUCCESSBIN_HH
# define HPP_STATISTICS_SUCCESSBIN_HH

# include <iostream>
# include <set>

# include "hpp/statistics/config.hh"
# include "hpp/statistics/bin.hh"
# include "hpp/statistics/fwd.hh"

# define HPP_DEFINE_REASON_FAILURE(ID, STRING) \
  const ::hpp::statistics::SuccessBin::Reason ID = \
    ::hpp::statistics::SuccessBin::createReason ( STRING ); \
  struct e_n_d__w_i_t_h__s_e_m_i_c_o_l_o_n

namespace hpp {
  namespace statistics {
    /// This class count the number of success and failure.
    class HPP_STATISTICS_DLLAPI SuccessBin : public Bin
    {
      public:
        class Reason;

        /// The default reason for 'failure'.
        const static Reason REASON_UNKNOWN;

        /// Constructor
        SuccessBin (const bool success, const Reason& r = REASON_UNKNOWN);

        /// Value of the bin.
        /// \return True is it counts "success", False otherwise.
        bool isSuccess () const;

        /// If this bin represents 'failure', returns the reason.
        const Reason& reason () const;

        /// If this bin represents 'failure', returns the reason as a string.
        const std::string& reasonString () const;

        /// Check for equality.
        /// \return True if both are 'success' or if they are both 'failure'
        /// with the same Reason.
        bool operator == (const SuccessBin& other) const;

        /// Comparison
        /// \return the comparison of their reason id.
        /// 'success' has a reason id of INT_MIN.
        bool operator < (const SuccessBin& other) const;

        /// Create a new Reason
        /// \param what The text associated with the reason.
        static Reason createReason (const std::string& what);

        /// In case of failure, you can provide a reason.
        /// Use macro DEFINE_REASON_FAILURE (REASON_NAME, Reason string)
        ///       to define a new reason.
        class Reason {
          public:
            unsigned int id;
            std::string what;
          private:
            Reason (unsigned int a_id, std::string a_what) :
              id (a_id), what (a_what) {}
            friend Reason SuccessBin::createReason (const std::string&);
        };

      private:
        bool success_;
        size_t freq_;
        Reason reason_;

        /// The reason for 'success'.
        const static Reason REASON_SUCCESS;
        static unsigned int reasonID_last;

        std::ostream& printValue (std::ostream& os) const;
    };

    class HPP_STATISTICS_DLLAPI SuccessStatistics :
      public Statistics < SuccessBin >
    {
      public:
        typedef Statistics <SuccessBin> Parent;

        /// Constructor
        SuccessStatistics ();

        /// Add a 'success'
        void addSuccess ();

        /// Add a 'failure'
        /// \param r the reason of the 'failure'
        /// \note Use macro DEFINE_REASON_FAILURE (REASON_NAME, 'Reason details')
        ///       to define a new reason.
        void addFailure (const SuccessBin::Reason& r = SuccessBin::REASON_UNKNOWN);

        /// Count the number of success.
        unsigned int nbSuccess () const;

        /// Count the number of failure, in total.
        unsigned int nbFailure () const;

        /// Count the number of a particular failure.
        unsigned int nbFailure (const SuccessBin::Reason& r) const;
    };
  } // namespace statistics
} // namespace hpp

#endif // HPP_STATISTICS_SUCCESSBIN_HH
