#pragma once

//1���� ���� ����. a�� b������ ���� ��, �������� t(0.0 ~ 1.0) ������ �ִ� ���� �����Ͽ� ��ȯ�Ѵ�.
inline float Lerp(float a, float b, float t)
{
	return float(1 - t)*a + (t*b);
}

//3���� ���� ����. min ���Ϳ� max ������ ���� �ึ�� 1���� ���������Ͽ� ������ ���͸� �����.
inline D3DXVECTOR3 Lerp(D3DXVECTOR3 departure, D3DXVECTOR3 destination, float t)
{
	D3DXVECTOR3 result = { Lerp(departure.x,destination.x,t),Lerp(departure.y,destination.y,t),Lerp(departure.z,destination.z,t) };
	return result;
}