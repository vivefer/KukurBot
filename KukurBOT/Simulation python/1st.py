import pybullet as p
import pybullet_data
import time
import keyboard  # For handling keyboard inputs

# Connect to PyBullet's GUI server
p.connect(p.GUI)

# Set additional search paths to load URDFs from PyBullet data
p.setAdditionalSearchPath(pybullet_data.getDataPath())

# Load the plane URDF (flat ground)
plane = p.loadURDF("plane.urdf")

# Set gravity
p.setGravity(0, 0, -9.8)

# Load your quadruped URDF (you can use your custom URDF here)
quadruped = p.loadURDF("quadruped/quadruped.urdf", [0, 0, 0.3])

# Number of joints in the quadruped
num_joints = p.getNumJoints(quadruped)

# Function to control the robot (example of setting joint positions)
def control_robot():
    for joint_index in range(num_joints):
        # Example control: move joints based on a simple sine wave pattern
        target_pos = 0.5 * p.sin(time.time())
        p.setJointMotorControl2(quadruped, jointIndex=joint_index, controlMode=p.POSITION_CONTROL, targetPosition=target_pos)

# Simulation loop: runs indefinitely unless terminated manually
print("Press 'ESC' to terminate the simulation.")

while True:
    # Step the simulation
    p.stepSimulation()
    
    # Call the control function to move the robot
    control_robot()

    # Sleep for a real-time feel of the simulation
    time.sleep(1./240.)

    # Check for termination key press (ESC key to exit)
    if keyboard.is_pressed('esc'):
        print("Terminating the simulation...")
        break

# Disconnect from the PyBullet server
p.disconnect()
