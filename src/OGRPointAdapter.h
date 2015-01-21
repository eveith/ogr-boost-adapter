#ifndef OGRPOINTTOBOOSTADAPTER_H
#define OGRPOINTTOBOOSTADAPTER_H


#include <QtGlobal>

#include <memory>

#include <ogr_geometry.h>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>


BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(
        OGRPoint,
        qreal,
        boost::geometry::cs::cartesian,
        getX,
        getY,
        setX,
        setY)


namespace boost {
    namespace geometry {
        namespace traits {
            template<>
            struct tag<std::shared_ptr<OGRPoint>>
            {
                typedef point_tag type;
            };


            template<>
            struct dimension<std::shared_ptr<OGRPoint>>: boost::mpl::int_<2>
            {
            };


            template<>
            struct coordinate_type<std::shared_ptr<OGRPoint>>
            {
                typedef qreal type;
            };


            template<>
            struct coordinate_system<std::shared_ptr<OGRPoint>>
            {
                typedef cs::cartesian type;
            };


            template<> struct access<std::shared_ptr<OGRPoint>, 0>
            {
                static inline qreal get(
                        const std::shared_ptr<OGRPoint> &point)
                {
                    return point->getX();
                }


                static inline void set(
                        std::shared_ptr<OGRPoint> &point,
                        const qreal &value)
                {
                    point->setX(value);
                }
            };


            template<> struct access<std::shared_ptr<OGRPoint>, 1>
            {
                static inline qreal get(
                        const std::shared_ptr<OGRPoint> &point)
                {
                    return point->getY();
                }


                static inline void set(
                        std::shared_ptr<OGRPoint> &point,
                        const qreal &value)
                {
                    point->setY(value);
                }
            };
        } // namespace traits
    } // namespace geometry
} // namespace boost


#endif // OGRPOINTTOBOOSTADAPTER_H
