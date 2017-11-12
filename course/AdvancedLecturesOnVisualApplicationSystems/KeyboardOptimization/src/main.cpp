#include "ofMain.h"
#include "AppParameters.h"
#include "KeyboardApp.h"
#include "OptimizationApp.h"

using namespace param;

int main(){
	//ofSetupOpenGL(W, H, OF_WINDOW);
	//ofRunApp(new KeyboardApp());

	ofGLFWWindowSettings settings;

	settings.width = W;
	settings.height = H;
	settings.setPosition(ofVec2f(100, 100));
	shared_ptr<ofAppBaseWindow> KeyboardWindow = ofCreateWindow(settings);

	settings.width = W/2;
	settings.height = H/2;
	settings.setPosition(ofVec2f(1200, 200));
	settings.resizable = false;
	settings.shareContextWith = KeyboardWindow;
	shared_ptr<ofAppBaseWindow> OptimizationWindow = ofCreateWindow(settings);

	shared_ptr<KeyboardApp> KeyboardApp(new KeyboardApp);
	shared_ptr<OptimizationApp> OptimizationApp(new OptimizationApp);
	KeyboardApp->opt = OptimizationApp;

	ofRunApp(OptimizationWindow, OptimizationApp);
	ofRunApp(KeyboardWindow, KeyboardApp);
	ofRunMainLoop();

	return 0;
}
