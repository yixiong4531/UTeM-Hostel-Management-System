#include <iostream>
#include <string>

// C++ Connector Headers
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

// Global connection
sql::Connection* con;

void connectDB() {
    try {
        sql::Driver* driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        con->setSchema("UTeM_Hostel_System");
    }
    catch (sql::SQLException& e) {
        cout << "[!] Database Connection Failed.\nError: " << e.what() << endl;
        exit(1);
    }
}

// ==========================================
// 1. STUDENTS TABLE OPERATIONS
// ==========================================
void insertStudent() {
    string id, name, contact, course;
    cout << "\nEnter Student ID: "; cin >> id; cin.ignore();
    cout << "Enter Full Name: "; getline(cin, name);
    cout << "Enter Contact Number: "; getline(cin, contact);
    cout << "Enter Course: "; getline(cin, course);

    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Students (StudentID, FullName, ContactNumber, Course) VALUES (?, ?, ?, ?)");
        pstmt->setString(1, id); pstmt->setString(2, name); pstmt->setString(3, contact); pstmt->setString(4, course);
        pstmt->executeUpdate();
        cout << "[SUCCESS] Student added!\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void searchStudent() {
    string id; cout << "\nEnter Student ID to search: "; cin >> id;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM Students WHERE StudentID = ?");
        pstmt->setString(1, id);
        sql::ResultSet* res = pstmt->executeQuery();
        if (res->next()) {
            cout << "ID: " << res->getString("StudentID") << " | Name: " << res->getString("FullName") << " | Contact: " << res->getString("ContactNumber") << endl;
        }
        else { cout << "[!] Student not found.\n"; }
        delete res; delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void updateStudent() {
    string id, contact; cout << "\nEnter Student ID to update: "; cin >> id; cin.ignore();
    cout << "Enter New Contact Number: "; getline(cin, contact);
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Students SET ContactNumber = ? WHERE StudentID = ?");
        pstmt->setString(1, contact); pstmt->setString(2, id);
        if (pstmt->executeUpdate() > 0) cout << "[SUCCESS] Contact updated!\n";
        else cout << "[!] Student not found.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void deleteStudent() {
    string id; cout << "\nEnter Student ID to delete: "; cin >> id;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM Students WHERE StudentID = ?");
        pstmt->setString(1, id);
        if (pstmt->executeUpdate() > 0) cout << "[SUCCESS] Student deleted!\n";
        else cout << "[!] Student not found.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

// ==========================================
// 2. ROOMS TABLE OPERATIONS
// ==========================================
void insertRoom() {
    int id, cap; string num, status;
    cout << "\nEnter Room ID (Number format): "; cin >> id; cin.ignore();
    cout << "Enter Room Number (e.g., A101): "; getline(cin, num);
    cout << "Enter Capacity: "; cin >> cap; cin.ignore();
    cout << "Enter Status (Available/Full): "; getline(cin, status);

    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Rooms (RoomID, RoomNumber, Capacity, AvailabilityStatus) VALUES (?, ?, ?, ?)");
        pstmt->setInt(1, id); pstmt->setString(2, num); pstmt->setInt(3, cap); pstmt->setString(4, status);
        pstmt->executeUpdate();
        cout << "[SUCCESS] Room added!\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void searchRoom() {
    int id; cout << "\nEnter Room ID to search: "; cin >> id;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM Rooms WHERE RoomID = ?");
        pstmt->setInt(1, id);
        sql::ResultSet* res = pstmt->executeQuery();
        if (res->next()) cout << "Room: " << res->getString("RoomNumber") << " | Capacity: " << res->getInt("Capacity") << " | Status: " << res->getString("AvailabilityStatus") << endl;
        else cout << "[!] Room not found.\n";
        delete res; delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void updateRoom() {
    int id; string status; cout << "\nEnter Room ID to update: "; cin >> id; cin.ignore();
    cout << "Enter New Status: "; getline(cin, status);
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Rooms SET AvailabilityStatus = ? WHERE RoomID = ?");
        pstmt->setString(1, status); pstmt->setInt(2, id);
        if (pstmt->executeUpdate() > 0) cout << "[SUCCESS] Room updated!\n";
        else cout << "[!] Room not found.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void deleteRoom() {
    int id; cout << "\nEnter Room ID to delete: "; cin >> id;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM Rooms WHERE RoomID = ?");
        pstmt->setInt(1, id);
        if (pstmt->executeUpdate() > 0) cout << "[SUCCESS] Room deleted!\n";
        else cout << "[!] Room not found.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

// ==========================================
// 3. STAFF TABLE OPERATIONS
// ==========================================
void insertStaff() {
    string id, name, role;
    cout << "\nEnter Staff ID: "; cin >> id; cin.ignore();
    cout << "Enter Staff Name: "; getline(cin, name);
    cout << "Enter Role (e.g., Admin): "; getline(cin, role);
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Staff (StaffID, StaffName, Role) VALUES (?, ?, ?)");
        pstmt->setString(1, id); pstmt->setString(2, name); pstmt->setString(3, role);
        pstmt->executeUpdate();
        cout << "[SUCCESS] Staff added!\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void searchStaff() {
    string id; cout << "\nEnter Staff ID to search: "; cin >> id;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM Staff WHERE StaffID = ?");
        pstmt->setString(1, id);
        sql::ResultSet* res = pstmt->executeQuery();
        if (res->next()) cout << "Name: " << res->getString("StaffName") << " | Role: " << res->getString("Role") << endl;
        else cout << "[!] Staff not found.\n";
        delete res; delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void updateStaff() {
    string id, role; cout << "\nEnter Staff ID to update: "; cin >> id; cin.ignore();
    cout << "Enter New Role: "; getline(cin, role);
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Staff SET Role = ? WHERE StaffID = ?");
        pstmt->setString(1, role); pstmt->setString(2, id);
        if (pstmt->executeUpdate() > 0) cout << "[SUCCESS] Staff role updated!\n";
        else cout << "[!] Staff not found.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void deleteStaff() {
    string id; cout << "\nEnter Staff ID to delete: "; cin >> id;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM Staff WHERE StaffID = ?");
        pstmt->setString(1, id);
        if (pstmt->executeUpdate() > 0) cout << "[SUCCESS] Staff deleted!\n";
        else cout << "[!] Staff not found.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

// ==========================================
// 4. BOOKINGS TABLE OPERATIONS (WITH JOIN)
// ==========================================
void insertBooking() {
    string sid, date; int rid;
    cout << "\nEnter Student ID: "; cin >> sid;
    cout << "Enter Room ID: "; cin >> rid; cin.ignore();
    cout << "Enter Booking Date (YYYY-MM-DD): "; getline(cin, date);
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Bookings (StudentID, RoomID, BookingDate) VALUES (?, ?, ?)");
        pstmt->setString(1, sid); pstmt->setInt(2, rid); pstmt->setString(3, date);
        pstmt->executeUpdate();
        cout << "[SUCCESS] Booking created!\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void searchBooking() {
    int id; cout << "\nEnter Booking ID to search: "; cin >> id;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "SELECT b.BookingID, b.BookingDate, b.RoomID, s.FullName "
            "FROM Bookings b "
            "JOIN Students s ON b.StudentID = s.StudentID "
            "WHERE b.BookingID = ?"
        );
        pstmt->setInt(1, id);
        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            cout << "\n--- BOOKING RECORD ---\n";
            cout << "Booking ID: " << res->getInt("BookingID") << endl;
            cout << "Room ID: " << res->getInt("RoomID") << endl;
            cout << "Date: " << res->getString("BookingDate") << endl;
            cout << "Booked By: " << res->getString("FullName") << " (Student)" << endl;
        }
        else { cout << "[!] Booking not found.\n"; }
        delete res; delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void updateBooking() {
    int id, rid; cout << "\nEnter Booking ID to update: "; cin >> id;
    cout << "Enter New Room ID: "; cin >> rid;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Bookings SET RoomID = ? WHERE BookingID = ?");
        pstmt->setInt(1, rid); pstmt->setInt(2, id);
        if (pstmt->executeUpdate() > 0) cout << "[SUCCESS] Booking updated!\n";
        else cout << "[!] Booking not found.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void deleteBooking() {
    int id; cout << "\nEnter Booking ID to delete: "; cin >> id;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM Bookings WHERE BookingID = ?");
        pstmt->setInt(1, id);
        if (pstmt->executeUpdate() > 0) cout << "[SUCCESS] Booking deleted!\n";
        else cout << "[!] Booking not found.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

// ==========================================
// 5. PAYMENTS TABLE OPERATIONS (WITH JOIN)
// ==========================================
void insertPayment() {
    int bid; double amt; string date, staff;
    cout << "\nEnter Booking ID: "; cin >> bid;
    cout << "Enter Amount Paid: "; cin >> amt; cin.ignore();
    cout << "Enter Payment Date (YYYY-MM-DD): "; getline(cin, date);
    cout << "Enter Processed By (Staff ID): "; getline(cin, staff);
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Payments (BookingID, AmountPaid, PaymentDate, ProcessedBy) VALUES (?, ?, ?, ?)");
        pstmt->setInt(1, bid); pstmt->setDouble(2, amt); pstmt->setString(3, date); pstmt->setString(4, staff);
        pstmt->executeUpdate();
        cout << "[SUCCESS] Payment recorded!\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void searchPayment() {
    int id; cout << "\nEnter Payment ID to search: "; cin >> id;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "SELECT p.PaymentID, p.AmountPaid, p.PaymentDate, st.StaffName, s.FullName "
            "FROM Payments p "
            "JOIN Bookings b ON p.BookingID = b.BookingID "
            "JOIN Students s ON b.StudentID = s.StudentID "
            "JOIN Staff st ON p.ProcessedBy = st.StaffID "
            "WHERE p.PaymentID = ?"
        );
        pstmt->setInt(1, id);
        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            cout << "\n--- PAYMENT RECORD ---\n";
            cout << "Payment ID: " << res->getInt("PaymentID") << endl;
            cout << "Amount Paid: RM " << res->getDouble("AmountPaid") << endl;
            cout << "Date: " << res->getString("PaymentDate") << endl;
            cout << "Paid By: " << res->getString("FullName") << " (Student)" << endl;
            cout << "Processed By: " << res->getString("StaffName") << " (Staff)" << endl;
        }
        else { cout << "[!] Payment not found.\n"; }
        delete res; delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void updatePayment() {
    int id; double amt; cout << "\nEnter Payment ID to update: "; cin >> id;
    cout << "Enter Corrected Amount: "; cin >> amt;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Payments SET AmountPaid = ? WHERE PaymentID = ?");
        pstmt->setDouble(1, amt); pstmt->setInt(2, id);
        if (pstmt->executeUpdate() > 0) cout << "[SUCCESS] Payment amount updated!\n";
        else cout << "[!] Payment not found.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

void deletePayment() {
    int id; cout << "\nEnter Payment ID to delete: "; cin >> id;
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM Payments WHERE PaymentID = ?");
        pstmt->setInt(1, id);
        if (pstmt->executeUpdate() > 0) cout << "[SUCCESS] Payment deleted!\n";
        else cout << "[!] Payment not found.\n";
        delete pstmt;
    }
    catch (sql::SQLException& e) { cout << "[!] Error: " << e.what() << endl; }
}

// ==========================================
// SUB-MENU ROUTING
// ==========================================
void tableMenu(string tableName, void (*insertFunc)(), void (*searchFunc)(), void (*updateFunc)(), void (*deleteFunc)()) {
    int choice = 0;
    while (choice != 5) {
        cout << "\n--- " << tableName << " MANAGEMENT ---\n";
        cout << "1. Insert Record\n2. Search Record\n3. Update Record\n4. Delete Record\n5. Back to Main Menu\nChoice: ";
        cin >> choice;
        if (choice == 1) insertFunc();
        else if (choice == 2) searchFunc();
        else if (choice == 3) updateFunc();
        else if (choice == 4) deleteFunc();
        else if (choice != 5) cout << "[!] Invalid Choice.\n";
    }
}

// ==========================================
// MAIN MENU
// ==========================================
int main() {
    connectDB();
    int choice = 0;

    while (choice != 6) {
        cout << "\n=======================================";
        cout << "\n UTeM HOSTEL MANAGEMENT SYSTEM - MAIN ";
        cout << "\n=======================================\n";
        cout << "1. Manage Students Table\n";
        cout << "2. Manage Rooms Table\n";
        cout << "3. Manage Staff Table\n";
        cout << "4. Manage Bookings Table (Relational)\n";
        cout << "5. Manage Payments Table (Relational)\n";
        cout << "6. Exit System\n";
        cout << "---------------------------------------\n";
        cout << "Select Database Table (1-6): ";
        cin >> choice;

        switch (choice) {
        case 1: tableMenu("STUDENTS", insertStudent, searchStudent, updateStudent, deleteStudent); break;
        case 2: tableMenu("ROOMS", insertRoom, searchRoom, updateRoom, deleteRoom); break;
        case 3: tableMenu("STAFF", insertStaff, searchStaff, updateStaff, deleteStaff); break;
        case 4: tableMenu("BOOKINGS", insertBooking, searchBooking, updateBooking, deleteBooking); break;
        case 5: tableMenu("PAYMENTS", insertPayment, searchPayment, updatePayment, deletePayment); break;
        case 6: cout << "Exiting system safely...\n"; break;
        default: cout << "[!] Invalid choice.\n";
        }
    }

    delete con;
    return 0;
}