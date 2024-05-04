#pragma once

class Game {
public:
    Game();  // Constructor
    ~Game(); // Destructor
    
    void run();
    void init();
    void loop();
    void input();
    void update();
    void render();
    void clean();
    void keyboard_input();
    void mouse_input();

private:

};