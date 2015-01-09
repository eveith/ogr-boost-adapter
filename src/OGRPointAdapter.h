#ifndef OGRPOINTTOBOOSTADAPTER_H
#define OGRPOINTTOBOOSTADAPTER_H


#include <QtGlobal>

#include <ogr_geometry.h>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>

#include "boost/OGRCoordinateSystem.h"


BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(
        OGRPoint,
        qreal,
        //boost::geometry::cs::cartesian,
        Winzent::Simulation::boost::OGRCoordinateSystem,
        getX,
        getY,
        setX,
        setY)


#endif // OGRPOINTTOBOOSTADAPTER_H
