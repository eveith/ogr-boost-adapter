#ifndef WINZENT_SIMULATION_OGRPOINTCOLLECTIONITERATOR_H
#define WINZENT_SIMULATION_OGRPOINTCOLLECTIONITERATOR_H



#include <QtDebug>
#include <QMap>

#include <memory>
#include <cstddef>
#include <cassert>

#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_concepts.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <ogr_geometry.h>


namespace Winzent {
    namespace Simulation {
        namespace boost {


            template<class Container, class Value>
            class OGRPointCollectionIter: public ::boost::iterator_facade<
                    OGRPointCollectionIter<Container, Value>,
                    Value,
                    ::boost::random_access_traversal_tag,
                    Value>
            {
            private:


                friend class ::boost::iterator_core_access;
                template <class, class> friend class OGRPointCollectionIter;


                struct enabler {};


                /*!
                 * \brief Index of the current point
                 */
                std::size_t m_currentPointIndex;


                /*!
                 * \brief The OGRLineString we iterate
                 */
                Container *m_collection;


                /*!
                 * \brief One step forward in the collection
                 */
                void increment()
                {
                    m_currentPointIndex += 1;
                }


                /*!
                 * \brief One step backwards
                 */
                void decrement()
                {
                    m_currentPointIndex -= 1;
                }


                /*!
                 * \brief Dereferences the iterator at the current position
                 *
                 * Does not do any bounds checking and may therefore result
                 * in SIGSEGV if not used properly.
                 *
                 * \return The point at the current index
                 */
                Value dereference() const
                {
                    assert(m_currentPointIndex
                            < m_collection->getNumPoints());

                    OGRPoint point;
                    m_collection->getPoint(
                            m_currentPointIndex,
                            &point);
                    return point;
                }


                /*!
                 * \brief Advances the iterator by an arbitrary index
                 *
                 * \param[in] n The step
                 */
                void advance(const std::size_t &n)
                {
                    m_currentPointIndex += n;
                }



                /*!
                 * \brief Checks for equality with another iterator
                 *
                 * Two iterators are deemed equal if they iterator over the
                 * same object and are currently at the same position.
                 *
                 * \param[in] other The other iterator
                 *
                 * \return true if equal, false otherwise
                 */
                template <class OCtr, class OVal>
                bool equal(const OGRPointCollectionIter<OCtr, OVal> &other)
                        const
                {
                    return (m_collection == other.m_collection
                            && m_currentPointIndex
                                == other.m_currentPointIndex);
                }


                /*!
                 * \brief Calculates the distance to another iterator
                 *
                 * \param[in] other The other iterator
                 *
                 * \return `other.index - this->index`
                 */
                template <class OCtr, class OVal>
                std::ptrdiff_t distance_to(
                        const OGRPointCollectionIter<OCtr, OVal> &other)
                        const
                {
                    return other.m_currentPointIndex - m_currentPointIndex;
                }


            public:


                OGRPointCollectionIter():
                        m_currentPointIndex(0),
                        m_collection(nullptr)
                {
                }


                template<class OCtr, class OVal>
                OGRPointCollectionIter(
                        const OGRPointCollectionIter<OCtr, OVal> &other,
                        typename ::boost::enable_if<
                                ::boost::is_convertible<OVal, Value>,
                                enabler>::type = enabler()):
                            m_currentPointIndex(other.m_currentPointIndex),
                            m_collection(other.m_collection)
                {
                }


                explicit OGRPointCollectionIter(Container &c):
                        m_currentPointIndex(0),
                        m_collection(&c)
                {
                }


                bool isEmpty() const
                {
                    return nullptr == m_collection;
                }
            };
        } // namespace boost
    } // namespace Winzent
} // namespace Simulation

#endif // WINZENT_SIMULATION_OGRPOINTCOLLECTIONITERATOR_H
