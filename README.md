# Mobile-Operator-Bill-Management-System
implementation of Mobile Operator Bill Management System C++ code
Mobile Operator Bill Management System
This program allows a mobile operator to manage the bills of different call plans. It consists of two main types of plans: Package Plan and Rate Plan.

Package Plan
Attributes:

Customer Name
Phone Number
Bill Month
Available minutes to the same operator
Available minutes to other operators
Monthly cost
Rate of out-of-package minutes
Functionality:

Calculates the bill based on the monthly cost and the rate of out-of-package minutes.
Reads call logs from a file and updates the used minutes for both same and other operators.
Prints account details including customer name, phone number, bill month, available minutes, total minutes consumed, monthly bill, remaining minutes, and out-of-package minutes.
Rate Plan
Attributes:

Customer Name
Phone Number
Bill Month
Call rate
Favorite number
Favorite rate
Functionality:

Calculates the bill based on the call rate and the rate for calls to the favorite number.
Reads call logs from a file and updates the used minutes for calls to the favorite number and other numbers.
Prints account details including customer name, phone number, bill month, call rate, favorite number, total minutes consumed, favorite minutes, other minutes, and monthly bill.
How to Use:
Run the program.
Choose between Package Plan (enter 0) and Rate Plan (enter 1).
Enter customer details and plan-specific attributes as prompted.
Repeat steps 2-3 for up to 5 plans.
The program will display the account details and calculate the bill for each plan.
Note:
Ensure that the call logs are stored in a file named "calls.txt" in the same directory as the program.
The bill calculation and minute usage are based on the call logs provided in the "calls.txt" file. Make sure the format of the call logs is compatible with the program's reading mechanism.
