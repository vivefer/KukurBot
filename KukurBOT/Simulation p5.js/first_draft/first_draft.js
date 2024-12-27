let hipAngleX = 0;  // Hip joint forward/backward
let hipAngleZ = 0;  // Hip joint sideways
let kneeAngle = 0;  // Knee joint

let bodyX = 0;
let bodyY = 100;
let bodyZ = 0;
let bodyW = 120;
let bodyH = 40;
let bodyD = 60;

let moveForward = false;
let moveBackward = false;

let speed = 2;  // Speed of movement

function setup() {
  createCanvas(1300, 620, WEBGL);  // 3D renderer
  //noStroke();
}

function draw() {
  background(200);
  
  // Improved lighting setup
  ambientLight(150);  // Stronger ambient light to brighten all objects
  directionalLight(255, 255, 255, 0, 1, 0);  // White directional light from above
  
  orbitControl();  // Allows the user to move the camera with the mouse

  // Draw ground plane
  push();
  fill(150);
  translate(0, 200, 0);
  rotateX(HALF_PI);
  plane(1000, 1000);
  pop();

  // Move the robot when the forward or backward keys are pressed
  if (moveForward) {
    bodyZ -= speed;
  } else if (moveBackward) {
    bodyZ += speed;
  }

  // Draw the quadruped robot body (Spot-like design)
  drawBody(bodyX, bodyY, bodyZ, bodyW, bodyH, bodyD);

  // Draw legs
  let legOffsetX = 40;
  let legOffsetZ = 50;
  drawLeg(bodyX - legOffsetX, bodyY + bodyH / 2, bodyZ - legOffsetZ, true);  // Front left
  drawLeg(bodyX + legOffsetX, bodyY + bodyH / 2, bodyZ - legOffsetZ, false);  // Front right
  drawLeg(bodyX - legOffsetX, bodyY + bodyH / 2, bodyZ + legOffsetZ, true);  // Back left
  drawLeg(bodyX + legOffsetX, bodyY + bodyH / 2, bodyZ + legOffsetZ, false);  // Back right

  // Update angles based on input
  handleInput();
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

// Function to draw a leg with three degrees of freedom
function drawLeg(x, y, z, isLeft) {
  let upperLegLength = 60;
  let lowerLegLength = 50;

  // Hip joint (x-axis and z-axis)
  push();
  translate(x, y, z);
  rotateX(radians(hipAngleX));  // Forward/backward motion at hip
  rotateZ(radians(hipAngleZ));  // Sideways motion at hip
  
  // Hip connector (joint)
  ambientMaterial(0);  // Black for joints
  box(10, 10, 10);
  
  // Upper leg - a more articulated structure
  ambientMaterial(isLeft ? [0, 0, 255] : [0, 255, 0]);  // Blue for left, green for right
  box(10, upperLegLength, 10);  // Upper leg
  
  // Knee joint
  translate(0, upperLegLength / 2, 0);
  rotateZ(radians(kneeAngle));  // Bend at knee
  ambientMaterial(0);  // Black for knee joint
  box(10, 10, 10);  // Knee connector

  // Lower leg - a slightly thinner structure for the bottom part
  ambientMaterial(255, 0, 0);  // Red for lower leg
  translate(0, upperLegLength / 2, 0);
  box(8, lowerLegLength, 8);  // Lower leg
  
  // Foot (small box at the end of the leg)
  translate(0, lowerLegLength / 2, 0);
  ambientMaterial(50);  // Gray for the foot
  box(15, 5, 15);  // Foot
  pop();
}

// Function to handle input for controlling the robot
function handleInput() {
  if (keyIsDown(LEFT_ARROW)) {
    hipAngleZ -= 1;  // Move hip sideways to the left
  }
  if (keyIsDown(RIGHT_ARROW)) {
    hipAngleZ += 1;  // Move hip sideways to the right
  }
  if (keyIsDown(UP_ARROW)) {
    hipAngleX -= 1;  // Move hip forward
  }
  if (keyIsDown(DOWN_ARROW)) {
    hipAngleX += 1;  // Move hip backward
  }
  if (keyIsDown(87)) {  // 'W' key to bend knee
    kneeAngle -= 1;
  }
  if (keyIsDown(83)) {  // 'S' key to straighten knee
    kneeAngle += 1;
  }
  if (keyIsDown(65)) {  // 'A' key to move forward
    moveForward = true;
    moveBackward = false;
  } else if (keyIsDown(68)) {  // 'D' key to move backward
    moveBackward = true;
    moveForward = false;
  } else {
    moveForward = false;
    moveBackward = false;
  }
}
