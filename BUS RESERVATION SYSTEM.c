#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to store bus information
struct Bus {
    int busNumber;
    char source[50];
    char destination[50];
    int totalSeats;
    int availableSeats;
    float fare;
};
// Define a structure to store passenger information
struct Passenger {
    char name[50];
    int seatNumber;
    int busNumber;
};
// Define a structure to store user login information
struct User {
    char username[500];
    char password[500];
};
// Define a structure to store bus schedule
struct Schedule {
    int busNumber;
    char source[50];
    char destination[50];
    char departureTime[10];
};
// Define a structure to store booking information
struct Booking {
    int busNumber;
    char passengerName[50];
    int seatNumber;
};

// Function to display the main menu
void displayMainMenu()
{
    printf("\n=== CAPSTONE RESERVATION SYSTEM ===\n");
    printf("1. Login\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
}

// Function to display the user menu
void displayUserMenu()
{
    printf("\n=== USER MENU ===\n");
    printf("1. Book a Ticket\n");
    printf("2. Cancel a Ticket\n");
    printf("3. Check Bus Schedule and Status\n");
    printf("4. View Booking History\n");
    printf("5. Logout\n");
    printf("Enter your choice: ");
}

// Function to perform user login
int loginUser(struct User users[], int numUsers, char username[], char password[])
{
    int i = 0;
    while (i < numUsers) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            system("cls");
            return i;
        }
        i++;
    }
    return -1;
}

// Function to book a ticket
void bookTicket(struct Bus buses[], int numBuses, struct Passenger passengers[], int* numPassengers, struct Booking bookingHistory[], int* numBookings, int userId) {
    printf("\nEnter Bus Number: ");
    int busNumber;
    scanf("%d", &busNumber);

    // Find the bus with the given busNumber
    int busIndex = -1;
    int i = 0;
    while (i < numBuses) {
        if (buses[i].busNumber == busNumber) {
            busIndex = i;
            break;
        }
        i++;
    }

    if (busIndex == -1) {
        printf("Bus with Bus Number %d not found.\n", busNumber);
    } else if (buses[busIndex].availableSeats == 0) {
        printf("Sorry, the bus is fully booked.\n");
    } else {
        int numPeople;
        printf("Enter the number of people: ");
        scanf("%d", &numPeople);

        int j = 0;
        while (j < numPeople) {
            printf("Enter Passenger Name for Person %d: ", j + 1);
            scanf("%s", passengers[*numPassengers].name);
            // Ask the customer to choose a specific seat number
            printf("Enter the desired seat number (1-%d): ", buses[busIndex].totalSeats);
            int desiredSeat;
            scanf("%d", &desiredSeat);

            if (desiredSeat < 1 || desiredSeat > buses[busIndex].totalSeats) {
                printf("Invalid seat number. Please choose a seat between 1 and %d.\n", buses[busIndex].totalSeats);
                continue;
            }

            if (buses[busIndex].availableSeats < numPeople) {
                printf("Sorry, there are not enough available seats for your group.\n");
                break;
            }

            if (desiredSeat > buses[busIndex].availableSeats) {
                printf("Sorry, the selected seat is not available. Please choose another seat.\n");
                continue;
            }
            // Check if the desired seat is already occupied
            int seatOccupied = 0;
            for (i = 0; i < *numPassengers; i++) {
                if (passengers[i].busNumber == busNumber && passengers[i].seatNumber == desiredSeat) {
                    seatOccupied = 1;
                    break;
                }
            }
            if (seatOccupied) {
                printf("Sorry, the selected seat is already occupied. Please choose another seat.\n");
                continue;
            }
            // Assign the chosen seat number to the passenger
            passengers[*numPassengers].seatNumber = desiredSeat;
            // Update the passenger's bus number
            passengers[*numPassengers].busNumber = busNumber;
            // Update available seats
            buses[busIndex].availableSeats--;
            // Record the booking in the booking history
            bookingHistory[*numBookings].busNumber = busNumber;
            strcpy(bookingHistory[*numBookings].passengerName, passengers[*numPassengers].name);
            bookingHistory[*numBookings].seatNumber = desiredSeat;

            printf("Ticket booked successfully for Person %d! (Seat %d)\n", j + 1, desiredSeat);

            // Print the receipt for this booking
            printf("-------- Booking Receipt --------\n");
            printf("Customer Name: %s\n", passengers[*numPassengers].name);
            printf("Seat Number: %d\n", desiredSeat);
            printf("Bus Number: %d\n", busNumber);
            printf("Total Fare: $%.2f\n", buses[busIndex].fare);
            printf("------------------------------\n");

            (*numPassengers)++;
            (*numBookings)++;
            j++;
        }
    }
}
// Function to display booking history
void displayBookingHistory(struct Booking bookingHistory[], int numBookings) {
    printf("\n=== Booking History ===\n");
    printf("Bus Number | Passenger Name | Seat Number\n");
    printf("----------------------------------------\n");

    int i = 0;
    while (i < numBookings) {
        printf("%-10d | %-14s | %-11d\n",
            bookingHistory[i].busNumber, bookingHistory[i].passengerName, bookingHistory[i].seatNumber);
        i++;
    }
}

