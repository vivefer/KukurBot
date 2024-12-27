let hipAngleX = 0;  // Hip joint forward/backward
let hipAngleZ = 0;  // Hip joint sideways
let kneeAngle = 0; // Knee joint
//let groundAngle = PI - radians(hipAngleX) + radians(kneeAngle); //angle needed to keep virtual straight line in standing position

let minHipX = -45;   //Define Constraints
let maxHipX = 45;
let minHipZ = -30;
let maxHipZ = 30;
let minKnee = 0;
let maxKnee = 90;
let minGround = 0;
let maxGround = 180;

let bodyX = 0;      //bodyX-Z coordinate of the body in the ground
let bodyY = 50;
let bodyZ = 0;
let bodyW = 80;    //bodyW-D the width, height and depth of the body
let bodyH = 40;
let bodyD = 150;

let upperLegLength = 60;
let lowerLegLength = 50;
let feetHeight = 5;
let GroundTolerance = 10;
let G = bodyY + upperLegLength + lowerLegLength + feetHeight - ( bodyH/2) + GroundTolerance;  // ground position along Y axis wrt body position

let legOffsetX = bodyW/2;
let legOffsetZ = bodyD/3;

let controls = {   // object with all the control booleans
  moveForward: false,
  moveBackward: false,
  moveLeftSide: false,
  moveRightSide: false,
  moveUpward: false,
  moveDownward: false
};


let showHat = false;
let speed = 2;  // Speed of movement  //rate at which it moves

let hatModel;
