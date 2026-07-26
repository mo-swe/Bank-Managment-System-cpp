# 🏦 Bank System Management (v2.0 - Level 4 Extension)

Welcome to the **Bank System Management** project (Version 2.0). This C++ console application is the official evolution of the Level 3 Bank System, significantly expanded and refactored as the final milestone for the **Algorithms & Problem Solving Level 3 & Level 4** courses.

---

## 🎯 The Philosophy Behind This Project

This project is more than just a functional tool; it is a manifestation of **Deep Learning**. After tackling over 50 algorithmic challenges across two levels, I applied a "Deep Dive" approach to master Logic, String Manipulation, Dynamic Memory, Permissions, and Data Persistence. 

My goal was to move beyond the surface and build a robust, production-ready system from scratch, adhering to the principle of focusing on tangible results and technical mastery.

---

## 🔑 Demo Login Credentials

To test and explore the system immediately, log in using the pre-configured administrator account:

| Property | Setting / Value | Description |
| :--- | :--- | :--- |
| **Username** | `Admin` | Primary system administrator account |
| **Password** | `1234` | System access security code |
| **Permission Level** | `Full Access (-1)` | Grants permission to view, edit, and access all sub-menus |

> 💡 **Pro Tip:** Logging in as `Admin` grants full control to navigate to the **User Management Menu** to create new employee accounts and assign customized bitwise access permissions.

---

## 🔄 Version Evolution & What's New (v1.0 vs v2.0)

Version 2.0 transforms a simple single-user console app into a multi-user administrative system with fine-grained access control.

| Feature / Aspect | 🟢 Version 1.0 (Level 3 Baseline) | 🚀 Version 2.0 (Level 4 Extension) |
| :--- | :--- | :--- |
| **Authentication** | None (Direct open access to main menu) | **Secure Login System** requiring Username & Password |
| **User Roles** | Single shared interface | **Multi-User Architecture** with dynamic access rights |
| **Security** | Open access to all screens | **Granular Bitwise Permissions** (Access Denied protection) |
| **User Management** | Not available | Full **User Management Module** (List, Add, Find, Update, Delete) |
| **Data Persistence** | Single storage file (`Clients.txt`) | Multi-file persistence (`Clients.txt` & `Users.txt`) |
| **Architecture** | Basic function-call navigation | **Loop-Driven Navigation** (Refactored to eliminate stack overflow) |

---

## 📖 System Setup & Usage Instructions

### 1. ⚙️ Prerequisites & Data Setup
* **Database Files:** Ensure `Clients.txt` and `Users.txt` are placed in the same directory as the executable application. If missing, the system automatically initializes default storage files upon launch.
* **Data Integrity:** Do not manually edit the custom delimiter lines (`#//#`) inside the `.txt` database files to avoid string parsing issues.

### 2. 🎮 User Workflow & Operational Steps

#### Phase A: Session Authentication
1. Launch the application to bring up the **Login Screen**.
2. Enter the administrator credentials (`Admin` / `12345`).
3. Upon successful validation, access is granted to the **Main Menu**.

#### Phase B: System Main Menu Navigation
Select an option from the main menu to navigate through system capabilities:
* `[1] Show Client List` - Displays registered clients in a clean, formatted table.
* `[2] Add New Client` - Registers a new account with a unique Account Number.
* `[3] Delete Client` - Safely purges client records after confirmation.
* `[4] Update Client Info` - Modifies customer personal details or balances.
* `[5] Find Client` - Instantly searches client profiles by Account Number.
* `[6] Transactions Menu` - Opens the financial operations subsystem.
* `[7] Manage Users` - Opens user administration and permission settings.
* `[8] Logout` - Terminates the active session and returns to the Login Screen.

#### Phase C: Financial Transactions Operations (Option 6)
* Select **Deposit** or **Withdrawal** to modify account balances.
* Enter the **Account Number** to retrieve client data; the system automatically validates balance limits during withdrawals before updating `Clients.txt`.

#### Phase D: Managing Users & Testing Bitwise Permissions (Option 7)
* Log in as `Admin` and select **Manage Users** to register a new operator (e.g., Username: `Teller1`, Password: `5678`).
* Assign specific access flags (e.g., grant access only to `Show Client List` and `Transactions`).
* Log out and log back in as `Teller1` to observe the dynamic **Access Denied** protection screen when trying to enter restricted menus.

---

## 🚀 System Functionalities

The application is structured into three main logical modules:

### 1. Client Management (Main Menu)
* **Show Client List:** Displays all registered clients in a clean, formatted table.
* **Add New Client:** Handles the registration of new accounts with unique identifiers.
* **Update / Delete Client:** Allows for precise management and modification of client records.
* **Find Client:** A quick search feature to retrieve specific account information.

### 2. Transaction Management
* **Deposit & Withdraw:** Securely manages financial movements with built-in balance validation.
* **Total Balances:** Calculates and displays the total liquidity managed within the system.

### 3. User & Permission Management (Level 4 Extension)
* **Login & Authentication:** Secure authentication system requiring credentials to access the application.
* **Manage System Users:** Full control to add, update, delete, list, and find system users.
* **Granular Access Control:** Restricts access to specific screens based on individual bitwise user permissions.

---

## 🛠️ Technical Implementation

* **Language:** C++.
* **Data Persistence:** Integrated a file-based storage system using `.txt` files (`Clients.txt` and `Users.txt`) to ensure data is saved permanently across sessions.
* **Memory Management:** Leveraged `std::vector` and custom `struct` types for efficient, type-safe data handling in RAM.
* **The Core Challenge:** Advanced String Manipulation using custom split and join functions to parse and format data between the application memory and storage files.
* **Clean Architecture:** Utilized Enums, structural decomposition, and loop-driven menu navigation (replacing recursion) to ensure code readability and prevent stack overflow.

---

## 💡 Key Takeaways

Building this extended system refined my ability to handle complex logic flows and authorization architecture. It transformed basic string and file operations into a powerful, real-world backend console application. This project marks a significant milestone in my journey toward software engineering excellence.

---

## 🔗 Certifications & Milestones

This project represents the cumulative practical milestone for completing both **Algorithms & Problem Solving Level 3** and **Level 4**.

* [Verify my Problem Solving & Algorithms - Level 3 Certificate (PDF)](<./certificate/certificate-of-completion-for-algorithms-problem-solving-level-3 (2).pdf>)
* [Verify my Problem Solving & Algorithms - Level 4 Certificate (PDF)](<./certificate/certificate-of-completion-for-08-algorithms-problem-solving-level-4.pdf>)
