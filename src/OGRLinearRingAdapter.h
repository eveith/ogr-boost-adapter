#ifndef OGRLINEARRINGTOBOOSTADAPTER_H
#define OGRLINEARRINGTOBOOSTADAPTER_H


#include <ogr_geometry.h>

#include <boost/range.hpp>
#include <boost/geometry/geometries/register/ring.hpp>

#include "boost/OGRPointCollectionIterator.h"


namespace  Winzent {
    namespace Simulation {
        namespace boost {


            /*!
             * \brief An iterator for OGRLineString objects
             */
            typedef OGRPointCollectionIter<OGRLinearRing, OGRPoint>
                    OGRLinearRingIterator;

            /*!
             * \brief A const-access iterator for OGRLineString objects
             */
            typedef OGRPointCollectionIter<
                    const OGRLinearRing,
                    const OGRPoint>
                        OGRLinearRingConstIterator;
        } // namespace boost
    } // namespace Simulation
} // namespace Winzent


namespace boost {
    template <>
    struct range_iterator<OGRLinearRing>
    {
        typedef Winzent::Simulation::boost::OGRLinearRingIterator type;
    };


    template <>
    struct range_const_iterator<OGRLinearRing>
    {
        typedef Winzent::Simulation::boost::OGRLinearRingConstIterator type;
    };
}


inline Winzent::Simulation::boost::OGRLinearRingIterator
range_begin(OGRLinearRing &l)
{
    return Winzent::Simulation::boost::OGRLinearRingIterator(l);
}


inline Winzent::Simulation::boost::OGRLinearRingIterator
range_end(OGRLinearRing &l)
{
    auto iter = range_begin(l);
    iter += l.getNumPoints();
    return iter;
}


inline Winzent::Simulation::boost::OGRLinearRingConstIterator
range_begin(const OGRLinearRing &l)
{
    return Winzent::Simulation::boost::OGRLinearRingConstIterator(l);
}


inline Winzent::Simulation::boost::OGRLinearRingConstIterator
range_end(const OGRLinearRing &l)
{
    auto iter = range_begin(l);
    iter += l.getNumPoints();
    return iter;
}


BOOST_GEOMETRY_REGISTER_RING(OGRLinearRing)


#endif // OGRLINEARRINGTOBOOSTADAPTER_H
