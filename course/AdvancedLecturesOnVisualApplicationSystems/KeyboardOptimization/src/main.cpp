#include "ofMain.h"
#include "AppParameters.h"
#include "KeyboardApp.h"
#include "OptimizationApp.h"
#include "PlotApp.h"

using namespace param;

int main() {
	ofGLFWWindowSettings settings;

	settings.width = W;
	settings.height = H;
	settings.setPosition(ofVec2f(100, 100));
	shared_ptr<ofAppBaseWindow> KeyboardWindow = ofCreateWindow(settings);

	settings.width = W >> 1;
	settings.height = H >> 1;
	settings.setPosition(ofVec2f(1200, 200));
	settings.resizable = false;
	settings.shareContextWith = KeyboardWindow;
	shared_ptr<ofAppBaseWindow> OptimizationWindow = ofCreateWindow(settings);

	settings.setPosition(ofVec2f(1200, 600));
	settings.resizable = false;
	settings.shareContextWith = KeyboardWindow;
	shared_ptr<ofAppBaseWindow> PlotWindow = ofCreateWindow(settings);

	shared_ptr<KeyboardApp> KeyboardApp(new KeyboardApp);
	shared_ptr<OptimizationApp> OptimizationApp(new OptimizationApp);
	shared_ptr<PlotApp> PlotApp(new PlotApp);
	KeyboardApp->opt = OptimizationApp;
	KeyboardApp->plt = PlotApp;

	ofRunApp(PlotWindow, PlotApp);
	ofRunApp(OptimizationWindow, OptimizationApp);
	ofRunApp(KeyboardWindow, KeyboardApp);
	ofRunMainLoop();

	return 0;
}