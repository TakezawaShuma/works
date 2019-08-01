#pragma once
#include "../GameObject.h"

class Bullet : GameObject
{
public:
	Bullet();
	~Bullet();

	// �J�n
	void Start();
	
	
	// ����
	void Shoot(DirectX::SimpleMath::Vector2 _pos,DirectX::SimpleMath::Vector2 _dir);

	// �X�V
	void Update();
	void OtherUpdate(DirectX::SimpleMath::Vector2 _pos);

	// �`��
	void Draw();
	void DrawBegin();
	void DrawEnd();

	// �Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }
	void SetPosition(float _x, float _y) { m_position.x = _x; m_position.y = _y; }
	void SetPosition(DirectX::SimpleMath::Vector2 _pos) { m_position = _pos; }

	bool GetActive() { return m_active; }
	void SetActive(bool _is) { m_active = _is; }
public:

private:
	// ����
	bool m_active;
	// �X�^�[�g�|�W�V����
	DirectX::SimpleMath::Vector2 m_startPosition;
};
