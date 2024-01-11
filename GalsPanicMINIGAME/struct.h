#pragma once

struct Vec2
{
	float x;
	float y;
public:
	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}

	float DistanceTo(const Vec2& other) const
	{
		float dx = x - other.x;
		float dy = y - other.y;
		return std::sqrt(dx * dx + dy * dy);
	}

	float Length() { return (float)sqrt(pow(x, 2) + pow(y, 2)); }

	Vec2& Normalize()
	{
		float fLen = Length();
		// 0으로 나누거나, 곱하는 경우를 없애야 한다(예외처리) -> 연산이 복잡해진다

		x /= fLen;
		y /= fLen;
		return *this;
	}

public:
	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	bool operator == (const Vec2& other) const {
		return (x == other.x) && (y == other.y);
	}

	bool operator != (const Vec2& other) const {
		return !(*this == other);
	}

	bool operator < (const Vec2& other) const {
		if (x < other.x) return true;
		if (x == other.x && y < other.y) return true;
		return false;
	}

	bool operator > (const Vec2& other) const {
		if (x > other.x) return true;
		if (x == other.x && y > other.y) return true;
		return false;
	}

	bool operator <= (const Vec2& other) const {
		return !(*this > other);
	}

	bool operator >= (const Vec2& other) const {
		return (*this > other) || (*this == other);
	}

	Vec2 operator + (Vec2 _vOther) { return Vec2(x + _vOther.x, y + _vOther.y); }
	void operator += (Vec2 _vOther) { x += _vOther.x; y += _vOther.y; }
	Vec2 operator - (Vec2 _vOther) { return Vec2(x - _vOther.x, y - _vOther.y); }
	Vec2 operator * (Vec2 _vOther) { return Vec2(x * _vOther.x, y * _vOther.y); }
	Vec2 operator * (int _i) { return Vec2(x * (float)_i, y * (float)_i); }
	Vec2 operator * (float _f) { return Vec2(x * _f, y * _f); }
	Vec2 operator / (Vec2 _vOther) { assert(!(0.f == _vOther.x || 0.f == _vOther.y)); return Vec2(x / _vOther.x, y / _vOther.y); } // 0이 아니여야댐
	Vec2 operator / (float _f) { assert(!(0.f == _f)); return Vec2(x / _f, y / _f); }

public:
	Vec2() : x(0.f), y(0.f) {}
	Vec2(float _x, float _y) : x(_x), y(_y) {}
	Vec2(int _x, int _y) : x((float)_x), y((float)_y) {}
	Vec2(const POINT& _pt) : x((float)_pt.x), y((float)_pt.y) {}
};