// Function to cancel a ticket
void cancelTicket(struct Bus buses[], int numBuses, struct Passenger passengers[], int* numPassengers, struct Booking bookingHistory[], int* numBookings, int userId) {
    printf("\nEnter Passenger Name: ");
    char name[50];
    scanf("%s", name);

    int found = 0;
    int i = 0;
    while (i < *numPassengers) {
        if (strcmp(passengers[i].name, name) == 0) {
            // Update available seats for the corresponding bus
            int busIndex = -1;
            int j = 0;
            while (j < numBuses) {
                if (buses[j].busNumber == passengers[i].busNumber) {
                    busIndex = j;
                    break;
                }
                j++;
            }
            if (busIndex != -1) {
                buses[busIndex].availableSeats++;
            }
            // Remove the canceled booking from booking history
            int k = i;
            while (k < *numPassengers - 1) {
                passengers[k] = passengers[k + 1];
                k++;
            }
            (*numPassengers)--;
            // Remove the canceled booking from booking history
            int bookingIndex = -1;
            j = 0;
            while (j < *numBookings) {
                if (bookingHistory[j].busNumber == passengers[i].busNumber &&
                    strcmp(bookingHistory[j].passengerName, name) == 0) {
                    bookingIndex = j;
                    break;
                }
                j++;
            }
            if (bookingIndex != -1) {
                k = bookingIndex;
                while (k < *numBookings - 1) {
                    bookingHistory[k] = bookingHistory[k + 1];
                    k++;
                }
                (*numBookings)--;
            }

            found = 1;
            printf("Ticket canceled successfully!\n");
            break;
        }
        i++;
    }
    if (!found) {
        printf("Passenger with name %s not found.\n", name);
    }
}
// Function to display bus schedule and status
void displayBusScheduleAndStatus(struct Schedule schedule[], struct Bus buses[], int numBuses) {
    printf("\n=== Bus Schedule and Status ===\n");
    printf("Bus Number | Source\t| Destination\t| Departure Time | Total Seats | Available Seats | Fare\n");
    printf("-----------------------------------------------------------------------------------------------------\n");

    int i = 0;
    while (i < numBuses) {
        printf("%-10d | %-10s | %-13s | %-14s | %-11d | %-15d | %-5.2f\n",
            buses[i].busNumber, buses[i].source, buses[i].destination,
            schedule[i].departureTime, buses[i].totalSeats, buses[i].availableSeats, buses[i].fare);
        i++;
    }
}
// Function to display the bus seat arrangement
void displaySeatArrangement() {
    int columns = 4;
    int rows = 44 / columns; // Calculate the number of rows

    printf("=== Seat Arrangement ===\n");

    int i;
    for (i = 1; i <= rows; i++) {
        printf("| Row %2d:| ", i);

        int j;
        for (j = 0; j < columns; j++) {
            int seat_number = i + (j * rows);

            // Print an extra space after the second column
            if (j == 2) {
                printf("  ");
            }

            printf("%2d ", seat_number);
        }

        printf("\n");
    }
}
// Function to save bus information to a file
void saveBusData(struct Bus buses[], int numBuses) {
    FILE *file = fopen("bus_data.txt", "w");
    if (file != NULL) {
    	int i;
        for ( i = 0; i < numBuses; ++i) {
            fprintf(file, "%d,%s,%s,%d,%d,%.2f\n",
                    buses[i].busNumber, buses[i].source, buses[i].destination,
                    buses[i].totalSeats, buses[i].availableSeats, buses[i].fare);
        }
        fclose(file);
    } else {
        printf("Error opening file for writing bus data.\n");
    }
}

