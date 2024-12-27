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
function drawHat(x, y, z) {
  push();
  translate(0, 210, 5);  // Position the hat on top of the head
  rotateX(PI);  // Adjust rotation if necessary, depending on your model orientation
  //rotateY(PI);
  scale(1.4);  // Adjust scale to fit the head
  normalMaterial();  // Apply material to the hat
  ambientMaterial(124, 40, 6);
  model(hatModel);  // Render the 3D model
  pop();
}


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
//  rotateX(radians(-groundAngle));
  ambientMaterial(50);  // Gray for the foot
  box(15, feetHeight, 15);  // Foot
  pop();
}
