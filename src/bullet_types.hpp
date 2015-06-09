#ifndef _BULLET_TYPES_HPP_
#define _BULLET_TYPES_HPP_

#include "bullet.hpp"

namespace Flyy
{
    namespace Game
    {
        class BulletBool :
            public Bullet
        {
            bool m_state;

        public:
            BulletBool();
            BulletBool(std::string text);

            std::string text();
        private:
            void getState();
        };

        class BulletInt :
            public Bullet
        {
            int m_lowerRange{0};
            int m_upperRange{100};

            int m_value;

        public:
            BulletInt();
            BulletInt(std::string text);

            std::string text();
            void setRange(int lower, int upper);
        private:
            void getValue();
        };
    } // namespace Game
} // namespace Flyy

#endif //_BULLET_TYPES_HPP_
