#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <utility>

bool collides(const sf::CircleShape& circle, const sf::RectangleShape& rect) {
    // Get the circle's center and radius
    sf::Vector2f circleCenter = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
    float radius = circle.getRadius();

    // Get the rectangle's bounds
    sf::FloatRect rectBounds = rect.getGlobalBounds();

    // Find the closest point on the rectangle to the circle's center
    float closestX = std::max(rectBounds.left, std::min(circleCenter.x, rectBounds.left + rectBounds.width));
    float closestY = std::max(rectBounds.top, std::min(circleCenter.y, rectBounds.top + rectBounds.height));

    // Calculate the distance between the circle's center and this closest point
    float distanceX = circleCenter.x - closestX;
    float distanceY = circleCenter.y - closestY;

    // If the distance is less than the circle's radius, there's a collision
    return (distanceX * distanceX + distanceY * distanceY) < (radius * radius);
}

bool collisionOccurredBetween(float pacmanRadius, sf::Vector2f pacmanPosition, const sf::RectangleShape& rect) {
    sf::Vector2f pacmanCenter = pacmanPosition + sf::Vector2f(pacmanRadius, pacmanRadius);

    // Get the rectangle's bounds
    sf::FloatRect rectBounds = rect.getGlobalBounds();

    // Find the closest point on the rectangle to the circle's center
    float closestX = std::max(rectBounds.left, std::min(pacmanCenter.x, rectBounds.left + rectBounds.width));
    float closestY = std::max(rectBounds.top, std::min(pacmanCenter.y, rectBounds.top + rectBounds.height));

    // Calculate the distance between the circle's center and this closest point
    float distanceX = pacmanCenter.x - closestX;
    float distanceY = pacmanCenter.y - closestY;

    // If the distance is less than the circle's radius, there's a collision
    return (distanceX * distanceX + distanceY * distanceY) < (pacmanRadius * pacmanRadius);
}

void print(std::string message) {
    std::cout << message << std::endl;
}

std::string float_to_s(float to_convert) {
    return std::to_string(to_convert);
}

