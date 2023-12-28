#include "ofApp.h"

void ofApp::draw() {
	if (!start_game) {
		// ���� ���� ���� "Click to start game" �ؽ�Ʈ�� ȭ�� ����� ���
		// start_game ������ false�� �� ����
		ofSetColor(0, visible_t);
		string startGameText = "Click to start game";
		float S_T_W = letters.stringWidth(startGameText);
		float S_T_H = letters.stringHeight(startGameText);
		float S_T_W_1 = (ofGetWidth() - S_T_W) / 2;
		float S_T_H_1 = (ofGetHeight() - S_T_H) / 2;
		letters.drawString(startGameText, S_T_W_1, S_T_H_1);
		return;
	}

	// ������ ���۵Ǹ� ���� ����� ���� �÷��̾� ǥ�ø� �׸�

	// ���� ���� 
	ofSetColor(0);
	ofSetLineWidth(2);
	float frame_unit_size = ofGetWidth() / 3.0;
	for (int i = 1; i < 3; i++) {
		// ���� �� 
		ofDrawLine(i * frame_unit_size, 0, i * frame_unit_size, ofGetHeight());
		// ���� �� 
		ofDrawLine(0, i * frame_unit_size, ofGetWidth(), i * frame_unit_size);
	}

	ofSetLineWidth(4);
	for (const auto& cell : UNIT_MANY) {
		// ���� ������ �� ���� X �Ǵ� O
		if (cell.twos == UNIT_FRAMES_NOW::X) {
			// X �׸���
			ofSetColor(255, 0, 0);  // ������
			ofDrawLine(cell.ones.getTopLeft(), cell.ones.getBottomRight());
			ofDrawLine(cell.ones.getTopRight(), cell.ones.getBottomLeft());
		}
		else if (cell.twos == UNIT_FRAMES_NOW::O) {
			// O �׸���
			ofSetColor(135, 206, 250);  // �ϴû�
			ofNoFill();
			ofSetLineWidth(6);
			ofDrawEllipse(cell.ones.getCenter(), cell.ones.getWidth() * 0.8, cell.ones.getHeight() * 0.8);
		}
	}

	if (finish_game) {
		// ������ ����Ǿ��� �� ���� �Ǵ� ���º� �޽����� ǥ��

		// ��� �簢�� �׸���
		ofSetColor(200, 200, 200, 200);
		ofDrawRectangle(bg_texts);

		// �޽��� ���
		ofSetColor(0);
		string message = "";
		if (player_win.empty()) {
			// ���º��� ���
			message = "It's a tie!";
		}
		else {
			if (player_win == "X") {
				// �÷��̾� 1(X) �¸�
				message = "Player 1 wins!";
			}
			else if (player_win == "O") {
				// �÷��̾� 2(O) �¸�
				message = "Player 2 wins!";
			}
		}
		float messageWidth = letters.stringWidth(message);
		float messageHeight = letters.stringHeight(message);
		float x = (ofGetWidth() - messageWidth) / 2 - 20;
		float y = (ofGetHeight() - messageHeight) / 2;
		// �޽����� ���δ� �簢�� 
		ofSetColor(255);
		ofDrawRectangle(x - 10, y - 10, messageWidth + 20, messageHeight + 20);
		ofSetColor(0);
		// �޽��� ���
		letters.drawString(message, x, y);
		letters.drawString("Click to play again", x, y + 30);
	}
	else {
		// ������ ������� �ʾ��� �� ���� �÷��̾� ���� ǥ��

		ofSetColor(255);
		string turnText = (x_time) ? "Player 1 Turn" : "Player 2 Turn";
		float turnTextWidth = letters.stringWidth(turnText);
		float turnTextHeight = letters.stringHeight(turnText);
		float turnTextX = (ofGetWidth() - turnTextWidth) / 2;
		float turnTextY = (ofGetHeight() + turnTextHeight) / 2 + 30;
		// ���� �÷��̾� ���� ���
		ofSetColor(0, (x_time) ? 128 : 128, 0);
		letters.drawString(turnText, turnTextX, turnTextY);
	}
}

void ofApp::setup() {
	// ���ø����̼� �ʱ�ȭ ����

	ofSetBackgroundColor(255);
	ofSetWindowTitle("Tic-Tac-Toe");
	ofSetWindowShape(500, 500);

	// ���� ������ �� ���� ����
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
	// ���ڸ� ã�� �Լ�
	if (searching_frames(0, 1, 2) || searching_frames(3, 4, 5) || searching_frames(6, 7, 8) ||
		searching_frames(0, 3, 6) || searching_frames(1, 4, 7) || searching_frames(2, 5, 8) ||
		searching_frames(0, 4, 8) || searching_frames(2, 4, 6)) {
		// ����, ����, �밢�� ���⿡ ���� �÷��̾��� ǥ�ð� �ִ� ��� ���ڷ� ����
		finish_game = true;
		player_win = (x_time) ? "O" : "X";
		bg_texts = ofRectangle(0, ofGetHeight() * 0.4, ofGetWidth(), ofGetHeight() * 0.2);
	}
	else {
		bool isTie = true;
		for (const auto& cell : UNIT_MANY) {
			// ���º����� Ȯ��
			if (cell.twos == UNIT_FRAMES_NOW::Empty) {
				isTie = false;
				break;
			}
		}
		if (isTie) {
			// ��� ���� �÷��̾��� ǥ�÷� ä������ �� ���ºη� ����
			finish_game = true;
			bg_texts = ofRectangle(0, ofGetHeight() * 0.4, ofGetWidth(), ofGetHeight() * 0.2);
		}
	}
}

void ofApp::update() {
	if (start_game && finish_game) {
		// ���� ���� �� ������ ����Ǿ��� �� ���� ���� �ؽ�Ʈ�� ������ ������� fadeout
		visible_t -= 3;
		if (visible_t < 0) {
			visible_t = 0;
		}
	}
}

void ofApp::Generate_back() {
	// ���� �ʱ�ȭ �Լ�
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
		// ���� ���� ���� ���콺 Ŭ������ ���� ����
		start_game = true;
		return;
	}

	if (finish_game) {
		// ������ ����Ǿ��� �� ���콺 Ŭ������ ���� �ʱ�ȭ
		Generate_back();
		return;
	}

	if (button == OF_MOUSE_BUTTON_LEFT) {
		for (auto& UNITS : UNIT_MANY) {
			if (UNITS.ones.inside(x, y) && UNITS.twos == UNIT_FRAMES_NOW::Empty) {
				// Ŭ���� ��ġ�� �÷��̾��� ǥ��(X �Ǵ� O)
				UNITS.twos = (x_time) ? UNIT_FRAMES_NOW::X : UNIT_FRAMES_NOW::O;
				x_time = !x_time;

				find_winner();
				break;
			}
		}
	}
}

bool ofApp::searching_frames(int a, int b, int c) {
	// �־��� �ε����� ������ ��� ���� �÷��̾��� ǥ������ Ȯ��
	if (UNIT_MANY[a].twos != UNIT_FRAMES_NOW::Empty &&
		UNIT_MANY[a].twos == UNIT_MANY[b].twos &&
		UNIT_MANY[a].twos == UNIT_MANY[c].twos) {
		return true;  // ���� �÷��̾��� ǥ�ð� ���� ��� true ��ȯ
	}
	return false;  // ���� �÷��̾��� ǥ�ð� ���� ��� false ��ȯ
}
