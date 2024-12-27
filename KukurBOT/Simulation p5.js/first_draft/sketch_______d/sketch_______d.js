
function preload() {
  hatModel = loadModel('hat.obj');
}

function setup() {
  createCanvas(1300, 620, WEBGL);  // 3D renderer
  //noStroke();
  let resetButton = createButton('Reset');
  resetButton.position(1200, 500);
  resetButton.mousePressed(resetRobot);

  let Hat = createButton('Perry');
  Hat.position(1200, 550);
  Hat.mousePressed(ToggleHat);
  // print('text');
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
  if (controls.moveForward) {
    bodyZ -= speed;
  } else if (controls.moveBackward) {
    bodyZ += speed;
  } else if (controls.moveLeftSide) {
    bodyX += speed;
  } else if (controls.moveRightSide) {
    bodyX -= speed;
  }/* else if (controls.moveUpward) {
    bodyY -= speed;
  } else if (controls.moveDownward) {
    bodyY += speed;
  }*/

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
  if (showHat) {
    drawHat(bodyX, bodyY/2+10, bodyZ + legOffsetZ+ bodyW*0.25);
  }
}
