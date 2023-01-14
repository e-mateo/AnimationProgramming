#pragma once
#include <cmath>


namespace maths
{
    const float PI = 3.14159265358979323846f;
    const float TAU = 6.283185307179586476925f;

    inline float cos(float x) { return cosf(x); }
    inline float sin(float x) { return sinf(x); }
    inline float tan(float x) { return tanf(x); }
    inline float rad(float x) { return (x * PI / 180); }

    template <typename T>
    inline T min(T x, T y)
    {
        return x <= y ? x : y;
    }

    template <typename T>
    inline T min(T x, T y, T z)
    {
        return min(x, min(y, z));
    }

    template <typename T>
    inline T max(T x, T y)
    {
        return x >= y ? x : y;
    }

    template <typename T>
    inline T Abs(T x)
    {
        return x >= 0 ? x : -x;
    }

    template <typename T>
    inline T Sign(T x)
    {
        return x >= 0 ? 1 : -1;
    }

    template <typename T>
    inline T Lerp(T a, T b, float t)
    {
        return a * (1 - t) + b * t;
    }

    class Vec2
    {
    public:
        float x, y;

        Vec2()
        {
            x = 0;
            y = 0;
        }

        Vec2(const float vecX, const float vecY)
        {
            x = vecX;
            y = vecY;
        }

        inline float GetMagnitude() const
        {
            return (sqrtf(x * x + y * y));
        }

        inline void Normalize()
        {
            float magnitude = GetMagnitude();
            x = x / magnitude;
            y = y / magnitude;
        }
    };

    inline Vec2 operator+(const Vec2 Vector1, const Vec2 Vector2)
    {
        Vec2 newVec2(Vector1.x + Vector2.x, Vector1.y + Vector2.y);
        return newVec2;
    }

    inline Vec2 operator-(const Vec2 Vector1, const Vec2 Vector2)
    {
        Vec2 newVec2(Vector1.x - Vector2.x, Vector1.y - Vector2.y);
        return newVec2;
    }

    inline Vec2 operator*(const Vec2 Vector1, const float a)
    {
        Vec2 newVec2(Vector1.x * a, Vector1.y * a);
        return newVec2;
    }

    inline float dotProduct(const Vec2 vec1, const Vec2 vec2)
    {
        return (vec1.x * vec2.x + vec1.y + vec2.y);
    }

    inline float crossProduct(const Vec2 vec1, const Vec2 vec2)
    {
        return (vec1.x * vec2.y - vec2.x + vec1.y);
    }

    inline bool isInsideTriangle(Vec2 point, Vec2 vertex0, Vec2 vertex1, Vec2 vertex2)
    {
        float edge_0_1 = (point.x - vertex0.x) * (vertex1.y - vertex0.y) - (point.y - vertex0.y) * (vertex1.x - vertex0.x);
        float edge_1_2 = (point.x - vertex1.x) * (vertex2.y - vertex1.y) - (point.y - vertex1.y) * (vertex2.x - vertex1.x);
        float edge_2_0 = (point.x - vertex2.x) * (vertex0.y - vertex2.y) - (point.y - vertex2.y) * (vertex0.x - vertex2.x);

        return (edge_0_1 >= -0.02 && edge_1_2 >= -0.02 && edge_2_0 >= -0.02) ? true : false;
    }

    inline float distanceBetweenTwoPoints(const Vec2 A, const Vec2 B)
    {
        float AB = (B - A).GetMagnitude();
        return AB;
    }

    inline Vec2 triangleGravityCenter(Vec2 vec1, Vec2 vec2, Vec2 vec3)
    {
        Vec2 gCenter;
        gCenter.x = (vec1.x + vec2.x + vec3.x) / 3;
        gCenter.y = (vec1.y + vec2.y + vec3.y) / 3;
        return gCenter;
    }

    inline float triangleArea(Vec2 vecA, Vec2 vecB, Vec2 vecC)
    {
        float a = distanceBetweenTwoPoints(vecA, vecB);
        float b = distanceBetweenTwoPoints(vecB, vecC);
        float c = distanceBetweenTwoPoints(vecC, vecA);
        float result = 0.25f * (sqrtf((a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c)));
        return result;
    }

    ////////////////////////////////////////////////////////////////////////

    class Vec3
    {
    public:
        float x, y, z;

