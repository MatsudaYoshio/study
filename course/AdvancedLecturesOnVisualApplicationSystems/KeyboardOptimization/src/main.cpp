#include "ofMain.h"
#include "AppParameters.h"
#include "KeyboardOptimizationApp.h"

using namespace param;

int main( ){
	ofSetupOpenGL(W, H, OF_WINDOW);

	ofRunApp(new KeyboardOptimizationApp());

	return 0;
}
