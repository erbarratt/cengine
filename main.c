#include "src/core/window.h"
#include "src/renderer/renderer.h"

int main() {

	if (window_init(800, 600, "GameEngine") != 0) {
		return -1;
	}

	renderer_init();

	while (!window_should_close()) {
		renderer_clear();

		// Update systems
		// Render scene
		renderer_draw();

		window_poll();
	}

	return 0;

}