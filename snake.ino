#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <CircularBuffer.h>


// LEDmatrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
    8, 8, 10, NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
    NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB + NEO_KHZ800
);

// game stuff
int GAME_SPEED;
const int GAME_WIDTH = matrix.width();
const int GAME_HEIGHT = matrix.height();

// snake and food
CircularBuffer<int,64> snakeBody;
int newBody;
int food;

byte Inputpins;
// left = digiin2 = 0b00000001
// up = digiin3 = 0b00000010
// right = digiin4 = 0b00000100
// down = digiin6 = 0b00110000

int isMoving;
// left = 0
// up = 1
// right = 2
// down = 3

// is also called when death occurs
void setup() {
    snakeBody.clear();
    for (int i=0; i<3; i++) { snakeBody.push(i+26); } // init snakeBody
    food = 8; // init food position
    isMoving = 2; // init snake direction
    GAME_SPEED = 300; //init gamespeed.
    matrix.begin();
    matrix.setBrightness(40);
}


void loop() {
    button2direction();
    updateSnake();
    updateFood();
    draw();
    delay(GAME_SPEED);
}


void draw() {
    matrix.clear();
    for (int i = 0; i < sizeof(snakeBody); i++) { matrix.setPixelColor(snakeBody[i], 0, 255, 0); }
    matrix.setPixelColor(food, 255, 0, 0);
    matrix.show();
}


void updateFood() {
    if (onSnake(food)) { // create new food which is not on the snakebody.
        while (onSnake(food)) {
            food = random(0, (GAME_WIDTH*GAME_HEIGHT)-1);
        } 
    }
}


void updateSnake() {
    // create newBody
    switch(isMoving) {
        case 0: // move left
            if ((snakeBody.last()-1)%GAME_WIDTH == (GAME_WIDTH-1) || (snakeBody.last()-1) < 0) {
                newBody = GAME_WIDTH-1;
            } else {
                newBody = -1;
            }
            break;

        case 1: // move up
            if ((snakeBody.last()-GAME_WIDTH) >= 0) {
                newBody = -GAME_WIDTH;
            } else {
                newBody = (GAME_WIDTH*GAME_HEIGHT)-GAME_WIDTH;
            }
            break;

        case 2: // move right
            if ((snakeBody.last()+1)%GAME_WIDTH == 0) {
                newBody = -(GAME_WIDTH-1);
            } else {
                newBody = 1;
            }
            break;

        case 3: // move down
            if ((snakeBody.last()+GAME_WIDTH) < (GAME_WIDTH*GAME_HEIGHT)) {
                newBody = GAME_WIDTH;
            } else {
                newBody = -((GAME_WIDTH*GAME_HEIGHT)-GAME_WIDTH);
            }
            break;
    }

    // check for death
    if (onSnake(newBody + snakeBody.last())) {
        setup();
    } else { // increment snake head and remove tail.
        snakeBody.push(snakeBody.last() + newBody);
        if (snakeBody.last() != food) {
            snakeBody.shift();
        } else {
            GAME_SPEED = GAME_SPEED-30;
        }
    }

}


bool onSnake(int elem) {
    for (int x=0; x < sizeof(snakeBody); x++) {
        if (snakeBody[x] == elem) {return true;}
    }
    return false;
}


void button2direction() {
    Inputpins = PIND >>2; // read digital pins 2-7
    switch(Inputpins){
        case 0b00000001: // move left
            if (isMoving == 2) {break;}
            isMoving = 0;
            break;

        case 0b00000010: // move up
            if (isMoving == 3) {break;}
            isMoving = 1; 
            break;

        case 0b00000100: // move right
            if (isMoving == 0) {break;} 
            isMoving = 2;
            break;

        case 0b00110000: // move down
            if (isMoving == 1) {break;}
            isMoving = 3;
            break;
    }
}