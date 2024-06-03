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

// Compass for Level
// "&"   = black space
// " "   = dot
// "*"   = intersection w/ dot
// "%"   = intersection w/ no dot ("*" do have dots)
// "!"   = powerpill
// "$"   = intersection w/ powerpill
// "X"   = ghost house
// "D"   = door

std::string level[36][28] = {
    { "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&" },
    { "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&" },
    { "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&", "&" },
    { "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#" },
    { "#", "*", " ", " ", " ", " ", "*", " ", " ", " ", " ", " ", "*", "#", "#", "*", " ", " ", " ", " ", " ", "*", " ", " ", " ", " ", "*", "#" },
    { "#", " ", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", " ", "#" },
    { "#", "!", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", "!", "#" },
    { "#", " ", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", " ", "#" },
    { "#", "*", " ", " ", " ", " ", "*", " ", " ", "*", " ", " ", "*", " ", " ", "*", " ", " ", "*", " ", " ", "*", " ", " ", " ", " ", "*", "#" },
    { "#", " ", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", " ", "#" },
    { "#", " ", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", " ", "#" },
    { "#", "*", " ", " ", " ", " ", "*", "#", "#", "*", " ", " ", "*", "#", "#", "*", " ", " ", "*", "#", "#", "*", " ", " ", " ", " ", "*", "#" },
    { "#", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", "&", "#", "#", "&", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", "#" },
    { "&", "&", "&", "&", "&", "#", " ", "#", "#", "#", "#", "#", "&", "#", "#", "&", "#", "#", "#", "#", "#", " ", "#", "&", "&", "&", "&", "&" },
    { "&", "&", "&", "&", "&", "#", " ", "#", "#", "%", "&", "&", "%", "&", "B", "%", "&", "&", "%", "#", "#", " ", "#", "&", "&", "&", "&", "&" },
    { "&", "&", "&", "&", "&", "#", " ", "#", "#", "&", "#", "#", "#", "D", "D", "#", "#", "#", "&", "#", "#", " ", "#", "&", "&", "&", "&", "&" },
    { "#", "#", "#", "#", "#", "#", " ", "#", "#", "&", "#", "X", "X", "X", "X", "X", "X", "#", "&", "#", "#", " ", "#", "#", "#", "#", "#", "#" },
    { "&", "&", "&", "&", "&", "&", "*", " ", " ", "%", "#", "X", "X", "X", "X", "X", "X", "#", "&", "#", "#", "*", "&", "&", "&", "&", "&", "&" },
    { "#", "#", "#", "#", "#", "#", " ", "#", "#", "&", "#", "X", "X", "X", "X", "X", "X", "#", "&", "#", "#", " ", "#", "#", "#", "#", "#", "#" },
    { "&", "&", "&", "&", "&", "#", " ", "#", "#", "&", "#", "#", "#", "#", "#", "#", "#", "#", "&", "#", "#", " ", "#", "&", "&", "&", "&", "&" },
    { "&", "&", "&", "&", "&", "#", " ", "#", "#", "%", "&", "&", "&", "&", "&", "&", "&", "&", "%", "#", "#", " ", "#", "&", "&", "&", "&", "&" },
    { "&", "&", "&", "&", "&", "#", " ", "#", "#", "&", "#", "#", "#", "#", "#", "#", "#", "#", "&", "#", "#", " ", "#", "&", "&", "&", "&", "&" },
    { "#", "#", "#", "#", "#", "#", " ", "#", "#", "&", "#", "#", "#", "#", "#", "#", "#", "#", "&", "#", "#", " ", "#", "#", "#", "#", "#", "#" },
    { "#", "*", " ", " ", " ", " ", "*", " ", " ", "*", " ", " ", "*", "#", "#", "*", " ", " ", "*", " ", " ", "*", " ", " ", " ", " ", "*", "#" },
    { "#", " ", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", " ", "#" },
    { "#", " ", "#", "#", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", " ", "#", "#", "#", "#", "#", " ", "#", "#", "#", "#", " ", "#" },
    { "#", "$", " ", "*", "#", "#", "*", " ", " ", "*", " ", " ", "*", "&", "O", "*", " ", " ", "*", " ", " ", "*", "#", "#", "*", " ", "$", "#" },
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
            else if (level[y][x] == "*" || level[y][x] == "%" || level[y][x] == "$") {
                sf::RectangleShape intersection(sf::Vector2f(32.0f, 32.0f));
                intersection.setFillColor(sf::Color::Black);
                intersection.setPosition(32.0f * x, 32.0f * y);
                intersections.push_back(intersection);
            }
        }
    }

    return std::make_pair(walls, intersections);
}

std::vector<sf::CircleShape> createDots(std::string level[36][28]) {
    std::vector<sf::CircleShape> dots;

    for (int y = 0; y < 36; y++) {
        for (int x = 0; x < 28; x++) {
            if (level[y][x] == " " || level[y][x] == "*") {
                sf::CircleShape dot(4.f);
                dot.setFillColor(sf::Color::White);
                dot.setPosition(32.0f * x + 12, 32.0f * y + 12);
                dots.push_back(dot);
            }
        }
    }

    return dots;
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

std::pair<float, float> blinkyInitialPosition() {
    float x_pos;
    float y_pos;

    for (int y = 0; y < 36; y++) {
        for (int x = 0; x < 28; x++) {
            if (level[y][x] == "B") {
                x_pos = x * 32;
                y_pos = y * 32;
            }
        }
    }

    return std::make_pair(x_pos, y_pos);
}

int currentScore = 0;

sf::Text score(int score, const sf::Font& font) {
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("HIGH SCORE:" + std::to_string(score));
    scoreText.setCharacterSize(80);
    scoreText.setFillColor(sf::Color::White);
    return scoreText;
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

float moveSpeed = 0.25f;

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

// Calc distance between two float points - needed to figure out pathing for ghosts.
// Ghosts will use the distance between them and pacman in evaluating their options
// when they enter an intersection.

float calculateDistance(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

bool collides(const sf::CircleShape circle1, const sf::CircleShape circle2) {
    // Get the positions of the centers of the circles
    sf::Vector2f position1 = circle1.getPosition();
    sf::Vector2f position2 = circle2.getPosition();

    // Calculate the distance between the centers of the circles
    float distance = calculateDistance(position1.x, position1.y, position2.x, position2.y);

    // Get the radii of the circles
    float radius1 = circle1.getRadius();
    float radius2 = circle2.getRadius();

    // Check if the distance is less than the sum of the radii
    return distance < (radius1 + radius2);
}

// Ghost stuff

enum movementMode {
    chase,
    scatter,
    frightened
};

class Ghost {
public:
    bool canMoveUp = false;
    bool canMoveDown = false;
    bool canMoveLeft = true;
    bool canMoveRight = true;
    sf::CircleShape body;
    movementMode movementMode;
    moveDir direction;
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
            print("cannot move into tile below");
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
        if (tileRight == "#") {
            canMoveRight = false;
        }
        else {
            canMoveRight = true;
        }
    }
    void chooseNewDirection(sf::CircleShape pacman) {
        sf::Vector2f ghostPosition = body.getPosition();
        sf::Vector2f pacmanPosition = pacman.getPosition();
        sf::Vector2f newPosition;

        float upTileDistance = 999;
        float downTileDistance = 999;
        float leftTileDistance = 999;
        float rightTileDistance = 999;

        if (canMoveUp) {
            newPosition = ghostPosition;
            newPosition.y -= 32;
            upTileDistance = calculateDistance(newPosition.x, newPosition.y, pacmanPosition.x, pacmanPosition.y);
        }

        if (canMoveDown) {
            newPosition = ghostPosition;
            newPosition.y += 32;
            downTileDistance = calculateDistance(newPosition.x, newPosition.y, pacmanPosition.x, pacmanPosition.y);
        }

        if (canMoveLeft) {
            newPosition = ghostPosition;
            newPosition.x -= 32;
            leftTileDistance = calculateDistance(newPosition.x, newPosition.y, pacmanPosition.x, pacmanPosition.y);
        }

        if (canMoveRight) {
            newPosition = ghostPosition;
            newPosition.x += 32;
            rightTileDistance = calculateDistance(newPosition.x, newPosition.y, pacmanPosition.x, pacmanPosition.y);
        }

        if (canMoveUp && upTileDistance < downTileDistance && upTileDistance < leftTileDistance && upTileDistance < rightTileDistance) {
            if (direction == down) {
                if (canMoveDown) {
                    direction = down;
                } else if (canMoveLeft) {
                    direction = left;
                } else if (canMoveRight) {
                    direction = right;
                } else {
                    direction = up;
                }
            } else {
                direction = up;
            }
        } else if (canMoveDown && downTileDistance < upTileDistance && downTileDistance < leftTileDistance && downTileDistance < rightTileDistance) {
            if (direction == up) {
                if (canMoveUp) {
                    direction = up;
                } else if (canMoveLeft) {
                    direction = left;
                } else if (canMoveRight) {
                    direction = right;
                } else {
                    direction = down;
                }
            } else {
                direction = down;
            }
        } else if (canMoveLeft && leftTileDistance < upTileDistance && leftTileDistance < downTileDistance && downTileDistance < rightTileDistance) {
            if (direction == right) {
                if (canMoveRight) {
                    direction = right;
                } else if (canMoveUp) {
                    direction = up;
                } else if (canMoveDown) {
                    direction = down;
                } else {
                    direction = left;
                }
            } else {
                direction = left;
            }
        } else if (canMoveRight && rightTileDistance < upTileDistance && rightTileDistance < downTileDistance && rightTileDistance < leftTileDistance) {
            if (direction == left) {
                if (canMoveLeft) {
                    direction = left;
                } else if (canMoveUp) {
                    direction = up;
                } else if (canMoveDown) {
                    direction = down;
                } else {
                    direction = right;
                }
            } else {
                direction = right;
            }
        } else {
            // We don't want the ghost moving through the wall, so if we have trouble
            // calculating the distance and picking a good direction, let's at least
            // ensure that the ghost will pick some appropriate path.
            if (direction == down && !canMoveDown) {
                if (canMoveLeft) {
                    direction = left;
                }
                else if (canMoveRight) {
                    direction = right;
                }
            } else if (direction == up && !canMoveUp) {
                if (canMoveLeft) {
                    direction = left;
                }
                else if (canMoveRight) {
                    direction = right;
                }
            } else if (direction == left && !canMoveLeft) {
                if (canMoveUp) {
                    direction = up;
                }
                else if (canMoveDown) {
                    direction = down;
                }
            } else if (direction == right && !canMoveRight) {
                if (canMoveUp) {
                    direction = up;
                }
                else if (canMoveDown) {
                    direction = down;
                }
            }
        }
    }
    void move() {
        sf::Vector2f nextPosition;

        if (direction == up) {
            nextPosition = body.getPosition() + moveUp();
        } else if (direction == down) {
            nextPosition = body.getPosition() + moveDown();
        } else if (direction == left) {
            nextPosition = body.getPosition() + moveLeft();
        } else if (direction == right) {
            nextPosition = body.getPosition() + moveRight();
        }

        body.setPosition(nextPosition);
    }
};

int main()
{
    // Window Init / Camera
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pacman");
    float x_pos = window.getSize().x / 2;
    sf::View view(sf::FloatRect(0 - x_pos, 0, 1600, 1200));

    // Game Font
    sf::Font font;
    font.loadFromFile("../VT323-Regular.ttf");

    // Blinky (Red Ghost)
    Ghost blinky;
    blinky.body.setFillColor(sf::Color::Red);
    std::pair<float, float> blinky_pos = blinkyInitialPosition();
    blinky.body.setPosition(blinky_pos.first - 16, blinky_pos.second);
    blinky.body.setRadius(16.f);
    blinky.movementMode = chase;
    blinky.direction = right;

    // Init Pacman
    sf::CircleShape pacman(16.f);
    pacman.setFillColor(sf::Color::Yellow);
    std::pair<float, float> pacman_pos = pacmanInitialPosition();
    pacman.setPosition(pacman_pos.first - 16, pacman_pos.second);
    bool dead = false;
    int extraLives = 2;

    // Pacman Directional Stuff
    sf::Vector2f previousDirection(0.0f, 0.0f);
    moveDir direction = left;
    moveDir desiredDirection;

    // Build the Level
    std::pair<std::vector<sf::RectangleShape>, std::vector<sf::RectangleShape>> wallsAndIntersections = createWallsAndIntersectionsFor(level);
    std::vector<sf::RectangleShape> walls = wallsAndIntersections.first;
    std::vector<sf::RectangleShape> intersections = wallsAndIntersections.second;

    // Create Dots
    std::vector<sf::CircleShape> dots = createDots(level);

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

        // Ghost movement
        blinky.move();

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

        //for (const auto& dot : dots) {
        //    if (collides(pacman, dot)) {
        //        currentScore += 10;
        //        
        //    }
        //}

        for (auto it = dots.begin(); it != dots.end();) {
            if (collides(pacman, *it)) {
                currentScore += 10;
                it = dots.erase(it); // Remove the dot from the vector
            } else {
                ++it;
            }
        }

        for (const auto& intersection : intersections) {
            if (collides(blinky.body, intersection)) {
                sf::Vector2f intersectionMiddlePoint = getMiddlePoint(intersection);
                sf::Vector2f blinkyMiddlePoint(blinky.body.getPosition().x + blinky.body.getRadius(), blinky.body.getPosition().y + blinky.body.getRadius());

                if (blinkyMiddlePoint.x - intersectionMiddlePoint.x <= 0.1 &&
                    blinkyMiddlePoint.x - intersectionMiddlePoint.x >= -0.1 &&
                    blinkyMiddlePoint.y - intersectionMiddlePoint.y <= 0.1 &&
                    blinkyMiddlePoint.y - intersectionMiddlePoint.y >= -0.1) {
                    blinky.setMovableDirections(intersection);
                    blinky.chooseNewDirection(pacman);
                }
            }

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

        window.draw(score(currentScore, font));
        
        for (const auto& wall : walls) {
            window.draw(wall);
        }

        for (const auto& dot : dots) {
            window.draw(dot);
        }

        //for (const auto& intersection : intersections) {
        //    window.draw(intersection);
        //}

        window.draw(blinky.body);
        window.draw(pacman);
        window.display();
    }

    return 0;
}
