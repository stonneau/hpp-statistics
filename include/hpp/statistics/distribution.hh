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

#ifndef HPP_STATISTICS_DISTRIBUTION_HH
# define HPP_STATISTICS_DISTRIBUTION_HH

# include <vector>
# include <assert.h>
# include <stdlib.h>

namespace hpp {
  namespace statistics {
    template < typename Value_t >
      class DiscreteDistribution 
      {
        public:
          typedef double Proba_t;
          typedef unsigned int Weight_t;
          typedef typename std::pair < Weight_t, Value_t> ProbaTPair;
          typedef typename std::vector < ProbaTPair >::iterator iterator;
          typedef typename std::vector < ProbaTPair >::const_iterator const_iterator;

          DiscreteDistribution () : values_(), cumulative_weights_() {}

          Value_t operator() () const {
            assert (values_.size() > 0);
            Weight_t r = rand() % cumulative_weights_.back();
            return operator() (r);
          }
          Value_t operator() (const Proba_t& p) const {
            return operator() ((Weight_t)(p * cumulative_weights_.back ()));
          }
          Value_t operator() (const Weight_t& w) const {
            assert (values_.size() > 0);
            return values_[dichotomy (w % cumulative_weights_.back())].second;
          }

          /// Update the distribution.
          /// If v is already in the set, then update its weight.
          /// Otherwise, insert it.
          void insert (Value_t v, Weight_t w = 1) {
            iterator itv = values_.begin ();
            WeightsIterator itcumul = cumulative_weights_.begin();
            Weight_t c = 0;
            while (itv != values_.end()) {
              if (itv->second == v)
                break;
              c = *itcumul;
              itv++; itcumul++;
            }
            if (itv == values_.end ()) {
              values_.push_back (ProbaTPair(w,v));
              cumulative_weights_.push_back (c + w);
              return;
            }
            itv->first = w;
            while (itv != values_.end()) {
              c = c + itv->first;
              *itcumul = c;
              itv++; itcumul++;
            }
          }

          /// Return the probabilities.
          std::vector < Proba_t > probabilities () const {
            std::vector < Proba_t > proba (values_.size());
            Proba_t total = cumulative_weights_.back();
            for (size_t i = 0; i < values_.size (); i++)
              proba[i] = values_[i].first / total;
            return proba;
          }

          /// \name Iterators
          /// Iterate on the values.
          /// \{
          iterator begin () {
            return values_.begin (); 
          }
          const_iterator begin () const {
            return values_.begin (); 
          }
          iterator end () {
            return values_.end (); 
          }
          const_iterator end () const {
            return values_.end (); 
          }
          /// \}
        private:
          size_t dichotomy (const Weight_t& r) const {
            if (r < cumulative_weights_[0]) return 0;
            size_t l = 0, h = values_.size () - 1, m;
            while (l < h - 1) {
              m = (l + h) / 2;
              if (cumulative_weights_[m] < r)
                l = m;
              else if (cumulative_weights_[m] > r)
                h = m;
              else
                return m;
            }
            return h;
          }

          std::vector < ProbaTPair > values_;
          std::vector < Weight_t > cumulative_weights_;

          typedef std::vector < Weight_t >::iterator WeightsIterator;
      };
  } // namespace statistics
} // namespace hpp

#endif // HPP_STATISTICS_DISTRIBUTION_HH
