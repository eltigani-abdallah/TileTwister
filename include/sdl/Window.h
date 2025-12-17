#ifndef TILETWISTER_WINDOW_H
#define TILETWISTER_WINDOW_H
#include <string>

class Window {

public:

    //initialize window class
    Window(std::string title);

    //open window
    void open();

    //close window
    void close();






private:

    const int WIDTH;
    const int HEIGHT;


};


#endif //TILETWISTER_WINDOW_H