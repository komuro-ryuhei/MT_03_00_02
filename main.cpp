#include <Novice.h>
#include "Vector3.h"
#include "Matrix4x4.h"

const char kWindowTitle[] = "LC1B_13_コムロ_リュウヘイ";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, Matrix4x4 matrix) {
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}

// 加算
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;
}

// 減算
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
}

// 積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

// 逆行列
Matrix4x4 Inverse4x4(Matrix4x4& matrix) {
	Matrix4x4 result = {};

	float a = matrix.m[0][0];
	float b = matrix.m[0][1];
	float c = matrix.m[0][2];
	float d = matrix.m[0][3];
	float e = matrix.m[1][0];
	float f = matrix.m[1][1];
	float g = matrix.m[1][2];
	float h = matrix.m[1][3];
	float i = matrix.m[2][0];
	float j = matrix.m[2][1];
	float k = matrix.m[2][2];
	float l = matrix.m[2][3];
	float m = matrix.m[3][0];
	float n = matrix.m[3][1];
	float o = matrix.m[3][2];
	float p = matrix.m[3][3];

	float det = a * (f * (k * p - l * o) - g * (j * p - l * n) + h * (j * o - k * n)) -
		b * (e * (k * p - l * o) - g * (i * p - l * m) + h * (i * o - k * m)) +
		c * (e * (j * p - l * n) - f * (i * p - l * m) + h * (i * n - j * m)) -
		d * (e * (j * o - k * n) - f * (i * o - k * m) + g * (i * n - j * m));

	if (det == 0.0f) {
		return result;
	}

	float invDet = 1.0f / det;

	result.m[0][0] = invDet * (matrix.m[1][1] * (matrix.m[2][2] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][2]) -
		matrix.m[1][2] * (matrix.m[2][1] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][1]) +
		matrix.m[1][3] * (matrix.m[2][1] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][1]));

	result.m[0][1] = invDet * (-(matrix.m[0][1] * (matrix.m[2][2] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][2]) -
		matrix.m[0][2] * (matrix.m[2][1] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][1]) +
		matrix.m[0][3] * (matrix.m[2][1] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][1])));

	result.m[0][2] = invDet * (matrix.m[0][1] * (matrix.m[1][2] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][2]) -
		matrix.m[0][2] * (matrix.m[1][1] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][1]) +
		matrix.m[0][3] * (matrix.m[1][1] * matrix.m[3][2] - matrix.m[1][2] * matrix.m[3][1]));

	result.m[0][3] = invDet * (-(matrix.m[0][1] * (matrix.m[1][2] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][2]) -
		matrix.m[0][2] * (matrix.m[1][1] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][1]) +
		matrix.m[0][3] * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1])));

	result.m[1][0] = invDet * (-(matrix.m[1][0] * (matrix.m[2][2] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][2]) -
		matrix.m[1][2] * (matrix.m[2][0] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][0]) +
		matrix.m[1][3] * (matrix.m[2][0] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][0])));

	result.m[1][1] = invDet * (matrix.m[0][0] * (matrix.m[2][2] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][2]) -
		matrix.m[0][2] * (matrix.m[2][0] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][0]) +
		matrix.m[0][3] * (matrix.m[2][0] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][0]));

	result.m[1][2] = invDet * (-(matrix.m[0][0] * (matrix.m[1][2] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][2]) -
		matrix.m[0][2] * (matrix.m[1][0] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][0]) +
		matrix.m[0][3] * (matrix.m[1][0] * matrix.m[3][2] - matrix.m[1][2] * matrix.m[3][0])));

	result.m[1][3] = invDet * (matrix.m[0][0] * (matrix.m[1][2] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][2]) -
		matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][0]) +
		matrix.m[0][3] * (matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]));

	result.m[2][0] = invDet * (matrix.m[1][0] * (matrix.m[2][1] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][1]) -
		matrix.m[1][1] * (matrix.m[2][0] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][0]) +
		matrix.m[1][3] * (matrix.m[2][0] * matrix.m[3][1] - matrix.m[2][1] * matrix.m[3][0]));

	result.m[2][1] = invDet * (-(matrix.m[0][0] * (matrix.m[2][1] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][1]) -
		matrix.m[0][1] * (matrix.m[2][0] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][0]) +
		matrix.m[0][3] * (matrix.m[2][0] * matrix.m[3][1] - matrix.m[2][1] * matrix.m[3][0])));

	result.m[2][2] = invDet * (matrix.m[0][0] * (matrix.m[1][1] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][1]) -
		matrix.m[0][1] * (matrix.m[1][0] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][0]) +
		matrix.m[0][3] * (matrix.m[1][0] * matrix.m[3][1] - matrix.m[1][1] * matrix.m[3][0]));

	result.m[2][3] = invDet * (-(matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][1]) -
		matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][0]) +
		matrix.m[0][3] * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0])));

	result.m[3][0] = invDet * (-(matrix.m[1][0] * (matrix.m[2][1] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][1]) -
		matrix.m[1][1] * (matrix.m[2][0] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][0]) +
		matrix.m[1][2] * (matrix.m[2][0] * matrix.m[3][1] - matrix.m[2][1] * matrix.m[3][0])));

	result.m[3][1] = invDet * (matrix.m[0][0] * (matrix.m[2][1] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][1]) -
		matrix.m[0][1] * (matrix.m[2][0] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][0]) +
		matrix.m[0][2] * (matrix.m[2][0] * matrix.m[3][1] - matrix.m[2][1] * matrix.m[3][0]));

	result.m[3][2] = invDet * (-(matrix.m[0][0] * (matrix.m[1][1] * matrix.m[3][2] - matrix.m[1][2] * matrix.m[3][1]) -
		matrix.m[0][1] * (matrix.m[1][0] * matrix.m[3][2] - matrix.m[1][2] * matrix.m[3][0]) +
		matrix.m[0][2] * (matrix.m[1][0] * matrix.m[3][1] - matrix.m[1][1] * matrix.m[3][0])));

	result.m[3][3] = invDet * (matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) -
		matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) +
		matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]));

	return result;
}

