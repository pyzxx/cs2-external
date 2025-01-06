#include "includes.h"

const float PI = acos(-1.0);

extern int screenWidth = GetSystemMetrics(SM_CXSCREEN);
extern int screenHeight = GetSystemMetrics(SM_CYSCREEN);

struct Vector2
{
    float x, y;
};

struct Vector4
{
    float w, x, y, z;
};

struct view_matrix_t
{
    float* operator[](int index)
    {
        return matrix[index];
    }

    float matrix[4][4];
};

// Inclua no seu struct Vector3 a função DistanceTo:
struct Vector3
{
    // Construtor
    Vector3(
        const float x = 0.f,
        const float y = 0.f,
        const float z = 0.f) noexcept :
        x(x), y(y), z(z) {}

    // Operador de subtração
    Vector3 operator-(const Vector3& other) const noexcept
    {
        return Vector3{ x - other.x, y - other.y, z - other.z };
    }

    // Operador de adição
    Vector3 operator+(const Vector3& other) const noexcept
    {
        return Vector3{ x + other.x, y + other.y, z + other.z };
    }

    // Operador de divisão
    Vector3 operator/(const float factor) const noexcept
    {
        return Vector3{ x / factor, y / factor, z / factor };
    }

    // Operador de multiplicação
    Vector3 operator*(const float factor) const noexcept
    {
        return Vector3{ x * factor, y * factor, z * factor };
    }

    // Método para calcular o comprimento (magnitude) do vetor
    float Length() const noexcept
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Método para calcular a distância entre dois vetores
    float DistanceTo(const Vector3& other) const noexcept
    {
        return (*this - other).Length();
    }

    Vector3 WTS(view_matrix_t matrix) const
    {
        float _x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
        float _y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];

        float w = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3];

        if (w < 0.01f)
            return Vector3{ 0, 0, 0 };

        float inv_w = 1.f / w;
        _x *= inv_w;
        _y *= inv_w;

        float x = screenWidth / 2;
        float y = screenHeight / 2;

        x += 0.5f * _x * screenWidth + 0.5f;
        y -= 0.5f * _y * screenHeight + 0.5f;

        return Vector3{ x, y, w };
    }

    const Vector3 ToAngle() const noexcept
    {
        return Vector3{
            std::atan2(-z, std::hypot(x, y)) * (180.0f / PI),
            std::atan2(y, x) * (180.0f / PI),
            0.0f };
    }

    const bool IsZero() const noexcept
    {
        return x == 0.f && y == 0.f && z == 0.f;
    }

    Vector3 Normalize() const noexcept
    {
        float magnitude = std::sqrt(x * x + y * y + z * z);
        if (magnitude == 0)
            return { 0, 0, 0 }; // Vetor nulo, sem normalização

        return { x / magnitude, y / magnitude, z / magnitude };
    }

    // Dados do vetor
    float x, y, z;
};

void simMouseclick()
{
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    SendInput(1, &input, sizeof(INPUT));

    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(1, &input, sizeof(INPUT));

}