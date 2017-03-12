#include <ege/opengl/util/matrix.hxx>

namespace ege
{
    namespace opengl
    {
        namespace util
        {
            template<typename T>
            math::Matrix<4, 4, T> scale(T x, T y, T z) noexcept
            {
                T matrix[4][4];

                matrix[0][0] = x;
                matrix[0][1] = 0;
                matrix[0][2] = 0;
                matrix[0][3] = 0;

                matrix[1][0] = 0;
                matrix[1][1] = y;
                matrix[1][2] = 0;
                matrix[1][3] = 0;

                matrix[2][0] = 0;
                matrix[2][1] = 0;
                matrix[2][2] = z;
                matrix[2][3] = 0;

                matrix[3][0] = 0;
                matrix[3][1] = 0;
                matrix[3][2] = 0;
                matrix[3][3] = 1;

                return math::Matrix<4, 4, T>(matrix);
            }

            template<typename T>
            math::Matrix<4, 4, T> scale(const math::Vector<3, T>& vector) noexcept
            {
                return scale(vector[0], vector[1], vector[2]);
            }

            template<typename T>
            math::Matrix<4, 4, T> translate(T x, T y, T z) noexcept
            {
                T matrix[4][4];

                matrix[0][0] = 1;
                matrix[0][1] = 0;
                matrix[0][2] = 0;
                matrix[0][3] = x;

                matrix[1][0] = 0;
                matrix[1][1] = 1;
                matrix[1][2] = 0;
                matrix[1][3] = y;

                matrix[2][0] = 0;
                matrix[2][1] = 0;
                matrix[2][2] = 1;
                matrix[2][3] = z;

                matrix[3][0] = 0;
                matrix[3][1] = 0;
                matrix[3][2] = 0;
                matrix[3][3] = 1;

                return math::Matrix<4, 4, T>(matrix);
            }

            template<typename T>
            math::Matrix<4, 4, T> translate(const math::Vector<3, T>& vector) noexcept
            {
                return translate(vector[0], vector[1], vector[2]);
            }

            template<typename T>
            math::Matrix<4, 4, T> rotateX(T radians) noexcept
            {
                T matrix[4][4];

                T sin = std::sin(radians);
                T cos = std::cos(radians);

                matrix[0][0] = 1;
                matrix[0][1] = 0;
                matrix[0][2] = 0;
                matrix[0][3] = 0;

                matrix[1][0] = 0;
                matrix[1][1] = cos;
                matrix[1][2] = -sin;
                matrix[1][3] = 0;

                matrix[2][0] = 0;
                matrix[2][1] = sin;
                matrix[2][2] = cos;
                matrix[2][3] = 0;

                matrix[3][0] = 0;
                matrix[3][1] = 0;
                matrix[3][2] = 0;
                matrix[3][3] = 1;

                return math::Matrix<4, 4, T>(matrix);
            }

            template<typename T>
            math::Matrix<4, 4, T> rotateY(T radians) noexcept
            {
                T matrix[4][4];

                T sin = std::sin(radians);
                T cos = std::cos(radians);

                matrix[0][0] = cos;
                matrix[0][1] = 0;
                matrix[0][2] = sin;
                matrix[0][3] = 0;

                matrix[1][0] = 0;
                matrix[1][1] = 1;
                matrix[1][2] = 0;
                matrix[1][3] = 0;

                matrix[2][0] = -sin;
                matrix[2][1] = 0;
                matrix[2][2] = cos;
                matrix[2][3] = 0;

                matrix[3][0] = 0;
                matrix[3][1] = 0;
                matrix[3][2] = 0;
                matrix[3][3] = 1;

                return math::Matrix<4, 4, T>(matrix);
            }

            template<typename T>
            math::Matrix<4, 4, T> rotateZ(T radians) noexcept
            {
                T matrix[4][4];

                T sin = std::sin(radians);
                T cos = std::cos(radians);

                matrix[0][0] = cos;
                matrix[0][1] = -sin;
                matrix[0][2] = 0;
                matrix[0][3] = 0;

                matrix[1][0] = sin;
                matrix[1][1] = cos;
                matrix[1][2] = 0;
                matrix[1][3] = 0;

                matrix[2][0] = 0;
                matrix[2][1] = 0;
                matrix[2][2] = 1;
                matrix[2][3] = 0;

                matrix[3][0] = 0;
                matrix[3][1] = 0;
                matrix[3][2] = 0;
                matrix[3][3] = 1;

                return math::Matrix<4, 4, T>(matrix);
            }

