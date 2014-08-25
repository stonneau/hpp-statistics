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
# include <set>

# include <hpp/statistics/config.hh>

namespace hpp {
  namespace statistics {
    class Bin;
    template < typename T >
      class Statistics;
  } // namespace statistics
} // namespace hpp

std::ostream& operator<< (std::ostream&, const hpp::statistics::Bin&);
template < typename T >
std::ostream& operator<< (std::ostream&, const hpp::statistics::Statistics <T>&);

namespace hpp {
  namespace statistics {
    /// Abstract class representing a bin.
    ///
    /// Bins are use for statistics. They keep the number of
    /// of apparition of a given value.
    /// Inherited class should also implement comparison and equality
    /// operators.
    class HPP_STATISTICS_DLLAPI Bin
    {
      public:
        /// Return the number of element in the bin.
        size_t freq () const
        {
          return freq_;
        }

        /// Add an occurence
        /// \return The frequency after increment;
        size_t operator ++()
        {
          return ++freq_;
        }

        /// Add an occurence
        /// \return The frequency before increment;
        size_t operator ++(int)
        {
          return freq_++;
        }

        /// Print the bin.
        std::ostream& print (std::ostream& os) const;

        /// Print the inner value of the bin.
        virtual std::ostream& printValue (std::ostream& os) const = 0;

      protected:
        /// Constructor
        Bin () : freq_ (0) {}

      private:
        /// The number of occurence.
        size_t freq_;
    };
    
    /// Template class to do statistics.
    /// You should derivate class Bin and construct a class
    /// Statistics < YourBin >.
    template < typename T >
    class HPP_STATISTICS_DLLAPI Statistics
    {
      public:
        typedef typename std::set <T>::iterator iterator;
        typedef typename std::set <T>::const_iterator const_iterator;

        /// Return the number of occurence of a Bin
        virtual size_t freq (const T& bin) const;

        /// Return the total number of occurence.
        unsigned int numberOfOccurence () const
        {
          return counts_;
        }
        
        /// Put the results in a stream.
        virtual std::ostream& print (std::ostream& os) const;

      protected:
        /// Constructor
        Statistics();

        /// Increment a Bin
        /// \note bin is inserted in the set of bins if it was not
        /// already in the set.
        virtual void increment (T& bin);

        /// Return an iterator pointing at the beginning of
        /// the set of bins.
        const_iterator begin() const
        {
          return bins_.begin();
        }

        /// Return an iterator pointing at the end of
        /// the set of bins.
        const_iterator end() const
        {
          return bins_.end();
        }

      private:
        std::set < T > bins_;

        unsigned int counts_;
    };
  } // namespace statistics
} // namespace hpp

/// Implementation

namespace hpp {
  namespace statistics {
    template < typename T >
    void Statistics <T>::increment (T& b)
    {
      b++;
      std::pair< iterator, bool > it = bins_.insert (b);
      if (!it.second) {
        // The bin exists already. We must copy and reinsert it.
        b = *(it.first);
        b++;
        bins_.erase (it.first);
        bins_.insert (b);
      }
      counts_++;
    }

    template < typename T >
    size_t Statistics <T>::freq (const T& b) const
    {
      typename std::set< T >::iterator it = bins_.find (b);
      if (it == bins_.end ()) {
        return 0;
      }
      return it->freq ();
    }

    template < typename T >
      Statistics <T>::Statistics () :bins_ (), counts_(0)
    {}

    template < typename T >
    std::ostream& Statistics<T>::print (std::ostream& os) const
    {
      const_iterator it;
      for (it = begin(); it != end(); it++)
        os << (*it) << std::endl;
      return os;
    }
  } // namespace statistics
} // namespace hpp

  template < typename T >
std::ostream& operator<< (std::ostream& os, const hpp::statistics::Statistics <T>& ss)
{
  return ss.print (os);
}

#endif // HPP_STATISTICS_HH
