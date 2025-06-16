#ifndef WINDOW_H
#define WINDOW_H

uint8_t window_init(int width, int height, const char* title);
void window_poll();
int window_should_close();

#endif //WINDOW_H
