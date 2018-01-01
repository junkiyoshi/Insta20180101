#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(30);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	this->cap.open("D:\\video\\dance2.mp4");

	this->blend_image.allocate(this->cap.get(CV_CAP_PROP_FRAME_WIDTH) * 0.5, this->cap.get(CV_CAP_PROP_FRAME_HEIGHT) * 0.5, OF_IMAGE_COLOR);
	this->blend_frame = cv::Mat(this->blend_image.getHeight(), this->blend_image.getWidth(), CV_MAKETYPE(CV_8UC3, this->blend_image.getPixels().getNumChannels()), this->blend_image.getPixels().getData(), 0);

	this->save_index = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
	this->cap >> this->cap_frame;
	if (this->cap_frame.empty()) { return; }

	cv::resize(this->cap_frame, this->cap_frame, cv::Size(), 0.5, 0.5);

	if (ofGetFrameNum() % 2 == 0) {
		this->cap_frame.copyTo(this->save_farme[this->save_index % 2]);
		this->save_index++;
	}
	
	if (ofGetFrameNum() > 6) {
		for (int x = 0; x < this->blend_frame.cols; x++) {
			for (int y = 0; y < this->blend_frame.rows; y++) {
				this->blend_frame.at<cv::Vec3b>(y, x) = cv::Vec3b(this->cap_frame.at<cv::Vec3b>(y, x)[0], this->save_farme[0].at<cv::Vec3b>(y, x)[1], this->save_farme[1].at<cv::Vec3b>(y, x)[2]);
			}
		}

		cv::imshow("blend", blend_frame);
		cv::waitKey(1);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	/*
	
	// ofImage‚ª‚È‚º‚©Â‚Ý‚ª‚©‚Á‚½Š´‚¶‚É‚È‚Á‚Ä‚µ‚Ü‚¤‚Ì‚ÅA’f”O

	this->cam.begin();

	this->blend_image.update();
	this->blend_image.draw(-this->blend_image.getWidth() / 2, -this->blend_image.getHeight() / 2);

	this->cam.end();

	*/
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}