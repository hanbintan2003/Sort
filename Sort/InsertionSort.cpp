#include <SFML/Graphics.hpp>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int NUM_BARS = 100;
const int FRAMERATE = 60;
const int SORTING_SPEED_DIVISOR = 4;

int main(){
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Insertion Sort Visualization");
    window.setFramerateLimit(FRAMERATE);

    std::vector<int> bars;
    bars.reserve(NUM_BARS);
    for (int i = 0; i < NUM_BARS; ++i) {
        bars.push_back(rand() % WINDOW_HEIGHT);
    }

    sf::RectangleShape bar;
    bar.setSize(sf::Vector2f(WINDOW_WIDTH / NUM_BARS, 0));
    bar.setOrigin(bar.getSize().x / 2, 0);
    bar.setFillColor(sf::Color(255,245,238));

    bool is_paused = true;
    bool is_reset = true;
    int i = 0, j = 0;
    int frame_counter = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    is_paused = !is_paused;
                }
                if (event.key.code == sf::Keyboard::R) {
                    is_reset = true;
                    is_paused = true;
                }
            }
        }

        window.clear(sf::Color(0xAD, 0xD8, 0xE6));

        // Reset bars
        if (is_reset) {
            bars.clear();
            bars.reserve(NUM_BARS);
            for (int i = 0; i < NUM_BARS; ++i) {
                bars.push_back(rand() % WINDOW_HEIGHT);
            }
            is_reset = false;
            j = 1;
        }

        // Insertion Sort
        if (!is_paused && frame_counter % SORTING_SPEED_DIVISOR == 0) {
            if (j < NUM_BARS) {
                int key = bars[j];
                i = j - 1;

                while (i >= 0 && bars[i] > key) {
                    bars[i + 1] = bars[i];
                    i--;
                }

                bars[i + 1] = key;
                j++;
            }
        }

        // Draw bars
        for (i = 0; i < NUM_BARS; ++i) {
            bar.setPosition(sf::Vector2f((i + 0.5) * WINDOW_WIDTH / NUM_BARS, WINDOW_HEIGHT));
            bar.setSize(sf::Vector2f(WINDOW_WIDTH / NUM_BARS, -bars[i]));
            window.draw(bar);
        }

        window.display();

        // Update frame counter
        frame_counter++;
    }

    return 0;
}
