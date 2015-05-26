#ifndef OGRLINESTRINGTOBOOSTADAPTER_H
#define OGRLINESTRINGTOBOOSTADAPTER_H


#include <ogr_geometry.h>

#include <boost/range.hpp>
#include <boost/geometry/geometries/register/linestring.hpp>
#include <boost/geometry/geometries/register/multi_linestring.hpp>

#include "boost/OGRPointAdapter.h"
#include "boost/OGRPointCollectionIterator.h"



namespace  Winzent {
    namespace Simulation {
        namespace boost {

            /*!
             * \brief An iterator for OGRLineString objects
             */
            typedef OGRPointCollectionIter<OGRLineString, OGRPoint>
                    OGRLineStringIterator;

            /*!
             * \brief A const-access iterator for OGRLineString objects
             */
            typedef OGRPointCollectionIter<
                        const OGRLineString, const OGRPoint>
                    OGRLineStringConstIterator;
        } // namespace boost
    } // namespace Simulation
} // namespace Winzent


namespace boost {
    template <>
    struct range_mutable_iterator<OGRLineString>
    {
        typedef Winzent::Simulation::boost::OGRLineStringIterator type;
    };


    template <>
    struct range_const_iterator<OGRLineString>
    {
        typedef Winzent::Simulation::boost::OGRLineStringConstIterator type;
    };
}


namespace boost {
    namespace geometry {
        namespace traits {
            template <>
            struct clear<OGRLineString>
            {
                static inline void apply(
                        typename rvalue_type<OGRLineString>::type range)
                {
                    range.empty();
                }
            };


           template <>
            struct resize<OGRLineString>
            {
                static inline void apply(
                            typename rvalue_type<OGRLineString>::type,
                            std::size_t)
                {
                    // NOP.
                }
            };


            template <>
            struct push_back<OGRLineString>
            {
                typedef OGRPoint item_type;


                static inline void apply(
                        typename rvalue_type<OGRLineString>::type range,
                        item_type const &item)
                {
                    range.addPoint(item.getX(), item.getY(), item.getZ());
                }
            };
        }
    }
}


inline Winzent::Simulation::boost::OGRLineStringIterator
range_begin(OGRLineString &l)
{
    return Winzent::Simulation::boost::OGRLineStringIterator(l);
}


inline Winzent::Simulation::boost::OGRLineStringIterator
range_end(OGRLineString &l)
{
    auto iter = range_begin(l);
    iter += l.getNumPoints();
    return iter;
}


inline Winzent::Simulation::boost::OGRLineStringConstIterator
range_begin(const OGRLineString &l)
{
    return Winzent::Simulation::boost::OGRLineStringConstIterator(l);
}


inline Winzent::Simulation::boost::OGRLineStringConstIterator
range_end(const OGRLineString &l)
{
    auto iter = range_begin(l);
    iter += l.getNumPoints();
    return iter;
}


BOOST_GEOMETRY_REGISTER_LINESTRING(OGRLineString)


#endif // OGRLINESTRINGTOBOOSTADAPTER_H