// Function to load bus information from a file
int loadBusData(struct Bus buses[]) {
    FILE *file = fopen("bus_data.txt", "r");
    if (file != NULL) {
        int i = 0;
        while (fscanf(file, "%d,%[^,],%[^,],%d,%d,%f\n",
                      &buses[i].busNumber, buses[i].source, buses[i].destination,
                      &buses[i].totalSeats, &buses[i].availableSeats, &buses[i].fare) != EOF) {
            i++;
        }
        fclose(file);
        return i; // Return the number of buses loaded
    } else {
        printf("Error opening file for reading bus data. Initializing with default values.\n");
        return 0;
    }
}
// Function to save user data to a file
void saveUserData(struct User users[], int numUsers) {
    FILE *file = fopen("users.txt", "w");
    if (file != NULL) {
    	int i;
        for (i = 0; i < numUsers; ++i) {
            fprintf(file, "%s %s\n", users[i].username, users[i].password);
        }
        fclose(file);
    } else {
        printf("Error opening file for saving user data.\n");
    }
}

// Function to load user data from a file
int loadUserData(struct User users[]) {
    FILE *file = fopen("users.txt", "r");
    int numUsers = 0;
    if (file != NULL) {
        while (fscanf(file, "%s %s\n", users[numUsers].username, users[numUsers].password) != EOF) {
            numUsers++;
        }
        fclose(file);
    } else {
        printf("Error opening file for loading user data.\n");
    }
    return numUsers;
}
// Function to save bus schedule to a file
void saveBusSchedule(struct Schedule schedule[], int numSchedules) {
    FILE *file = fopen("bus_schedule.txt", "w");
    if (file != NULL) {
    	int i;
        for (i = 0; i < numSchedules; ++i) {
            fprintf(file, "%d %s %s %s\n", schedule[i].busNumber, schedule[i].source, schedule[i].destination, schedule[i].departureTime);
        }
        fclose(file);
    } else {
        printf("Error opening file for saving bus schedule.\n");
    }
}

// Function to load bus schedule from a file
int loadBusSchedule(struct Schedule schedule[]) {
    FILE *file = fopen("bus_schedule.txt", "r");
    int numSchedules = 0;
    if (file != NULL) {
        while (fscanf(file, "%d %s %s %s\n", &schedule[numSchedules].busNumber, schedule[numSchedules].source, schedule[numSchedules].destination, schedule[numSchedules].departureTime) != EOF) {
            numSchedules++;
        }
        fclose(file);
    } else {
        printf("Error opening file for loading bus schedule.\n");
    }
    return numSchedules;
}
// Function to save passenger data to a file
void savePassengerData(struct Passenger passengers[], int numPassengers) {
    FILE *file = fopen("passengers.txt", "w");
    if (file != NULL) {
    	int i;
        for (i = 0; i < numPassengers; ++i) {
            fprintf(file, "%s %d %d\n", passengers[i].name, passengers[i].seatNumber, passengers[i].busNumber);
        }
        fclose(file);
    } else {
        printf("Error opening file for saving passenger data.\n");
    }
}

// Function to load passenger data from a file
int loadPassengerData(struct Passenger passengers[]) {
    FILE *file = fopen("passengers.txt", "r");
    int numPassengers = 0;
    if (file != NULL) {
        while (fscanf(file, "%s %d %d\n", passengers[numPassengers].name, &passengers[numPassengers].seatNumber, &passengers[numPassengers].busNumber) != EOF) {
            numPassengers++;
        }
        fclose(file);
    } else {
        printf("Error opening file for loading passenger data.\n");
    }
    return numPassengers;
}
// Function to save booking history to a file
void saveBookingHistory(struct Booking bookingHistory[], int numBookings) {
    FILE *file = fopen("booking_history.txt", "w");
    if (file != NULL) {
    	int i;
        for (i = 0; i < numBookings; ++i) {
            fprintf(file, "%d %s %d\n", bookingHistory[i].busNumber, bookingHistory[i].passengerName, bookingHistory[i].seatNumber);
        }
        fclose(file);
    } else {
        printf("Error opening file for saving booking history.\n");
    }
}