            template<typename T>
            math::Matrix<4, 4, T> rotate(T radians, T x, T y, T z, bool normalize) noexcept
            {
                T matrix[4][4];

                if (normalize)
                {
                    T length = std::sqrt(x * x + y * y + z * z);
                    T factor = 1 / length;
                    x *= factor;
                    y *= factor;
                    z *= factor;
                }

                T sin = std::sin(radians);
                T cos = std::cos(radians);
                T mcos = 1 - cos;
                T xmcos = x * mcos;
                T ymcos = y * mcos;
                T zmcos = z * mcos;
                T xymcos = x * ymcos;
                T yzmcos = y * zmcos;
                T zxmcos = z * xmcos;
                T xsin = x * sin;
                T ysin = y * sin;
                T zsin = z * sin;

                matrix[0][0] = x * xmcos + cos;
                matrix[0][1] = xymcos - zsin;
                matrix[0][2] = zxmcos + ysin;
                matrix[0][3] = 0;

                matrix[1][0] = xymcos + zsin;
                matrix[1][1] = y * ymcos + cos;
                matrix[1][2] = yzmcos - xsin;
                matrix[1][3] = 0;

                matrix[2][0] = zxmcos - ysin;
                matrix[2][1] = yzmcos + xsin;
                matrix[2][2] = z * zmcos + cos;
                matrix[2][3] = 0;

                matrix[3][0] = 0;
                matrix[3][1] = 0;
                matrix[3][2] = 0;
                matrix[3][3] = 1;

                return math::Matrix<4, 4, T>(matrix);
            }

            template<typename T>
            math::Matrix<4, 4, T> rotate(T radians, const math::Vector<3, T>& vector, bool normalize) noexcept
            {
                if (normalize)
                {
                    math::Vector<3, T> normalized = vector.normalized();
                    return rotate(radians, normalized[0], normalized[1], normalized[2], false);
                }
                else
                    return rotate(radians, vector[0], vector[1], vector[2], false);
            }

            template<typename T>
            math::Matrix<4, 4, T> frustum(T left, T right, T bottom, T top, T near, T far) noexcept
            {
                T matrix[4][4];

                T rml = right - left;
                T tmb = top - bottom;
                T fmn = far - near;
                T n2 = 2 * near;

                matrix[0][0] = n2 / rml;
                matrix[0][1] = 0;
                matrix[0][2] = (right + left) / rml;
                matrix[0][3] = 0;

                matrix[1][0] = 0;
                matrix[1][1] = n2 / tmb;
                matrix[1][2] = (top + bottom) / tmb;
                matrix[1][3] = 0;

                matrix[2][0] = 0;
                matrix[2][1] = 0;
                matrix[2][2] = -((far + near) / fmn);
                matrix[2][3] = -((n2 * far) / fmn);

                matrix[3][0] = 0;
                matrix[3][1] = 0;
                matrix[3][2] = -1;
                matrix[3][3] = 0;

                return math::Matrix<4, 4, T>(matrix);
            }

            template<typename T>
            math::Matrix<4, 4, T> perspective(T radians, T ratio, T near, T far) noexcept
            {
                T matrix[4][4];

                T f = 1 / std::tan(radians / 2);
                T d = near - far;

                matrix[0][0] = f / ratio;
                matrix[0][1] = 0;
                matrix[0][3] = 0;
                matrix[0][2] = 0;

                matrix[1][0] = 0;
                matrix[1][1] = f;
                matrix[1][2] = 0;
                matrix[1][3] = 0;

                matrix[2][0] = 0;
                matrix[2][1] = 0;
                matrix[2][2] = (far + near) / d;
                matrix[2][3] = (2 * far * near) / d;

                matrix[3][0] = 0;
                matrix[3][1] = 0;
                matrix[3][2] = -1;
                matrix[3][3] = 0;

                return math::Matrix<4, 4, T>(matrix);
            }

