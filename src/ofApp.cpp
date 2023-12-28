#include "ofApp.h"

void ofApp::draw() {
	if (!start_game) {
		// 게임 시작 전에 "Click to start game" 텍스트를 화면 가운데에 출력
		// start_game 변수가 false일 때 실행
		ofSetColor(0, visible_t);
		string startGameText = "Click to start game";
		float S_T_W = letters.stringWidth(startGameText);
		float S_T_H = letters.stringHeight(startGameText);
		float S_T_W_1 = (ofGetWidth() - S_T_W) / 2;
		float S_T_H_1 = (ofGetHeight() - S_T_H) / 2;
		letters.drawString(startGameText, S_T_W_1, S_T_H_1);
		return;
	}

	// 게임이 시작되면 게임 보드와 게임 플레이어 표시를 그림

	// 게임 보드 
	ofSetColor(0);
	ofSetLineWidth(2);
	float frame_unit_size = ofGetWidth() / 3.0;
	for (int i = 1; i < 3; i++) {
		// 수직 선 
		ofDrawLine(i * frame_unit_size, 0, i * frame_unit_size, ofGetHeight());
		// 수평 선 
		ofDrawLine(0, i * frame_unit_size, ofGetWidth(), i * frame_unit_size);
	}

	ofSetLineWidth(4);
	for (const auto& cell : UNIT_MANY) {
		// 게임 보드의 각 셀에 X 또는 O
		if (cell.twos == UNIT_FRAMES_NOW::X) {
			// X 그리기
			ofSetColor(255, 0, 0);  // 빨간색
			ofDrawLine(cell.ones.getTopLeft(), cell.ones.getBottomRight());
			ofDrawLine(cell.ones.getTopRight(), cell.ones.getBottomLeft());
		}
		else if (cell.twos == UNIT_FRAMES_NOW::O) {
			// O 그리기
			ofSetColor(135, 206, 250);  // 하늘색
			ofNoFill();
			ofSetLineWidth(6);
			ofDrawEllipse(cell.ones.getCenter(), cell.ones.getWidth() * 0.8, cell.ones.getHeight() * 0.8);
		}
	}

	if (finish_game) {
		// 게임이 종료되었을 때 승자 또는 무승부 메시지를 표시

		// 배경 사각형 그리기
		ofSetColor(200, 200, 200, 200);
		ofDrawRectangle(bg_texts);

		// 메시지 출력
		ofSetColor(0);
		string message = "";
		if (player_win.empty()) {
			// 무승부일 경우
			message = "It's a tie!";
		}
		else {
			if (player_win == "X") {
				// 플레이어 1(X) 승리
				message = "Player 1 wins!";
			}
			else if (player_win == "O") {
				// 플레이어 2(O) 승리
				message = "Player 2 wins!";
			}
		}
		float messageWidth = letters.stringWidth(message);
		float messageHeight = letters.stringHeight(message);
		float x = (ofGetWidth() - messageWidth) / 2 - 20;
		float y = (ofGetHeight() - messageHeight) / 2;
		// 메시지를 감싸는 사각형 
		ofSetColor(255);
		ofDrawRectangle(x - 10, y - 10, messageWidth + 20, messageHeight + 20);
		ofSetColor(0);
		// 메시지 출력
		letters.drawString(message, x, y);
		letters.drawString("Click to play again", x, y + 30);
	}
	else {
		// 게임이 종료되지 않았을 때 현재 플레이어 턴을 표시

		ofSetColor(255);
		string turnText = (x_time) ? "Player 1 Turn" : "Player 2 Turn";
		float turnTextWidth = letters.stringWidth(turnText);
		float turnTextHeight = letters.stringHeight(turnText);
		float turnTextX = (ofGetWidth() - turnTextWidth) / 2;
		float turnTextY = (ofGetHeight() + turnTextHeight) / 2 + 30;
		// 현재 플레이어 턴을 출력
		ofSetColor(0, (x_time) ? 128 : 128, 0);
		letters.drawString(turnText, turnTextX, turnTextY);
	}
}