std::string level[36][28] = {
    { "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&" },
    { "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&" },
    { "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&" },
    { "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#" },
    { "#", "*", " ", " ", " ", " ", "*", " ", " ", " ", " ", " ", "*", "#", "#", "*", " ", " ", " ", " ", " ", "*", " ", " ", " ", " ", "*", "#" },
    { "#", " ", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", " ", "#" },
    { "#", " ", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", " ", "#" },
    { "#", " ", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", " ", "#" },
    { "#", "*", " ", " ", " ", " ", "*", " ", " ", "*", " ", " ", "*", " ", " ", "*", " ", " ", "*", " ", " ", "*", " ", " ", " ", " ", "*", "#" },
    { "#", " ", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", " ", "#" },
    { "#", " ", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", " ", "#" },
    { "#", "*", " ", " ", " ", " ", "*", "#", "#", "*", " ", " ", "*", "#", "#", "*", " ", " ", "*", "#", "#", "*", " ", " ", " ", " ", "*", "#" },
    { "#", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", "&", "#", "#", "&", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", "#" },
    { "&", "&", "&", "&", "&", "#", " ", "#", "#", "#", "#", "#", "&", "#", "#", "&", "#", "#", "#", "#", "#", " ", "#", "&", "&", "&", "&", "&" },
    { "&", "&", "&", "&", "&", "#", " ", "#", "#", "%", "&", "&", "%", "&", "&", "%", "&", "&", "%", "#", "#", " ", "#", "&", "&", "&", "&", "&" },
    { "&", "&", "&", "&", "&", "#", " ", "#", "#", "&", "#", "#", "#", "#", "#", "#", "#", "#", "&", "#", "#", " ", "#", "&", "&", "&", "&", "&" },
    { "#", "#", "#", "#", "#", "#", " ", "#", "#", "&", "#", " ", " ", " ", " ", " ", " ", "#", "&", "#", "#", " ", "#", "#", "#", "#", "#", "#" },
    { " ", " ", " ", " ", " ", " ", "*", " ", " ", "%", "#", " ", " ", " ", " ", " ", " ", "#", "&", "#", "#", "*", " ", " ", " ", " ", " ", " " },
    { "#", "#", "#", "#", "#", "#", " ", "#", "#", "&", "#", " ", " ", " ", " ", " ", " ", "#", "&", "#", "#", " ", "#", "#", "#", "#", "#", "#" },
    { "&", "&", "&", "&", "&", "#", " ", "#", "#", "&", "#", "#", "#", "#", "#", "#", "#", "#", "&", "#", "#", " ", "#", "&", "&", "&", "&", "&" },
    { "&", "&", "&", "&", "&", "#", " ", "#", "#", "%", "&", "&", "&", "&", "&", "&", "&", "&", "%", "#", "#", " ", "#", "&", "&", "&", "&", "&" },
    { "&", "&", "&", "&", "&", "#", " ", "#", "#", "&", "#", "#", "#", "#", "#", "#", "#", "#", "&", "#", "#", " ", "#", "&", "&", "&", "&", "&" },
    { "#", "#", "#", "#", "#", "#", " ", "#", "#", "&", "#", "#", "#", "#", "#", "#", "#", "#", "&", "#", "#", " ", "#", "#", "#", "#", "#", "#" },
    { "#", "*", " ", " ", " ", " ", "*", " ", " ", "*", " ", " ", "*", "#", "#", "*", " ", " ", "*", " ", " ", "*", " ", " ", " ", " ", "*", "#" },
    { "#", " ", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", " ", "#" },
    { "#", " ", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", " ", "#" },
    { "#", "*", " ", "*", "#", "#", "*", " ", " ", "*", " ", " ", "*", " ", "O", "*", " ", " ", "*", " ", " ", "*", "#", "#", "*", " ", "*", "#" },
    { "#", "#", "#", " ", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", " ", "#", "#", "#" },
    { "#", "#", "#", " ", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", " ", "#", "#", "#" },
    { "#", "*", " ", "*", " ", " ", "*", "#", "#", "*", " ", " ", "*", "#", "#", "*", " ", " ", "*", "#", "#", "*", " ", " ", "*", " ", "*", "#" },
    { "#", " ", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", " ", "#" },
    { "#", " ", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", " ", "#" },
    { "#", "*", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "*", " ", " ", "*", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "*", "#" },
    { "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#" },
    { "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&" },
    { "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&" },
};

std::pair<std::vector<sf::RectangleShape>, std::vector<sf::RectangleShape>> createWallsAndIntersectionsFor(std::string level[36][28]) {
    std::vector<sf::RectangleShape> walls;
    std::vector<sf::RectangleShape> intersections;

    for (int y = 0; y < 36; y++) {
        for (int x = 0; x < 28; x++) {
            if (level[y][x] == "#") {
                sf::RectangleShape wall(sf::Vector2f(32.0f, 32.0f));
                wall.setFillColor(sf::Color::Blue);
                wall.setPosition(32.0f * x, 32.0f * y);
                walls.push_back(wall);
            }
            else if (level[y][x] == "*" || level[y][x] == "%") {
                sf::RectangleShape intersection(sf::Vector2f(32.0f, 32.0f));
                intersection.setFillColor(sf::Color::Black);
                intersection.setPosition(32.0f * x, 32.0f * y);
                intersections.push_back(intersection);
            }
        }
    }

    return std::make_pair(walls, intersections);
}

std::pair<float, float> pacmanInitialPosition() {
    float x_pos;
    float y_pos;

    for (int y = 0; y < 36; y++) {
        for (int x = 0; x < 28; x++) {
            if (level[y][x] == "O") {
                x_pos = x * 32;
                y_pos = y * 32;
            }
        }
    }

    return std::make_pair(x_pos, y_pos);
}

sf::Vector2f getMiddlePoint(const sf::RectangleShape& rectangle) {
    // Get the position (top-left corner) and size of the rectangle
    sf::Vector2f position = rectangle.getPosition();
    sf::Vector2f size = rectangle.getSize();

    // Calculate the middle point
    sf::Vector2f middlePoint(position.x + size.x / 2.0f, position.y + size.y / 2.0f);

    return middlePoint;
}

enum moveDir {
    up, down, left, right, idle
};

float moveSpeed = 0.07f;

sf::Vector2f stopMoving() {
    return sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f moveLeft() {
    return sf::Vector2f(-moveSpeed, 0.0f);
}

sf::Vector2f moveRight() {
    return sf::Vector2f(moveSpeed, 0.0f);
}

sf::Vector2f moveUp() {
    return sf::Vector2f(0.0f, -moveSpeed);
}

sf::Vector2f moveDown() {
    return sf::Vector2f(0.0f, moveSpeed);
}

bool canMoveLeft = true;
bool canMoveRight = true;
bool canMoveUp = false;
bool canMoveDown = false;
bool pacmanHasMovedOnce = false;

void setMovableDirections(sf::RectangleShape intersection) {
    int gridX = intersection.getPosition().x / 32;
    int gridY = intersection.getPosition().y / 32;

    // Get the surrounding tiles
    // Tile Above
    std::string tileAbove = level[gridY - 1][gridX];
    if (tileAbove == "#") {
        canMoveUp = false;
    }
    else {
        canMoveUp = true;
    }

    // Tile Below
    std::string tileBelow = level[gridY + 1][gridX];
    if (tileBelow == "#") {
        canMoveDown = false;
    }
    else {
        canMoveDown = true;
    }

    // Tile Left
    std::string tileLeft = level[gridY][gridX - 1];
    if (tileLeft == "#") {
        canMoveLeft = false;
    }
    else {
        canMoveLeft = true;
    }

    // Tile Below
    std::string tileRight = level[gridY][gridX + 1];
    if (tileRight== "#") {
        canMoveRight = false;
    }
    else {
        canMoveRight = true;
    }
}

std::string directionToString(moveDir direction) {
    std::string directionString;
    if (direction == left) directionString = "left";
    if (direction == right) directionString = "right";
    if (direction == up) directionString = "up";
    if (direction == down) directionString = "down";
    return directionString;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pacman");
    float x_pos = window.getSize().x / 2;
    sf::View view(sf::FloatRect(0 - x_pos, 0, 1600, 1200));
    sf::CircleShape pacman(16.f);
    pacman.setFillColor(sf::Color::Yellow);
    std::pair<float, float> pacman_pos = pacmanInitialPosition();
    pacman.setPosition(pacman_pos.first - 16, pacman_pos.second);
    std::pair<std::vector<sf::RectangleShape>, std::vector<sf::RectangleShape>> wallsAndIntersections = createWallsAndIntersectionsFor(level);
    std::vector<sf::RectangleShape> walls = wallsAndIntersections.first;
    std::vector<sf::RectangleShape> intersections = wallsAndIntersections.second;
    sf::Vector2f previousDirection(0.0f, 0.0f);

    moveDir direction = left;
    moveDir desiredDirection;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
                    pacmanHasMovedOnce = true;

                if (event.key.code == sf::Keyboard::Up) {
                    
                    desiredDirection = up;
                    if (canMoveUp) direction = up;
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    desiredDirection = down;
                    if (canMoveDown) direction = down;
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    desiredDirection = left;
                    if (canMoveLeft) direction = left;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    desiredDirection = right;
                    if (canMoveRight) direction = right;
                }
            }
        }

        if (pacmanHasMovedOnce) {
            if (direction == right) {
                sf::Vector2f nextPosition = pacman.getPosition() + moveRight();
                pacman.setPosition(nextPosition);
            } else if (direction == left) {
                sf::Vector2f nextPosition = pacman.getPosition() + moveLeft();
                pacman.setPosition(nextPosition);
            } else if (direction == up) {
                sf::Vector2f nextPosition = pacman.getPosition() + moveUp();
                pacman.setPosition(nextPosition);
            } else if (direction == down) {
                sf::Vector2f nextPosition = pacman.getPosition() + moveDown();
                pacman.setPosition(nextPosition);
            }
        }

        for (const auto& intersection : intersections) {
            if (collides(pacman, intersection)) {
                sf::Vector2f intersectionMiddlePoint = getMiddlePoint(intersection);
                sf::Vector2f pacmanMiddlePoint(pacman.getPosition().x + pacman.getRadius(), pacman.getPosition().y + pacman.getRadius());

                if (pacmanMiddlePoint.x - intersectionMiddlePoint.x <= 0.1 && 
                    pacmanMiddlePoint.x - intersectionMiddlePoint.x >= -0.1 &&
                    pacmanMiddlePoint.y - intersectionMiddlePoint.y <= 0.1 &&
                    pacmanMiddlePoint.y - intersectionMiddlePoint.y >= -0.1) {
                    setMovableDirections(intersection);

                    // Stop Pacman if he continues moving in a direction he can no longer move in at the intersection
                    if (direction == right && !canMoveRight) {
                        direction = idle;
                        pacman.setPosition(intersection.getPosition().x, intersection.getPosition().y);
                    }

                    if (direction == left && !canMoveLeft) {
                        direction = idle;
                        pacman.setPosition(intersection.getPosition().x, intersection.getPosition().y);
                    }

                    if (direction == up && !canMoveUp) {
                        direction = idle;
                        pacman.setPosition(intersection.getPosition().x, intersection.getPosition().y);
                    }

                    if (direction == down && !canMoveDown) {
                        direction = idle;
                        pacman.setPosition(intersection.getPosition().x, intersection.getPosition().y);
                    }

                    // Move Pacman out of the intersection

                    if (desiredDirection == up && canMoveUp)
                        direction = desiredDirection;

                    if (desiredDirection == down && canMoveDown)
                        direction = desiredDirection;

                    if (desiredDirection == left && canMoveLeft)
                        direction = desiredDirection;

                    if (desiredDirection == right && canMoveRight)
                        direction = desiredDirection;

                    if (direction == up && canMoveUp) pacman.setPosition(pacman.getPosition() + moveUp());
                    if (direction == down && canMoveDown) pacman.setPosition(pacman.getPosition() + moveDown());
                    if (direction == left && canMoveLeft) pacman.setPosition(pacman.getPosition() + moveLeft());
                    if (direction == right && canMoveRight) pacman.setPosition(pacman.getPosition() + moveRight());
                }
            }
            else {
                if (direction == right || direction == left) {
                    canMoveRight = true;
                    canMoveLeft = true;
                    canMoveUp = false;
                    canMoveDown = false;
                }

                if (direction == up || direction == down) {
                    canMoveRight = false;
                    canMoveLeft = false;
                    canMoveUp = true;
                    canMoveDown = true;
                }
            }
        }

        window.clear();
        window.setView(view);
        
        for (const auto& wall : walls) {
            window.draw(wall);
        }

        for (const auto& intersection : intersections) {
            window.draw(intersection);
        }

        window.draw(pacman);
        window.display();
    }

    return 0;
}
