# FSEvent-Based Automatic File Restoration and Backup System

## 📌 Project Description

The **FSEvent-Based Automatic File Restoration and Backup System** is a system-level application written in **C** that monitors file system activities and automatically creates backups when changes occur.

The program watches a specified directory and detects file events such as **file creation, modification, deletion, and renaming**. Whenever a file is modified or created, the system automatically stores a backup copy in a backup directory. This helps protect important files from accidental loss or corruption.

The system uses **Linux file system event mechanisms (inotify)** to efficiently detect file changes without continuously scanning directories.

---

# 🚀 Features

* Real-time file system monitoring
* Automatic backup of files when changes occur
* Detection of file creation, modification, and deletion
* Lightweight and efficient implementation in C
* Helps prevent accidental data loss

---

# ⚙️ Technologies Used

* **C Programming Language**
* **Linux inotify (File System Event API)**
* **GCC Compiler**
* **Linux System Calls**

---

# 📂 Project Structure

```
FSEvent-Based-Automatic-File-Restoration-and-Backup-System
│
├── main.c              # Main program for file system monitoring
├── backup/             # Directory where backup copies are stored
└── README.md
```

---

# 💻 How to Install and Run the Project

## 1️⃣ Clone the Repository

```bash
git clone https://github.com/samarth235/FSEvent-Based-Automatic-File-Restoration-and-Backup-System.git
```

---

## 2️⃣ Navigate to the Project Directory

```bash
cd FSEvent-Based-Automatic-File-Restoration-and-Backup-System
```

---

## 3️⃣ Compile the Program

Use the **GCC compiler** to compile the C file:

```bash
gcc main.c -o backup_system
```

---

## 4️⃣ Run the Program

```bash
./backup_system
```

The program will begin monitoring the specified directory and automatically create backups when file changes are detected.

---

# 📌 Applications

* Automatic backup of important files
* Protection against accidental file deletion or modification
* Monitoring file changes in development environments
* Basic file recovery and backup system

