#include "PlotApp.h"

void PlotApp::setup() {
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(22, 22, 22, 255);

	this->plot.reset(new ofxHistoryPlot(NULL, "Evaluation value", 15, false));
	this->plot->setRangeAuto();
	this->plot->addHorizontalGuide(ofGetHeight()/2, ofColor::red);
	this->plot->setColor(ofColor::green);
	this->plot->setShowNumericalInfo(true);
	this->plot->setRespectBorders(true);
	this->plot->setLineWidth(1);
	this->plot->setBackgroundColor(ofColor(0, 220));
	this->plot->setDrawGrid(true);
	this->plot->setGridColor(ofColor(30));
	this->plot->setGridUnit(40);
	this->plot->setCropToRect(true);
}

void PlotApp::update() {}

void PlotApp::draw() {
	this->plot->draw(10, 10, 640, 240);
}