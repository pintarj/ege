#include <cmath>

template<unsigned H, unsigned W, typename T>
ege::math::Matrix<H, W, T>::Matrix()
{
    for (unsigned h = 0; h < H; ++h)
        for (unsigned w = 0; w < W; ++w)
            this->raw[h][w] = 0;
}

template<unsigned H, unsigned W, typename T>
ege::math::Matrix<H, W, T>::Matrix(T (& raw)[H][W])
{
    for (unsigned h = 0; h < H; ++h)
        for (unsigned w = 0; w < W; ++w)
            this->raw[h][w] = raw[h][w];
}

template<unsigned H, unsigned W, typename T>
T* ege::math::Matrix<H, W, T>::operator [](unsigned index)
{
    return raw[index];
}

template<unsigned H, unsigned W, typename T>
const T* ege::math::Matrix<H, W, T>::operator [](unsigned index) const
{
    return raw[index];
}

template<unsigned M, unsigned N, unsigned P, typename T = float>
ege::math::Matrix<M, P, T> ege::math::operator *(ege::math::Matrix<M, N, T> const& left, ege::math::Matrix<N, P, T> const& right)
{
    T raw[M][P];

    for (unsigned i = 0; i < M; ++i)
    {
        for (unsigned j = 0; j < P; ++j)
        {
            T sum = 0;

            for (unsigned k = 0; k < N; ++k)
                sum += left[i][k] * right[k][j];

            raw[i][j] = sum;
        }
    }

    return ege::math::Matrix<M, P, T>(raw);
}

template<unsigned M, unsigned N, unsigned P, typename T = float>
ege::math::Matrix<M, P, T>& ege::math::operator *=(ege::math::Matrix<M, N, T>& left, ege::math::Matrix<N, P, T> const& right)
{
    ege::math::Matrix<M, P, T> tmp = left * right;
    left = tmp;
}

template<unsigned M = 4, typename T = float>
ege::math::Matrix<M, M, T> ege::math::matrix::identity()
{
    T matrix[M][M];

    for (unsigned i = 0; i < M; ++i)
        for (unsigned j = 0; j < M; ++j)
            matrix[i][j] = (i == j) ? 1 : 0;

    return ege::math::Matrix<M, M, T>(matrix);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::scale(T x, T y, T z)
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

    return ege::math::Matrix<4, 4, T>(matrix);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::scale(Vector<3, T> const& vector)
{
    return scale(vector[0], vector[1], vector[2]);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::translate(T x, T y, T z)
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

    return ege::math::Matrix<4, 4, T>(matrix);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::translate(Vector<3, T> const& vector)
{
    return translate(vector[0], vector[1], vector[2]);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::rotateX(T radians)
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

    return ege::math::Matrix<4, 4, T>(matrix);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::rotateY(T radians)
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

    return ege::math::Matrix<4, 4, T>(matrix);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::rotateZ(T radians)
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

    return ege::math::Matrix<4, 4, T>(matrix);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::rotate(T radians, T x, T y, T z, bool normalize)
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

    return ege::math::Matrix<4, 4, T>(matrix);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::rotate(T radians, Vector<3, T> const& vector, bool normalize)
{
    if (normalize)
    {
        Vector<3, T> normalized = vector.normalized();
        return rotate(radians, normalized[0], normalized[1], normalized[2], false);
    }
    else
        return rotate(radians, vector[0], vector[1], vector[2], false);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::frustum(T left, T right, T bottom, T top, T near, T far)
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

    return ege::math::Matrix<4, 4, T>(matrix);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::perspective(T radians, T ratio, T near, T far)
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

    return ege::math::Matrix<4, 4, T>(matrix);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::ortho(T left, T right, T bottom, T top, T near, T far)
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

    return ege::math::Matrix<4, 4, T>(matrix);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::ortho2D(T left, T right, T bottom, T top)
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

    return ege::math::Matrix<4, 4, T>(matrix);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::fromOriginLookAt(T centerX, T centerY, T centerZ, T upX, T upY, T upZ)
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

    return ege::math::Matrix<4, 4, T>(matrix);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::fromOriginLookAt(Vector<3, T> const& center, Vector<3, T> const& up)
{
    return fromOriginLookAt(center[0], center[1], center[2], up[0], up[1], up[2]);
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::lookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ)
{
    ege::math::Matrix<4, 4, T> left = ege::math::matrix::fromOriginLookAt<T>(centerX, centerY, centerZ, upX, upY, upZ);
    ege::math::Matrix<4, 4, T> right = ege::math::matrix::translate<T>(-eyeX, -eyeY, -eyeZ);
    return left * right;
}

template<typename T = float>
ege::math::Matrix<4, 4, T> ege::math::matrix::lookAt(Vector<3, T> const& eye, Vector<3, T> const& center, Vector<3, T> const& up)
{
    return lookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
}
