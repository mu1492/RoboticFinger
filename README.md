# Robotic Finger

The presented robotic finger concept is based on the combination of mechanical modeling, sensing, and closed-loop position/force control. This work has been preliminary to the dynamical and contact modeling of the fingertip, continuing with component and system calibration. Although design principles are similar, the focus has been on grasping systems with a small number of robotic fingers, and not necessarily on anthropomorphic hands.

---

The paper in which this work is described can be cited as
[Ursu, M., Ursu-Fischer, N. - *Robotic Hand Design for Position and Force Control*, Acta Technica Napocensis, Applied Mathematics and Mechanics Series 47, Volume III, pp. 103-112, Cluj-Napoca, 2004](ATN/Ursu%20-%20Robotic%20hand%20design%202004%2010pp.pdf)

---

The source code creates the plots from figures 6, 7, 8 and 9 from the paper, with design parameters that can be interactively modified in order to cover:
- **Mechatronic system modeling**: the robotic finger is treated as an integrated motor–gearbox–load system, with the main mechanical and electrical parameters explicitly modeled;
- **Closed-loop control**: position feedback is combined with force/torque feedback rather than relying only on open-loop actuation;
- **Force sensing**: the use of a strain-gauge-based sensor to estimate contact torque has been a technically relevant approach for robotic grasping during early 2000s;
- **Position–force control**: it is addressed the robotic problem of controlling both position and contact force, which is particularly relevant to manipulation;
- **Variable compliance/stiffness**: the possibility of modifying the apparent stiffness of the finger through feedback;
- **Quantitative control analysis**: the transfer functions are derived for analyzing natural frequency, damping, transient response, frequency response, and stability-related parameters;
- **Hardware-oriented engineering**: actuator, gearbox, sensor, data converters, and other implementation parameters are considered quantitatively, while balancing the angular resolution with DAC requirements points to limitations imposed by electronics;
- **System-level integration**: mechanical design, sensing, actuation, and control are considered together and tightly coupled;

The first **ROS** (Robotic Operating System) was released only three years after this paper was published (2004), but nowadays it is the standard software framework for describing robotic states, parameters, commands etc. The table below lists some of the variables from the article that are suitable for a straightforward ROS-based implementation.

| Variable  | Meaning | ROS2 |
| :------------: | :------------: | :------------: |
| *θ<sub>i</sub>* | input angular position / set point | command |
| *θ<sub>o</sub>* | output angular position | state |
| *τ<sub>d</sub>* | disturbing torque / torque exerted on the finger | state |
| *S* | joint stiffness | parameter |
| *E* | torque transducer signal gain | parameter |
| *T<sub>s</sub>* | system time constant | parameter |
| *K<sub>a</sub>* | forward path gain | parameter |
| *K<sub>b</sub>* | speed feedback gain | parameter |

**Build steps:**

	cd RoboticFinger
	mkdir build
	cd build
	cmake ..
	make
