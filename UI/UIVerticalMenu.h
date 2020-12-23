#ifndef UI_VERTICAL_MENU_H_
#define UI_VERTICAL_MENU_H_
#include <SFML/Graphics.hpp>

class UIVerticalMenu
{
public:
    UIVerticalMenu(sf::Vector2f position, int numOfText, std::vector<sf::Text> textArray, int numToDisplay, int numAboveSelected, int textSpacing, int textPosition = 0);
    ~UIVerticalMenu();
    void Update(float delta_time, float beat_time);
    void Draw(sf::RenderWindow& render_window) const;

    void ScrollUp();
    void ScrollDown();
    void SetDisplay(const bool display);

private:
    UIVerticalMenu* nextText_{nullptr};
    sf::Vector2f staticPosition_{0.0f, 0.0f};
    sf::Vector2f position_{0.0f, 0.0f};
    sf::Vector2f endPosition_{0.0f, 0.0f};
    sf::Text text_;
    int textPosition_{0};
    int numOfText_{0};
    int menuPosition_{0};
    int alpha_{255};
    int numToDisplay_{0};
    int numAboveSelected_{0};
    int textSpacing_{0};
    bool display_{true};
};

#endif