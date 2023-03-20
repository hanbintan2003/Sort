#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int NUM_BARS = 100;
const int FRAMERATE = 60;
const int SORTING_SPEED_DIVISOR = 4;

int partition(std::vector<int>& bars, int low, int high) {
    int pivot = bars[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (bars[j] < pivot) {
            i++;
            std::swap(bars[i], bars[j]);
        }
    }
    std::swap(bars[i + 1], bars[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& bars, int low, int high) {
    std::stack<int> stack;
    stack.push(low);
    stack.push(high);

    while (!stack.empty()) {
        high = stack.top(); stack.pop();
        low = stack.top(); stack.pop();

        int p = partition(bars, low, high);

        if (p - 1 > low) {
            stack.push(low);
            stack.push(p - 1);
        }

        if (p + 1 < high) {
            stack.push(p + 1);
            stack.push(high);
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Quick Sort Visualization");
    window.setFramerateLimit(FRAMERATE);

    std::vector<int> bars;
    bars.reserve(NUM_BARS);
    for (int i = 0; i < NUM_BARS; ++i) {
        bars.push_back(rand() % WINDOW_HEIGHT);
    }

    sf::RectangleShape bar;
    bar.setSize(sf::Vector2f(WINDOW_WIDTH / NUM_BARS, 0));
    bar.setOrigin(bar.getSize().x / 2, 0);
    bar.setFillColor(sf::Color(255, 245, 238));

    bool is_paused = true;
    bool is_reset = true;
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
        }

        // Quick Sort
        if (!is_paused && frame_counter % SORTING_SPEED_DIVISOR == 0) {
            quickSort(bars, 0, NUM_BARS - 1);
            is_paused = true;
        }

        // Draw bars
        for (int i = 0; i < NUM_BARS; ++i) {
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