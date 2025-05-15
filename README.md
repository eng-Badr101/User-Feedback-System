# 🗣️ User Feedback Management System

This is a **C++ console application** that allows users to register, log in, and submit feedback of various types (bug reports, feature requests, and general feedback). Admins can view, sort, and prioritize feedback, as well as analyze the most common types submitted.

## 📌 Features

### 👤 User Functionality
- Register with name, password, email, and address.
- Log in securely using credentials.
- Submit up to 10 feedback entries.
- Choose feedback types: 
  - Bug Report
  - Feature Request
  - General Feedback
- Edit or delete existing feedback.
- Automatically assigns priority to feedback based on how commonly the message is repeated.

### 🔐 Admin Functionality
- Log in using a special admin passkey (`"admin"` by default).
- View:
  - All feedback entries
  - Filtered feedback by type
  - Most reported feedback type
- Feedback statistics and analysis

### 💾 Data Persistence
- All feedback is saved to `feedback_data.txt`
- Automatically loads previous data on startup
- Saves current session on exit

## 📁 File Structure

.
├── feedback_data.txt # Auto-generated file to store user data
├── main.cpp # Main source code
└── README.md # You're here!

r
Copy
Edit

## 🛠️ How to Run

1. Compile the code using g++ or any compatible C++ compiler:
   ```bash
   g++ main.cpp -o feedback_app
Run the program:

bash
Copy
Edit
./feedback_app
⚙️ Dependencies
Standard C++17

No external libraries required

🧠 How Prioritization Works
Each feedback message is compared with others. If a message is reported multiple times (i.e., identical messages from different users), its priority score increases. This helps admins identify frequent or critical issues.

🛡️ Admin Access
To log in as an admin, use:

Username: Any name

Passkey: admin

📷 Sample Output
text
Copy
Edit
======Welcome in our user feedback project=====
1.Registeration  2.Login  3.Exit
🧾 License
This project is open-source and free to use for learning and development purposes.
