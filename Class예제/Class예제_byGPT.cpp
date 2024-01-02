/**
 * @file Class¿¹Á¦_byGPT.cpp
 * @brief This file contains the implementation of Point and PointSet classes.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

 /**
  * @class Point
  * @brief A class to represent a point in 2D space.
  */
class Point {
public:
    /**
     * @brief Construct a new Point object with random x and y coordinates.
     */
    Point() : x(rand() % 100), y(rand() % 100) {}

    /**
     * @brief Calculate the distance to another Point object.
     * @param other The other Point object.
     * @return The distance to the other Point object.
     */
    double distanceTo(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
        }

    /**
     * @brief Get the x coordinate.
     * @return The x coordinate.
     */
    int getX() const { return x; }

    /**
     * @brief Get the y coordinate.
     * @return The y coordinate.
     */
    int getY() const { return y; }

    /**
     * @brief Set the x and y coordinates.
     * @param x The x coordinate.
     * @param y The y coordinate.
     */
    void plotXY(int x, int y) {
        this->x = x;
        this->y = y;
        }

private:
    int x, y;
    };

/**
 * @class PointSet
 * @brief A class to represent a set of Point objects.
 */
class PointSet {
public:
    /**
     * @brief Add a Point object to the set.
     * @param point The Point object to add.
     */
    void addPoint(const Point& point) {
        points.push_back(point);
        }

    /**
     * @brief Calculate the number of points with distance <= 10.
     */
    void calculateDistances() {
        for (size_t i = 0; i < points.size(); ++i) {
            for (size_t j = i + 1; j < points.size(); ++j) {
                if (points[i].distanceTo(points[j]) <= 10) {
                    ++count;
                    }
                }
            }
        }

    /**
     * @brief Print the number of points with distance <= 10.
     */
    void printResult() const {
        std::cout << "Number of points with distance <= 10: " << count << std::endl;
        }

    /**
     * @brief Plot all points in the set.
     */
    void plotAll() {
        /// Plot points
        sf::RenderWindow window(sf::VideoMode(800, 600), "Plot Points"); // Create window
        while (window.isOpen()) { 
            sf::Event event; // Event handler
            while (window.pollEvent(event)) { // Handle events
                if (event.type == sf::Event::Closed) 
                    window.close();
                }
            window.clear();
            for (const auto& point : points) {
                sf::CircleShape shape(5);
                shape.setPosition(point.getX()*10, point.getY()*10);
                window.draw(shape);
                }
            window.display();
            }
        }

private:
    std::vector<Point> points;
    int count = 0;
    };

/**
 * @brief The main function.
 * @return 0 on successful execution.
 */
int main() {
    srand(time(0)); // Seed random number generator
    PointSet pointSet;
    for (int i = 0; i < 100; ++i) {
        pointSet.addPoint(Point());
        }
    pointSet.calculateDistances();
    pointSet.printResult();
    pointSet.plotAll();
    return 0;
    }