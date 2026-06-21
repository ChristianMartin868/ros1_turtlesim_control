# ros1_turtlesim_control

ROS-1-Node, mit der `turtle2` der `turtle1` in `turtlesim` folgt. Studienprojekt
aus dem Modul *Autonome Systeme* (2020).

> Verwendet die **ROS 1**-API (`ros/ros.h`, `ros::NodeHandle`, `ros::Rate`,
> `subscribe`/`advertise`). Ausgelegt für ROS 1 (catkin).

## Funktionsweise

`src/turtle_control_node.cpp`:

- Abonniert die Posen beider Schildkröten: `turtle1/pose`, `turtle2/pose`
  (`turtlesim/Pose`).
- Berechnet pro Iteration:
  - **Abstand** `dabs = sqrt(dx² + dy²)` zwischen beiden Schildkröten,
  - **Winkeldifferenz** `deltaTheta = atan2(dy, dx) − theta2`.
- Veröffentlicht `geometry_msgs/Twist` auf `turtle2/cmd_vel`:
  - Lineargeschwindigkeit `0.1 · dabs`,
  - Winkelgeschwindigkeit `0.5 · deltaTheta`.
- **Stoppschwelle:** bei `dabs < 0.8` wird die Vorwärtsbewegung auf 0 gesetzt,
  damit `turtle2` nicht in `turtle1` hineinfährt.
- Läuft mit 1 Hz (`ros::Rate(1)`).

## Topics

| Richtung | Topic            | Typ                   |
|----------|------------------|-----------------------|
| sub      | `turtle1/pose`   | `turtlesim/Pose`      |
| sub      | `turtle2/pose`   | `turtlesim/Pose`      |
| pub      | `turtle2/cmd_vel`| `geometry_msgs/Twist` |

## Bauen & Ausführen

Die Datei ist ein Auszug und enthält keine Build-Konfiguration. Für eine
lauffähige Umgebung in ein catkin-Package einbinden:

```bash
# in einem catkin-Workspace, Package mit CMakeLists.txt + package.xml anlegen,
# turtle_control_node.cpp als Node-Target hinzufügen, dann:
catkin_make
source devel/setup.bash

# turtlesim starten und zweite Schildkröte spawnen:
rosrun turtlesim turtlesim_node
rosservice call /spawn 2 2 0 turtle2

rosrun <dein_package> turtle_control_node
```

Abhängigkeiten: ROS 1 mit `turtlesim`, `geometry_msgs`.
