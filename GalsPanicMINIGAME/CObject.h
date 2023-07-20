#pragma once
class CObject
{
private:
	Vec2 vPos;
	Vec2 vScale;

public:
	void SetPos(Vec2 _vPos) { vPos = _vPos; }
	void SetScale(Vec2 _vScale) { vScale = _vScale; }

	Vec2 GetPos() { return vPos; }
	Vec2 GetScale() { return vScale; }

public:
	virtual void Update() = 0;
	virtual void Render(HDC hdc);

public:
	CObject();
	~CObject();
};