// 転置行列
Matrix4x4 Transpose4x4(Matrix4x4& matrix) {
	Matrix4x4 result;

	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			result.m[row][column] = matrix.m[column][row];
		}
	}
	return result;
}

// 単位行列の作成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 identity;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			identity.m[i][j] = (i == j) ? 1.0f : 0.0f;
		}
	}
	return identity;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Matrix4x4 m1 = {
			3.2f,0.7f,9.6f,4.4f,
			5.5f,1.3f,7.8f,2.1f,
			6.9f,8.0f,2.6f,1.0f,
			0.5f,7.2f,5.1f,3.3f
	};

	Matrix4x4 m2 = {
		4.1f,6.5f,3.3f,2.2f,
		8.8f,0.6f,9.9f,7.7f,
		1.1f,5.5f,6.6f,0.0f,
		3.3f,9.9f,8.8f,2.2f
	};

	Matrix4x4 resultAdd = Add(m1, m2);
	Matrix4x4 resultSubtract = Subtract(m1, m2);
	Matrix4x4 resultMultiply = Multiply(m1, m2);
	Matrix4x4 inverseM1 = Inverse4x4(m1);
	Matrix4x4 inverseM2 = Inverse4x4(m2);
	Matrix4x4 transposeM1 = Transpose4x4(m1);
	Matrix4x4 transposeM2 = Transpose4x4(m2);
	Matrix4x4 identity = MakeIdentity4x4();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, resultAdd);
		MatrixScreenPrintf(0, kRowHeight * 5, resultSubtract);
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultMultiply);
		MatrixScreenPrintf(0, kRowHeight * 5 * 3, inverseM1);
		MatrixScreenPrintf(0, kRowHeight * 5 * 4, inverseM2);
		MatrixScreenPrintf(kColumnWidth * 5, 0, transposeM1);
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5, transposeM2);
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, identity);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
