#pragma once

//1차원 선형 보간. a와 b사이의 값들 중, 수직선상 t(0.0 ~ 1.0) 지점에 있는 값을 추정하여 반환한다.
inline float Lerp(float a, float b, float t)
{
	return float(1 - t)*a + (t*b);
}

//3차원 선형 보간. min 벡터와 max 벡터의 대응 축마다 1차원 선형보간하여 보간된 벡터를 만든다.
inline D3DXVECTOR3 Lerp(D3DXVECTOR3 departure, D3DXVECTOR3 destination, float t)
{
	D3DXVECTOR3 result = { Lerp(departure.x,destination.x,t),Lerp(departure.y,destination.y,t),Lerp(departure.z,destination.z,t) };
	return result;
}