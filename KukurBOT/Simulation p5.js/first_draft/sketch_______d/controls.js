//Function to determine the booleans
function setControl(active_control) {
  for (let control in controls){
  controls[control] = (control == active_control);
  }
}

//Function to false all the bools
function FalseBools() {
  for (let control in controls) {
    controls[control] = false;
  }
}
// Function to handle input for controlling the robot
function handleInput() {
  if (keyIsDown(LEFT_ARROW)) {
    hipAngleZ += 1;  // Move hip sideways to the left

    if (hipAngleZ > minHipZ && hipAngleZ < maxHipZ) {
      setControl("moveLeftSide");
    } else {
      FalseBools();
    }
  } else if (keyIsDown(RIGHT_ARROW)) {
    hipAngleZ -= 1;  // Move hip sideways to the right

    if (hipAngleZ > minHipZ && hipAngleZ < maxHipZ) {
      setControl("moveRightSide");
    } else {
      FalseBools();
    }
  } else if (keyIsDown(UP_ARROW)) {
    hipAngleX -= 1;  // Move hip forward
    if (hipAngleX > minHipX && hipAngleX < maxHipX) {
      setControl("moveBackward");
    } else {
      FalseBools();
    }
  } else if (keyIsDown(DOWN_ARROW)) {
    hipAngleX += 1;  // Move hip backward
    if (hipAngleX > minHipX && hipAngleX < maxHipX) {
      setControl("moveForward");
    } else {
      FalseBools();
    }
  } else if (keyIsDown(87)) {  // 'W' key to bend knee
   kneeAngle -= 2; //Bent knee downward
   hipAngleX += 1;
     if (kneeAngle > minKnee && kneeAngle < maxKnee) {
       setControl("moveDownward");
     } else {
       FalseBools();
     }
  } else if (keyIsDown(83)) { //'S' key to bend knee
    kneeAngle += 2; //Bent knee upward
    hipAngleX -= 1 ;
      if (kneeAngle > minKnee && kneeAngle < maxKnee ) {
        setControl("moveUpward");
      } else {
        FalseBools();
      }
  }
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
  FalseBools();
}

function ToggleHat() {
  showHat = !showHat ;
}
