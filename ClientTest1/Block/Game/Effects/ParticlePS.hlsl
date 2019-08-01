#include "Particle.hlsli"


Texture2D tex1 : register(t0);
Texture2D tex2 : register(t1);
Texture2D tex3 : register(t2);
Texture2D tex4 : register(t3);
Texture2D tex5 : register(t4);
Texture2D tex6 : register(t5);

SamplerState samLinear : register(s0);



// ノイズ -----------------------------------------------------------------------------------------
// ランダムノイズ(テクスチャ)
float Random(float2 _s)
{
	// frac = 小数点以下を取り出す　12.343->0.343
	return frac(sin(dot(_s, float2(12.9898f, 78.233f)))*43758.5453f);
}
// ブロックノイズ(テクスチャ)
float BlockNoise(float2 _s)
{
	float2 p = floor(_s);
	return Random(p);
}
// トーンノイズ(テクスチャ)
float ToneNoise(float2 _s)
{
	_s = float2(dot(_s, float2(127.1f, 311.7f)), dot(_s, float2(269.5f, 183.3f)));
	float ret = (float)(-1.0f + 2.0f * frac(sin(_s) * 43758.5453123f));
	return ret;
}
// パーリンノイズ(テクスチャ)
float PerlinNoise(float2 _s)
{
	float2 p = floor(_s);
	float2 f = frac(_s);
	float2 u = f * f * (3.0f - 2.0f * f);

	float v00 = ToneNoise(p + float2(0, 0));
	float v10 = ToneNoise(p + float2(1, 0));
	float v01 = ToneNoise(p + float2(0, 1));
	float v11 = ToneNoise(p + float2(1, 1));


	// lerp = 線形補間(2点間の中間をとっている)
	// dot  = 内積
	return lerp(lerp(dot(v00, f - float2(0, 0)), dot(v10, f - float2(1, 0)), u.x),
		lerp(dot(v01, f - float2(0, 1)), dot(v11, f - float2(1, 1)), u.x),
		u.y) + 0.5f;
}
// FBM(テクスチャ)
float FBM(float2 _s)
{
	float f = 0;
	float2 q = _s;

	f += 0.5000f * PerlinNoise(q); q = q * 2.01f;
	f += 0.2500f * PerlinNoise(q); q = q * 2.02f;
	f += 0.1250f * PerlinNoise(q); q = q * 2.03f;
	//f += 0.0625f * PerlinNoise(q); q = q * 2.01f;

	return f;
}
// ------------------------------------------------------------------------------------------------

/// <summary>
/// グレースケール
/// </summary>
float GrayScale(float4 _color)
{
	// 画像の灰色化
	float gray = _color.r * 0.2f + _color.g * 0.7f + _color.b * 0.1f;
	return gray;
}



//　歪みをつける ----------------------------------------------------------------------------------
/// <summary>
/// 歪ませる
/// </summary>
float Distortion(float2 _center, float _radius, float _width, float2 _tex)
{
	// 中心からの距離
	float dist = distance(_center, _tex);

	// 歪みを出す(第一と第二の差がゆがみの大きさ)
	float distortion = 1 - smoothstep(_radius - _width, _radius, dist);

	return distortion;
}
/// <summary>
/// 歪みに色を付ける
/// </summary>
float4 DistortionColor(float2 _center, float _radius, float _width, float2 _tex,Texture2D _texture)
{
	// 穴の歪み
	float distortion = Distortion(_center, _radius, _width, _tex);

	// 歪んだ画像のUV座標
	float2 uv = lerp(_tex, _center, distortion);

	// サンプリング画像(歪んだ画像 (穴無し))
	float4 base = _texture.Sample(samLinear, uv);

	// 空けた穴の色情報(穴を開けたところを補完して埋める)
	float4 L1 = lerp(base, float4(1, 0, 0, 1), step(1, distortion));

	return L1;
}
// ------------------------------------------------------------------------------------------------

/// <summary>
/// _a に大きい値 _b に小さい値を入れる
/// </summary>
float2 Mod(float2 _a, float2 _b)
{
	return _a - floor(_a / _b) * _b;

}
/// <summary>
/// ディゾルブ(input.Tex)
/// </summary>
float Dissolve(float2 _tex)
{
	float rand = PerlinNoise(_tex * 10);

	if (rand < diffuse.x)
	{
		return 0;
	}
	return 1;
}
/// <summary>
/// ブラー処理(input.Tex)
/// </summary>
float4 Blur(float2 _tex,Texture2D _texture)
{
	float2 noise = float2(0.005f, 0.005f);			// float2 noise = 0.005f でもできる

													// ブラー (気絶直前のボヤケ)
	float4 base = _texture.Sample(samLinear, _tex + float2(noise.x, noise.y))
		+ _texture.Sample(samLinear, _tex + float2(noise.x, 0))
		+ _texture.Sample(samLinear, _tex + float2(noise.x, -noise.y))
		+ _texture.Sample(samLinear, _tex + float2(0, noise.y))
		+ _texture.Sample(samLinear, _tex + float2(0, 0))
		+ _texture.Sample(samLinear, _tex + float2(0, -noise.y))
		+ _texture.Sample(samLinear, _tex + float2(-noise.x, noise.y))
		+ _texture.Sample(samLinear, _tex + float2(-noise.x, 0))
		+ _texture.Sample(samLinear, _tex + float2(-noise.x, -noise.y));

	// ベースの明るさを元に戻す
	base /= 9;

	return base;
}

