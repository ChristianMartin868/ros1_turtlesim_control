# ros1_turtlesim_control

ROS 1 node that makes `turtle2` follow `turtle1` in `turtlesim`. Study project
from the *Autonomous Systems* module (2020).

> Uses the **ROS 1** API (`ros/ros.h`, `ros::NodeHandle`, `ros::Rate`,
> `subscribe`/`advertise`). Targets ROS 1 (catkin).

## How it works

`src/turtle_control_node.cpp`:

- Subscribes to the poses of both turtles: `turtle1/pose`, `turtle2/pose`
  (`turtlesim/Pose`).
- Computes per iteration:
  - **distance** `dabs = sqrt(dx² + dy²)` between the two turtles,
  - **heading difference** `deltaTheta = atan2(dy, dx) − theta2`.
- Publishes `geometry_msgs/Twist` on `turtle2/cmd_vel`:
  - linear velocity `0.1 · dabs`,
  - angular velocity `0.5 · deltaTheta`.
- **Stop threshold:** when `dabs < 0.8` the forward motion is set to 0, so
  `turtle2` does not drive into `turtle1`.
- Runs at 1 Hz (`ros::Rate(1)`).

## Topics

| Direction | Topic            | Type                  |
|-----------|------------------|-----------------------|
| sub       | `turtle1/pose`   | `turtlesim/Pose`      |
| sub       | `turtle2/pose`   | `turtlesim/Pose`      |
| pub       | `turtle2/cmd_vel`| `geometry_msgs/Twist` |

## Build & run

The file is an excerpt and contains no build configuration. For a runnable
setup, add it to a catkin package:

```bash
# in a catkin workspace, create a package with CMakeLists.txt + package.xml,
# add turtle_control_node.cpp as a node target, then:
catkin_make
source devel/setup.bash

# start turtlesim and spawn a second turtle:
rosrun turtlesim turtlesim_node
rosservice call /spawn 2 2 0 turtle2

rosrun <your_package> turtle_control_node
```

Dependencies: ROS 1 with `turtlesim`, `geometry_msgs`.

> A ROS 2 port is available at
> [`ros2_turtlesim_control`](https://github.com/ChristianMartin868/ros2_turtlesim_control).
