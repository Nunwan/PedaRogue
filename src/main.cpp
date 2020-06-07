#include "Window.h"

int main() {
        Window rootWindow = Window();
        while (!TCOD_console_is_window_closed()) {
            rootWindow.nextEvent(TCOD_EVENT_KEY, true);
            if (rootWindow.event.eventtype == TCOD_EVENT_KEY_PRESS && rootWindow.event.key.vk == TCODK_ESCAPE)
            {
                return EXIT_SUCCESS;
            }
        }


}