        Vec3()
        {
            x = 0.f;
            y = 0.f;
            z = 0.f;
        }

        Vec3(const float vecX, const float vecY, const float vecZ)
        {
            x = vecX;
            y = vecY;
            z = vecZ;
        }

        inline Vec3 Add(const Vec3& other)
        {
            return Vec3(x + other.x, y + other.y, z + other.z);
        }

        inline float GetMagnitude() const
        {
            return (sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2)));
        }

        inline Vec3 Normalize()
        {
            float magnitude = GetMagnitude();
            Vec3 newVec;
            newVec.x = x / magnitude;
            newVec.y = y / magnitude;
            newVec.z = z / magnitude;
            return newVec;
        }

        inline Vec3 operator=(Vec3 other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }
    };

    inline Vec3 operator+(Vec3 Vector1, Vec3 Vector2)
    {
        Vec3 newVec3(Vector1.x + Vector2.x, Vector1.y + Vector2.y, Vector1.z + Vector2.z);
        return newVec3;
    }

    inline Vec3 operator-(Vec3 Vector1, Vec3 Vector2)
    {
        Vec3 newVec3(Vector1.x - Vector2.x, Vector1.y - Vector2.y, Vector1.z - Vector2.z);
        return newVec3;
    }

    inline Vec3 operator*(Vec3 Vector1, float a)
    {
        Vec3 newVec3(Vector1.x * a, Vector1.y * a, Vector1.z * a);
        return newVec3;
    }

    inline Vec3 operator*(float a, Vec3 Vector1)
    {
        Vec3 newVec3(Vector1.x * a, Vector1.y * a, Vector1.z * a);
        return newVec3;
    }

    inline bool operator==(Vec3 Vector1, Vec3 Vector2)
    {
        return (Vector1.x == Vector2.x && Vector1.y == Vector2.y && Vector1.z == Vector2.z);
    }

    inline Vec3 vectorProduct(const Vec3 vec1, const Vec3 vec2)
    {
        Vec3 newVector;
        newVector.x = vec1.y * vec2.z - vec1.z * vec2.y;
        newVector.y = vec1.z * vec2.x - vec1.x * vec2.z;
        newVector.x = vec1.x * vec2.y - vec1.y * vec2.x;
        return newVector;
    }

    inline float dotProduct(const Vec3 vec1, const Vec3 vec2)
    {
        return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
    }

    inline Vec3 findBarycentricCoor(Vec2 point, Vec2 vertexA, Vec2 vertexB, Vec2 vertexC)
    {
        float wA = triangleArea(point, vertexB, vertexC) / triangleArea(vertexA, vertexB, vertexC);
        float wB = triangleArea(point, vertexC, vertexA) / triangleArea(vertexA, vertexB, vertexC);
        float wC = triangleArea(point, vertexA, vertexB) / triangleArea(vertexA, vertexB, vertexC);
        Vec3 baryCoor(wA, wB, wC);
        return baryCoor;
    }

    inline Vec3 operator/(Vec3 Vector1, int a)
    {
        Vec3 newVec3(Vector1.x / a, Vector1.y / a, Vector1.z / a);
        return newVec3;
    }

    inline float distanceBetweenTwoPoints(const Vec3 A, const Vec3 B)
    {
        float AB = (B - A).GetMagnitude();
        return AB;
    }

    ////////////////////////////////////////////////////////////////////////

    class Vec4
    {
    public:
        float x, y, z, w;

        Vec4()
        {
            x = 0;
            y = 0;
            z = 0;
            w = 0;
        }

        Vec4(const float vecX, const float vecY, const float vecZ, const float vecW)
        {
            x = vecX;
            y = vecY;
            z = vecZ;
            w = vecW;
        }

        inline Vec3 Homogenize()
        {
            Vec3 newVec;
            if (w != 0)
            {
                newVec.x = x / w;
                newVec.y = y / w;
                newVec.z = z / w;
            }
            return newVec;
        }

        inline float GetMagnitude() const
        {
            return (sqrtf(x * x + y * y + z * z + w * w)); // x * x to not use powf
        }

        inline Vec3 NormalizeVec3()
        {
            Vec3 newVec;
            float magnitude = GetMagnitude();
            newVec.x = x / magnitude;
            newVec.y = y / magnitude;
            newVec.z = z / magnitude;
            return newVec;
        }

        inline Vec3 FillVec3(Vec3* other)
        {
            other->x = x;
            other->y = y;
            other->z = z;
            return *other;
        }

        inline Vec4 Normalize()
        {
            float magnitude = GetMagnitude();
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
            w /= magnitude;
            return *this;
        }

        Vec4(const Vec3& vec3, float _w = 1.f)
        {
            x = vec3.x;
            y = vec3.y;
            z = vec3.z;
            w = 1.f;
        }
    };

    inline Vec4 operator+(Vec4 Vector1, Vec4 Vector2)
    {
        Vec4 newVec4(Vector1.x + Vector2.x, Vector1.y + Vector2.y, Vector1.z + Vector2.z, Vector1.w + Vector2.w);
        return newVec4;
    }

    inline Vec4 operator-(Vec4 Vector1, Vec4 Vector2)
    {
        Vec4 newVec4(Vector1.x - Vector2.x, Vector1.y - Vector2.y, Vector1.z - Vector2.z, Vector1.w - Vector2.w);
        return newVec4;
    }

    inline Vec4 operator*(Vec4 Vector1, float a)
    {
        Vec4 newVec4(Vector1.x * a, Vector1.y * a, Vector1.z * a, Vector1.w * a);
        return newVec4;
    }

    inline Vec4 operator/(Vec4 Vector1, int a)
    {
        Vec4 newVec4(Vector1.x / a, Vector1.y / a, Vector1.z / a, Vector1.w / a);
        return newVec4;
    }

    ////////////////////////////////////////////////////////////////////////

    class Mat3
    {
    public:
        float matrix[3][3];
        float matrixArray[9];

        Mat3()
        {
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    matrix[j][i] = 0;

            FillArray();
        }

        Mat3(const float tab[3][3])
        {
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    matrix[j][i] = tab[j][i];

            FillArray();
        }

        inline float detMatrix()
        {
            float det = (this->matrix[0][0] * (this->matrix[1][1] * this->matrix[2][2] - (this->matrix[2][1] * this->matrix[1][2])))
                - (this->matrix[0][1] * (this->matrix[1][0] * this->matrix[2][2] - (this->matrix[2][0] * this->matrix[1][2])))
                + (this->matrix[0][2] * (this->matrix[1][0] * this->matrix[2][1] - (this->matrix[2][0] * this->matrix[1][1])));
            return det;
        }

        void FillArray()
        {
            int i = 0;

            for (int row = 0; row < 3; row++)
            {
                for (int column = 0; column < 3; column++)
                {
                    matrixArray[i] = matrix[column][row];
                    i++;
                }
            }
        }
    };

    ////////////////////////////////////////////////////////////////////////

    class Mat4
    {
    public:
        float matrix[4][4];
        float matrixArray[16];

        Mat4()
        {
            for (int row = 0; row < 4; row++)
                for (int column = 0; column < 4; column++)
                    matrix[column][row] = 0;

            for (int i = 0; i < 16; i++)
                matrixArray[i] = 0;
        }

        Mat4(const float tab[4][4])
        {
            for (int row = 0; row < 4; row++)
                for (int column = 0; column < 4; column++)
                    matrix[row][column] = tab[row][column];

            int i = 0;
            for (int row = 0; row < 4; row++)
            {
                for (int column = 0; column < 4; column++)
                {
                    matrixArray[i] = matrix[column][row];
                    i++;
                }
            }
        }

        inline Mat4 operator*(Mat4 other)
        {
            Mat4 newMat;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    newMat.matrix[i][j] = this->matrix[i][0] * other.matrix[0][j] + this->matrix[i][1] * other.matrix[1][j] + this->matrix[i][2] * other.matrix[2][j] + this->matrix[i][3] * other.matrix[3][j];

            newMat.FillArray();
            return newMat;
        }

        inline Mat4 operator=(Mat4 other)
        {
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    this->matrix[i][j] = other.matrix[i][j];

            FillArray();
            return *this;
        }

        inline float detMatrix()
        {
            float matrixA[3][3] = {{this->matrix[1][1], this->matrix[1][2], this->matrix[1][3]},
                                   {this->matrix[2][1], this->matrix[2][2], this->matrix[2][3]},
                                   {this->matrix[3][1], this->matrix[3][2], this->matrix[3][3]}};

            float matrixB[3][3] = {{this->matrix[1][0], this->matrix[1][2], this->matrix[1][3]},
                                   {this->matrix[2][0], this->matrix[2][2], this->matrix[2][3]},
                                   {this->matrix[3][0], this->matrix[3][2], this->matrix[3][3]}};

            float matrixC[3][3] = {{this->matrix[1][0], this->matrix[1][1], this->matrix[1][3]},
                                   {this->matrix[2][0], this->matrix[2][1], this->matrix[2][3]},
                                   {this->matrix[3][0], this->matrix[3][1], this->matrix[3][3]}};

            float matrixD[3][3] = {{this->matrix[1][0], this->matrix[1][1], this->matrix[1][2]},
                                   {this->matrix[2][0], this->matrix[2][1], this->matrix[2][2]},
                                   {this->matrix[3][0], this->matrix[3][1], this->matrix[3][2]}};

            Mat3 detMat4A(matrixA);
            Mat3 detMat4B(matrixB);
            Mat3 detMat4C(matrixC);
            Mat3 detMat4D(matrixD);

            float det = this->matrix[0][0] * detMat4A.detMatrix() - this->matrix[0][1] * detMat4B.detMatrix() + this->matrix[0][2] * detMat4C.detMatrix() - this->matrix[0][3] * detMat4D.detMatrix();
            return det;
        }

        inline static Mat4 CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale)
        {
            Mat4 transformMatrix = CreateTranslationMatrix(position) * CreateYRotationMatrix(rotation.y) * CreateXRotationMatrix(rotation.x) * CreateZRotationMatrix(rotation.z) * CreateScaleMatrix(scale);
            transformMatrix.FillArray();
            return transformMatrix;
        }

        inline static Mat4 CreateTranslationMatrix(const Vec3& translation)
        {
            Mat4 translationMatrix;
            translationMatrix.matrix[0][3] = translation.x;
            translationMatrix.matrix[1][3] = translation.y;
            translationMatrix.matrix[2][3] = translation.z;

            for (int i = 0; i < 4; i++)
                translationMatrix.matrix[i][i] = 1.f;

            translationMatrix.FillArray();
            return translationMatrix;
        }

        inline static Mat4 CreateScaleMatrix(const Vec3& scale)
        {
            Mat4 scaleMat;
            scaleMat.matrix[0][0] = scale.x;
            scaleMat.matrix[1][1] = scale.y;
            scaleMat.matrix[2][2] = scale.z;
            scaleMat.matrix[3][3] = 1.f;

            scaleMat.FillArray();
            return scaleMat;
        }

        inline static Mat4 CreateXRotationMatrix(const float angle) //(Matrix de rotation autour de laxe des X)
        {
            Mat4 rotaX;
            rotaX.matrix[0][0] = 1.f;
            rotaX.matrix[3][3] = 1.f;

            float radAngle = rad(angle);
            rotaX.matrix[1][1] = cosf(radAngle);
            rotaX.matrix[1][2] = -sinf(radAngle);
            rotaX.matrix[2][1] = sinf(radAngle);
            rotaX.matrix[2][2] = cosf(radAngle);

            rotaX.FillArray();
            return rotaX;
        }

        inline static Mat4 CreateYRotationMatrix(const float angle) //(Matrix de rotation autour de laxe des Y)
        {
            Mat4 rotaY;
            rotaY.matrix[1][1] = 1.f;
            rotaY.matrix[3][3] = 1.f;

            float radAngle = rad(angle);
            rotaY.matrix[0][0] = cosf(radAngle);
            rotaY.matrix[0][2] = -sinf(radAngle);
            rotaY.matrix[2][0] = sinf(radAngle);
            rotaY.matrix[2][2] = cosf(radAngle);

            rotaY.FillArray();
            return rotaY;
        }

        inline static Mat4 CreateZRotationMatrix(const float angle) //(Matrix de rotation autour de laxe des Z)
        {
            Mat4 rotaZ;
            rotaZ.matrix[2][2] = 1.f;
            rotaZ.matrix[3][3] = 1.f;

            float radAngle = rad(angle);
            rotaZ.matrix[0][0] = cosf(radAngle);
            rotaZ.matrix[0][1] = -sinf(radAngle);
            rotaZ.matrix[1][0] = sinf(radAngle);
            rotaZ.matrix[1][1] = cosf(radAngle);

            rotaZ.FillArray();
            return rotaZ;
        }

        inline Mat4 transposeMatrix()
        {
            Mat4 newMatrix;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    newMatrix.matrix[j][i] = this->matrix[i][j];

            newMatrix.FillArray();
            return newMatrix;
        }

        inline Mat4 inverseMatrix()
        {
            int line;
            int column;
            float det = this->detMatrix();
            Mat4 inverseMatrix;
            Mat4 adjMatrix;
            Mat3 matrix3;

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    line = 0;
                    column = 0;
                    for (int k = 0; k < 3; k++)
                    {
                        for (int h = 0; h < 3; h++)
                        {
                            if (column == j)
                            {
                                column++;
                                if (column >= 4)
                                {
                                    column = 0;
                                    line++;
                                }
                            }

                            if (line == i)
                                line++;

                            matrix3.matrix[k][h] = this->matrix[line][column];
                            column++;

                            if (column >= 4)
                            {
                                column = 0;
                                line++;
                            }
                        }
                    }
                    adjMatrix.matrix[i][j] = powf(-1.f, (float)(i + j)) * matrix3.detMatrix();
                }
            }

            adjMatrix = adjMatrix.transposeMatrix();

            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    inverseMatrix.matrix[i][j] = adjMatrix.matrix[i][j] * (1 / det);

            inverseMatrix.FillArray();
            return inverseMatrix;
        }

        inline static Mat4 identity()
        {
            float matrix[4][4] = {
                {1.f, 0.f, 0.f, 0.f},
                {0.f, 1.f, 0.f, 0.f},
                {0.f, 0.f, 1.f, 0.f},
                {0.f, 0.f, 0.f, 1.f},
            };
            return matrix;
        }

        Mat3 Mat4ToMat3()
        {
            Mat3 mat3;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    mat3.matrix[j][i] = matrix[j][i];

            mat3.FillArray();
            return mat3;
        }

        void FillArray()
        {
            int i = 0;

            for (int row = 0; row < 4; row++)
            {
                for (int column = 0; column < 4; column++)
                {
                    matrixArray[i] = matrix[column][row];
                    i++;
                }
            }
        }
    };

    inline Vec4 operator*(const Mat4 mat4, const Vec4 vec4)
    {
        Vec4 result;
        result.x = mat4.matrix[0][0] * vec4.x + mat4.matrix[0][1] * vec4.y + mat4.matrix[0][2] * vec4.z + mat4.matrix[0][3] * vec4.w;
        result.y = mat4.matrix[1][0] * vec4.x + mat4.matrix[1][1] * vec4.y + mat4.matrix[1][2] * vec4.z + mat4.matrix[1][3] * vec4.w;
        result.z = mat4.matrix[2][0] * vec4.x + mat4.matrix[2][1] * vec4.y + mat4.matrix[2][2] * vec4.z + mat4.matrix[2][3] * vec4.w;
        result.w = mat4.matrix[3][0] * vec4.x + mat4.matrix[3][1] * vec4.y + mat4.matrix[3][2] * vec4.z + mat4.matrix[3][3] * vec4.w;

        return result;
    }

    ////////////////////////////////////////////////////////////////////////

    class Quat 
    {
    public:
        float x, y, z, w;

        Quat()
        {
            x = 0.f;
            y = 0.f;
            z = 0.f;
            w = 0.f;
        }

        Quat(const float quatX, const float quatY, const float quatZ, const float quatW)
        {
            x = quatX;
            y = quatY;
            z = quatZ;
            w = quatW;
        }

        Quat(Vec3 axis, float angle)
        {
            x = sinf(angle / 2) * axis.x;
            y = sinf(angle / 2) * axis.y;
            z = sinf(angle / 2) * axis.z;
            w = cosf(angle / 2);
        }

        inline Quat operator=(Quat other)
        {
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
            this->w = other.w;
            return *this;
        }

        float Magnitude()
        {
            return sqrt(x * x + y * y + z * z + w * w);
        }

        float DotProduct(const Quat other)
        {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        Quat Conjugate()
        {
            return Quat(-x, -y, -z, w);
        }

        Quat Invert()
        {
            float invert = Magnitude() * Magnitude();
            return Quat(-x/invert, -y/invert, -z/invert, w/invert);
        }

        Quat Normalize()
        {
            float m = Magnitude();
            return Quat(x/m, y/m, z/m, w/m);
        }

        Quat AxisAngle2Quat(Vec3 axis, float angle)
        {
            return Quat(sinf(angle / 2) * axis.x, 
                        sinf(angle / 2) * axis.y, 
                        sinf(angle / 2) * axis.z, 
                        cosf(angle / 2));
        }

        void Quat2AxisAngle(Vec3& axis, float& angle)
        {
            angle = 2 * acosf(w);
            axis.x = x / sqrt(1 - w * w);
            axis.y = y / sqrt(1 - w * w);
            axis.z = z / sqrt(1 - w * w);
        }

        Mat4 AxisAngle2Mat4(Vec3 axis, float angle)
        {
            float cos = cosf(angle);
            float sin = sinf(angle);

            float tab[4][4] = {
                  { axis.x * axis.x * (1 - cos) + cos,              axis.x * axis.y * (1 - cos) - axis.z * sin,     axis.x * axis.z * (1 - cos) + axis.y * sin,     0},
                  { axis.x * axis.y * (1 - cos) - axis.z * sin,     axis.y * axis.y * (1 - cos) + cos,              axis.y * axis.z * (1 - cos) - axis.x * sin,     0},
                  { axis.x * axis.z * (1 - cos) + axis.y * sin,     axis.y * axis.z * (1 - cos) - axis.x * sin,     axis.z * axis.z * (1 - cos) + cos,              0},
                  { 0,                                              0,                                              0,                                              1}
            };

            Mat4 mat(tab);
            return mat;
        }

        Mat4 Quat2Mat()
        {
            float tab[4][4] = { 
                  { 2*(w*w + x*x) - 1,      2*(x*y - z*w),          2*(x*z + y*w),          0},
                  { 2*(x*y + z*w),          2*(w*w + y*y) - 1,      2*(y*z - x*w),          0},
                  { 2*(x*z - y*w),          2*(y*z + x*w),          2*(w*w + z*z) - 1,      0},
                  { 0,                       0,                     0,                      1}
            };

            Mat4 mat(tab);
            return mat;
        }
    };

    inline Quat operator+(const Quat q1, const Quat q2)
    {
        return Quat(q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w);
    }

    inline Quat operator-(const Quat q1, const Quat q2)
    {
        return Quat(q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w);
    }

    inline Quat operator*(const Quat q1, const Quat q2)
    {
        return Quat(q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
                    q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
                    q1.w * q2.z + q1.x * q2.y + q1.y * q2.x + q1.z * q2.w,
                    q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z);
    }

    inline Quat operator*(const float f, const Quat q1)
    {
        return Quat(q1.x * f, q1.y * f, q1.z * f, q1.w * f);
    }

    inline Quat operator/(const Quat q, const float f)
    { 
        return Quat(q.x / f, q.y / f, q.z / f, q.w / f);
    }

    inline Quat Slerp(Quat q1, Quat q2, const float t)
    {
        float cosTheta = q1.DotProduct(q2);

        if (Abs(cosTheta) >= 1)
            return q1;

        if (cosTheta < 0.f)
        {
            q2 = -1 * q2;
            cosTheta *= -1;
        }

        float theta = acosf(cosTheta);
        return (sinf((1 - t) * theta) * q1 + sinf(t * theta) * q2) / sinf(theta);
    }

    inline Quat Mat4ToQuaternion(Mat4 matrix)
    {
        Quat quat;
        quat.w = sqrtf(1 + matrix.matrix[0][0] + matrix.matrix[1][1] + matrix.matrix[2][2]) / 2.f;
        quat.x = (matrix.matrix[2][1] - matrix.matrix[1][2]) / (4 * quat.w);
        quat.y = (matrix.matrix[0][2] - matrix.matrix[2][0]) / (4 * quat.w);
        quat.z = (matrix.matrix[1][0] - matrix.matrix[0][1]) / (4 * quat.w);
        return quat;
    }

    inline Mat4 CreateTransformMatrix(const Quat& rotation, const Vec3& position)
    {
        Quat quat = rotation;
        Mat4 transformMatrix = Mat4::CreateTranslationMatrix(position) * quat.Normalize().Quat2Mat();
        transformMatrix.FillArray();
        return transformMatrix;
    }
}