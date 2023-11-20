# bus-reservation-system-using-C
OVERVIEW OF THE SYSTEM
The bus reservation system operates within designated bus reservation offices, where authorized employees manage bookings for customers seeking tickets. 
Each employee has a unique username and password combination assigned to them, such as "agent1-Cap*1," providing secure access to the system. Upon 
successful login, employees can access the bus schedule, seat availability, and a seating arrangement displaying available seat numbers.

**Functions used:**
1.displayMainMenu() and displayUserMenu():
Display the main menu and user menu respectively for user interaction.

2.loginUser():
Takes user input for username and password and checks if the credentials match any user in the system.

3.bookTicket():
Allows users to book tickets by selecting a bus, specifying the number of people, entering passenger details, and choosing available seats.

4.cancelTicket():
Allows users to cancel a ticket by providing their name, freeing up the seat they previously booked.

5.displayBusScheduleAndStatus() and displaySeatArrangement():
Display the bus schedule, availability, and seat arrangement for users to view.

6.saveData() and loadData() functions for:
-User data: Saving/loading user credentials to/from a file.
-Bus data: Saving/loading bus information to/from a file.
-Passenger data: Saving/loading passenger information to/from a file.
-Booking history: Saving/loading booking history to/from a file.
-Bus schedule: Saving/loading bus schedules to/from a file.

7.main() function:
Initializes data structures for users, buses, schedules, passengers, and booking history.
Loads data from files at the beginning of the program.
Enters a loop allowing users to interact with the system based on menu options until the user chooses to exit.

**Data Structures used:**
struct Bus: Stores information about buses like bus number, source, destination, total seats, available seats, and fare.
struct Passenger: Stores information about passengers including their name, seat number, and the bus they are booked on.
struct User: Stores login credentials like username and password.
struct Schedule: Holds the schedule information for each bus, including bus number, source, destination, and departure time.
struct Booking: Keeps track of booking information such as bus number, passenger name, and seat number

Overall, this code constructs a basic bus reservation system allowing empoyes to log in, book/cancel tickets, view schedules, 
and manage bookings while persisting data through file operations.





