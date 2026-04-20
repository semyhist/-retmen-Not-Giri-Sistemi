<div align="center">

# 📚 -retmen-Not-Giri-Sistemi

A lightweight C CLI tool for managing school grades and student records with ease. Streamline your grade tracking workflow from the command line.

![GitHub Stars](https://img.shields.io/github/stars/semyhist/-retmen-Not-Giri-Sistemi?style=for-the-badge&logo=github&logoColor=white&color=0891b2)
![License](https://img.shields.io/github/license/semyhist/-retmen-Not-Giri-Sistemi?style=for-the-badge&color=6366f1)
![Language](https://img.shields.io/badge/C-0891b2?style=for-the-badge&logo=c&logoColor=white)

</div>

---

## 📖 Table of Contents

- [About](#about)
- [Key Features](#key-features)
- [Tech Stack](#tech-stack)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

---

## About

**-retmen-Not-Giri-Sistemi** is a command-line grade management system designed for educational institutions and teachers who need a fast, reliable way to track student performance. Built in C for maximum performance and minimal overhead, this tool brings efficiency to the classroom by eliminating the need for spreadsheets and complex graphical interfaces.

Whether you're managing a single class or multiple courses, this CLI tool provides an intuitive interface for recording grades, calculating statistics, and generating reports. It's perfect for educators who prefer working in the terminal and want a straightforward solution without unnecessary complexity.

The project targets schools, tutoring centers, and individual instructors looking for a lightweight, open-source alternative to traditional grade management systems.

---

## Key Features

✨ **Student Grade Recording** — Quickly add and update student grades through simple command-line prompts

📊 **Grade Statistics** — Automatically calculate averages, medians, and distribution analysis

🔍 **Student Search** — Find and filter students by name, ID, or course

📝 **Report Generation** — Export grade reports in readable formats

⚡ **Fast & Lightweight** — Built in C for minimal resource usage and instant performance

🎓 **Multi-Course Support** — Manage grades across different subjects and classes

💾 **Data Persistence** — Save and load student records reliably

🖥️ **User-Friendly CLI** — Intuitive menu-driven interface for all operations

---

## Tech Stack

![C](https://img.shields.io/badge/C-0891b2?style=for-the-badge&logo=c&logoColor=white)

---

## Getting Started

### Prerequisites

- GCC compiler (or any C compiler)
- Make (optional, for build automation)
- Linux/macOS/Windows (with appropriate C compiler)

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/semyhist/-retmen-Not-Giri-Sistemi.git
   cd -retmen-Not-Giri-Sistemi
   ```

2. **Compile the program**
   ```bash
   gcc -o grade_system *.c -lm
   ```

3. **Run the application**
   ```bash
   ./grade_system
   ```

> **Tip:** If you have a Makefile, simply run `make` to compile automatically.

---

## Usage

### Adding a Student and Grade

```bash
$ ./grade_system
Welcome to Grade Management System
1. Add Student
2. View Grades
3. Calculate Statistics
4. Exit

Enter choice: 1
Enter student name: John Doe
Enter student ID: 1001
Enter course: Mathematics
Enter grade: 85

✓ Student added successfully!
```

### Viewing Statistics

```bash
$ ./grade_system
...
Enter choice: 3
Course: Mathematics
Class Average: 82.5
Highest Grade: 95
Lowest Grade: 70
```

---

## Project Structure

```
-retmen-Not-Giri-Sistemi/
├── main.c              # Main entry point
├── grade.c             # Grade management functions
├── student.c           # Student data handling
├── utils.c             # Utility functions
├── grade.h             # Header files
├── student.h
├── Makefile            # Build configuration
└── README.md           # This file
```

---

## Contributing

We welcome contributions from the community! Here's how to get involved:

1. **Fork the repository** on GitHub
2. **Create a feature branch** for your changes: `git checkout -b feature/your-feature-name`
3. **Make your improvements** and test thoroughly
4. **Commit with clear messages**: `git commit -m "Add feature: description"`
5. **Submit a pull request** and describe your changes

Found a bug? Open an issue on our [issues page](https://github.com/semyhist/-retmen-Not-Giri-Sistemi/issues).

---

## License

This project is licensed under the terms specified in the [LICENSE](LICENSE) file. Please review it before using or contributing to this project.

Created by Semih Aydın