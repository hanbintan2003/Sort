#include <SFML/Graphics.hpp>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int NUM_BARS = 100;
const int FRAMERATE = 60;
const int SORTING_SPEED_DIVISOR = 4;

void merge(std::vector<int> &bars, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = bars[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = bars[middle + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            bars[k] = L[i];
            i++;
        } else {
            bars[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        bars[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        bars[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int> &bars, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(bars, left, middle);
        mergeSort(bars, middle + 1, right);

        merge(bars, left, middle, right);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Merge Sort Visualization");
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
        }    // Merge Sort
        if (!is_paused && frame_counter % SORTING_SPEED_DIVISOR == 0) {
            mergeSort(bars, 0, NUM_BARS - 1);
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