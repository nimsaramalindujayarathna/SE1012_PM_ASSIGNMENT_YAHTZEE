# Grocery Management System Web App

## Project Overview
This web application allows users to manage groceries efficiently using load cell scales and real-time weight updates via Firebase.

## Features
- **Base Page**: Central navigation accessible at all times.
- **User's Database Table**: Each user has a table with the fields: Grocery Name, Load Cell Scale Number (real-time data from Firebase), Expiry Date, and Weight.
- **User Home Page**: Displays two subsections: Add New Grocery and Stock Levels.
- **Add New Grocery Page**:
  - Fields: Grocery Name, Expiry Date, and Load Cell Assignment (selected by the user, enabling real-time weight updates via Firebase).
  - Submit button updates the user’s data table.
- **Stock Levels Page**:
  - Displays a table with Grocery Name, Weight (real-time updates from Firebase), Expiry Date, and Days to Expire (calculated locally using JS).
  - Items past their expiry are shown in a separate table labeled "Expired Groceries".
  - Options: Delete (with confirmation, frees up the load cell) and Edit (opens a modal to update Expiry Date and Load Cell Assignment).
  - Updated data reflects in the user’s table with real-time weight updates.
- **Notification Icon**: Pops up an empty window for future design.
- **Core Functionality**: Load cell assignment and real-time weight updates via Firebase.

## Technology Stack
- **Frontend**: HTML, CSS, JavaScript
- **Backend**: Python
- **Database**: Firebase (for weight updates)

## Setup Instructions
1. Clone the repository.
2. Set up a Python virtual environment:
   ```sh
   python -m venv venv
   ```
3. Activate the virtual environment:
   - **Windows**:
     ```sh
     venv\Scripts\activate
     ```
   - **Mac/Linux**:
     ```sh
     source venv/bin/activate
     ```
4. Install dependencies:
   ```sh
   pip install -r requirements.txt
   ```
5. Configure Firebase for real-time weight updates.
6. Run the application:
   ```sh
   python app.py
   ```
7. Open the application in a browser.

## Notes
- A scale can only be assigned if its weight is 0. After assignment, weight must be placed on the scale.
- An unassigned scale with a non-zero weight cannot be assigned.

This project is in the prototype phase, and improvements are ongoing. Contributions and feedback are welcome!

