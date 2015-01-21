#ifndef OGRPOLYGONTOBOOSTADAPTER_H
#define OGRPOLYGONTOBOOSTADAPTER_H


#include <cstddef>

#include <ogr_geometry.h>

#include <boost/optional.hpp>

#include <boost/range.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/interior_type.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/geometries/concepts/polygon_concept.hpp>


namespace Winzent {
    namespace Simulation {
        namespace boost {


            template <class Container>
            class OGRPolygonIter: public ::boost::iterator_facade<
                    OGRPolygonIter<Container>,
                    OGRLinearRing,
                    ::boost::random_access_traversal_tag,
                    OGRLinearRing>
            {
            private:


                friend class ::boost::iterator_core_access;


                /*!
                 * \brief The polygon we iterate
                 */
                ::boost::optional<Container &> m_polygon;


                /*!
                 * \brief The linear ring currently pointed to.
                 */
                std::ptrdiff_t m_currentRing;


                void increment()
                {
                    ++m_currentRing;
                }


                void decrement()
                {
                    --m_currentRing;
                }


                OGRLinearRing dereference() const
                {
                    OGRLinearRing *ring;

                    if (0 == m_currentRing) {
                        ring = m_polygon->getExteriorRing();
                    } else {
                        ring = m_polygon->getInteriorRing(m_currentRing-1);
                    }

                    return OGRLinearRing(ring);
                }


                void advance(const std::ptrdiff_t &n)
                {
                    m_currentRing += n;
                }


                std::ptrdiff_t distance_to(const OGRPolygonIter &other) const
                {
                    return other.m_currentRing - m_currentRing;
                }


                bool equal(const OGRPolygonIter<Container> &other) const
                {
                    return (other.m_currentRing == m_currentRing &&
                            m_polygon->Equals(&(other.m_polygon.get())));
                }


            public:


                OGRPolygonIter(): m_currentRing(0)
                {
                }


                explicit OGRPolygonIter(Container &polygon):
                        m_polygon(polygon),
                        m_currentRing(0)
                {
                }


                OGRPolygonIter(const OGRPolygonIter &other):
                        m_polygon(other.m_polygon.get()),
                        m_currentRing(other.m_currentRing)
                {
                }
            };


            /*!
             * \brief An iterator for OGRLineString objects
             */
            typedef OGRPolygonIter<OGRPolygon> OGRPolygonIterator;

            /*!
             * \brief A const-access iterator for OGRPolygon objects
             */
            typedef OGRPolygonIter<const OGRPolygon> OGRPolygonConstIterator;


            class CustomOGRPolygonRingRange
            {
            private:


                OGRPolygonIterator m_begin;
                OGRPolygonIterator m_end;


            public:

                CustomOGRPolygonRingRange(
                        OGRPolygonIterator begin,
                        OGRPolygonIterator end):
                            m_begin(begin),
                            m_end(end)
                {
                }


                OGRPolygonIterator begin()
                {
                    return m_begin;
                }


                OGRPolygonIterator end()
                {
                    return m_end;
                }
            };


            class CustomOGRPolygonConstRingRange
            {
            private:


                OGRPolygonConstIterator m_cbegin;
                OGRPolygonConstIterator m_cend;


            public:


                CustomOGRPolygonConstRingRange(
                        OGRPolygonConstIterator begin,
                        OGRPolygonConstIterator end):
                            m_cbegin(begin),
                            m_cend(end)
                {
                }


                OGRPolygonConstIterator cbegin() const
                {
                    return m_cbegin;
                }


                OGRPolygonConstIterator cend() const
                {
                    return m_cend;
                }
            };
        } // namespace boost
    } // namespace Simulation
} // namespace Winzent


namespace boost {
    template <>
    struct range_iterator<OGRPolygon>
    {
        typedef Winzent::Simulation::boost::OGRPolygonIterator type;
    };


    template <>
    struct range_const_iterator<OGRPolygon>
    {
        typedef Winzent::Simulation::boost::OGRPolygonConstIterator type;
    };
}


inline Winzent::Simulation::boost::OGRPolygonIterator
range_begin(OGRPolygon &l)
{
    return Winzent::Simulation::boost::OGRPolygonIterator(l);
}


inline Winzent::Simulation::boost::OGRPolygonIterator
range_end(OGRPolygon &l)
{
    auto iter = range_begin(l);
    iter += l.getNumInteriorRings() + 1;
    return iter;
}


inline Winzent::Simulation::boost::OGRPolygonConstIterator
range_begin(const OGRPolygon &l)
{
    return Winzent::Simulation::boost::OGRPolygonConstIterator(l);
}


inline Winzent::Simulation::boost::OGRPolygonConstIterator
range_end(const OGRPolygon &l)
{
    auto iter = range_begin(l);
    iter += l.getNumInteriorRings() + 1;
    return iter;
}


namespace boost {
    namespace geometry {
        namespace traits {



            using Winzent::Simulation::boost::CustomOGRPolygonRingRange;
            using Winzent::Simulation::boost::CustomOGRPolygonConstRingRange;



            template <>
            struct tag<OGRPolygon>
            {
                typedef polygon_tag type;
            };


            template <>
            struct ring_const_type<OGRPolygon>
            {
                typedef const OGRLinearRing &type;
            };


            template <>
            struct ring_mutable_type<OGRPolygon>
            {
                typedef OGRLinearRing &type;
            };


            template <>
            struct interior_const_type<OGRPolygon>
            {
                typedef CustomOGRPolygonConstRingRange type;
            };


            template <>
            struct interior_mutable_type<OGRPolygon>
            {
                typedef CustomOGRPolygonRingRange type;
            };


            template <>
            struct exterior_ring<OGRPolygon>
            {
                static OGRLinearRing &get(OGRPolygon &p)
                {
                    return *(p.getExteriorRing());
                }


                static const OGRLinearRing &get(OGRPolygon const &p)
                {
                    return *(p.getExteriorRing());
                }
            };


            template <>
            struct interior_rings<OGRPolygon>
            {
                static CustomOGRPolygonRingRange get(OGRPolygon &p)
                {
                    auto beginIter = range_begin(p);
                    beginIter++;

                    return CustomOGRPolygonRingRange(beginIter, range_end(p));
                }


                static const CustomOGRPolygonConstRingRange get(
                        OGRPolygon const &p)
                {
                    auto beginIter = range_begin(p);
                    beginIter++;

                    return CustomOGRPolygonConstRingRange(
                            beginIter,
                            range_end(p));
                }
            };
        }
    }
}

#endif // OGRPOLYGONTOBOOSTADAPTER_H