void ofApp::setup() {
	// 애플리케이션 초기화 설정

	ofSetBackgroundColor(255);
	ofSetWindowTitle("Tic-Tac-Toe");
	ofSetWindowShape(500, 500);

	// 게임 보드의 각 셀을 생성
	float theone = ofGetWidth() / 3.0;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			frames unit;
			unit.ones = ofRectangle(col * theone, row * theone, theone, theone);
			unit.twos = UNIT_FRAMES_NOW::Empty;
			UNIT_MANY.push_back(unit);
		}
	}

	Generate_back();

	letters.load(OF_TTF_SANS, 20);
	visible_t = 255;
}

void ofApp::find_winner() {
	// 승자를 찾는 함수
	if (searching_frames(0, 1, 2) || searching_frames(3, 4, 5) || searching_frames(6, 7, 8) ||
		searching_frames(0, 3, 6) || searching_frames(1, 4, 7) || searching_frames(2, 5, 8) ||
		searching_frames(0, 4, 8) || searching_frames(2, 4, 6)) {
		// 가로, 세로, 대각선 방향에 같은 플레이어의 표시가 있는 경우 승자로 결정
		finish_game = true;
		player_win = (x_time) ? "O" : "X";
		bg_texts = ofRectangle(0, ofGetHeight() * 0.4, ofGetWidth(), ofGetHeight() * 0.2);
	}
	else {
		bool isTie = true;
		for (const auto& cell : UNIT_MANY) {
			// 무승부인지 확인
			if (cell.twos == UNIT_FRAMES_NOW::Empty) {
				isTie = false;
				break;
			}
		}
		if (isTie) {
			// 모든 셀이 플레이어의 표시로 채워졌을 때 무승부로 결정
			finish_game = true;
			bg_texts = ofRectangle(0, ofGetHeight() * 0.4, ofGetWidth(), ofGetHeight() * 0.2);
		}
	}
}

void ofApp::update() {
	if (start_game && finish_game) {
		// 게임 시작 후 게임이 종료되었을 때 시작 게임 텍스트를 서서히 사라지게 fadeout
		visible_t -= 3;
		if (visible_t < 0) {
			visible_t = 0;
		}
	}
}

void ofApp::Generate_back() {
	// 게임 초기화 함수
	for (auto& cell : UNIT_MANY) {
		cell.twos = UNIT_FRAMES_NOW::Empty;
	}
	x_time = true;
	finish_game = false;
	player_win = "";
	visible_t = 255;
}

void ofApp::mousePressed(int x, int y, int button) {
	if (!start_game) {
		// 게임 시작 전에 마우스 클릭으로 게임 시작
		start_game = true;
		return;
	}

	if (finish_game) {
		// 게임이 종료되었을 때 마우스 클릭으로 게임 초기화
		Generate_back();
		return;
	}

	if (button == OF_MOUSE_BUTTON_LEFT) {
		for (auto& UNITS : UNIT_MANY) {
			if (UNITS.ones.inside(x, y) && UNITS.twos == UNIT_FRAMES_NOW::Empty) {
				// 클릭한 위치에 플레이어의 표시(X 또는 O)
				UNITS.twos = (x_time) ? UNIT_FRAMES_NOW::X : UNIT_FRAMES_NOW::O;
				x_time = !x_time;

				find_winner();
				break;
			}
		}
	}
}

bool ofApp::searching_frames(int a, int b, int c) {
	// 주어진 인덱스의 셀들이 모두 같은 플레이어의 표시인지 확인
	if (UNIT_MANY[a].twos != UNIT_FRAMES_NOW::Empty &&
		UNIT_MANY[a].twos == UNIT_MANY[b].twos &&
		UNIT_MANY[a].twos == UNIT_MANY[c].twos) {
		return true;  // 같은 플레이어의 표시가 있을 경우 true 반환
	}
	return false;  // 같은 플레이어의 표시가 없을 경우 false 반환
}
