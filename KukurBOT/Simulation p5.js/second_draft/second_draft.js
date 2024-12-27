let hipAngleX = 0;  // Hip joint forward/backward
let hipAngleZ = 0;  // Hip joint sideways
let kneeAngle = 0;  // Knee joint

let minHipX = -45;
let maxHipX = 45;
let minHipZ = -30;
let maxHipZ = 30;
let minKnee = 0;
let maxKnee = 90;

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


let moveForward = false;    //boolean variable to determine movement
let moveBackward = false;
let moveLeftSide = false;
let moveRightSide = false;

let speed = 2;  // Speed of movement  //rate at which it moves

//let hatModel;

/*function preload(){
 hatModel = loadModel('hat.obj');
 }*/

function setup() {
  createCanvas(1300, 620, WEBGL);  // 3D renderer
  //noStroke();
  let resetButton = createButton('Reset');
  resetButton.position(1200, 500);
  resetButton.mousePressed(resetRobot);

  /*let Hat = createButton('Perry');
   Hat.position(1200,550);
   Hat.mousePressed(Perry);*/
   print('text');
}

function draw() {
  background(200);   // grey background

  // Limit hip and knee angles to avoid unnatural movement
  hipAngleX = constrain(hipAngleX, minHipX, maxHipX);  // Constrain hip angle forward/backward between -45 and 45 degrees
  hipAngleZ = constrain(hipAngleZ, minHipZ, maxHipZ);  // Constrain hip sideways angle between -30 and 30 degrees
  kneeAngle = constrain(kneeAngle, minKnee, maxKnee);    // Constrain knee bend between 0 and 90 degrees (cannot bend backwards)


  // Improved lighting setup
  ambientLight(150);  // Stronger ambient light to brighten all objects
  directionalLight(255, 255, 255, 0, 1, 0);  // White directional light from above

  orbitControl();  // Allows the user to move the camera with the mouse

  // Draw ground plane
  push();        // keep tracks of ground configurations while program running
  fill(150);
  translate(0, G, 0);
  rotateX(HALF_PI);  // to set the ground horizontal or 90 degree position
  plane(1000, 1000); // dimension of ground
  pop();

  //Draw Axes indicator
  push();
  translate(0, 0, 0); //to centre of the ground plane

  stroke(255, 0, 0);  //red color
  line(0, 0, 0, 50, 0, 0); //X axis
  // stroke(0,255,255);
  //line(0,0,0,-50,0,0); // -X axis

  stroke(0, 255, 0);  //green color
  line(0, 0, 0, 0, -50, 0); //Y
  //stroke(255,0,255);
  //line(0,0,0,0,50,0); // -Y

  stroke(0, 0, 255); //blue color
  line(0, 0, 0, 0, 0, 50); //Z
  //stroke(255,255,0);
  //line(0,0,0,0,0,-50); //-Z

  pop();

  // Move the robot when the forward or backward keys are pressed
  if (moveForward) {
    bodyZ -= speed;
  } else if (moveBackward) {
    bodyZ += speed;
  } else if (moveLeftSide) {
    bodyX -= speed;
  } else if (moveRightSide) {
    bodyX += speed;
  }

  // Draw the quadruped robot body (Spot-like design)
  drawBody(bodyX, bodyY, bodyZ, bodyW, bodyH, bodyD);

  // Draw legs
  drawLeg(bodyX - legOffsetX, bodyY + bodyH / 2, bodyZ - legOffsetZ, true);  // Front left
  drawLeg(bodyX + legOffsetX, bodyY + bodyH / 2, bodyZ - legOffsetZ, false);  // Front right
  drawLeg(bodyX - legOffsetX, bodyY + bodyH / 2, bodyZ + legOffsetZ, true);  // Back left
  drawLeg(bodyX + legOffsetX, bodyY + bodyH / 2, bodyZ + legOffsetZ, false);  // Back right

  // Update angles based on input
  handleInput();
  //Draw the Head
  drawHead(bodyX, bodyY/2, bodyZ + legOffsetZ+ bodyW*0.25, bodyW, bodyH, bodyD);
}
//Function to false all the bools
function FalseBools () {
  moveForward = false;
  moveBackward = false;
  moveLeftSide = false;
  moveRightSide = false;
  moveUpward = false;
  moveDownward = false;
}
// Function to draw the robot body with a more mechanical design
function drawBody(x, y, z, w, h, d) {
  push();
  translate(x, y, z);

  // Spot-like design - a sleek body with rounded edges
  ambientMaterial(255, 204, 0);  // Spot's main yellow color

  // Create a rounded box (main body)
  box(w, h, d);  // Main body box

  // Add additional details for a more mechanical look
  ambientMaterial(50);  // Dark gray for internal parts
  box(w * 0.8, h * 0.6, d * 0.6);  // Inner box for body mechanics
  pop();
}
//Function to draw head
function drawHead(x, y, z, w, h, d) {
  push();
  ambientMaterial(0);
  translate(x, y, z);
  box(w*0.5, h*0.5, d*0.5);
  
}



