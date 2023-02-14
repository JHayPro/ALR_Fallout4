#pragma once
#include "pch.h"
#include "PathData.h"
#include "cmd.cpp"

class ImageConvertParent {
public:

};

class AR {
public:
	short width = 0,
		height = 0;

	AR() {};

	AR(short _width, short _height) {
		short cd = gcd(_width, _height);
		width = _width / cd;
		height = _height / cd;
	}

	bool operator==(AR _ar) {
		return (this->width == _ar.width && this->height == _ar.height) ? true : false;
	}
};

class AR_MUL {
public:
	short res2kMul = 0,
		res4kMul = 0;

	AR_MUL() {};
	AR_MUL(AR _ar);
	AR_MUL(short _res2kMul, short _res4kMul) : res2kMul(_res2kMul), res4kMul(_res4kMul) {};
};

class RES {
public:
	short width = 0,
		height = 0;

	RES() {};
	RES(short _res) : width(_res), height(_res) {};
	RES(short _width, short _height) : width(_width), height(_height) {};
};

class OFF {
public:
	short width = 0,
		height = 0;

	OFF() {};
	OFF(short _width, short _height) : width(_width), height(_height) {};
};

class OFF_CON {
private:
	short offset2kMul = 1,
		offset4kMul = 2;

public:
	OFF off2k,
		off4k,
		offDef = OFF();

	OFF_CON() {};

	OFF_CON(short _width, short _height) {

		if (_width == 0 && _height == 0) {
			off2k = offDef;
			off4k = offDef;
		}
		else {
			off2k = OFF(_width * offset2kMul, _height * offset2kMul);
			off4k = OFF(_width * offset4kMul, _height * offset4kMul);
		}
	}

	OFF_CON(AR _ar);
};

class imageData {
private:
	OFF_CON offCon;

public:
	RES res;
	AR ar;
	AR_MUL arMul;
	OFF off;

	short resMul = 0;
	bool res4k = false;

	imageData() {};

	imageData(short _width, short _height) {
		res = RES(_width, _height);
		ar = AR(_width, _height);
		arMul = AR_MUL(ar);

		resMul = _width / ar.width;
		res4k = arMul.res4kMul == resMul;
		off = res4k ? OFF_CON(ar).off4k : OFF_CON(ar).off2k;
	};

	imageData(AR _ar, AR_MUL _arMul, short _resMul) : ar(_ar), arMul(_arMul) {

		resMul = (_resMul < _arMul.res4kMul) ? _arMul.res2kMul : _arMul.res4kMul;
		res = RES(ar.width * resMul, ar.height * resMul);
		res4k = arMul.res4kMul == resMul;
		off = res4k ? OFF_CON(ar).off4k : OFF_CON(ar).off2k;
	};

	imageData(AR _ar, bool _res4k) : ar(_ar), res4k(_res4k) {
		arMul = AR_MUL(_ar);
		resMul = res4k ? arMul.res4kMul : arMul.res2kMul;
		res = RES(ar.width * resMul, ar.height * resMul);
		off = OFF(0, 0);
	};

	imageData(AR_MUL _arMul, short _resMul, OFF _off, AR _ar) : off(_off), ar(_ar) {
		arMul = AR_MUL(ar);
		resMul = _resMul == _arMul.res4kMul ? arMul.res4kMul : arMul.res2kMul;
		res = RES(resMul * ar.width, resMul * ar.height);
		res4k = arMul.res4kMul == resMul;
	};
};

static array<tuple<AR, AR_MUL, OFF_CON>, 8> ARtupleArray = {
	tuple<AR, AR_MUL, OFF_CON>(AR(1, 1), AR_MUL(2048, 4096), OFF_CON(0, 0)),	//1:1 AR 2048x2048 2k Res, 4096x4096 4k Res 
	tuple<AR, AR_MUL, OFF_CON>(AR(2, 1), AR_MUL(1024, 2048), OFF_CON(0, 0)),	//2:1 AR 2048x1024 2k Res, 4096x2048 4k Res 

	tuple<AR, AR_MUL, OFF_CON>(AR(16, 9), AR_MUL(120, 240), OFF_CON(64, 484)),	//16:9 AR 1920 1080 2k Res, 3840 2160 4k Res 
	tuple<AR, AR_MUL, OFF_CON>(AR(8, 5), AR_MUL(240, 480), OFF_CON(64, 484)),	//16:10 AR 1920 1200 2k Res, 3840 2400 4k Res //Apparently 4K 16:10 monitors dont exist, probably will never be used

																				//~21:9 AR
	tuple<AR, AR_MUL, OFF_CON>(AR(7, 3), AR_MUL(180, 360), OFF_CON(64, 484)),	//21:9 AR 1260 540 2k Res, 2520 1080 4k Res //Not really a resolution used, Standard is 64:27
	tuple<AR, AR_MUL, OFF_CON>(AR(64, 27), AR_MUL(20, 40), OFF_CON(64, 484)),	//64:27 AR 1280 540 2k Res, 2560 1080 4k Res 
	tuple<AR, AR_MUL, OFF_CON>(AR(43, 18), AR_MUL(40, 80), OFF_CON(64, 484)),	//43:18 AR 1720 2048 2k Res, 3440 1440 4k Res 
	tuple<AR, AR_MUL, OFF_CON>(AR(12, 5), AR_MUL(160, 320), OFF_CON(64, 484))	//12:5 AR 1920 800 2k Res, 3840 1600 4k Res 
};

class ImageConvert : public ImageConvertParent {
private:

	PathDataParent* pathData = NULL;

	void convert(wstring _inputFilePath, wstring _outputFilePath),
		createOverlay(wstring _outputFilePath);

	imageData sizeImageData, maxOutputImageData, maxDisplayImageData;

	AR outputAR;

	short outImageMaxMul, sizeARMul;

public:

	ImageConvert(PathDataParent& _pathData);
	~ImageConvert();
};