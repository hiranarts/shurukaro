#pragma once
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Shapes~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* PLEASE KEEP IN MIND THAT ALL SHAPES ARE DEFINED IN COUNTER CLOCKWISE ORDER */

/* Line has two vertices */
struct Line {
    glm::vec2 one;
    glm::vec2 two;
};

/* Everyones favorite shape */
struct Circle {
    glm::vec2 center;
    float radius;
    Circle() = default;
    Circle(glm::vec2 c, float r) {
        center = c;
        radius = r;
    }
    void debugInfo() {
        std::cout << "[ Center: { " << center[0] << ", " << center[1] << " } | Radius: " << radius << std::endl;
    }

};
/* A gpus best friend */ 
struct Triangle {
    std::array<glm::vec2, 3> vertices;
    /* Imagine a vector(direction) with its origin at pos and projecting itself the the x axis. The resulting shape is a right triangle */
    static Triangle Right(glm::vec2 pos, glm::vec2 direction) {
        /* Quadrants
         *|--2--|--3--|
         *|--1--|--0--|
         */
        Triangle triangle;
        triangle.vertices[0] = pos; // origin
        triangle.vertices[1] = pos;
        triangle.vertices[2] = pos;

        //4 cases
        //case 1 x,y > 0 aka Quad 0 in left handed coordiante system
        if (direction[0] > 0 && direction[1] > 0) {
            //code
            triangle.vertices[1][0] += direction[0];
            triangle.vertices[2] += direction;
        }
        //Quad 1
        else if (direction[0] < 0 && direction[1] > 0) {
            //code
            triangle.vertices[1] += direction;
            triangle.vertices[2][0] += direction[0];
        }
        //Quad 2
        else if (direction[0] < 0 && direction[1] < 0) {
            triangle.vertices[1][0] += direction[0];
            triangle.vertices[2] += direction;
        }
        //Quad 3
        else if (direction[0] > 0 && direction[1] < 0) {
            triangle.vertices[1] += direction;
            triangle.vertices[2][0] += direction[0];
        }

        return triangle;
    }
    /* An Equilateral triangle with center at pos and "r" distance from pos. Note r is not the length of the side */
    static Triangle Equilateral(glm::vec2 pos, float r) {
        Triangle t;

        t.vertices[0] = pos + glm::vec2(0, -r);
        t.vertices[1] = pos + glm::vec2(r * cos(M_PI / 6), r * sin(M_PI / 6));
        t.vertices[2] = pos + glm::vec2(-(r * cos(M_PI / 6)), r * sin(M_PI / 6));

        return t;
    }
    void debugInfo() {
        printf("~~~\n");
        for (int i = 0; i < 3; i++) {
            printf("VX : (%.2f, %.2f) \n", vertices[i][0], vertices[i][1]);
        }
        printf("~~~\n");
    }
};

//TODO change so the Quadrialteral struct vertices gets changed not returning a struct
struct Quadrilateral {
    glm::vec2 vertices[4];
    /* Constructing Rectangle with center pos, and width and height. Vertices are defined clockwise */
    static Quadrilateral Rectangle(glm::vec2 pos, float width, float height) {
        Quadrilateral q;
        q.vertices[0] = pos + glm::vec2(-width / 2, -height / 2);
        q.vertices[1] = pos + glm::vec2(width / 2, -height / 2);
        q.vertices[2] = pos + glm::vec2(width / 2, height / 2);
        q.vertices[3] = pos + glm::vec2(-width / 2, height / 2);
        return q;
    }
    static Quadrilateral Rectangle(glm::vec2 top_left, glm::vec2 direction) {
        Quadrilateral q; 
        q.vertices[0] = top_left; 
        q.vertices[1] = top_left + glm::vec2(direction[0], 0);
        q.vertices[2] = top_left + direction;
        q.vertices[3] = top_left + glm::vec2(0, direction[1]);
        return q;
    }
    void clear() {
        for (int i = 0; i < 4; i++) {
            vertices[i] = glm::vec2(0, 0);
        }
    }

    void debugInfo() {
        printf("~~~\n");
        for (int i = 0; i < 4; i++) {
            printf("VX : (%.2f, %.2f) \n", vertices[i][0], vertices[i][1]);
        }
        printf("~~~\n");
    }
};