// Function to load booking history from a file
int loadBookingHistory(struct Booking bookingHistory[]) {
    FILE *file = fopen("booking_history.txt", "r");
    int numBookings = 0;
    if (file != NULL) {
        while (fscanf(file, "%d %s %d\n", &bookingHistory[numBookings].busNumber, bookingHistory[numBookings].passengerName, &bookingHistory[numBookings].seatNumber) != EOF) {
            numBookings++;
        }
        fclose(file);
    } else {
        printf("Error opening file for loading booking history.\n");
    }
    return numBookings;
}
// Function prototypes
void displayMainMenu();
void displayUserMenu();
int loginUser(struct User users[], int numUsers, char username[], char password[]);
void bookTicket(struct Bus buses[], int numBuses, struct Passenger passengers[], int* numPassengers, struct Booking bookingHistory[], int* numBookings, int userId);

int main() {
    // Initialize user data
    struct User users[5] = {
        { "agent1", "Cap*1" }, { "agent2", "Cap*2" }, { "agent3", "Cap*3" }, { "agent4", "Cap*4" },
        { "agent5", "Cap*5" },
    };
    int numUsers = 5;

    // Initialize bus data
    struct Bus buses[4] = {
        { 1, "Nairobi", "Kisumu", 44, 44, 1000.0 },
        { 2, "Nairobi", "Mombasa", 44, 44, 1000.0 },
        { 3, "Nairobi", "Garissa", 44, 44, 1500.0 },
		{ 4, "Nairobi", "Kitale", 44, 44, 1500.0 },
    };
    int numBuses = 4;

    // Initialize bus schedule data
    struct Schedule schedule[4] = {
        { 1, "Nairobi", "Kisumu", "09:00 AM" },
        { 2, "Nairobi", "Mombasa", "09:30 AM" },
        { 3, "Nairobi", "Garissa", "10:00 AM" },
   		{ 4, "Nairobi", "Kitale", "10:30 AM" },
    };
    struct Passenger passengers[500];
    int numPassengers = 0;

    struct Booking bookingHistory[1000];
    int numBookings = 0;

    int loggedInUserId = -1;

    // Load necessary data from files at the beginning of the program
    numUsers = loadUserData(users);
    numBuses = loadBusData(buses);
    numPassengers = loadPassengerData(passengers);
    numBookings = loadBookingHistory(bookingHistory);


    while (1) {
        if (loggedInUserId == -1) {
            displayMainMenu();
            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
                char username[50];
                char password[50];

                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Password: ");
                scanf("%s", password);

                loggedInUserId = loginUser(users, numUsers, username, password);
                if (loggedInUserId == -1) {
                    printf("Login failed. Please check your username and password.\n");
                } else {
                    printf("Login successful. Welcome, %s!\n", username);
                }
                // Display Bus Schedule and Status after login
                displayBusScheduleAndStatus(schedule, buses, numBuses);
                // Display the Seat Arrangement table
                displaySeatArrangement();
            } else if (choice == 2) {
             // Save data before exiting
                saveUserData(users, numUsers);
                saveBusData(buses, numBuses);
                savePassengerData(passengers, numPassengers);
                saveBookingHistory(bookingHistory, numBookings);
                printf("Exiting the program.\n");
                break;
            } else {
                printf("Invalid choice. Please try again.\n");
            }
        } else {
            displayUserMenu();
            int userChoice;
            scanf("%d", &userChoice);

            switch (userChoice) {
                case 1:
                    bookTicket(buses, numBuses, passengers, &numPassengers, bookingHistory, &numBookings, loggedInUserId);
                    break;
                case 2:
                    cancelTicket(buses, numBuses, passengers, &numPassengers, bookingHistory, &numBookings, loggedInUserId);
                    break;
                case 3:
                    displayBusScheduleAndStatus(schedule, buses, numBuses);
                    break;
                case 4:
                    displayBookingHistory(bookingHistory, numBookings);
                    break;
                case 5:
                    printf("Logging out.\n");
                    loggedInUserId = -1;
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    }
 
    return 0;
}