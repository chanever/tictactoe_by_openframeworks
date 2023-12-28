#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

	enum class UNIT_FRAMES_NOW {
		Empty,  // ���� ����ִ� ����
		X,      // X �÷��̾��� ǥ��
		O       // O �÷��̾��� ǥ��
	};

	struct frames {
		UNIT_FRAMES_NOW twos;    // ���� ���� ���� (�������, X ǥ��, O ǥ��)
		ofRectangle ones;        // ���� ��ġ�� ũ�⸦ ��Ÿ���� �簢��
	};

public:
	void setup();
	void update();
	
	void Generate_back();        // ���� �ʱ�ȭ �Լ�
	void find_winner();          // ���� Ȯ�� �Լ�
	void draw();
	void mousePressed(int x, int y, int button);

	bool searching_frames(int a, int b, int c);  // ���� �÷��̾��� ǥ�ð� �ִ��� Ȯ���ϴ� �Լ�
	vector<frames> UNIT_MANY;    // ��� ���� ������ �����ϴ� ����
	bool x_time;                 // ���� �÷��̾��� ���� ����


	float visible_t;             // ���� ���� �ؽ�Ʈ�� ����
	bool finish_game;            // ���� ���� ����
	bool start_game;             // ���� ���� ����
	string player_win;           // �¸��� �÷��̾�
	ofTrueTypeFont letters;      // �ؽ�Ʈ ��¿� ���Ǵ� ��Ʈ
	ofRectangle bg_texts;        // ��� �ؽ�Ʈ�� ���δ� �簢��
};
