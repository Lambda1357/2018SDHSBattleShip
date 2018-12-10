#pragma once

class Button : public Object
{
private:
	function<void()> behavior;
	enum Status
	{
		none, over, push
	};
	Status status;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Destroy()	override;

	Button(D3DXVECTOR3 vPos, D3DXVECTOR3 vSz, string spriteName, std::function<void()> _behavior);
	~Button();
};