// Function to load and draw the 3D hat
/*function drawHat(x, y, z) {
 push();
 translate(x, y, z);  // Position the hat on top of the head
 rotateX(PI / 2);  // Adjust rotation if necessary, depending on your model orientation
 scale(0.5);  // Adjust scale to fit the head
 normalMaterial();  // Apply material to the hat
 model(hatModel);  // Render the 3D model
 pop();
 }
 function Perry(){
 drawHat(bodyX, bodyY/2 + 30, bodyZ + legOffsetZ+ bodyW*0.25);
 }*/

// Function to draw a leg with three degrees of freedom
function drawLeg(x, y, z, isLeft) {

  // Hip joint (x-axis and z-axis)
  push();
  translate(x, y, z);
  rotateX(radians(hipAngleX));  // Forward/backward motion at hip
  rotateZ(radians(hipAngleZ));  // Sideways motion at hip

  // Hip connector (joint)
  //ambientMaterial(0);  // Black for joints
  //box(10, 10, 10);

  // Upper leg - a more articulated structure
  ambientMaterial(isLeft ? [0, 0, 255] : [0, 255, 0]);  // Blue for left, green for right
  box(10, upperLegLength, 10);  // Upper leg

  // Knee joint
  translate(0, upperLegLength / 2, 0);
  rotateX(radians(kneeAngle));  // Bend at knee
  ambientMaterial(0);  // Black for knee joint
  box(10, 10, 10);  // Knee connector

  // Lower leg - a slightly thinner structure for the bottom part
  ambientMaterial(255, 0, 0);  // Red for lower leg
  translate(0, upperLegLength / 2, 0);
  box(8, lowerLegLength, 8);  // Lower leg

  // Foot (small box at the end of the leg)
  translate(0, lowerLegLength / 2, 0);
  ambientMaterial(50);  // Gray for the foot
  box(15, feetHeight, 15);  // Foot
  pop();
}

// Function to handle input for controlling the robot
function handleInput() {
  if (keyIsDown(LEFT_ARROW)) {
    hipAngleZ -= 1;  // Move hip sideways to the left

    if (hipAngleZ > minHipZ && hipAngleZ < maxHipZ) {
      moveLeftSide = true;
      moveRightSide = false;
      moveForward = false;
      moveBackward = false;
    }
    else {
      FalseBools();
    }
  } else if (keyIsDown(RIGHT_ARROW)) {
    hipAngleZ += 1;  // Move hip sideways to the right

    if (hipAngleZ > minHipZ && hipAngleZ < maxHipZ) {
      moveRightSide = true;
      moveLeftSide = false;
      moveForward = false;
      moveBackward = false;
    }
    else {
      FalseBools();
    }
  } else if (keyIsDown(UP_ARROW)) {
    hipAngleX -= 1;  // Move hip forward
    if (hipAngleX > minHipX && hipAngleX < maxHipX) {
      moveBackward = true;
      moveForward = false;
      moveLeftSide = false;
      moveRightSide = false;
    }
    else {
      FalseBools();
    }
  } else if (keyIsDown(DOWN_ARROW)) {
    hipAngleX += 1;  // Move hip backward
    if (hipAngleX > minHipX && hipAngleX < maxHipX) {
      moveForward = true;
      moveBackward = false;
      moveLeftSide = false;
      moveRightSide = false;
    }
    else {
      FalseBools();
    }
    
  }/*
   if (keyIsDown(87)) {  // 'W' key to bend knee
   kneeAngle -= 1;
   }
   else if (keyIsDown(83)) {  // 'S' key to straighten knee
   kneeAngle += 1;
   }
  /* if (keyIsDown(65)) {  // 'A' key to move forward
   moveForward = true;
   moveBackward = false;
   } else if (keyIsDown(68)) {  // 'D' key to move backward
   moveBackward = true;
   moveForward = false;
   }*/
  else {
    FalseBools();
  }
}

function resetRobot() {
  // Reset joint angles to initial state
  hipAngleX = 0;
  hipAngleZ = 0;
  kneeAngle = 0;

  // Reset the body position to initial state
  bodyX = 0;
  bodyY = 50;
  bodyZ = 0;

  // Reset movement flags
  moveForward = false;
  moveBackward = false;
  moveLeftSide = false;
  moveRightSide = false;
}
