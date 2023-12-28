#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

	enum class UNIT_FRAMES_NOW {
		Empty,  // 셀이 비어있는 상태
		X,      // X 플레이어의 표시
		O       // O 플레이어의 표시
	};

	struct frames {
		UNIT_FRAMES_NOW twos;    // 셀의 현재 상태 (비어있음, X 표시, O 표시)
		ofRectangle ones;        // 셀의 위치와 크기를 나타내는 사각형
	};

public:
	void setup();
	void update();
	
	void Generate_back();        // 게임 초기화 함수
	void find_winner();          // 승자 확인 함수
	void draw();
	void mousePressed(int x, int y, int button);

	bool searching_frames(int a, int b, int c);  // 같은 플레이어의 표시가 있는지 확인하는 함수
	vector<frames> UNIT_MANY;    // 모든 셀의 정보를 저장하는 벡터
	bool x_time;                 // 현재 플레이어의 차례 여부


	float visible_t;             // 게임 시작 텍스트의 투명도
	bool finish_game;            // 게임 종료 여부
	bool start_game;             // 게임 시작 여부
	string player_win;           // 승리한 플레이어
	ofTrueTypeFont letters;      // 텍스트 출력에 사용되는 폰트
	ofRectangle bg_texts;        // 배경 텍스트를 감싸는 사각형
};
