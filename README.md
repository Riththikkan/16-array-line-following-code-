# 🤖 Line Follower Robot (Arduino Nano + TB6612FNG)

An **autonomous line-following robot** using an **Arduino Nano**, **TB6612FNG motor driver**, and a **16-sensor IR reflectance array** with a multiplexer for precise and fast line tracking.

---

## 🔧 Features
- 🧠 **PD Control** for smooth and stable line following
- 🎛️ **Automatic Sensor Calibration** at startup
- 🔍 **16-Sensor IR Array** via 74HC4067 multiplexer
- 🔌 **TB6612FNG Motor Driver** with standby control
- ⚡ Compact 2-wheel differential drive design
- 🔋 Battery-powered (≤12V)

---

## 📦 Hardware Used
| Component                       | Notes                          |
|--------------------------------|-------------------------------|
| Arduino Nano                   | Main controller               |
| TB6612FNG Motor Driver         | Dual DC motor driver          |
| 2x DC Motors + Wheels          | Differential drive            |
| 16-Sensor IR Reflectance Array | Track detection               |
| 74HC4067 Multiplexer           | Reads all 16 sensors on Nano  |
| LiPo/Battery Pack              | Power supply (max 12V)        |

---

## ⚙️ Pin Configuration

| Component       | Arduino Nano Pins           |
|-----------------|----------------------------|
| **Right Motor** | AIN1=3, AIN2=8, PWMA=5     |
| **Left Motor**  | BIN1=4, BIN2=7, PWMB=6     |
| **STBY**        | 9                          |
| **MUX S0-S3**   | A0, A1, A2, A3             |
| **MUX SIG**     | A4                         |

Sensor read order:  
`{9,10,11,12,13,14,15,16,8,7,6,5,4,3,2,1}`

---

## 🧩 How It Works
1. On startup, the bot auto-calibrates its sensors over black and white areas.  
2. The 74HC4067 multiplexer reads **16 analog sensors** one by one.  
3. Calculates the line position (0–15000) based on sensor values.  
4. A **PD controller** adjusts left and right motor speeds for smooth line tracking.  
5. Runs fully autonomously without external control.

---

## 🚀 Quick Start
1. Clone the repo and upload the code to your **Arduino Nano**:
   ```bash
   git clone https://github.com/yourusername/line-follower-robot.git