            template<typename T>
            math::Matrix<4, 4, T> ortho(T left, T right, T bottom, T top, T near, T far) noexcept
            {
                T matrix[4][4];

                T rml = right - left;
                T tmb = top - bottom;
                T fmn = far - near;

                matrix[0][0] = 2 / rml;
                matrix[0][1] = 0;
                matrix[0][2] = 0;
                matrix[0][3] = -((right + left) / rml);

                matrix[1][0] = 0;
                matrix[1][1] = 2 / tmb;
                matrix[1][2] = 0;
                matrix[1][3] = -((top + bottom) / tmb);

                matrix[2][0] = 0;
                matrix[2][1] = 0;
                matrix[2][2] = -2 / fmn;
                matrix[2][3] = -((far + near) / fmn);

                matrix[3][0] = 0;
                matrix[3][1] = 0;
                matrix[3][2] = 0;
                matrix[3][3] = 1;

                return math::Matrix<4, 4, T>(matrix);
            }

            template<typename T>
            math::Matrix<4, 4, T> ortho2D(T left, T right, T bottom, T top) noexcept
            {
                T matrix[4][4];

                T rml = right - left;
                T tmb = top - bottom;

                matrix[0][0] = 2 / rml;
                matrix[0][1] = 0;
                matrix[0][2] = 0;
                matrix[0][3] = -((right + left) / rml);

                matrix[1][0] = 0;
                matrix[1][1] = 2 / tmb;
                matrix[1][2] = 0;
                matrix[1][3] = -((top + bottom) / tmb);

                matrix[2][0] = 0;
                matrix[2][1] = 0;
                matrix[2][2] = -1;
                matrix[2][3] = 0;

                matrix[3][0] = 0;
                matrix[3][1] = 0;
                matrix[3][2] = 0;
                matrix[3][3] = 1;

                return math::Matrix<4, 4, T>(matrix);
            }

            template<typename T>
            math::Matrix<4, 4, T> fromOriginLookAt(T centerX, T centerY, T centerZ, T upX, T upY, T upZ) noexcept
            {
                T matrix[4][4];

                T icl = 1 / std::sqrt((centerX * centerX) + (centerY * centerY) + (centerZ * centerZ));
                T ncx = centerX * icl;
                T ncy = centerY * icl;
                T ncz = centerZ * icl;
                T mx0 = (ncy * upZ) - (ncz * upY);
                T mx4 = (ncz * upX) - (ncx * upZ);
                T mx8 = (ncx * upY) - (ncy * upX);
                T isl = 1 / std::sqrt((mx0 * mx0) + (mx4 * mx4) + (mx8 * mx8));
                T snX = mx0 * isl;
                T snY = mx4 * isl;
                T snZ = mx8 * isl;

                matrix[0][0] = mx0;
                matrix[0][1] = mx4;
                matrix[0][2] = mx8;
                matrix[0][3] = 0;

                matrix[1][0] = (snY * ncz) - (snZ * ncy);
                matrix[1][1] = (snZ * ncx) - (snX * ncz);
                matrix[1][2] = (snX * ncy) - (snY * ncx);
                matrix[1][3] = 0;

                matrix[2][0] = -ncx;
                matrix[2][1] = -ncy;
                matrix[2][2] = -ncz;
                matrix[2][3] = 0;

                matrix[3][0] = 0;
                matrix[3][1] = 0;
                matrix[3][2] = 0;
                matrix[3][3] = 1;

                return math::Matrix<4, 4, T>(matrix);
            }

            template<typename T>
            math::Matrix<4, 4, T> fromOriginLookAt(const math::Vector<3, T>& center, const math::Vector<3, T>& up) noexcept
            {
                return fromOriginLookAt(center[0], center[1], center[2], up[0], up[1], up[2]);
            }

            template<typename T>
            math::Matrix<4, 4, T> lookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ) noexcept
            {
                math::Matrix<4, 4, T> left = fromOriginLookAt<T>(centerX, centerY, centerZ, upX, upY, upZ);
                math::Matrix<4, 4, T> right = translate<T>(-eyeX, -eyeY, -eyeZ);
                return left * right;
            }

            template<typename T>
            math::Matrix<4, 4, T> lookAt(const math::Vector<3, T>& eye, const math::Vector<3, T>& center, const math::Vector<3, T>& up) noexcept
            {
                return lookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
            }            
        }
    }
}
