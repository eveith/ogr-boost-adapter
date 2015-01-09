#ifndef WINZENT_SIMULATION_OGRPOINTCOLLECTIONITERATOR_H
#define WINZENT_SIMULATION_OGRPOINTCOLLECTIONITERATOR_H


#include <memory>
#include <cstddef>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_concepts.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/optional.hpp>

#include <ogr_geometry.h>


namespace Winzent {
    namespace Simulation {
        namespace boost {


            template<class Container, class Value>
            class OGRPointCollectionIter: public ::boost::iterator_facade<
                    OGRPointCollectionIter<Container, Value>,
                    Value,
                    ::boost::random_access_traversal_tag,
                    Value &,
                    int>
            {
            private:


                friend class ::boost::iterator_core_access;


                /*!
                 * \brief Index of the current point
                 */
                size_t m_currentPointIndex;


                /*!
                 * \brief The OGRLineString we iterate
                 */
                ::boost::optional<Container &> m_collection;


                void increment()
                {
                    ++m_currentPointIndex;
                }


                void decrement()
                {
                    --m_currentPointIndex;
                }


                Value &dereference() const
                {
                    auto point = std::make_shared<OGRPoint>();
                    m_collection->getPoint(
                            m_currentPointIndex,
                            point.get());
                    return *point;
                }


                void advance(const size_t &n)
                {
                    m_currentPointIndex += n;
                }



                bool equal(const OGRPointCollectionIter &other)
                        const
                {
                    return (&(*m_collection) == &(*(other.m_collection))
                            && m_currentPointIndex
                                == other.m_currentPointIndex);
                }


                int distance_to(const OGRPointCollectionIter &other) const
                {
                    return other.m_currentPointIndex - m_currentPointIndex;
                }


            public:


                OGRPointCollectionIter()
                {
                }


                explicit OGRPointCollectionIter(Container &c):
                        m_currentPointIndex(0),
                        m_collection(c)
                {
                }


                bool isEmpty() const
                {
                    return m_collection->empty();
                }
            };
        } // namespace boost
    } // namespace Winzent
} // namespace Simulation

#endif // WINZENT_SIMULATION_OGRPOINTCOLLECTIONITERATOR_H