// ポータル ---------------------------------------------------------------------------------------
/// <summary>
/// ポータル(input.Tex)
/// </summary>
float4 Portal(float2 _center, float _radius, float _width, float2 _tex,Texture2D _texture, Texture2D _texture2)
{
	// 歪みを出す
	float distortion = Distortion(_center, _radius, _width, _tex);

	// テクスチャに中央からの差にゆがみをかけたものを足す
	float2 uv = _tex + (_center - _tex) * distortion;

	float4 base = _texture.Sample(samLinear, uv);
	float4 gate = _texture2.Sample(samLinear, _tex);

	float4 L1 = lerp(base, gate, step(1, distortion));

	return L1;
}
/// <summary>
/// ポータル(input.Tex, 揺らぎなどがあるTex)
/// </summary>
float4 ShakenPortal(float2 _center, float _radius, float _width, float2 _tex, Texture2D _texture, Texture2D _texture2)
{
	// 歪みを出す
	float distortion = Distortion(_center, _radius, _width, _tex);

	// テクスチャに中央からの差にゆがみをかけたものを足す
	float2 uv = _tex + (_center - _tex) * distortion;


	float2 gateUV = _tex;
	float noize = PerlinNoise(gateUV * 20);

	gateUV.x += (noize - 0.5f) * 0.1f * frac(diffuse.x);
	gateUV.y += (noize - 0.5f) * 0.1f * frac(diffuse.x);


	float4 base = _texture.Sample(samLinear, uv);
	float4 gate = _texture2.Sample(samLinear, gateUV);

	float4 L1 = lerp(base, gate, step(1, distortion));

	return L1;
}
// ------------------------------------------------------------------------------------------------

/// <summary>
/// テレビの枠を作る
/// </summary>
float4 Braunkan(float2 _uv, Texture2D _texture)
{
	float2 uv = _uv;

	// 長さを求めている(distans(float2(0,0),uv)と同じ)
	float vignet = length(uv);

	uv /= 1 - vignet * 0.2f;

	// ずらした中心点を戻す
	float2 texUV = uv + float2 (0.5f, 0.5f);

	// abs() ← アブソリュート、絶対値をとる
	//if (texUV.x > 1 || texUV.x < 0 || texUV.y>1 || texUV.y < 0) と同じ
	if (max(abs(uv.y) - 0.5f, abs(uv.x) - 0.5f) > 0)
	{
		// 此処をいじるとフレームを変更できる
		return float4(0, 0, 0, 1);
	}

	float4 base = _texture.Sample(samLinear, texUV);
	base.a = 0;
	return base;
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float2 i = input.Tex;
	float4 base = float4(0, 0, 0, 0);
	

	// タイトルシーン
	if (effectType.x == 0.0)
	{
		// 背景
		base = tex1.Sample(samLinear, i);

		// タイトル表示
		float4 title = tex2.Sample(samLinear, i);
		// 透明非表示
		if (title.a != 0)
		{
			base = title;
			base.r = (float)half3(1, effectType.z, 0);
			base.g = (float)half3(effectType.z, 0, 1);
			base.b = (float)half3(0, 1, effectType.z);
		}
		// Push to Enter
		float4 push = tex3.Sample(samLinear, i);
		// 透明非表示
		if (push.a != 0) { base = push; }
	}
	// ログインシーン
	else if (effectType.x == 1.0) 
	{
		// 黒くする
		base = float4(0, 0, 0, 1);
	}
	// ロビーシーン
	else if (effectType.x == 2.0) 
	{

	}
	// プレイシーン
	else if (effectType.x == 3.0) 
	{
		float4 noise;
		// 移動距離分ずらす
		i += diffuse.xy;
		// 背景
		base = tex1.Sample(samLinear, i);
		float2 tex = i;
		float2 buf = tex*(times.x * 1000.0f);

		tex.x = ToneNoise(buf);
		noise = tex1.Sample(samLinear, tex);
		// ずらしたものを戻す
		i -= diffuse.xy;

		if (i.x <= colors.x) { base.rg = 0.7f; }
		else if (i.x >= colors.y) { base.rg = 0.7f; }
		if (i.y <= colors.z) { base.rg = 0.7f; }
		else if (i.y >= colors.w) { base.rg = 0.7f; }

		if (times.x > 0)
		{
			noise.r = times.x;
			base += noise;
		}

	}
	// リザルトシーン
	else if (effectType.x == 4.0) 
	{
		base = tex1.Sample(samLinear, i);
		float4 push = tex2.Sample(samLinear, i);
		// 透明非表示
		if (push.a != 0) { base = push; }
	}

	return base;


	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}