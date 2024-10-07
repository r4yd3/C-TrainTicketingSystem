#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#pragma warning(disable:4996)

// Define structure for storing information
typedef struct {
    int min, hour, day, month, year;
} Time;
typedef struct {
    bool paidStatus;
    Time purchaseTime;
    double totalPrice;
} paymentInfo;
typedef struct {
    char ticketID[10];
    int seatNum;
    char sectorCode;
    char trainID[5];
    paymentInfo payInfo;
    char dpStation[20], arrStation[20];
    Time dpDate;
} TicketInfo;
typedef struct {
    char userID[9];
    char password[21];
    char name[51];
    char gender;
    char contactNo[13];
    char bookTicketID[20][10];
} Member;
typedef struct {
    char staffID[10];
    char name[40];
    char position[20];
    char department[21];
    char gender;
    char password[20];
    char email[50];
    char phoneNo[12];
    char ic[11];
}Staff;
typedef struct {
	char stationName[20];
	Time arrTime;
	Time dpTime;
}Station;
typedef struct {
	char trainID[5];
	int lineNo;
	Station stationStop[7];
}TrainInfo;
typedef struct {
	char lineName[20];
	int lineNo, linePrice;
	char stationName[5][20];
}TrainLine;
// =========================================== Member
void userMain();
void memberMenu(Member* memberInfo, int numMembers); // Display member menu
void displayBookingHistory(Member* currentMember, int numMembers); // Display booking history of the current member
void displayUserProfile(Member* currentMember, int numMembers); // Display profile of the current member
void editUserProfile(Member* memberInfo, int index); // Edit profile of the current member
void memberLogin(Member* memberInfo, int numMembers); // Login for member
void AllMenu(Member* memberInfo, int numMembers);
// =========================================== Staff
void staffMain();
void staff(Staff(*stf)[20]);
int writeStaff(Staff(*stf)[20]);
int modifyStaff(Staff(*stf)[20]);
int displayStaff(Staff(*stf)[20]);
int searchStaff(Staff(*stf)[20]);
int deleteStaff(Staff(*stf)[20]);
int sortStaff(Staff(*stf)[20]);
int user(Member(*memberInfo)[20]);
int modifyMem(Member(*memberInfo)[20]); // Under member module but access by staff only
int displayMem(Member(*memberInfo)[20]);
int searchUser(Member(*memberInfo)[20]);
int deleteUser(Member(*memberInfo)[20]);
void addUser(Member(*memberInfo)[20]);
//============================================ Ticket Booking
void TBMain(char(*ptrTicketIDCart)[10][10]);
void TBfindTickets(Member(*memberInfo)[20], TrainInfo trains[6], TicketInfo(*tickets)[40], TrainLine trainLine[3], char(*ptrTicketIDCart)[10][10]);
void TBsearchTrain(Member(*memberInfo)[20], int temp, TrainInfo trains[6], TicketInfo(*tickets)[40], TrainLine trainLine[4], char(*ptrTicketIDCart)[10][10]);
void TBDisplayTicketID(TicketInfo tickets[40], char(*ptrTicketIDCart)[10][10]);
void TBEditTicketID(TrainLine trainLine[3], TicketInfo(*tickets)[40], char(*ptrTicketIDCart)[10][10]);
void TBBuy(Member(*memberInfo)[20], int isDoubleTicket, char arrDpStation[2][20], char tempTrainID[5], TrainInfo trains[6], TicketInfo(*ticketS)[40], TrainLine trainLine[4], char(*ptrTicketIDCart)[10][10]);
void TBPayment(Member(*memberInfo)[20], TrainLine trainLine[4], TicketInfo(*tickets)[40], char(*ptrTicketIDCart)[10][10]);
//============================================= Schedule
int scheduleMenu();
int displaySchedule(TrainInfo(*trainSchedule)[6], TrainLine(*trainLinePtr)[3]);
int searchSchedule(TrainInfo(*trainSchedule)[6], TrainLine(*trainLinePtr)[3]);
void report(TrainInfo* trains, TrainLine* trainLines);
int modifyScheduleMenu(TrainInfo* trains, TrainLine* trainLines);
int insertSchedule(TrainInfo* trains, TrainLine(*trainLinePtr)[3]);
int updateSchedule(TrainInfo* trains, TrainLine(*trainLinePtr)[3]);
int deleteSchedule(TrainInfo* trains, TrainLine(*trainLinePtr)[3]);
int seatAvailability(TrainInfo(*trains)[6], TrainLine(*trainLine)[3]);
void displaySeatMap(char sectorCode);
// Global variables
int totalStaff = 1, noOfStaff = 0, totalMem = 20, noOfMem = 0;
int indexMem = -1;
char userType = '\0'; char inputUserID[9];
void main() {
    userMain();
}
// ==================================================================================== Member ======================================================================================================================
void userMain() {
	//Member memberInfo[4] = {
	//	 {"2020-MCD","itskamarulm", "Kamarul Muhammad", 'M', "0111234567", {"101B3030", "102B5445"}},
	//	 {"2020-MJK", "kelloggsyum", "Kelly Sim", 'F', "0127654321", {""}},
	//	 {"2020-MMN", "kmljc8988", "Kamala J Chopra",'F', "0193274962",{""}},
	//	 {"2020-MUV", "sisisiti9441", "Siti Nurhaliza Tarudin", 'F', "0115263279", {""}}
	// };
	// FILE* fwb;
	// if ((fwb = fopen("memberInfo.bin", "wb")) != NULL) {
	//     size_t elementsWritten = fwrite(memberInfo, sizeof(Member), 4, fwb);

	//     // Check if all elements were written successfully
	//     if (elementsWritten == 4) {
	//         printf("Data written successfully to file.\n");
	//     }
	//     else {
	//         printf("Error writing data to file.\n");
	//     }
	//     fclose(fwb);

	// }
	// else {
	//     printf("Error reading from file!\n");
	//     exit(1);
	// }

	Member memberInfo[20] = { "" };
	FILE* frb;
	if ((frb = fopen("memberInfo.bin", "rb")) != NULL) {
		fread(&memberInfo, sizeof(Member), totalMem, frb);
		fclose(frb);
	}
	else {
		printf("Error reading from file!\n");
		exit(1);
	}
	totalMem = 0;
	for (int i = 0; i < 20; i++) {
		
		if (strcmp(memberInfo[i].userID, "") == 0 || memberInfo[i].userID == NULL) {
			break;
		}totalMem++;
	};
	 
  
    // Prompt user to choose between staff and member login
	do {
		printf("\nAre you staff or member (S-Staff, M-Member, X-Exit): ");
		rewind(stdin);
		scanf("%c", &userType);
		rewind(stdin);

		// Redirect to appropriate login function based on user type
		if (toupper(userType) == 'M') {
			system("cls"); // Clear screen
			memberLogin(memberInfo, totalMem);
		}
		else if (toupper(userType) == 'S') {
			staffMain();
		}
		else if (toupper(userType) == 'X') {
			exit(0);
		}
		else {
			printf("\nInvalid user type, please re-enter.\n");
			userType = '\0';
		}
	} while (userType == '\0');
}
void memberLogin(Member* memberInfo, int numMembers) {
    
    char inputPassword[21];

    printf("\nMEMBER LOGIN PAGE\n");

    int found = 0;
    

    do {
        printf("\nEnter userID (X to previous page) : ");
        scanf(" %8[^\n]", inputUserID); // Limiting to 8 characters for memberID
        rewind(stdin);

        // Validate userID format (4 digits, a dash, and 3 random alphabets (eg. 2020-MCD)
		if (toupper(inputUserID[0]) != 'X') {
			while (strlen(inputUserID) != 8 || !isdigit(inputUserID[0]) || !isdigit(inputUserID[1]) || !isdigit(inputUserID[2]) || !isdigit(inputUserID[3]) ||
				inputUserID[4] != '-' || !isupper(inputUserID[5]) || !isupper(inputUserID[6]) || !isupper(inputUserID[7])) {
				printf("\nUserID should not exceed 8 characters and match the format 'YYYY-XXX'. Please re-enter: ");
				scanf(" %8[^\n]", inputUserID);
				rewind(stdin);
				if (toupper(inputUserID[0]) == 'X') {
					break; system("cls"); main();
				}
			}
		}
		else {
			system("cls"); main();
		}

        printf("\nEnter password: ");
        scanf(" %[^\n]", inputPassword);
        rewind(stdin);

        // Check if input credentials match any member's credentials
        for (int i = 0; i < numMembers; i++) { // Loop through the memberInfo array
            if (strcmp(inputUserID, memberInfo[i].userID) == 0 && strcmp(inputPassword, memberInfo[i].password) == 0) {
                // Copy member information to currentMember for session
                indexMem = i; // Store the index of the current member
                found = 1;
                break;
            }
        }

        // If credentials not found, prompt for re-entry
        if (!found) {
            printf("\nUserID or Password does not match, kindly re-enter. (Passwords should not exceed 20 characters)\n");
        }
    } while (!found);

    if (found && indexMem != -1) { // If login successful and index is valid
        system("cls");
        AllMenu(memberInfo, indexMem);
        editUserProfile(memberInfo, indexMem); // Pass index to editUserProfile function
    }
}
void AllMenu(Member* memberInfo, int numMembers) {
	int option; static char ticketIDCart[10][10] = {""};
	system("cls");
	printf("\nWelcome, %s !\n", memberInfo[numMembers].name);
    do {
        printf("\nMain Menu\n\n");
        printf("1 - Schedule Menu\n");
        printf("2 - Ticket Booking Menu\n");
        printf("3 - Member Menu\n");
        printf("4 - Logout\n\n");
		printf(": ");
        scanf("%d", &option);
        rewind(stdin);

        // Execute chosen option
        switch (option) {
        case 1:
			scheduleMenu();
            system("cls"); // Clear screen

            break;
        case 2:
			TBMain(&ticketIDCart);
            system("cls"); // Clear screen

            break;
        case 3:
            system("cls"); // Clear screen
            memberMenu(memberInfo, numMembers);
            break;
        case 4:
			system("cls"); main(); // Clear screen

            break;
        default:
            printf("Invalid option. Please re-enter:\n"); // Display error message
            break;
        }
    } while (option != 5);
}
void memberMenu(Member* memberInfo, int numMembers) {
	system("cls");
    int option;
	printf("\nMember Menu\n\n");
	printf("1 - View Booking History\n");
	printf("2 - Display My Profile\n");
	printf("3 - Edit My Profile\n");
	printf("4 - Previous Menu\n\n");
	printf(": ");
    do {
       
        scanf("%d", &option);
        rewind(stdin);

        // Execute chosen option
        switch (option) {
        case 1:
            system("cls"); // Clear screen
            displayBookingHistory(memberInfo, numMembers);
            break;
        case 2:
            system("cls"); // Clear screen
            displayUserProfile(memberInfo, numMembers);
            break;
        case 3:
            system("cls"); // Clear screen
            editUserProfile(memberInfo, numMembers); // Assuming index 0 for editing profile
            break;
        case 4:
			AllMenu(memberInfo, numMembers); break;
        default:
			printf("Invalid option. Please re-enter: "); option = 0; // Display error message
            break;
        }
    } while (option != 5);
}
void displayBookingHistory(Member* currentMember, int numMembers) {
    // Read tickets file
    TicketInfo tickets[40] = { "" };
    FILE* ticketsFile;
    char tempPaidStatus[7] = "";
    if ((ticketsFile = fopen("tickets.txt", "r+")) == NULL) {
        printf("Error. Can't open file!"); exit(-1);
    }
    else {
        for (int i = 0; i < 40 || !feof(ticketsFile); i++) {
            int numRead = fscanf(ticketsFile, "%s %d %c %s | %s (%d/%d/%d) %lf | %[^|]| %[^|]| (%d/%d/%d)\n",
                tickets[i].ticketID, &tickets[i].seatNum, &tickets[i].sectorCode, tickets[i].trainID,
                tempPaidStatus, &tickets[i].payInfo.purchaseTime.day, &tickets[i].payInfo.purchaseTime.month,
                &tickets[i].payInfo.purchaseTime.year, &tickets[i].payInfo.totalPrice, tickets[i].dpStation, tickets[i].arrStation,
                &tickets[i].dpDate.day, &tickets[i].dpDate.month, &tickets[i].dpDate.year);
            if (numRead != 15 && numRead != 14) {
                break;
            }
            if (strcmp(tempPaidStatus, "true") == 0) {
                tickets[i].payInfo.paidStatus = true;
            }
            else if (strcmp(tempPaidStatus, "false") == 0) {
                tickets[i].payInfo.paidStatus = false;
            }
            else {
                printf("\n\nWhoops Error in Paid Status!\n\n");
            }
        }
        fclose(ticketsFile);
    };
    printf("\nALL BOOKING HISTORY:\n\n");
	for (int i = 0; i < 20; i++) {
		char* ticketID = currentMember[numMembers].bookTicketID[i];
		for (int j = 0; j < 40; j++) {
			if (strcmp(ticketID, tickets[j].ticketID) == 0 && strcmp(tickets[j].ticketID, "") != 0) {
				printf("Ticket ID: %s\n", tickets[j].ticketID);
				printf("Seat Number: %d\n", tickets[j].seatNum);
				printf("Sector Code: %c\n", tickets[j].sectorCode);
				printf("Train ID: %s\n", tickets[j].trainID);
				printf("Departure Station: %s\n", tickets[j].dpStation);
				printf("Arrival Station: %s\n", tickets[j].arrStation);
				printf("Departure Date: %02d/%02d/%d\n", tickets[j].dpDate.day, tickets[j].dpDate.month, tickets[j].dpDate.year);
				printf("\n");
				break;
			}
		}
	}
       
    

    printf("Press any to return to the main menu: ");
    char choice;
    scanf("%c", &choice);
    rewind(stdin);
	system("cls"); memberMenu(currentMember, numMembers);
}
void displayUserProfile(Member* currentMember, int numMembers) {
    printf("\nMY USER PROFILE\n");
    printf("\nUser ID: %s\n", currentMember[numMembers].userID);
    printf("Password: %s\n", currentMember[numMembers].password);
    printf("Name: %s\n", currentMember[numMembers].name);
    printf("Gender: %c\n", currentMember[numMembers].gender);
    printf("Contact Number: %s\n", currentMember[numMembers].contactNo);
    printf("\nPress any to return to the main menu: ");
    char choice;
    scanf(" %c", &choice);
    rewind(stdin);
	system("cls"); memberMenu(currentMember, numMembers);
}
void editUserProfile(Member* memberInfo, int index) {
    system("cls"); // Clear screen

    printf("EDIT USER PROFILE\n");
    int option = 0;
    do {
        printf("\nChoose a field to update:\n");
        printf("1. Name\n");
        printf("2. Password\n");
        printf("3. Gender\n");
        printf("4. Contact Number\n");
        printf("5. Return to Main Menu\n\n");
		printf(":");
        scanf("%d", &option);
        rewind(stdin);

        // Update chosen field
        if (option == 1 || option == 2 || option == 3 || option == 4 || option == 5)
        {
            switch (option) {
            case 1:
                printf("Current Name: %s\n", memberInfo[index].name); // Display current name
                printf("Enter new name (or type 'C' to cancel, 'R' to return to main menu): ");
                char newName[51];
                fgets(newName, sizeof(newName), stdin);
                newName[strcspn(newName, "\n")] = '\0'; // Remove newline character
                if (toupper(newName[0]) == 'C') {
                    printf("Update canceled.\n");
                    break;
                }
                else if (toupper(newName[0]) == 'R') {
                    return; // Return to main menu
                }
                strcpy(memberInfo[index].name, newName); // Update memberInfo using index
                printf("Name updated successfully.\n");
                break;
            case 2:
                printf("Current Password: %s\n", memberInfo[index].password); // Display current password
                printf("Enter new password (or type 'C' to cancel, 'R' to return to main menu): ");
                char newPassword[21];
                fgets(newPassword, sizeof(newPassword), stdin);
                newPassword[strcspn(newPassword, "\n")] = '\0'; // Remove newline character
                if (toupper(newPassword[0]) == 'C') {
                    printf("Update canceled.\n");
                    break;
                }
                else if (toupper(newPassword[0]) == 'R') {
                    return; // Return to main menu
                }
                strcpy(memberInfo[index].password, newPassword); // Update memberInfo using index
                printf("Password updated successfully.\n");
                break;
            case 3:
                printf("Current Gender: %c\n", memberInfo[index].gender); // Display current gender
                printf("Enter new gender (M/F or type 'C' to cancel, 'R' to return to main menu): ");
                char newGender;
                scanf(" %c", &newGender);
                rewind(stdin);
                if (toupper(newGender) == 'C') {
                    printf("Update canceled.\n");
                    break;
                }
                else if (toupper(newGender) == 'R') {
                    return; // Return to main menu
                }
                memberInfo[index].gender = newGender; // Update memberInfo using index
                printf("Gender updated successfully.\n");
                break;
            case 4:
                printf("Current Contact Number: %s\n", memberInfo[index].contactNo); // Display current contact number
                printf("Enter new contact number (or type 'C' to cancel, 'R' to return to main menu): ");
                char newContactNo[13];
                fgets(newContactNo, sizeof(newContactNo), stdin);
                newContactNo[strcspn(newContactNo, "\n")] = '\0'; // Remove newline character
                if (toupper(newContactNo[0]) == 'C') {
                    printf("Update canceled.\n");
                    break;
                }
                else if (toupper(newContactNo[0]) == 'R') {
                    return; // Return to main menu
                }
                strcpy(memberInfo[index].contactNo, newContactNo); // Update memberInfo using index
                printf("Contact number updated successfully.\n");
                break;
            case 5:
                printf("Exiting profile update.\n");
                system("cls"); // Clear screen before returning to main menu
                return; // Return to main menu
            default:
                printf("Invalid option. Please try again.\n");
            }
            FILE* fwb;
            if ((fwb = fopen("memberInfo.bin", "wb")) != NULL) {
                fwrite(memberInfo, sizeof(Member), 20, fwb);
                fclose(fwb);
            }
            else {
                printf("Error writing to file\n");
                exit(1);
            }
        }
        else {
            printf("Invalid option. Please try again.\n");
        }
    } while (option != 5);

    // Write updated memberInfo array back to the binary file
   
}
// ==================================================================================== Staff ======================================================================================================================
void staffMain() {
	system("cls");
	Staff stf[20] = { "" };
	int mainValid, activeUser = 0;
	char idValid[10], passwordValid[15], idCompare[10], passCompare[20], validIdCheck = 1, validPassCheck = 1;
	FILE* ptr;
	if ((ptr = fopen("staffFile.bin", "rb")) != NULL) {
		fread(&stf, sizeof(Staff), 20, ptr);
		fclose(ptr);

	}
	else {
		printf("error opening file");
	}

	// ======================= Writing ==============================
	//FILE* ptr;
	//if ((ptr = fopen("staffFile.bin", "wb")) != NULL) {
	//	// Value declaration, manager
	//	strcpy(stf[0].staffID, "2020-M201");
	//	strcpy(stf[0].name, "Ernest Yip");
	//	strcpy(stf[0].position, "Manager");
	//	strcpy(stf[0].department, "Human Resources");
	//	stf[0].gender = 'M';
	//	strcpy(stf[0].password, "iamernest");
	//	strcpy(stf[0].email, "ernestywk@gmail.com");
	//	strcpy(stf[0].phoneNo, "01111111111");
	//	strcpy(stf[0].ic, "0503070832");

	//	fwrite(&stf[0], sizeof(Staff), 1, ptr);

	//	//2nd Values, normal staff
	//	strcpy(stf[1].staffID, "2021-S029");
	//	strcpy(stf[1].name, "Chuu Chuu");
	//	strcpy(stf[1].position, "Staff");
	//	strcpy(stf[1].department, "Operatons");
	//	stf[1].gender = 'F';
	//	strcpy(stf[1].password, "chuuchuutrain");
	//	strcpy(stf[1].email, "shorty@gmail.com");
	//	strcpy(stf[1].phoneNo, "0122211111");
	//	strcpy(stf[1].ic, "0501381920");

	//	fwrite(&stf[1], sizeof(Staff), 1, ptr);

	//	// Close the file after writing

	//	fclose(ptr);

		//}
		//else {
		//	printf("error opening file");
		//}

		// ======================================================

	Member memberInfo[20] = {""};
	FILE* frb;
	if ((frb = fopen("memberInfo.bin", "rb")) != NULL) {
		fread(&memberInfo, sizeof(Member), totalMem, frb);
		fclose(frb);
	}
	else {
		printf("Error reading from file!\n");
		exit(1);
	}
	totalMem = 0;
	for (int i = 0; i < 20; i++) {
		if (strcmp(memberInfo[i].userID, "") == 0 || memberInfo[i].userID == NULL) {
			break;
		}totalMem++;
	};
	static int logStatus = 0;
	if(logStatus == 0){
		logStatus++;

		printf("||||||||||||||||||||||||||||||||||||||||\n");
		printf("||||                                ||||\n");
		printf("||||  Welcome to the staff system!  ||||\n");
		printf("||||                                ||||\n");
		printf("||||||||||||||||||||||||||||||||||||||||\n");

		// Staff ID input
		do {
			printf("\n\nPlease enter your staff ID (X to go back) : ");
			scanf("%s", idCompare);
			rewind(stdin);

			for (int x = 0; x <= totalStaff; x++) {
				if (strcmp(idCompare, stf[x].staffID) == 0) {
					printf("\nID Found!");
					validIdCheck = 0;
					activeUser = x;
					break;
				}
			}
			if (strcmp(idCompare, "X") == 0 || strcmp(idCompare, "x") == 0) {
				system("cls"); main();
			}
			if (validIdCheck == 1) {
				printf("\nStaff ID not found!");
			}

		} while (validIdCheck == 1);

		// Password input
		do {
			printf("\n\nPlease enter your password: ");
			scanf("%s", passCompare);
			rewind(stdin);

			if (strcmp(passCompare, stf[activeUser].password) == 0) {
				printf("\nPassword Found!");
				validPassCheck = 0;
				break;
			}

			if (validPassCheck == 1) {
				printf("\nPassword not found!");
			}
		} while (validPassCheck == 1);

	}

	//Check if user is Manager or regular staff

	char* pos = strchr(stf[activeUser].staffID, 'M');

	//Manager (can edit staff)
	char ptrCart[10][10]; // Placeholder for tbmain
	system("cls");
	if (pos != NULL) {
		printf("\n\nHello %s!", stf[activeUser].name);

		do {
			printf("\n\nWhat would you like to do?");
			printf("\n1. View your data.");
			printf("\n2. Manage Staff Profiles.");
			printf("\n3. Manage User Profiles.");
			printf("\n4. Manage Ticket Booking.");
			printf("\n5. Manage Train Schedule.");
			printf("\n6. Logout.");
			printf("\n\nEnter your choice (1-6): ");
			scanf("%d", &mainValid);

			if (mainValid < 1 || mainValid > 6) {
				printf("\nInvalid input. Please enter a number between 1 and 5.");
			}
			else if (mainValid == 1) {
				system("cls");
				printf("Here is your information:\n");
				printf("\nName       : %s", stf[activeUser].name);
				printf("\nStaff ID   : %s", stf[activeUser].staffID);
				printf("\nGender     : %c", stf[activeUser].gender);
				printf("\nIC No      : %s", stf[activeUser].ic);
				printf("\nEmail      : %s", stf[activeUser].email);
				printf("\nPhone No   : %s", stf[activeUser].phoneNo);
				printf("\nDepartment : %s", stf[activeUser].department);
				printf("\nPosition   : %s\n", stf[activeUser].position);
			}
			else if (mainValid == 2)
				staff(&stf, totalStaff, noOfStaff);
			else if (mainValid == 3)
				user(&memberInfo, totalMem, noOfMem);
			else if (mainValid == 4)
				TBMain(&ptrCart);
			else if (mainValid == 5)
				scheduleMenu();
			else
				logStatus--;  system("cls"); main();
		} while (mainValid < 2 || mainValid > 6);
	}

	//Staff table (only edit members)

	pos = strchr(stf[activeUser].staffID, 'S');
	if (pos != NULL) {
		printf("\n\nHello %s!", stf[activeUser].name);

		do {
			printf("\n\nWhat would you like to do?");
			printf("\n1. View your data.");
			printf("\n2. Manage User Profiles.");
			printf("\n3. Logout.");
			printf("\n\nEnter your choice (1-3): ");
			scanf("%d", &mainValid);

			if (mainValid < 1 || mainValid > 3) {
				printf("\nInvalid input. Please enter a number between 1 and 3.");
			}
			else if (mainValid == 1) {
				system("cls");
				printf("Here is your information:\n");
				printf("\nName       : %s", stf[activeUser].name);
				printf("\nStaff ID   : %s", stf[activeUser].staffID);
				printf("\nGender     : %c", stf[activeUser].gender);
				printf("\nIC No      : %s", stf[activeUser].ic);
				printf("\nEmail      : %s", stf[activeUser].email);
				printf("\nPhone No   : %s", stf[activeUser].phoneNo);
				printf("\nDepartment : %s", stf[activeUser].department);
				printf("\nPosition   : %s\n", stf[activeUser].position);
			}
			else if (mainValid == 2) {
				user(&memberInfo, totalMem, noOfMem);
			}
			else
				logStatus--; main();
		} while (mainValid < 2 || mainValid > 3);
	}

}
void staff(Staff(*stf)[20]) {
	int menuValid;
	system("cls");

	do {
		printf("Staff System");
		printf("\n------------");
		printf("\n1. Add new staff data.");
		printf("\n2. Modify existing staff data.");
		printf("\n3. Display staff data.");
		printf("\n4. Search for staff data.");
		printf("\n5. Delete staff data.");
		printf("\n6. Sort staff data.");
		printf("\n7. Return to previous menu.");
		printf("\n\nEnter your choice (1-7): ");
		scanf("%d", &menuValid);

		if (menuValid < 1 || menuValid > 7)
			printf("\nInvalid input. Please enter a number between 1 and 7.\n\n");
		else if (menuValid == 1) {
			writeStaff(stf, totalStaff, noOfStaff);
		}
		else if (menuValid == 2)
			modifyStaff(stf, totalStaff, noOfStaff);
		else if (menuValid == 3)
			displayStaff(stf, totalStaff, noOfStaff);
		else if (menuValid == 4)
			searchStaff(stf, totalStaff, noOfStaff);
		else if (menuValid == 5)
			deleteStaff(stf, totalStaff, noOfStaff);
		else if (menuValid == 6)
			sortStaff(stf, totalStaff, noOfStaff);
		else
			staffMain();
	} while (menuValid < 1 || menuValid > 7);
}
int writeStaff(Staff(*stf)[20]) {
	FILE* ptr;
	if ((ptr = fopen("staffFile.bin", "ab")) != NULL) {


		int currentAmount = 0;
		system("cls");

		do {
			printf("How many staff would you like to enter (Enter 0 to go back): ");
			scanf("%d", &noOfStaff);
			rewind(stdin);

			if (noOfStaff == 0)
				staff(stf, totalStaff, noOfStaff);
			else if (noOfStaff >= 1)
				break;
			else if (noOfStaff < 0)
				printf("\n\nPlease enter a valid number!\n");
		} while (noOfStaff != 0);

		for (int x = totalStaff + 1; currentAmount < noOfStaff; x++) {
			printf("\nPlease enter the name of the staff : ");
			scanf("%[^\n]", (*stf)[x].name);
			rewind(stdin);

			do {
				printf("\nPlease enter the staff ID : ");
				scanf("%s", (*stf)[x].staffID);
				rewind(stdin);

				char* pos = strchr((*stf)[x].staffID, 'M');
				if (pos != NULL) {
					strcpy((*stf)[x].position, "Manager");
					break;
				}
				pos = strchr((*stf)[x].staffID, 'S');
				if (pos != NULL) {
					strcpy((*stf)[x].position, "Staff");
					break;
				}
				printf("Invalid staff ID format. Please include 'M' for manager or 'S' for regular staff.\n");
			} while (1);

			do {
				printf("\nPlease enter the gender of the staff : ");
				scanf(" %c", &(*stf)[x].gender);
				rewind(stdin);

				if (toupper((*stf)[x].gender) == 'M' || toupper((*stf)[x].gender) == 'F') {
					break;
				}
				else {
					printf("Invalid gender.\n");
				}
			} while (1);

			printf("\nPlease enter the IC number of the staff : ");
			scanf("%s", (*stf)[x].ic);
			rewind(stdin);

			printf("\nPlease enter the email of the staff : ");
			scanf("%s", (*stf)[x].email);
			rewind(stdin);

			printf("\nPlease enter the phone number of the staff : ");
			scanf("%s", (*stf)[x].phoneNo);
			rewind(stdin);

			do {
				printf("\nPlease enter the department of the staff");
				printf("\n(Operations/Cust Service/Maintenance/Human Resources) :");
				scanf("%[^\n]", (*stf)[x].department);
				rewind(stdin);

				if (strcmp((*stf)[x].department, "Operations") == 0 ||
					strcmp((*stf)[x].department, "Cust Service") == 0 ||
					strcmp((*stf)[x].department, "Maintenance") == 0 ||
					strcmp((*stf)[x].department, "Human Resources") == 0) {
					break;
				}
				else {
					printf("Invalid department. Please enter one of the specified departments.\n");
				}
			} while (1);

			printf("\nPlease enter the staff's password : ");
			scanf("%[^\n]", (*stf)[x].password);
			rewind(stdin);

			printf("\n\n");
			fwrite(&(*stf)[x], sizeof(Staff), 1, ptr);

			currentAmount++;
		}

		fclose(ptr);
		totalStaff = totalStaff + noOfStaff;
		staff(stf, totalStaff, noOfStaff);
	}
	else {
		printf("\nError opening file");
	}
}
int modifyStaff(Staff(*stf)[20]) {
	FILE* ptr;
	ptr = fopen("staffFile.bin", "wb");
	char idCompare[10];
	int validCheck = 1, currentStaff, menuValid = 0;

	system("cls");

	do {
		printf("Please enter the staff ID of the staff you want to change (Enter 'XXX' to exit) : ");
		scanf("%s", idCompare);
		rewind(stdin);

		for (int x = 0; x <= totalStaff; x++) {
			if (strcmp(idCompare, (*stf)[x].staffID) == 0) {
				printf("\n\nID Found!");
				validCheck = 0;
				currentStaff = x;
				break;
			}
		}

		if (strcmp(idCompare, "XXX") == 0)
			staff(stf, totalStaff, noOfStaff);

		if (validCheck == 1) {
			printf("\nStaff ID not found!\n\n");
		}
	} while (validCheck == 1);

	do {
		printf("\n\n===================================================\n");
		printf("||  Current Staff Name   : %20s  ||\n", (*stf)[currentStaff].name);
		printf("||  Current Staff ID     : %20s  ||\n", (*stf)[currentStaff].staffID);
		printf("||  Current Gender       : %20c  ||\n", (*stf)[currentStaff].gender);
		printf("||  Current IC No        : %20s  ||\n", (*stf)[currentStaff].ic);
		printf("||  Current Email        : %20s  ||\n", (*stf)[currentStaff].email);
		printf("||  Current Phone No     : %20s  ||\n", (*stf)[currentStaff].phoneNo);
		printf("||  Current Department   : %20s  ||\n", (*stf)[currentStaff].department);
		printf("||  Current Position     : %20s  ||\n", (*stf)[currentStaff].position);
		printf("||  Current Password     : %20s  ||\n", (*stf)[currentStaff].password);
		printf("===================================================\n\n");

		printf("What would you like to edit?\n");
		printf("1. Staff Name\n");
		printf("2. Staff ID\n");
		printf("3. Staff Gender\n");
		printf("4. Staff IC No\n");
		printf("5. Staff Email\n");
		printf("6. Staff Phone No\n");
		printf("7. Staff Department\n");
		printf("8. Staff Password\n");
		printf("9. Finish\n");
		printf("\nEnter your choice (To change Staff Position, edit ID) (1-9) : ");
		scanf("%d", &menuValid);

		switch (menuValid) {
		case 1:
			printf("Enter the new name of the employee: ");
			rewind(stdin);
			scanf("%[^\n]", (*stf)[currentStaff].name);
			rewind(stdin);
			break;
		case 2:
			do {
				printf("\nEnter the new staff ID : ");
				scanf("%s", (*stf)[currentStaff].staffID);
				rewind(stdin);

				char* pos = strchr((*stf)[currentStaff].staffID, 'M');
				if (pos != NULL) {
					strcpy((*stf)[currentStaff].position, "Manager");
					break;
				}
				pos = strchr((*stf)[currentStaff].staffID, 'S');
				if (pos != NULL) {
					strcpy((*stf)[currentStaff].position, "Staff");
					break;
				}
				printf("Invalid staff ID format. Please include 'M' for manager or 'S' for regular staff.\n");
			} while (1);
			break;
		case 3:
			do {
				printf("\nEnter the new gender of the staff : ");
				scanf(" %c", &((*stf)[currentStaff].gender));
				rewind(stdin);

				if (toupper((*stf)[currentStaff].gender) == 'M' || toupper((*stf)[currentStaff].gender) == 'F') {
					break;
				}
				else {
					printf("Invalid gender.\n");
				}
			} while (1);
			break;
		case 4:
			printf("\nEnter the new IC number of the staff : ");
			scanf("%s", (*stf)[currentStaff].ic);
			rewind(stdin);
			break;
		case 5:
			printf("\nEnter the new email of the staff : ");
			scanf("%s", (*stf)[currentStaff].email);
			rewind(stdin);
			break;
		case 6:
			printf("\nEnter the new phone number of the staff : ");
			scanf("%s", (*stf)[currentStaff].phoneNo);
			rewind(stdin);
			break;
		case 7:
			do {
				printf("\nEnter the new department of the staff");
				printf("\n(Operations/Cust Service/Maintenance/Human Resources) :");
				scanf("%[^\n]", (*stf)[currentStaff].department);
				rewind(stdin);

				if (strcmp((*stf)[currentStaff].department, "Operations") == 0 ||
					strcmp((*stf)[currentStaff].department, "Cust Service") == 0 ||
					strcmp((*stf)[currentStaff].department, "Maintenance") == 0 ||
					strcmp((*stf)[currentStaff].department, "Human Resources") == 0) {
					break;
				}
				else {
					printf("Invalid department. Please enter one of the specified departments.\n");
				}
			} while (1);
			break;
		case 8:
			printf("\nEnter the new staff's password : ");
			scanf("%[^\n]", (*stf)[currentStaff].password);
			rewind(stdin);
			break;
		case 9:
			break;
		}
		fwrite(((*stf) + currentStaff), sizeof(Staff), 1, ptr);
	} while (menuValid != 9);

	fclose(ptr);
	staff(stf, totalStaff, noOfStaff);
}
int displayStaff(Staff(*stf)[20]) {
	int noStaffPlacehold = 0;
	char exitFunc[10];
	system("cls");

	for (noStaffPlacehold; noStaffPlacehold <= totalStaff; noStaffPlacehold++) {

		(*stf)[noStaffPlacehold].ic[10] = '\0';

		printf("Staff No: %d\n\n", noStaffPlacehold + 1);
		printf("=========================================\n");
		printf("||  Staff Name   : %20s  ||\n", (*stf)[noStaffPlacehold].name);
		printf("||  Staff ID     : %20s  ||\n", (*stf)[noStaffPlacehold].staffID);
		printf("||  Gender       : %20c  ||\n", (*stf)[noStaffPlacehold].gender);
		printf("||  IC No        : %20s  ||\n", (*stf)[noStaffPlacehold].ic);
		printf("||  Email        : %20s  ||\n", (*stf)[noStaffPlacehold].email);
		printf("||  Phone No     : %20s  ||\n", (*stf)[noStaffPlacehold].phoneNo);
		printf("||  Department   : %20s  ||\n", (*stf)[noStaffPlacehold].department);
		printf("||  Position     : %20s  ||\n", (*stf)[noStaffPlacehold].position);
		printf("=========================================\n\n");
	}

	printf("Enter any key when ready to exit: ");
	scanf("%s", exitFunc);
	staff(stf, totalStaff, noOfStaff);
}
int searchStaff(Staff(*stf)[20]) {
	char idCompare[10];
	char exitFunc[10];
	int validCheck = 1, currentStaff, menuValid = 0;

	system("cls");

	do {
		printf("Please enter the staff ID of the staff you want to find : ");
		scanf("%s", idCompare);
		rewind(stdin);

		for (int x = 0; x <= totalStaff; x++) {
			if (strcmp(idCompare, (*stf)[x].staffID) == 0) {
				printf("\n\nID Found!");
				validCheck = 0;
				currentStaff = x;
				break;
			}
		}

		if (validCheck == 1) {
			printf("\nStaff ID not found!\n\n");
		}
	} while (validCheck == 1);

	printf("\n\n=========================================\n");
	printf("||  Staff Name   : %20s  ||\n", (*stf)[currentStaff].name);
	printf("||  Staff ID     : %20s  ||\n", (*stf)[currentStaff].staffID);
	printf("||  Gender       : %20c  ||\n", (*stf)[currentStaff].gender);
	printf("||  IC No        : %20s  ||\n", (*stf)[currentStaff].ic);
	printf("||  Email        : %20s  ||\n", (*stf)[currentStaff].email);
	printf("||  Phone No     : %20s  ||\n", (*stf)[currentStaff].phoneNo);
	printf("||  Department   : %20s  ||\n", (*stf)[currentStaff].department);
	printf("||  Position     : %20s  ||\n", (*stf)[currentStaff].position);
	printf("||  Password     : %20s  ||\n", (*stf)[currentStaff].password);
	printf("===========================================\n\n");

	printf("Enter any key when ready to exit: ");
	scanf("%s", exitFunc);
	staff(stf, totalStaff, noOfStaff);
}
int deleteStaff(Staff(*stf)[20]) {
	FILE* ptr;
	ptr = fopen("staffFile.bin", "wb");
	char idCompare[10];
	char exitFunc[10];
	int validCheck = 1, currentStaff, menuValid = 0;

	system("cls");

	do {
		printf("Please enter the staff ID of the staff you want to delete (Enter 'XXX' to leave) : ");
		scanf("%s", idCompare);
		rewind(stdin);

		for (int x = 0; x <= totalStaff; x++) {
			if (strcmp(idCompare, (*stf)[x].staffID) == 0) {
				printf("\n\nID Found!");
				validCheck = 0;
				currentStaff = x;
				break;
			}
		}

		if (strcmp(idCompare, "XXX") == 0)
			staff(stf, totalStaff, noOfStaff);

		if (validCheck == 1) {
			printf("\nStaff ID not found!\n\n");
		}
	} while (validCheck == 1);

	// Shift elements to fill the gap
	for (int i = currentStaff; i < totalStaff - 1; i++) {
		(*stf)[i] = (*stf)[i + 1];
	}

	// Write the updated records back to the file
	for (int i = 0; i < totalStaff - 1; i++) {
		fwrite(&((*stf)[i]), sizeof(Staff), 1, ptr);
	}

	totalStaff--;

	printf("\nStaff record has been deleted successfully!\n");
	printf("Enter any key when ready to exit: ");
	scanf("%s", exitFunc);
	fclose(ptr);
	staff(stf, totalStaff, noOfStaff);
}
int sortStaff(Staff(*stf)[20]) {
	int i, j;
	char exitFunc[50];
	Staff temp;
	system("cls");

	for (i = 0; i < totalStaff; i++) {
		for (j = 0; j < totalStaff - i; j++) {
			// Extract the year from the staffID
			int year1 = ((*stf)[j].staffID[0] - '0') * 1000 + ((*stf)[j].staffID[1] - '0') * 100 + ((*stf)[j].staffID[2] - '0') * 10 + ((*stf)[j].staffID[3] - '0');
			int year2 = ((*stf)[j + 1].staffID[0] - '0') * 1000 + ((*stf)[j + 1].staffID[1] - '0') * 100 + ((*stf)[j + 1].staffID[2] - '0') * 10 + ((*stf)[j + 1].staffID[3] - '0');

			// Compare the years and swap the staff members if necessary
			if (year1 > year2) {
				temp = (*stf)[j];
				(*stf)[j] = (*stf)[j + 1];
				(*stf)[j + 1] = temp;
			}
		}
	}

	printf("Here is the staff data sorted by year joined:\n");
	for (i = 0; i <= totalStaff; i++) {
		printf("=========================================\n");
		printf("||  Staff Name   : %20s  ||\n", (*stf)[i].name);
		printf("||  Staff ID     : %20s  ||\n", (*stf)[i].staffID);
		printf("||  Gender       : %20c  ||\n", (*stf)[i].gender);
		printf("||  IC No        : %20s  ||\n", (*stf)[i].ic);
		printf("||  Email        : %20s  ||\n", (*stf)[i].email);
		printf("||  Phone No     : %20s  ||\n", (*stf)[i].phoneNo);
		printf("||  Department   : %20s  ||\n", (*stf)[i].department);
		printf("||  Position     : %20s  ||\n", (*stf)[i].position);
		printf("=========================================\n\n");
	}
	printf("Enter any key when ready to exit: ");
	scanf("%s", exitFunc);
	staff(stf, totalStaff, noOfStaff);
}
int user(Member(*memberInfo)[20]) {
	int menuValid;
	system("cls");

	do {
		printf("Member System");
		printf("\n------------");
		printf("\n1. Modify existing member data.");
		printf("\n2. Display member data.");
		printf("\n3. Search for member data.");
		printf("\n4. Delete member data.");
		printf("\n5. Add member data.");
		printf("\n6. Return to previous menu.");
		printf("\n\nEnter your choice (1-6): ");
		scanf("%d", &menuValid);

		if (menuValid < 1 || menuValid > 6)
			printf("\nInvalid input. Please enter a number between 1 and 7.\n\n");
		else if (menuValid == 1)
			modifyMem(memberInfo, totalMem, noOfMem);
		else if (menuValid == 2)
			displayMem(memberInfo, totalMem, noOfMem);
		else if (menuValid == 3)
			searchUser(memberInfo, totalMem, noOfMem);
		else if (menuValid == 4)
			deleteUser(memberInfo, totalMem, noOfMem);
		else if (menuValid == 5)
			addUser(memberInfo);
		else
			staffMain();
	} while (menuValid < 1 || menuValid > 6);

}
int modifyMem(Member(*memberInfo)[20]) {
	char idCompare[10];
	int validCheck = 1, currentMem, menuValid = 0;
	system("cls");
	FILE* ptr;
	if ((ptr = fopen("memberInfo.bin", "wb")) != NULL) {
		do {
			printf("Please enter the member ID of the member you want to change (Enter 'XXX' to exit) : ");
			scanf("%s", idCompare);
			rewind(stdin);

			for (int x = 0; x <= totalMem; x++) {
				if (strcmp(idCompare, (*memberInfo)[x].userID) == 0) {
					printf("\n\nID Found!");
					validCheck = 0;
					currentMem = x;
					break;
				}
			}

			if (strcmp(idCompare, "XXX") == 0) {
				return; // Exit the modifyUser function
			}

			if (validCheck == 1) {
				printf("\nMember ID not found!\n\n");
			}
			else {
				break; // Exit the loop if a valid member ID is found
			}
		} while (validCheck == 1);

		do {
			printf("\n\n===================================================\n");
			printf("||  Current Member Name  : %20s  ||\n", (*memberInfo)[currentMem].name);
			printf("||  Current Member ID    : %20s  ||\n", (*memberInfo)[currentMem].userID);
			printf("||  Current Gender       : %20c  ||\n", (*memberInfo)[currentMem].gender);
			printf("||  Current Contact No   : %20s  ||\n", (*memberInfo)[currentMem].contactNo);
			printf("===================================================\n\n");

			printf("What would you like to edit?\n");
			printf("1. Member Name\n");
			printf("2. Member ID\n");
			printf("3. Member Gender\n");
			printf("4. Member Contact No\n");
			printf("5. Finish\n");
			printf("\nEnter your choice (To change Staff Position, edit ID) (1-5) : ");
			scanf("%d", &menuValid);
			rewind(stdin);

			switch (menuValid) {
			case 1:
				printf("Enter the new name of the employee: ");
				scanf("%[^\n]", (*memberInfo)[currentMem].name);
				rewind(stdin);
				break;
			case 2:
				printf("\nEnter the new staff ID : ");
				scanf("%s", (*memberInfo)[currentMem].userID);
				rewind(stdin);
				break;
			case 3:
				do {
					printf("\nEnter the new gender of the employee : ");
					scanf(" %c", &((*memberInfo)[currentMem].gender));

					rewind(stdin);

					if ((*memberInfo)[currentMem].gender == 'M' || (*memberInfo)[currentMem].gender == 'F') {
						break;
					}
					else {
						printf("Invalid gender.\n");
					}
				} while (1);
				break;
			case 4:
				printf("\nEnter the new contact number of the employee : ");
				scanf("%s", (*memberInfo)[currentMem].contactNo);
				rewind(stdin);
				break;
			case 5:
				break;
			}
			fwrite(*memberInfo, sizeof(Member), 20, ptr);
			fclose(ptr);
		} while (menuValid != 5);

		user(memberInfo, totalMem, noOfMem);
	}
	else {
		printf("Can't open file!");
	}
}
int displayMem(Member(*memberInfo)[20]) {
	int noMemPlacehold = 0;
	char exitFunc[10];
	system("cls");
	for (noMemPlacehold; noMemPlacehold < totalMem; noMemPlacehold++) {

		if (strcmp((*memberInfo)[noMemPlacehold].name, "") != 0) {
			printf("Mem No: %d\n\n", noMemPlacehold + 1);
			printf("===================================================\n");
			printf("||  Member Name  : %28s  ||\n", (*memberInfo)[noMemPlacehold].name);
			printf("||  Member ID    : %28s  ||\n", (*memberInfo)[noMemPlacehold].userID);
			printf("||  Gender       : %28c  ||\n", (*memberInfo)[noMemPlacehold].gender);
			printf("||  Contact No   : %28s  ||\n", (*memberInfo)[noMemPlacehold].contactNo);
			printf("===================================================\n\n");
		}
		
	}

	printf("Enter any key when ready to exit: ");
	scanf("%s", exitFunc);
	user(memberInfo, totalMem, noOfMem);
}
int searchUser(Member(*memberInfo)[20]) {
	char idCompare[10];
	char exitFunc[10];
	int validCheck = 1, currentMem, menuValid = 0;

	system("cls");

	do {
		printf("Please enter the user ID of the staff you want to find : ");
		scanf("%s", idCompare);
		rewind(stdin);

		for (int x = 0; x <= totalMem; x++) {
			if (strcmp(idCompare, (*memberInfo)[x].userID) == 0) {
				printf("\n\nID Found!");
				validCheck = 0;
				currentMem = x;
				break;
			}
		}

		if (validCheck == 1) {
			printf("\nUser ID not found!\n\n");
		}
	} while (validCheck == 1);

	printf("===================================================\n");
	printf("||  Member Name  : %28s  ||\n", (*memberInfo)[currentMem].name);
	printf("||  Member ID    : %28s  ||\n", (*memberInfo)[currentMem].userID);
	printf("||  Gender       : %28c  ||\n", (*memberInfo)[currentMem].gender);
	printf("||  Contact No   : %28s  ||\n", (*memberInfo)[currentMem].contactNo);
	printf("===================================================\n\n");

	printf("Enter any key when ready to exit: ");
	scanf("%s", exitFunc);
	user(memberInfo, totalMem, noOfMem);
}
int deleteUser(Member(*memberInfo)[20]) {
	FILE* ptr;
	ptr = fopen("memberInfo.bin", "wb");
	char idCompare[9];
	char exitFunc[10];
	int validCheck = 1, currentMem, menuValid = 0;

	system("cls");

	do {
		printf("Please enter the user ID of the staff you want to delete (Enter 'XXX' to leave) : ");
		scanf("%s", idCompare);
		rewind(stdin);

		for (int x = 0; x <= totalMem; x++) {
			if (strcmp(idCompare, (*memberInfo)[x].userID) == 0) {
				printf("\n\nID Found!");
				validCheck = 0;
				currentMem = x;
				break;
			}
		}

		if (strcmp(idCompare, "XXX") == 0)
			user(memberInfo, totalMem, noOfMem);

		if (validCheck == 1) {
			printf("\nStaff ID not found!\n\n");
		}
	} while (validCheck == 1);

	// Shift elements to fill the gap
	for (int i = currentMem; i < totalMem - 1; i++) {
		(*memberInfo)[i] = (*memberInfo)[i + 1];
	}

	// Write the updated records back to the file
	for (int i = 0; i < totalMem - 1; i++) {
		fwrite(&memberInfo[i], sizeof(Member), 1, ptr);
	}

	totalMem--;

	printf("\nStaff record has been deleted successfully!\n");
	printf("Enter any key when ready to exit: ");
	scanf("%s", exitFunc);
	fclose(ptr);
	user(memberInfo, totalMem, noOfMem);
}
void addUser(Member(*memberInfo)[20]) {
	Member tempMember; int memberIDValid = 0, counter = 0, index = 0;
	char commit;
	printf("\nEnter new Member ID: ");
	rewind(stdin);
	scanf(" %8[^\n]", tempMember.userID); 
	rewind(stdin);
	for (int i = 0; i < 20; i++) {
		
		if (strcmp((*memberInfo)[i].userID, "") == 0 || (*memberInfo)[i].userID == NULL) {
			break;
		}index++;
	};
	// Validate userID format (4 digits, a dash, and 3 random alphabets (eg. 2020-MCD)
	while (memberIDValid == 0) {
		for (int i = 0; i < totalMem; i++) {
			counter++;
			if (strcmp(tempMember.userID, (*memberInfo)[i].userID) == 0) {
				printf("\nUserID already taken! Please re-enter: ");
				scanf(" %8[^\n]", tempMember.userID);
				rewind(stdin);
			}
			else if (strlen(tempMember.userID) != 8 || !isdigit(tempMember.userID[0]) || !isdigit(tempMember.userID[1]) || !isdigit(tempMember.userID[2]) || !isdigit(tempMember.userID[3]) ||
				tempMember.userID[4] != '-' || !isupper(tempMember.userID[5]) || !isupper(tempMember.userID[6]) || !isupper(tempMember.userID[7]) && counter == totalMem) {
				printf("\nUserID should not exceed 8 characters and match the format 'YYYY-XXX'. Please re-enter: ");
				scanf(" %8[^\n]", tempMember.userID);
				rewind(stdin);
			}
		}
		memberIDValid++;
	}
	strcpy((*memberInfo)[index].userID, tempMember.userID);
	printf("\nEnter new Password: ");
	scanf("%[^\n]", tempMember.password);
	rewind(stdin);
	while (strlen(tempMember.password) > 21) {
		printf("\nPassword must be less than 21 characters! Try again: ");
		scanf("%[^\n]", tempMember.password);
		rewind(stdin);
	}
	strcpy((*memberInfo)[index].password, tempMember.password);
	printf("\nEnter new Name: ");
	scanf("%[^\n]", tempMember.name);
	rewind(stdin);
	while (strlen(tempMember.name) > 51) {
		printf("\nPassword must be less than 51 characters! Try again: ");
		scanf("%[^\n]", tempMember.name);
		rewind(stdin);
	}
	strcpy((*memberInfo)[index].name, tempMember.name);
	printf("\nEnter new Gender: ");
	scanf("%c", &tempMember.gender);
	rewind(stdin);
	while (toupper(tempMember.gender) != 'M' && toupper(tempMember.gender) != 'F') {
		printf("\nGender:%c", tempMember.gender);
		printf("\nOnly F or M gender! Try again: ");
		scanf("%c", &tempMember.gender);
		rewind(stdin);
	}
	tempMember.gender = toupper(tempMember.gender);
	(*memberInfo)[index].gender = tempMember.gender;
	printf("\nEnter new Contact Number: ");
	scanf("%s", tempMember.contactNo);
	rewind(stdin);
	while (strlen(tempMember.contactNo) > 13) {
		printf("\nContact Number must be less than 13 numbers! Try again: ");
		scanf("%s", tempMember.contactNo);
		rewind(stdin);
	}
	strcpy((*memberInfo)[index].contactNo, tempMember.contactNo);
	system("cls");
	printf("\nYour new Member Details:\n");
	printf("\nUserID: %s", (*memberInfo)[index].userID);
	printf("\nName: %s", (*memberInfo)[index].name);
	printf("\nPassword: %s", (*memberInfo)[index].password);
	printf("\nGender: %c", (*memberInfo)[index].gender);
	printf("\nContact Number: %s", (*memberInfo)[index].contactNo);
	do {
		printf("\n\nWould you like to commit and go back (Y) or delete and go back (X) : ");
		scanf("%c", &commit);
		if (toupper(commit) == 'Y') {
			
			
			FILE* fwb;
			if ((fwb = fopen("memberInfo.bin", "wb")) != NULL) {
				size_t elementsWritten = fwrite(*memberInfo, sizeof(Member), 20, fwb);


				// Check if all elements were written successfully
				if (elementsWritten == 20) {
					printf("\nData written successfully to file. Going back to Staff Menu in 2 seconds...\n"); totalMem++; Sleep(2000); system("cls"); staffMain();
				}
				else {
					printf("Error writing data to file.\n");
				}
				fclose(fwb);

			}
			else {
				printf("Error reading from file!\n");
				exit(1);
			}totalMem++;
			break;
		}
		else if (toupper(commit) == 'X') {
			system("cls"); staffMain(); break;
		}
		else {
			printf("\nPlease choose the correct option. Try again.");
		}
	} while (1);

}
// ==================================================================================== Ticket Booking ================================================================================================================
void TBMain(char(*ptrTicketIDCart)[10][10]) {
	
	int temp;
	TrainInfo trains[6] = {
   {"101A",  101, { {"Cambridge"}, {"Fenchurch"},{"Victoria"}, {"Liverpool"}, {"Everton"}}},
   {"101B", 101,{ {"Everton" }, {"Liverpool"}, {"Victoria"}, {"Fenchurch" }, {"Cambridge"} }},
   {"102A", 102, { {"Cambridge"}, {"Paddington"}, {"King's Cross"}, {"Marylebone"} }},
   {"102B", 102, { {"Marylebone"}, {"King's Cross"}, {"Paddington"}, {"Cambridge"} }},
   {"103A", 103, { {"Everton"}, {"Marylebone"}, {"Leicester"}, {"Oxford"} }},
   {"103B", 103, { {"Oxford"}, {"Leicester"}, {"Marylebone"}, {"Everton"} }},
	};
	TrainLine trainLine[3] = {
   {"Liverpool", 101, 50, { "Cambridge", "Fenchurch", "Victoria", "Liverpool", "Everton"}},
   {"King's Cross", 102, 60,{ "Cambridge", "Paddington", "King's Cross", "Marylebone"}},
   {"Oxford",  103, 70, {"Everton", "Marylebone", "Leicester", "Oxford"}}
	};

	Member memberInfo[20] = { "" };
	FILE* frb;
	if ((frb = fopen("memberInfo.bin", "rb")) != NULL) {
		fread(&memberInfo, sizeof(Member), totalMem, frb);
		fclose(frb);
	}
	else {
		printf("Error reading from file!\n");
		exit(1);
	}
	totalMem = 0;
	for (int i = 0; i < 20; i++) {

		if (strcmp(memberInfo[i].userID, "") == 0 || memberInfo[i].userID == NULL) {
			break;
		}totalMem++;
	};
	TicketInfo tickets[40] = { "" };
	FILE* ticketsFile;
	char tempPaidStatus[7] = "";

	if ((ticketsFile = fopen("tickets.txt", "r+")) == NULL) {
		printf("Error. Can't open file!"); exit(-1);
	}
	else {

		// Write
		/*for (int i = 0; i < 40; i++) {
			if (tickets[i].seatNum != NULL || tickets[i].seatNum != 0) {
				fprintf(ticketsFile, "%s %d %c %s | %s (%d/%d/%d) %.2lf | %s| %s| (%d/%d/%d)\n", tickets[i].ticketID, tickets[i].seatNum, tickets[i].sectorCode,
					tickets[i].trainID, tickets[i].payInfo.paidStatus ? "true" : "false", tickets[i].payInfo.purchaseTime.day,
					tickets[i].payInfo.purchaseTime.month, tickets[i].payInfo.purchaseTime.year, tickets[i].payInfo.totalPrice,
					tickets[i].dpStation, tickets[i].arrStation, tickets[i].dpDate.day, tickets[i].dpDate.month, tickets[i].dpDate.year);
			}
		}*/

		// Read
		for (int i = 0; i < 40 || !feof(ticketsFile); i++) {

			int numRead = fscanf(ticketsFile, "%s %d %c %s | %s (%d/%d/%d) %lf | %[^|]| %[^|]| (%d/%d/%d)\n",
				tickets[i].ticketID, &tickets[i].seatNum, &tickets[i].sectorCode, tickets[i].trainID,
				tempPaidStatus, &tickets[i].payInfo.purchaseTime.day, &tickets[i].payInfo.purchaseTime.month,
				&tickets[i].payInfo.purchaseTime.year, &tickets[i].payInfo.totalPrice, tickets[i].dpStation, tickets[i].arrStation,
				&tickets[i].dpDate.day, &tickets[i].dpDate.month, &tickets[i].dpDate.year);

			if (numRead != 15 && numRead != 14) {
				/*printf("breaking: %d", i);
				printf("numRead =%d", numRead);*/
				break;
			}
			if (strcmp(tempPaidStatus, "true") == 0) {
				tickets[i].payInfo.paidStatus = true;
			}
			else if (strcmp(tempPaidStatus, "false") == 0) {
				tickets[i].payInfo.paidStatus = false;
			}
			else {
				printf("\n\nWhoops Error in Paid Status!\n\n");
			}
		}

		fclose(ticketsFile);
	}

	system("cls");
	if (toupper(userType) == 'M') {
		printf("\n--------------- Ticket Booking ---------------\n");
		printf("\n1. Search By Destination and Departure Station");
		printf("\n2. Search By Specific Train ID");
		printf("\n3. Search By Train Line");
		printf("\n4. Search & Display Ticket ID Information");
		printf("\n5. Payment & Cart");
		printf("\n6. Go back to previous menu");

		printf("\n\n Maximum number of tickets you can order per session is 10");
		int a = 0;
		
		while (a == 0) {
			printf("\n\nEnter Number > ");
			rewind(stdin);
			scanf_s("%d", &temp);

			rewind(stdin);
			switch (temp) {
			case 1: system("cls"); TBfindTickets(&memberInfo, trains, &tickets, trainLine, ptrTicketIDCart);  a++;
				break;
			case 2: system("cls"); TBsearchTrain(&memberInfo,  temp, trains, &tickets, trainLine, ptrTicketIDCart); a++;
				break;
			case 3:  system("cls"); TBsearchTrain(&memberInfo,  temp, trains, &tickets, trainLine, ptrTicketIDCart); a++;
				break;
			case 4: system("cls"); TBDisplayTicketID(&tickets, ptrTicketIDCart);  a++;
				break;
			case 5: system("cls"); TBPayment(&memberInfo, trainLine, &tickets, ptrTicketIDCart);  a++;
				break;
			case 6: system("cls"); AllMenu(memberInfo, indexMem); a++;
				break;
			default: printf("\nPlease select an available number!"); break;
			};

		}
	}
	else if (toupper(userType) == 'S'){
		system("cls"); TBEditTicketID(trainLine, tickets, ptrTicketIDCart);
	}
}
void TBfindTickets(Member(*memberInfo)[20], TrainInfo trains[6], TicketInfo(*tickets)[40], TrainLine trainLine[3], char(*ptrTicketIDCart)[10][10]) {
	char tempDest[20] = "", tempDepart[20] = "", tempTicketID[5] = "";
	int checkDest = 0, checkDepart = 0, tempDestLine[2] = { 0, 0 }, tempDepLine[2] = { 0 ,0 }, cntDtLine = 0, cntDpLine = 0;
	static int firstTicket = 0;
	// Transit stations are : Cambridge, Marylebone, Everton

	printf("\n----------- Find A Train Ticket -----------\n");
	while (checkDest == 0) {
		printf("\nEnter a destination station > ");
		gets(tempDest);
		rewind(stdin);
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 5; k++) {
				if (strcmp(tempDest, trainLine[i].stationName[k]) == 0) {
					checkDest++;
					if (tempDestLine[0] == 0) {
						tempDestLine[0] = trainLine[i].lineNo;
						cntDtLine++;
					}
					else if (trainLine[i].lineNo != tempDestLine[0]) {
						tempDestLine[1] = trainLine[i].lineNo;
						cntDtLine++;
					}
					firstTicket = 0;
					break;
				}
			}
		}
		if (checkDest == 0) {
			printf("\nDestination station not found. Try again.\n");
		}
	}
	while (checkDepart == 0) {
		printf("\nEnter a departing station > ");
		gets(tempDepart);
		rewind(stdin);
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 5; k++) {
				if (strcmp(tempDepart, trainLine[i].stationName[k]) == 0 && strcmp(tempDepart, tempDest) != 0) {
					checkDepart++;
					if (tempDepLine[0] == 0) {
						tempDepLine[0] = trainLine[i].lineNo;
						cntDpLine++;
					}
					else if (trainLine[i].lineNo != tempDepLine[1]) {
						tempDepLine[1] = trainLine[i].lineNo;
						cntDpLine++;
					}
					break;
				}
			}
		}
		if (checkDepart == 0) {
			printf("\nDeparting station not found or is the same as destination station. Try again.\n");
		}
	}
	char arrDpStation[2][20];
	strcpy_s(arrDpStation[0], sizeof(arrDpStation[0]), tempDest);
	strcpy_s(arrDpStation[1], sizeof(arrDpStation[1]), tempDepart);
	// Arrival = Destination, Departure = Departure. Hopefully no confusion.
	char transStation[20], tempTrainID[5];
	int firstTimeDp = 0, firstTimeDest = 0; // counter to count the times it takes to reach the station in the array, stations has order in the array
	int isSame = 0, isSameLine, countDp = 0, countDest = 0;
	for (int i = 0; i < 2; i++) {
		for (int a = 0; a < 2; a++) {
			if (tempDestLine[i] == tempDepLine[a] && tempDestLine[i] != 0) {
				isSame++;
				isSameLine = tempDestLine[i];
				for (int b = 0; b < 3; b++) {
					if (trainLine[b].lineNo == isSameLine) {
						for (int c = 0; c < 5; c++) {
							if (strcmp(trainLine[b].stationName[c], tempDepart) == 0) {
								firstTimeDp++;
							}
							else if (firstTimeDp == 0) {
								countDp++;
							}
							if (strcmp(trainLine[b].stationName[c], tempDest) == 0) {
								firstTimeDest++;
							}
							else if (firstTimeDest == 0) {
								countDest++;
							}
						}
						if (countDp > countDest) {
							sprintf(tempTrainID, "%dB", trainLine[b].lineNo);
						}
						else if (countDest > countDp) {
							sprintf(tempTrainID, "%dA", trainLine[b].lineNo);
						}
						break;
					}

				}

			}
		}
	}
	if (isSame != 0) {
		int isDoubleTicket = 1;
		TBBuy(memberInfo, isDoubleTicket, arrDpStation, tempTrainID, trains, tickets, trainLine, ptrTicketIDCart);
	}
	else if (isSame == 0) { // not the same line therefore we need to buy two tickets for two lines
		printf("\nSorry to inform you that you will require two tickets\nsince your departure and destination stations are on separate train lines!");
		int chooseTransLine = 0;
		if (cntDpLine == 2) { // Departure Line to Buy if there are two departure lines, one arrival line
			printf("\n\nChoose a train line to arrive at transit station (will be shown once you pick a line) :");
			printf("\n\n1. %d", tempDepLine[0]);
			printf("\n2. %d", tempDepLine[1]);

			int a = 0;
			while (a == 0) {
				printf("\n\nChoose an option (1 or 2) > ");
				rewind(stdin);
				scanf_s("%d", &chooseTransLine);
				if (chooseTransLine != 1 && chooseTransLine != 2) {
					printf("\nWrong input! Try again.");
				}
				else if (chooseTransLine == 1) {
					a++;
				}
				else if (chooseTransLine == 2) {
					tempDepLine[0] = tempDepLine[1]; a++;
				}
			}
		}
		else if (cntDtLine == 2) { // Arrival Line to Buy if there are 2 arrival lines, one departure line
			printf("\n\nChoose a train line to depart from transit station (will be shown once you pick a line) :");
			printf("\n\n1. %d", tempDestLine[0]);
			printf("\n2. %d", tempDestLine[1]);
			int a = 0;
			while (a == 0) {
				printf("\n\nChoose an option (1 or 2) > ");
				rewind(stdin);
				scanf_s("%d", &chooseTransLine);
				if (chooseTransLine != 1 && chooseTransLine != 2) {
					printf("\nWrong input! Try again.");
				}
				else if (chooseTransLine == 1) {
					a++;
				}
				else if (chooseTransLine == 2) {
					tempDestLine[0] = tempDestLine[1]; a++;
				}
			}
		}
		int done = 0;
		for (int i = 0; i < 3; i++) {
			for (int a = 0; a < 3; a++) {
				if (trainLine[i].lineNo == tempDepLine[0] && trainLine[a].lineNo == tempDestLine[0]) {
					for (int b = 0; b < 5; b++) {
						for (int c = 0; c < 5; c++) {
							if (strcmp(trainLine[i].stationName[b], trainLine[a].stationName[c]) == 0 && done == 0) {
								strcpy_s(transStation, sizeof(transStation), trainLine[i].stationName[b]);
								printf("\nYour Transit Station will be: %s", trainLine[i].stationName[b]);
								isSameLine = trainLine[i].lineNo;
								done++; //there was an issue where it still came back to this loop and print twice but only for one of the stations, it is very weird so im adding this as security
								break;
							}
						}
					}
				}
			}
		}
		//================================================================ Comparator function, refer to our train map to check the logic. A trains go south while B trains go north. Arrays are organised in order.
		for (int b = 0; b < 3; b++) {
			if (trainLine[b].lineNo == tempDepLine[0]) {
				firstTimeDp = 0; countDp = 0; int countTransStation = 0, firstTimeTransStation = 0;
				for (int c = 0; c < 5; c++) {
					if (strcmp(trainLine[b].stationName[c], tempDepart) == 0) {
						firstTimeDp++;
					}
					else if (firstTimeDp == 0) {
						countDp++;
					}
					if (strcmp(trainLine[b].stationName[c], transStation) == 0) {
						firstTimeTransStation++;
					}
					else if (firstTimeTransStation == 0) {
						countTransStation++;
					}
				}
				if (countDp > countTransStation) {
					sprintf(tempTrainID, "%dB", trainLine[b].lineNo);
				}
				else if (countTransStation > countDp) {
					sprintf(tempTrainID, "%dA", trainLine[b].lineNo);
				}
				printf("\nYour Departure Train ID: %s", tempTrainID);
				strcpy_s(arrDpStation[0], sizeof(arrDpStation[0]), transStation);

				if (firstTicket == 0) { //Show different message depending on whether it is the first ticket or second
					printf("\n\nThis will be your first ticket train ID. Do you wish to buy it? (Y = yes / Other = back to ticket booking menu) > ");
					firstTicket++;
				}
				else if (firstTicket == 1) {
					printf("\n\nThis will be your second ticket train ID. Do you wish to buy it? (Y = yes / Other = back to ticket booking menu) > ");
					firstTicket--;
				}
				char decision;
				rewind(stdin);
				decision = getchar();
				rewind(stdin);
				if (toupper(decision) == 'Y') {
					int isDoubleTicket = 2;
					TBBuy(memberInfo, isDoubleTicket, arrDpStation, tempTrainID, trains, tickets, trainLine, ptrTicketIDCart);
				}
				else {
					system("cls"); TBMain(ptrTicketIDCart);
				}
			}
		}
		for (int b = 0; b < 3; b++) { // Two separate loops so that there is priority in getting the tickets, get the Departure first then only destination. Trust me you can put it in and see.
			if (trainLine[b].lineNo == tempDestLine[0]) {
				firstTimeDp = 0; countDp = 0; int countTransStation = 0, firstTimeTransStation = 0;
				for (int c = 0; c < 5; c++) {
					if (strcmp(trainLine[b].stationName[c], tempDest) == 0) {
						firstTimeDp++;
						//printf("\nTempDepart: %s", tempDepart);
					}
					else if (firstTimeDp == 0) {
						countDp++;
					}
					if (strcmp(trainLine[b].stationName[c], transStation) == 0) {
						firstTimeTransStation++;
						//printf("\nTempDest: %s", tempDest);
					}
					else if (firstTimeTransStation == 0) {
						countTransStation++;
					}
				}
				if (countDp < countTransStation) {
					sprintf(tempTrainID, "%dB", trainLine[b].lineNo);
				}
				else if (countTransStation < countDp) {
					sprintf(tempTrainID, "%dA", trainLine[b].lineNo);
				}
				printf("\nYour Destination Train ID: %s", tempTrainID);
				strcpy_s(arrDpStation[1], sizeof(arrDpStation[1]), transStation);
				strcpy_s(arrDpStation[0], sizeof(arrDpStation[0]), tempDest);
				if (firstTicket == 0) { //Show different message depending on whether it is the first ticket or second
					printf("\n\nThis will be your first ticket train ID. Do you wish to buy it? (Y = yes / Other = back to ticket booking menu) > ");
					firstTicket++;
				}
				else if (firstTicket == 1) {
					printf("\n\nThis will be your second ticket train ID. Do you wish to buy it? (Y = yes / Other = back to ticket booking menu) > ");
					firstTicket--;
				}
				char decision;
				rewind(stdin);
				decision = getchar();
				rewind(stdin);
				if (toupper(decision) == 'Y') {
					int isDoubleTicket = 1;
					TBBuy(memberInfo, isDoubleTicket, arrDpStation, tempTrainID, trains, tickets, trainLine, ptrTicketIDCart);
				}
				else {
					system("cls"); TBMain(ptrTicketIDCart);
				}

			}
		}

	}

};
void TBsearchTrain(Member(*memberInfo)[20], int temp, TrainInfo trains[6], TicketInfo(*tickets)[40], TrainLine trainLine[4], char(*ptrTicketIDCart)[10][10]) {
	printf("\nDisclaimer: No arrival or departure station will be set. We assume you know where you're going.\n");
	char tempTrainID[5] = { "" }, tempSector, tempWantTicket = 'G';
	int tempTrainLine = 0, countAvSeats = 100, tempSeatNo = 0, breaker = 0;
	int checkTrainID = 0, checkTrainLine = 0;
	Time tempDate;
	if (temp == 2) {
		printf("\n----------- Search Train ID -----------\n");
		while (checkTrainID == 0) {
			printf("\nEnter Train ID > ");
			rewind(stdin);
			gets(tempTrainID);
			rewind(stdin);
			for (int k = 0; k < 8; k++) {
				if (strcmp(trains[k].trainID, tempTrainID) == 0) {
					tempTrainLine = trains[k].lineNo;
					checkTrainID++; break;
				}
			};
			if (checkTrainID == 0) {
				printf("\nTrainID not found. Please try to key in an available one!\n");
			}
		}
	}
	else if (temp == 3) {
		printf("\n----------- Search Train Line -----------\n");
		while (checkTrainLine == 0) {
			printf("\nEnter Train Line > ");
			scanf_s("%d", &tempTrainLine);
			rewind(stdin);
			for (int k = 0; k < 8; k++) {
				if (tempTrainLine == trains[k].lineNo) {
					checkTrainLine++; break;
				};
			};
			if (checkTrainLine == 0) {
				printf("\nTrain Line is not found. Please try to key in an available one!\n");
			}
		}
		printf("\nTrain ID with that line:");
		for (int k = 0; k <= 8; k++) {
			if (tempTrainLine == trains[k].lineNo) {
				printf(" %s", trains[k].trainID);
			};
		};
		while (checkTrainID == 0) {
			printf("\n\nPick a train ID > ");
			gets(tempTrainID);
			rewind(stdin);
			for (int i = 0; i < 8; i++) {
				if (strcmp(tempTrainID, trains[i].trainID) == 0 && trains[i].lineNo == tempTrainLine) {
					checkTrainID++; break;
				}
			}
			if (checkTrainID == 0) {
				printf("\nTrainID not found or not the same line. Please try to key in an available one!");
			}

		}
	}
	else { printf("Error"); }
	int isDoubleTicket = 0;
	char arrDpStation[2][20] = {"", ""};
	TBBuy(memberInfo, isDoubleTicket, arrDpStation, tempTrainID, trains, tickets, trainLine, ptrTicketIDCart);

};
void TBBuy(Member(*memberInfo)[20], int isDoubleTicket, char arrDpStation[2][20], char tempTrainID[5], TrainInfo trains[6], TicketInfo(*tickets)[40], TrainLine trainLine[4], char(*ptrTicketIDCart)[10][10]) {
	char  tempSector, tempWantTicket = 'G';
	int tempTrainLine = 0, countAvSeats = 100, tempSeatNo = 0;
	Time tempDate;
	for (int i = 0; i < 40; i++) {
		if (strcmp(tempTrainID, (*tickets)[i].trainID) == 0) {
			countAvSeats--;
		};
	};
	for (int i = 0; i < 6; i++) {
		if (strcmp(tempTrainID, trains[i].trainID) == 0) {
			tempTrainLine = trains[i].lineNo;
		}
	}
	system("cls");
	printf("\n----------- Train Details -----------\n");
	printf("\nTrain ID: %s", tempTrainID);
	printf("\nTrain Line: %d", tempTrainLine);
	printf("\nAvailable Seats: %d", countAvSeats);

	while (tempWantTicket != 'Y' && tempWantTicket != 'N') {
		printf("\n\nWould you like a ticket from this train? (Y/N) > ");
		tempWantTicket = getchar();
		rewind(stdin);
		if (toupper(tempWantTicket) == 'N') {
			char tempDecision;
			printf("\n\nWould you like to go back to main menu? (Y = yes / other = exit program) > ");
			tempDecision = getchar();
			rewind(stdin);
			if (toupper(tempDecision) == 'Y') {
				system("cls"); TBMain(ptrTicketIDCart);
			}
			else {
				exit(0);
			} break;
		}
		else if (toupper(tempWantTicket) == 'Y') {
			int anyTicketsAvailable = 0, sectorCodeCorrect = 0;
			char tempTryAgain, sectorCodes[5] = { 'A', 'B', 'C', 'D', 'E' };

			while (sectorCodeCorrect == 0) {
				printf("\nA = First Class (Additional 20$) | B to E = Economy (Standard)\n");
				printf("\nWhich sector of the train would you like? > ");
				rewind(stdin);
				tempSector = getchar();
				rewind(stdin);

				for (int i = 0; i < 5; i++) {
					if (toupper(tempSector) == sectorCodes[i]) {
						tempSector = sectorCodes[i]; //turn it into caps only
						sectorCodeCorrect++; break;
					}
				}
				if (sectorCodeCorrect == 0) {
					printf("\nSector code is wrong. Please key in again.\n");
				}
			}

			while (tempSeatNo > 24 || tempSeatNo < 1) {
				printf("\nWhat seat number would you like? (1-24) > ");
				scanf_s("%d", &tempSeatNo);
				rewind(stdin);
				if (tempSeatNo > 24 || tempSeatNo < 1) {
					printf("\nNumber is not in range (1-24). Please key in again.\n");
				}
			}
			int n = 0;
			while (n == 0) {
				printf("\nDate must be within 2 years.\n");
				printf("\nDeparture date? (DD/MM/YYYY) > ");
				scanf_s("%d/%d/%d", &tempDate.day, &tempDate.month, &tempDate.year);
				rewind(stdin);
				if (tempDate.day > 0 && tempDate.day <= 30 && tempDate.month > 0 && tempDate.month <= 12 && tempDate.year >= 2024 && tempDate.year <= 2026) {
					n++; break;
				}
				else {
					printf("\nWrong date format!\n");
					rewind(stdin);
				}
			}
			for (int l = 0; l < 40; l++) {
				if (strcmp(tempTrainID, (*tickets)[l].trainID) == 0) {
					for (int a = 0; a < 40; a++) {
						if (toupper(tempSector) == (*tickets)[a].sectorCode && tempSeatNo == (*tickets)[a].seatNum && (*tickets)[a].payInfo.paidStatus == true && tempDate.day == (*tickets)[a].dpDate.day && tempDate.month == (*tickets)[a].dpDate.month && tempDate.year == (*tickets)[a].dpDate.year) {
							printf("\nThere are no tickets available!");
							printf("\n\nDo you want to try keying the details again? (Y = yes / N = Return to ticket booking menu / Others = Exit program) > ");
							rewind(stdin);
							tempTryAgain = getchar();
							rewind(stdin);
							switch (toupper(tempTryAgain)) {
							case 'Y': TBBuy(memberInfo, isDoubleTicket, arrDpStation, tempTrainID, trains, tickets, trainLine, ptrTicketIDCart); break;
							case 'N': system("cls"); TBMain(ptrTicketIDCart); break;
							default: exit(0); break;
							} 
							break;
						}
					}
				}
			
			}
				char confirmDetails;
				printf("\nYour ticket is available!\n");
				printf("\nClearing screen in 2 seconds..."); Sleep(2000); system("cls");
				printf("\n\n-------- Your Chosen Ticket Details --------\n");
				printf("\nTrain ID: %s", tempTrainID);
				printf("\nSector Code: %c", tempSector);
				printf("\nSeat Number: %d", tempSeatNo);
				if (isDoubleTicket > 0) {
					printf("\nArrival Station: %s", arrDpStation[0]);
					printf("\nDeparture Station: %s", arrDpStation[1]);
				}
				printf("\nDeparture Date: %d/%d/%d", tempDate.day, tempDate.month, tempDate.year);
				printf("\n\nConfirm Details? (Y = yes / Others = Go back to menu) >");
				rewind(stdin);
				confirmDetails = getchar();
				rewind(stdin);
				if (toupper(confirmDetails) == 'Y') {
					for (int i = 0; i < 40; i++) {
						if (strcmp((*tickets)[i].ticketID, "") == 0) {
							char genTicketID[10] = "";
							int randBreaker = 0;
							while (randBreaker == 0) {
								srand(time(NULL));
								int randTicketIDNum = rand() % (9999 - 1000 + 1) + 1000;
								sprintf(genTicketID, "%s%d", tempTrainID, randTicketIDNum);
								if (strcmp((*tickets)[i].ticketID, genTicketID) != 0) {
									randBreaker++;
								}

							}
							int finalChoice = 0;
							system("cls");
							printf("\n\n-------- Your Ticket Details --------\n");
							printf("\nTicket ID: %s\n", genTicketID);
							printf("\nTrain ID: %s", tempTrainID);
							printf("\nSector Code: %c", tempSector);
							printf("\nSeat Number: %d", tempSeatNo);
							if (isDoubleTicket > 0) {
								printf("\nArrival Station: %s", arrDpStation[0]);
								printf("\nDeparture Station: %s", arrDpStation[1]);
							}
							printf("\nDeparture Date: %d/%d/%d\n", tempDate.day, tempDate.month, tempDate.year);
							printf("\n--------------------------------------\n");
							printf("\n1. Add to cart and go back to ticket booking menu\n");
							printf("\n2. Proceed to payment\n");
							printf("\n3. Go back to ticket booking menu\n");
							printf("\n4. Exit program\n");
							if (isDoubleTicket == 2) {
								printf("\n5. Buy the second ticket\n");
							};
							while (finalChoice != 1 && finalChoice != 2 && finalChoice != 3 && finalChoice != 4 && finalChoice != 5) {
								printf("\nSelect a number > ");
								scanf_s("%d", &finalChoice);
								rewind(stdin);
								if (finalChoice == 1 || finalChoice == 2) {
									// Store TicketID inside the Cart
									for (int d = 0; d < 10; d++) {
										if (strcmp((*ptrTicketIDCart)[d], "") == 0) {
											strcpy_s((*ptrTicketIDCart)[d], sizeof(genTicketID), genTicketID);
											break;
										}
									}
									// Store ticket info inside the tickets structure
									for (int a = 0; a < 40; a++) {
										if (strcmp((*tickets)[a].ticketID, "") == 0) {
											strcpy_s((*tickets)[a].ticketID, sizeof(genTicketID), genTicketID);
											strcpy_s((*tickets)[a].trainID, sizeof(tempTrainID), tempTrainID);
											(*tickets)[a].sectorCode = tempSector;
											(*tickets)[a].seatNum = tempSeatNo;
											(*tickets)[a].dpDate = tempDate;
											(*tickets)[a].payInfo.paidStatus = false;
											if (strcmp(arrDpStation[0], "") != 0) {
												strcpy_s((*tickets)[a].arrStation, sizeof(arrDpStation[0]), arrDpStation[0]);
												strcpy_s((*tickets)[a].dpStation, sizeof(arrDpStation[1]), arrDpStation[1]);
											}
											else {
												strcpy_s((*tickets)[a].arrStation, sizeof((*tickets)[a].arrStation), "None");
												strcpy_s((*tickets)[a].dpStation, sizeof((*tickets)[a].dpStation), "None");
											}
											break;
										}
									}
									FILE* ticketsFile;
									if ((ticketsFile = fopen("tickets.txt", "w")) == NULL) {
										printf("Error. Can't open file!"); exit(-1);
									}
									else {

										// Write
										for (int i = 0; i < 40; i++) {
											if ((*tickets)[i].seatNum != NULL || (*tickets)[i].seatNum != 0) {
												fprintf(ticketsFile, "%s %d %c %s | %s (%d/%d/%d) %.2lf | %s| %s| (%d/%d/%d)\n", (*tickets)[i].ticketID, (*tickets)[i].seatNum, (*tickets)[i].sectorCode,
													(*tickets)[i].trainID, (*tickets)[i].payInfo.paidStatus ? "true" : "false", (*tickets)[i].payInfo.purchaseTime.day,
													(*tickets)[i].payInfo.purchaseTime.month, (*tickets)[i].payInfo.purchaseTime.year, (*tickets)[i].payInfo.totalPrice,
													(*tickets)[i].dpStation, (*tickets)[i].arrStation, (*tickets)[i].dpDate.day, (*tickets)[i].dpDate.month, (*tickets)[i].dpDate.year);
											}
										} fclose(ticketsFile);
									}
								}
								if (finalChoice == 1) {
									system("cls");
									TBMain(ptrTicketIDCart);
								}
								else if (finalChoice == 2) {
									TBPayment(memberInfo, trainLine, tickets, ptrTicketIDCart);
								}
								else if (finalChoice == 3) {
									system("cls");
									TBMain(ptrTicketIDCart);
								}
								else if (finalChoice == 4) {
									exit(0);
								}
								else if (finalChoice == 5 && isDoubleTicket == 2) {
									system("cls"); // Have to duplicate because of the isDoubleTicket
									for (int d = 0; d < 10; d++) {
										if (strcmp((*ptrTicketIDCart)[d], "") == 0) {
											strcpy_s((*ptrTicketIDCart)[d], sizeof(genTicketID), genTicketID);
											break;
										}
									}
									for (int a = 0; a < 40; a++) {
										if (strcmp((*tickets)[a].ticketID, "") == 0) {
											strcpy_s((*tickets)[a].ticketID, sizeof(genTicketID), genTicketID);
											strcpy_s((*tickets)[a].trainID, sizeof(tempTrainID), tempTrainID);
											(*tickets)[a].sectorCode = tempSector;
											(*tickets)[a].seatNum = tempSeatNo;
											(*tickets)[a].dpDate = tempDate;
											(*tickets)[a].payInfo.paidStatus = false;
											if (strcmp(arrDpStation[0], "") != 0) {
												strcpy_s((*tickets)[a].arrStation, sizeof(arrDpStation[0]), arrDpStation[0]);
												strcpy_s((*tickets)[a].dpStation, sizeof(arrDpStation[1]), arrDpStation[1]);
											}
											else {
												strcpy_s((*tickets)[a].arrStation, sizeof((*tickets)[a].arrStation), "None");
												strcpy_s((*tickets)[a].dpStation, sizeof((*tickets)[a].dpStation), "None");
											}
											break;
										}
									}
									FILE* ticketsFile;
									if ((ticketsFile = fopen("tickets.txt", "w")) == NULL) {
										printf("Error. Can't open file!"); exit(-1);
									}
									else {
										for (int i = 0; i < 40; i++) {
											if ((*tickets)[i].seatNum != NULL || (*tickets)[i].seatNum != 0) {
												fprintf(ticketsFile, "%s %d %c %s | %s (%d/%d/%d) %.2lf | %s| %s| (%d/%d/%d)\n", (*tickets)[i].ticketID, (*tickets)[i].seatNum, (*tickets)[i].sectorCode,
													(*tickets)[i].trainID, (*tickets)[i].payInfo.paidStatus ? "true" : "false", (*tickets)[i].payInfo.purchaseTime.day,
													(*tickets)[i].payInfo.purchaseTime.month, (*tickets)[i].payInfo.purchaseTime.year, (*tickets)[i].payInfo.totalPrice,
													(*tickets)[i].dpStation, (*tickets)[i].arrStation, (*tickets)[i].dpDate.day, (*tickets)[i].dpDate.month, (*tickets)[i].dpDate.year);
											}
										} fclose(ticketsFile);
									}
									return 0;
								}
								else if (finalChoice == 5 && isDoubleTicket != 2) {
									finalChoice = 0;
								}
								if (finalChoice != 1 && finalChoice != 2 && finalChoice != 3 && finalChoice != 4 && finalChoice != 5) {
									printf("\nWrong input. Please try again.\n");
								}
							}
							break;
						}
					} break;
				}
				else {
					system("cls"); TBMain(ptrTicketIDCart);
				}
				break;
			
		}
		else
		{
			printf("Wrong input. Please type only Y or N");
		}
	}
}
void TBDisplayTicketID(TicketInfo tickets[40], char(*ptrTicketIDCart)[10][10]) {
	char tempTicketID[10] = ""; int isFound = 1;

	printf("\n---------Display Ticket ID Information ---------\n");

	while (isFound == 1 || isFound == 0) {
		printf("\nEnter ticket ID > ");
		gets(tempTicketID);
		for (int i = 0; i <= 40; i++) {
			if (strcmp(tempTicketID, tickets[i].ticketID) == 0) {
				printf("\n--------- Ticket Details ---------\n");
				printf("\nTicket ID: %s", tickets[i].ticketID);
				printf("\nTrain ID: %s", tickets[i].trainID);
				printf("\nSector : %c", tickets[i].sectorCode);
				printf("\nSeat Number : %d", tickets[i].seatNum);
				printf("\nClass : ");

				if (tickets[i].sectorCode == 'A') {
					printf("First");
				}
				else {
					printf("Economy");
				}
				printf("\nArrival Station: %s", tickets[i].arrStation);
				printf("\nDeparture Station: %s", tickets[i].dpStation);

				char tempTrainLine[5];
				strcpy_s(tempTrainLine, sizeof(tickets[i].trainID), tickets[i].trainID);
				tempTrainLine[3] = '\0';

				printf("\nTrain Line: %s", tempTrainLine);
				printf("\nPaid Status: %s", tickets[i].payInfo.paidStatus ? "Paid" : "Unpaid");
				printf("\n\nSearch another? (Y = yes / Other = Ticket Booking Menu) > ");
				char choose;
				choose = getchar();
				rewind(stdin);
				if (toupper(choose) == 'Y') {
					isFound--;
				}
				else {
					isFound++; system("cls"); TBMain(ptrTicketIDCart); break;
				}
				
			};
		};
		if (isFound == 1) {
			printf("\nWrong input. Please try to put a valid ticket ID.\n");
		}
	}

};
void TBEditTicketID(TrainLine trainLine[3], TicketInfo(*tickets)[40], char(*ptrTicketIDCart)[10][10]) {
	int editChoice = 0, validInput = 0, correctTicketID = 0; char tempTicketID[5];
	while (validInput == 0) {
		printf("--------------- Edit Ticket Information -------------\n");
		printf("\n1. Modify Ticket Details");
		printf("\n2. Delete Ticket");
		printf("\n3. Sort Ticket by Train ID numerically and alphabetically");
		printf("\n4. Display All Records");
		printf("\n5. Back to Staff Menu");
		printf("\n\nChoose a number > ");
		rewind(stdin);
		scanf_s("%d", &editChoice);
		if (editChoice == 1) {
			validInput++;
			while (correctTicketID == 0) {
				printf("\nTicket ID to Modify > ");
				rewind(stdin);
				gets(tempTicketID);
				rewind(stdin);
				for (int i = 0; i < 40; i++) { if (strcmp((*tickets)[i].ticketID, tempTicketID) == 0) { correctTicketID++; }; }
				if (correctTicketID == 0) { printf("\nTicket ID not found. Please try again.\n"); };

			}
			if (correctTicketID == 1) {
				int modifyNum = 0, tryAgain = 0;

				while (modifyNum != 1 && modifyNum != 2 && modifyNum != 3 && modifyNum != 4 && modifyNum != 5) {
					printf("\n\n---------- Choose one detail to modify ---------\n");
					printf("\n1. Sector");
					printf("\n2. Seat Number");
					printf("\n3. Arrival Station");
					printf("\n4. Departure Station");
					printf("\n5. Back to Ticket Booking Menu");
					printf("\n\nSelect a number > ");
					scanf_s("%d", &modifyNum);
					rewind(stdin);
					if (modifyNum == 1) {
						char newSectorCode, sectorCodes[5] = { 'A', 'B', 'C', 'D', 'E' };
						bool isCorrect = false;
						while (isCorrect == false) {
							printf("\nEnter new Sector Code > ");
							rewind(stdin);
							newSectorCode = getchar();
							rewind(stdin);
							for (int i = 0; i < 5; i++) {
								if (toupper(newSectorCode) == sectorCodes[i]) {
									newSectorCode = sectorCodes[i];
									isCorrect = true;
								}
							}
							if (isCorrect == false) {
								printf("\nSector code is wrong. Please key in again.\n");
							}
						}
						for (int i = 0; i < 40; i++) {
							if (strcmp((*tickets)[i].ticketID, tempTicketID) == 0) {
								(*tickets)[i].sectorCode = newSectorCode;
								printf("\nSector Code changed to %c\n", newSectorCode);
							};
						}
					}
					else if (modifyNum == 2) {
						int newSeatNum = 0;
						while (newSeatNum > 24 || newSeatNum < 1) {
							printf("\nEnter new Seat Number > ");
							rewind(stdin);
							scanf_s("%d", &newSeatNum);
							rewind(stdin);
							if (newSeatNum > 24 || newSeatNum < 1) {
								printf("\nWrong Seat Number ( Must be between 1 to 24). Try again.\n");
							}
						}
						for (int i = 0; i < 40; i++) {
							if (strcmp((*tickets)[i].ticketID, tempTicketID) == 0) {
								(*tickets)[i].seatNum = newSeatNum;
								printf("\nSeat Number changed to %d\n", newSeatNum);
							};
						}
						
					}
					else if (modifyNum == 3) {
						char newArrStation[20];
						bool isCorrect = false;
						while (isCorrect == false) {
							printf("\nEnter new Arrival Station > ");
							rewind(stdin);
							gets(newArrStation);
							rewind(stdin);
							for (int i = 0; i < 3; i++) {
								for (int j = 0; j < 5; j++) {
									if (strcmp(newArrStation, trainLine[i].stationName[j]) == 0) {
										isCorrect = true;
									}
								}

							}
							if (isCorrect == false) {
								printf("\nArrival Station is wrong. Please key in again.\n");
							}
						}
						for (int i = 0; i < 40; i++) {
							if (strcmp((*tickets)[i].ticketID, tempTicketID) == 0) {
								strcpy_s((*tickets)[i].arrStation, sizeof((*tickets)[i].arrStation), newArrStation);
								printf("\nArrival Station changed to %s\n", newArrStation);
							};
						}
					}
					else if (modifyNum == 4) {
						char newDpStation[20];
						bool isCorrect = false;
						while (isCorrect == false) {
							printf("\nEnter new Departure Station > ");
							rewind(stdin);
							gets(newDpStation);
							rewind(stdin);
							for (int i = 0; i < 3; i++) {
								for (int j = 0; j < 5; j++) {
									if (strcmp(newDpStation, trainLine[i].stationName[j]) == 0) {
										isCorrect = true;
									}
								}
							}
							if (isCorrect == false) {
								printf("\nArrival Station is wrong. Please key in again.\n");
							}
						}
						for (int i = 0; i < 40; i++) {
							if (strcmp((*tickets)[i].ticketID, tempTicketID) == 0) {
								strcpy_s((*tickets)[i].dpStation, sizeof((*tickets)[i].arrStation), newDpStation);
								printf("\nArrival Station changed to %s\n", newDpStation);
							};
						}
					}
					else if (modifyNum == 5) {
						system("cls"); staffMain();
					}
					else if (modifyNum != 1 && modifyNum != 2 && modifyNum != 3 && modifyNum != 4 && modifyNum != 5 && tryAgain > 0) {
						printf("\nWrong number please reselect.");
					}
					char chooseAnother;
					printf("\nChoose another detail to modify? ( Y = yes / Others = Staff Menu ) > ");
					chooseAnother = getchar();
					if (toupper(chooseAnother) == 'Y') {
						tryAgain++; modifyNum = 0;
					}
					else {
						system("cls"); staffMain();
					}
				}
			}
		}
		else if (editChoice == 2) {
			printf("\n\n---------- Delete a Ticket ---------\n");
			while (correctTicketID == 0) {
				printf("\nTicket ID to delete > ");
				rewind(stdin);
				gets(tempTicketID);
				rewind(stdin);
				for (int i = 0; i < 40; i++) {
					if (strcmp((*tickets)[i].ticketID, tempTicketID) == 0) {
						correctTicketID++;
						printf("\n\nTicket ID : %s\n\n", (*tickets)[i].ticketID);
						(*tickets)[i].seatNum = 0;
						(*tickets)[i].sectorCode = '\0';
						strcpy_s((*tickets)[i].ticketID, sizeof(""), "");
						(*tickets)[i].payInfo.paidStatus = false;
						(*tickets)[i].payInfo.purchaseTime.min = 0;
						(*tickets)[i].payInfo.purchaseTime.hour = 0;
						(*tickets)[i].payInfo.purchaseTime.day = 0;
						(*tickets)[i].payInfo.purchaseTime.month = 0;
						(*tickets)[i].payInfo.purchaseTime.year = 0;
						strcpy_s((*tickets)[i].dpStation, sizeof(""), "");
						strcpy_s((*tickets)[i].arrStation, sizeof(""), "");
						(*tickets)[i].dpDate.day = 0;
						(*tickets)[i].dpDate.month = 0;
						(*tickets)[i].dpDate.year = 0;

						break;
					}
				}
				if (correctTicketID == 0) {
					printf("\nTicket ID not found. Please try again.\n");
				}
				else {
					printf("Successfully Deleted! Going back toStaff Menu in 2 seconds..."); Sleep(2000); system("cls"); staffMain();
				}
			}

			validInput++;
		}
		else if (editChoice == 3) {
			FILE* ticketsSortFile;
			if ((ticketsSortFile = fopen("ticketsSorted.txt", "r+")) == NULL) {
				printf("Error. Can't open file!"); exit(-1);
			}
			else {
				// Write
				for (int i = 0; i < 40; i++) {

					if (strcmp((*tickets)[i].trainID, "101A") == 0) {
						fprintf(ticketsSortFile, "%s %d %c %s | %s (%d/%d/%d) %.2lf | %s | %s | (%d/%d/%d)\n", (*tickets)[i].ticketID, (*tickets)[i].seatNum, (*tickets)[i].sectorCode,
							(*tickets)[i].trainID, (*tickets)[i].payInfo.paidStatus ? "true" : "false", (*tickets)[i].payInfo.purchaseTime.day,
							(*tickets)[i].payInfo.purchaseTime.month, (*tickets)[i].payInfo.purchaseTime.year, (*tickets)[i].payInfo.totalPrice,
							(*tickets)[i].dpStation, (*tickets)[i].arrStation, (*tickets)[i].dpDate.day, (*tickets)[i].dpDate.month, (*tickets)[i].dpDate.year);
					}
				}
				for (int i = 0; i < 40; i++) {
					if (strcmp((*tickets)[i].trainID, "101B") == 0) {
						fprintf(ticketsSortFile, "%s %d %c %s | %s (%d/%d/%d) %.2lf | %s | %s | (%d/%d/%d)\n", (*tickets)[i].ticketID, (*tickets)[i].seatNum, (*tickets)[i].sectorCode,
							(*tickets)[i].trainID, (*tickets)[i].payInfo.paidStatus ? "true" : "false", (*tickets)[i].payInfo.purchaseTime.day,
							(*tickets)[i].payInfo.purchaseTime.month, (*tickets)[i].payInfo.purchaseTime.year, (*tickets)[i].payInfo.totalPrice,
							(*tickets)[i].dpStation, (*tickets)[i].arrStation, (*tickets)[i].dpDate.day, (*tickets)[i].dpDate.month, (*tickets)[i].dpDate.year);
					}
				}
				for (int i = 0; i < 40; i++) {

					if (strcmp((*tickets)[i].trainID, "102A") == 0) {
						fprintf(ticketsSortFile, "%s %d %c %s | %s (%d/%d/%d) %.2lf | %s | %s | (%d/%d/%d)\n", (*tickets)[i].ticketID, (*tickets)[i].seatNum, (*tickets)[i].sectorCode,
							(*tickets)[i].trainID, (*tickets)[i].payInfo.paidStatus ? "true" : "false", (*tickets)[i].payInfo.purchaseTime.day,
							(*tickets)[i].payInfo.purchaseTime.month, (*tickets)[i].payInfo.purchaseTime.year, (*tickets)[i].payInfo.totalPrice,
							(*tickets)[i].dpStation, (*tickets)[i].arrStation, (*tickets)[i].dpDate.day, (*tickets)[i].dpDate.month, (*tickets)[i].dpDate.year);
					}
				}
				for (int i = 0; i < 40; i++) {
					if (strcmp((*tickets)[i].trainID, "102B") == 0) {
						fprintf(ticketsSortFile, "%s %d %c %s | %s (%d/%d/%d) %.2lf | %s | %s | (%d/%d/%d)\n", (*tickets)[i].ticketID, (*tickets)[i].seatNum, (*tickets)[i].sectorCode,
							(*tickets)[i].trainID, (*tickets)[i].payInfo.paidStatus ? "true" : "false", (*tickets)[i].payInfo.purchaseTime.day,
							(*tickets)[i].payInfo.purchaseTime.month, (*tickets)[i].payInfo.purchaseTime.year, (*tickets)[i].payInfo.totalPrice,
							(*tickets)[i].dpStation, (*tickets)[i].arrStation, (*tickets)[i].dpDate.day, (*tickets)[i].dpDate.month, (*tickets)[i].dpDate.year);
					}
				}

				for (int i = 0; i < 40; i++) {

					if (strcmp((*tickets)[i].trainID, "103A") == 0) {
						fprintf(ticketsSortFile, "%s %d %c %s | %s (%d/%d/%d) %.2lf | %s | %s | (%d/%d/%d)\n", (*tickets)[i].ticketID, (*tickets)[i].seatNum, (*tickets)[i].sectorCode,
							(*tickets)[i].trainID, (*tickets)[i].payInfo.paidStatus ? "true" : "false", (*tickets)[i].payInfo.purchaseTime.day,
							(*tickets)[i].payInfo.purchaseTime.month, (*tickets)[i].payInfo.purchaseTime.year, (*tickets)[i].payInfo.totalPrice,
							(*tickets)[i].dpStation, (*tickets)[i].arrStation, (*tickets)[i].dpDate.day, (*tickets)[i].dpDate.month, (*tickets)[i].dpDate.year);
					}
				}
				for (int i = 0; i < 40; i++) {
					if (strcmp((*tickets)[i].trainID, "103B") == 0) {
						fprintf(ticketsSortFile, "%s %d %c %s | %s (%d/%d/%d) %.2lf | %s | %s | (%d/%d/%d)\n", (*tickets)[i].ticketID, (*tickets)[i].seatNum, (*tickets)[i].sectorCode,
							(*tickets)[i].trainID, (*tickets)[i].payInfo.paidStatus ? "true" : "false", (*tickets)[i].payInfo.purchaseTime.day,
							(*tickets)[i].payInfo.purchaseTime.month, (*tickets)[i].payInfo.purchaseTime.year, (*tickets)[i].payInfo.totalPrice,
							(*tickets)[i].dpStation, (*tickets)[i].arrStation, (*tickets)[i].dpDate.day, (*tickets)[i].dpDate.month, (*tickets)[i].dpDate.year);
					}
				}
				fclose(ticketsSortFile);
				printf("Successfully Sorted into ticketsSorted.txt! Going back to Staff Menu in 2 seconds..."); Sleep(2000); system("cls"); staffMain();
			}
			validInput++;
		}
		else if (editChoice == 4) {
			printf("\n------------- All Ticket Records Details ---------------\n");
			printf("\n%-11s | %s | %-11s | %-9s | %-12s | Payment Date | Amount Paid | %-20s | %-20s | Departure Date\n", "Ticket ID", "Seat Num", "Sector Code", "Train ID", "Paid Status", "Departure Station", "Arrival Station");
			for (int i = 0; i < 40; i++) {
				if (strcmp((*tickets)[i].ticketID, "") != 0) {
					printf("\n%-11s   %-8d   %-11c   %-12s   %-10s   %02d/%02d/%-6d   %-11.2lf   %-20s %-20s   %d/%d/%d\n",
						(*tickets)[i].ticketID, (*tickets)[i].seatNum, (*tickets)[i].sectorCode, (*tickets)[i].trainID, (*tickets)[i].payInfo.paidStatus ? "True" : "False",
						(*tickets)[i].payInfo.purchaseTime.day, (*tickets)[i].payInfo.purchaseTime.month, (*tickets)[i].payInfo.purchaseTime.year,
						(*tickets)[i].payInfo.totalPrice, (*tickets)[i].dpStation, (*tickets)[i].arrStation, (*tickets)[i].dpDate.day, (*tickets)[i].dpDate.month, (*tickets)[i].dpDate.year);
				}
			}
			char backtoTB;
			printf("\nGo back to Staff Menu? ( Y = yes / Other = quit program ) > ");
			rewind(stdin);
			backtoTB = getchar();
			if (toupper(backtoTB) == 'Y') {
				staffMain();
			}
			validInput++;
		}
		else if (editChoice == 5) {
			validInput++; system("cls"); staffMain();
		}
		else {
			printf("\n\nPlease try again and input the right number.");
		}

	}
};
void TBPayment(Member(*memberInfo)[20], TrainLine trainLine[4], TicketInfo(*tickets)[40], char(*ptrTicketIDCart)[10][10]) {
	int temp, countCart = 0;
	char tempTicketID[10] = "";
	system("cls");
	printf("\n------------ Payment & Cart ------------\n");
	printf("\nCurrent tickets in cart: ");

	for (int d = 0; d < 10; d++) {
		if (strcmp((*ptrTicketIDCart)[d], "") != 0) {
			printf("%s ", (*ptrTicketIDCart)[d]);
			countCart++;
		}
		else if (strcmp((*ptrTicketIDCart)[d], "") == 0 && d == 0) {
			printf("None");
		}
	};
	printf("\nNumber of tickets in cart: %d", countCart);
	printf("\n\n-------------------------------\n");
	if (countCart >= 1){
		printf("\n1. Remove a ticket.");
		printf("\n2. Proceed to check out.");
		printf("\n\nOther Numbers = Back to ticket booking menu.");
		printf("\n\n Enter a number > ");
		rewind(stdin);
		scanf_s("%d", &temp);
	}
	else {
		printf("\nEnter anything to go back > ");
		rewind(stdin);
		scanf_s("%d", &temp);
		system("cls"); TBMain(ptrTicketIDCart);
	}
	switch (temp) {
	case 1: printf("\n\nTicket ID to be removed > ");
		rewind(stdin);
		gets(tempTicketID);
		for (int d = 0; d < 10; d++) {
			if (strcmp((*ptrTicketIDCart)[d], tempTicketID) == 0) {
				strcpy_s((*ptrTicketIDCart)[d], sizeof(""), "");
				printf("\nTicket has been removed... going back to payment menu..."); Sleep(700); system("cls"); TBPayment(memberInfo, trainLine, tickets, ptrTicketIDCart);
			};
		};
		break;
	case 2: 
		system("cls");
		printf("\n\n---------- Checkout ----------\n");
		int count = 0, basePrice = 0, totalPrice = 0;
		for (int d = 0; d < 10; d++) {
			if (strcmp((*ptrTicketIDCart)[d], "") != 0) {
				count++;
				printf("\n%d. %s", count, (*ptrTicketIDCart)[d]);
				for (int a = 0; a < 40; a++) {
					if (strcmp((*ptrTicketIDCart)[d], (*tickets)[a].ticketID) == 0) {
						char lineNum[3];
						for (int e = 0; e < 3; e++) {
							lineNum[e] = (*tickets)[a].ticketID[e];
						}
						int lineNumInt = atoi(lineNum);

						for (int c = 0; c < 3; c++) {
							if (trainLine[c].lineNo == lineNumInt) {
								if ((*tickets)[a].sectorCode != 'A') {
									basePrice = trainLine[c].linePrice;
									printf("\t%d", basePrice);
									(*tickets)[a].payInfo.totalPrice = basePrice;
								}
								else {
									basePrice = trainLine[c].linePrice + 10;
									printf("\t%d", basePrice);
									(*tickets)[a].payInfo.totalPrice = basePrice;
								}
								totalPrice = basePrice + totalPrice;
							}
						}
					}

				}
			};
		};
		printf("\n\nTotal Price:\t%d", totalPrice);
		printf("\n\nBuy all? (Y = yes / Others = go back to Ticket Booking menu) > ");
		char buy;
		rewind(stdin);
		buy = getchar();
		if (toupper(buy) == 'Y') {
			printf("\nThanks for purchasing!");
			for (int a = 0; a < 20; a++) {
				if (strcmp(inputUserID, (*memberInfo)[a].userID) == 0) {
					for (int p = 0; p < 20; p++) {
						if (strcmp((*memberInfo)[a].bookTicketID[p], "") == 0) {
							int bookCount = 0;
							for (int k = 0; k < count; k++) {
								
								strcpy_s((*memberInfo)[a].bookTicketID[p + bookCount], sizeof((*memberInfo)[a].bookTicketID[p]), (*ptrTicketIDCart)[k]);
							 bookCount++;
							}
							break;
						}
						
					}
				}
			}
			for (int d = 0; d < 10; d++) {
				if (strcmp((*ptrTicketIDCart)[d], "") != 0) {
					for (int a = 0; a < 40; a++) {
						if (strcmp((*ptrTicketIDCart)[d], (*tickets)[a].ticketID) == 0) {
							Time currentTime; // declare the current Time
							time_t now; //built it function from time.h
							struct tm* localTime;
							now = time(NULL);
							localTime = localtime(&now);
							currentTime.min = localTime->tm_min; //Dereference localTime and put it inside currentTime
							currentTime.hour = localTime->tm_hour;
							currentTime.day = localTime->tm_mday;
							currentTime.month = localTime->tm_mon + 1;
							currentTime.year = localTime->tm_year + 1900;
							(*tickets)[a].payInfo.paidStatus = true;
							(*tickets)[a].payInfo.purchaseTime = currentTime; // put currentTime inside purchaseTime
							strcpy_s((*ptrTicketIDCart)[d], sizeof((*ptrTicketIDCart)[d]), ""); //Remove it from cart
							if (strcmp((*tickets)[a].arrStation, "") == 0) {
								strcpy_s((*tickets)[a].arrStation, sizeof((*tickets)[a].arrStation), "None");
								strcpy_s((*tickets)[a].dpStation, sizeof((*tickets)[a].dpStation), "None");
							}

						}
					} // Store the ticket into ticket booking history
				};
			};
			

			FILE* fwb;
			if ((fwb = fopen("memberInfo.bin", "wb")) != NULL) {
				size_t elementsWritten = fwrite(*memberInfo, sizeof(Member), 20, fwb);
				if (elementsWritten == 20) {
				}
				else {
					printf("Error writing data to file.\n");
				}
				fclose(fwb);
			}
			else {
				printf("Error reading from file!\n");
				exit(1);
			}
		}
		else {
			TBMain(ptrTicketIDCart);
		}
		FILE* ticketsFile;

		if ((ticketsFile = fopen("tickets.txt", "r+")) == NULL) {
			printf("Error. Can't open file!"); exit(-1);
		}
		else {
			// Write
			for (int i = 0; i < 40; i++) {
				if ((*tickets)[i].seatNum != NULL || (*tickets)[i].seatNum != 0) {
					fprintf(ticketsFile, "%s %d %c %s | %s (%d/%d/%d) %.2lf | %s| %s| (%d/%d/%d)\n", (*tickets)[i].ticketID, (*tickets)[i].seatNum, (*tickets)[i].sectorCode,
						(*tickets)[i].trainID, (*tickets)[i].payInfo.paidStatus ? "true" : "false", (*tickets)[i].payInfo.purchaseTime.day,
						(*tickets)[i].payInfo.purchaseTime.month, (*tickets)[i].payInfo.purchaseTime.year, (*tickets)[i].payInfo.totalPrice,
						(*tickets)[i].dpStation, (*tickets)[i].arrStation, (*tickets)[i].dpDate.day, (*tickets)[i].dpDate.month, (*tickets)[i].dpDate.year);
				}
			}
			fclose(ticketsFile);
		}
		printf("\n\nReturn to Ticket Booking menu or quit? (R = return / Other = quit) > ");
		char returnMenu;
		rewind(stdin);
		returnMenu = getchar();
		if (toupper(returnMenu) == 'R') {
			system("cls"); TBMain(ptrTicketIDCart);
		}
		else {
			exit(0);
		}
		break;
	default: system("cls"); TBMain(ptrTicketIDCart); break;
	}
};
// ==================================================================================== Schedule ================================================================================================================
int seatAvailability(TrainInfo(*trains)[6], TrainLine(*trainLine)[3]) {


	struct SeatInfo {
		char sectorCode;
		int seatNum[24];  //assuming 24 seats per sector
	};

	struct SeatData {
		int row;
		int seatNumber;
	};
	char searchTrainID[5];
	char searchSectorCode;
	int searchRow, searchSeat;
	char choice;
	char yesNo;

	char seatMapA[6][4] = {
		{'X', 'X', 'O', 'O'},
		{'X', 'O', 'O', 'O'},
		{'O', 'O', 'O', 'O'},
		{'X', 'X', 'X', 'X'},
		{'X', 'X', 'X', 'X'},
		{'O', 'X', 'O', 'O'}
	};

	char seatMapB[6][4] = {
		{'X', 'X', 'X', 'X'},
		{'X', 'O', 'O', 'X'},
		{'O', 'O', 'O', 'O'},
		{'O', 'O', 'X', 'X'},
		{'O', 'O', 'X', 'X'},
		{'X', 'X', 'O', 'O'}
	};

	char seatMapC[6][4] = {
		{'X', 'X', 'O', 'X'},
		{'X', 'O', 'X', 'O'},
		{'O', 'O', 'O', 'O'},
		{'X', 'X', 'O', 'X'},
		{'O', 'X', 'X', 'X'},
		{'X', 'O', 'X', 'O'}
	};

	char seatMapD[6][4] = {
		{'O', 'O', 'X', 'O'},
		{'X', 'O', 'X', 'O'},
		{'O', 'O', 'X', 'X'},
		{'O', 'X', 'O', 'O'},
		{'X', 'X', 'O', 'X'},
		{'O', 'X', 'O', 'O'}
	};

	char seatMapE[6][4] = {
		{'O', 'O', 'O', 'O'},
		{'X', 'O', 'O', 'X'},
		{'O', 'O', 'O', 'O'},
		{'X', 'O', 'X', 'X'},
		{'X', 'O', 'X', 'O'},
		{'O', 'O', 'X', 'O'}
	};

	// Array to store seat information for each sector
	struct SeatInfo seatData[5];
	// Array to store overall seat information
	struct SeatData allSeats[5][6][4];  // Assuming 5 sectors with 6 rows of 4 seats each


	do {
		printf("\n");
		printf("Enter Train ID to search for seat availability (e.g., 101A): ");
		scanf("%s", searchTrainID);

		// Convert input Train ID to uppercase
		for (int i = 0; searchTrainID[i]; i++) {
			searchTrainID[i] = toupper(searchTrainID[i]);
		}

		// Validate Train ID
		bool validTrainID = false; //sets to false initially
		for (int i = 0; i < 6; i++) {
			if (strcmp(searchTrainID, (*trains)[i].trainID) == 0) {
				validTrainID = true;
				break;
			}
		}
		if (!validTrainID) {
			printf("Invalid Train ID. Please enter a valid Train ID.\n");
			seatAvailability(&trains, &trainLine); // Prompt user to enter valid Train ID
			return;
		}

		// Input the remaining data
		printf("Enter Sector Code (A to E): ");
		scanf(" %c", &searchSectorCode);
		printf("Enter Row Number (1 to 6): ");
		scanf("%d", &searchRow);
		printf("Enter Seat Number (1 to 4): ");
		scanf("%d", &searchSeat);

		// Convert Sector Code to uppercase
		searchSectorCode = toupper(searchSectorCode);

		// Validate Sector Code
		if (searchSectorCode < 'A' || searchSectorCode > 'E') {
			printf("Invalid Sector Code. Please enter a valid Sector Code (A to E).\n");
			seatAvailability(trains, trainLine);
			return;
		}

		// Validate Row Number
		if (searchRow < 1 || searchRow > 6) {
			printf("Invalid Row Number. Please enter a valid Row Number (1 to 6).\n");
			seatAvailability(trains, trainLine);
			return;
		}

		// Validate Seat Number
		if (searchSeat < 1 || searchSeat > 4) {
			printf("Invalid Seat Number. Please enter a valid Seat Number (1 to 4).\n");
			seatAvailability(trains, trainLine);
			return;
		}

		if (searchSectorCode >= 'A' && searchSectorCode <= 'E' && searchRow >= 1 && searchRow <= 6 && searchSeat >= 1 && searchSeat <= 4) {
			switch (searchSectorCode) {
			case 'A':
				if (seatMapA[searchRow - 1][searchSeat - 1] == 'X') {
					printf("\n");
					printf("Seat %d in Row %d is taken.\n", searchSeat, searchRow);
				}
				else {
					printf("\n");
					printf("Seat %d in Row %d is available.\n", searchSeat, searchRow);
				}
				break;
			case 'B':
				if (seatMapB[searchRow - 1][searchSeat - 1] == 'X') {
					printf("\n");
					printf("Seat %d in Row %d is taken.\n", searchSeat, searchRow);
				}
				else {
					printf("\n");
					printf("Seat %d in Row %d is available.\n", searchSeat, searchRow);
				}
				break;
			case 'C':
				if (seatMapC[searchRow - 1][searchSeat - 1] == 'X') {
					printf("\n");
					printf("Seat %d in Row %d is taken.\n", searchSeat, searchRow);
				}
				else {
					printf("\n");
					printf("Seat %d in Row %d is available.\n", searchSeat, searchRow);
				}
				break;
			case 'D':
				if (seatMapD[searchRow - 1][searchSeat - 1] == 'X') {
					printf("\n");
					printf("Seat %d in Row %d is taken.\n", searchSeat, searchRow);
				}
				else {
					printf("\n");
					printf("Seat %d in Row %d is available.\n", searchSeat, searchRow);
				}
				break;
			case 'E':
				if (seatMapE[searchRow - 1][searchSeat - 1] == 'X') {
					printf("\n");
					printf("Seat %d in Row %d is taken.\n", searchSeat, searchRow);
				}
				else {
					printf("\n");
					printf("Seat %d in Row %d is available.\n", searchSeat, searchRow);
				}
				break;
			default:
				break;
			}
		}
		else {
			printf("\n");
			printf("Invalid row or seat number.\n");
		}
		displaySeatMap(searchSectorCode);
		printf("\n");
		printf("Seat availability check complete.\n");

		printf("\nDo you want to check again? (Y/N): ");
		scanf(" %c", &yesNo);

	} while (yesNo == 'Y' || yesNo == 'y');

	printf("\n");
	printf("Do you want to go back to the main menu? (y/n): ");
	scanf(" %c", &choice);
	rewind(stdin);

	if (choice == 'y' || choice == 'Y') {
		system("cls");
		scheduleMenu();
	}
	else {
		// Exit the program
		printf("Exiting the program...\n");
		exit(-1);
	}

}
void displaySeatMap(char sectorCode) {

	// Display the map based on the sector code
	switch (sectorCode) {
	case 'A':
		printf("\n");
		printf("Displaying Sector A.....\n");
		printf("Seat  1  2  3  4\n");
		printf("Row1  X  X  O  O\n");
		printf("Row2  X  O  O  O\n");
		printf("Row3  O  O  O  O\n");
		printf("Row4  X  X  X  X\n");
		printf("Row5  X  X  X  X\n");
		printf("Row6  O  X  O  O\n");
		break;
	case 'B':
		printf("\n");
		printf("Displaying Sector B.....\n");
		printf("Seat  1  2  3  4\n");
		printf("Row1  X  X  X  X\n");
		printf("Row2  X  O  O  X\n");
		printf("Row3  O  O  O  O\n");
		printf("Row4  O  O  X  X\n");
		printf("Row5  O  O  X  X\n");
		printf("Row6  X  X  O  O\n");
		break;
	case 'C':
		printf("\n");
		printf("Displaying Sector C.....\n");
		printf("Seat  1  2  3  4\n");
		printf("Row1  X  X  O  X\n");
		printf("Row2  X  O  X  O\n");
		printf("Row3  O  O  O  O\n");
		printf("Row4  X  X  O  X\n");
		printf("Row5  O  X  X  X\n");
		printf("Row6  X  O  X  O\n");
		break;
	case 'D':
		printf("\n");
		printf("Displaying Sector D.....\n");
		printf("Seat  1  2  3  4\n");
		printf("Row1  O  O  X  O\n");
		printf("Row2  X  O  X  O\n");
		printf("Row3  O  O  X  X\n");
		printf("Row4  O  X  O  O\n");
		printf("Row5  X  X  O  X\n");
		printf("Row6  O  X  O  O\n");
		break;
	case 'E':
		printf("\n");
		printf("Displaying Sector E.....\n");
		printf("Seat  1  2  3  4\n");
		printf("Row1  O  O  O  O\n");
		printf("Row2  X  O  O  X\n");
		printf("Row3  O  O  O  O\n");
		printf("Row4  X  O  X  X\n");
		printf("Row5  X  O  X  O\n");
		printf("Row6  O  O  X  O\n");
		break;
	default:
		printf("Invalid Sector Code.\n");
		break;
	}

}
int searchSchedule(TrainInfo(*trainSchedule)[6], TrainLine(*trainLinePtr)[3]) {

	int searchLineNo;
	char lineChoice;
	char choice;
	int numStations;

	FILE* scheduleFile;
	scheduleFile = fopen("schedule6.bin", "rb");
	if (scheduleFile == NULL) {
		printf("Error opening the schedule file for reading.\n");
		return 0;
	}


	fread(*trainLinePtr, sizeof(TrainLine), 3, scheduleFile);
	fread(*trainSchedule, sizeof(TrainInfo), 6, scheduleFile);


	printf("\n\n");
	printf("SEARCH SCHEDULE\n");
	printf("===============\n");
	do {
		printf("Enter the Line Number (101, 102, 103): ");
		scanf("%d", &searchLineNo);
		rewind(stdin);
		printf("\nEnter Line A or B (A/B): ");
		scanf("%c", &lineChoice);
		rewind(stdin);

		while (lineChoice != 'A' && lineChoice != 'B' && lineChoice != 'a' && lineChoice != 'b') {
			printf("Invalid input. Please enter Line A or B (A/B): ");
			scanf("%c", &lineChoice);
			rewind(stdin);

		}

		printf("\n");

		while (searchLineNo != 101 && searchLineNo != 102 &&
			searchLineNo != 103) {
			printf("Invalid Line Number. Please enter a valid Line Number (Eg: 101, 102, 103): ");
			scanf("%d", &searchLineNo);
			rewind(stdin);
			printf("\n");
		}

		for (int i = 0; i < 6; i++) {
			if ((*trainSchedule)[i].lineNo == searchLineNo && (*trainSchedule)[i].trainID[3] == lineChoice) {
				printf("\nTrain ID: %s\n", (*trainSchedule)[i].trainID);
				printf("Line Number: %d\n", (*trainSchedule)[i].lineNo);
				printf("|-------------------|-----------------|----------------|--------------|\n");
				printf("| Departure Station | Arrival Station | Departure Time | Arrival Time |\n");
				printf("|-------------------|-----------------|----------------|--------------|\n");

				if (i == 0 || i == 1) {
					numStations = 4;
				}
				else if (i == 4 || i == 5) {
					numStations = 3;
				}
				else {
					numStations = 3;  // Default for most trains
				}

				// Print the schedule for the current train
				for (int j = 0; j < numStations; j++) {
					// Check if the hour is greater than or equal to 12
					if ((*trainSchedule)[i].stationStop[j].dpTime.hour > 12) {
						printf("| %-17s | %-15s | %02d:%02d PM       | ", (*trainSchedule)[i].stationStop[j].stationName,
							(*trainSchedule)[i].stationStop[j + 1].stationName,
							((*trainSchedule)[i].stationStop[j].dpTime.hour - 12), // Convert to PM format
							(*trainSchedule)[i].stationStop[j].dpTime.min);
					}
					else if ((*trainSchedule)[i].stationStop[j].dpTime.hour = 12) {
						printf("| %-17s | %-15s | %02d:%02d PM       | ", (*trainSchedule)[i].stationStop[j].stationName,
							(*trainSchedule)[i].stationStop[j + 1].stationName,
							((*trainSchedule)[i].stationStop[j].dpTime.hour), // Convert to PM format
							(*trainSchedule)[i].stationStop[j].dpTime.min);
					}
					else {
						printf("| %-17s | %-15s | %02d:%02d AM       | ", (*trainSchedule)[i].stationStop[j].stationName,
							(*trainSchedule)[i].stationStop[j + 1].stationName,
							(*trainSchedule)[i].stationStop[j].dpTime.hour,
							(*trainSchedule)[i].stationStop[j].dpTime.min);
					}

					// Check arrival time as well
					if ((*trainSchedule)[i].stationStop[j + 1].arrTime.hour >= 12) {
						printf("%02d:%02d PM     |\n",
							((*trainSchedule)[i].stationStop[j + 1].arrTime.hour - 12), // Convert to PM format
							(*trainSchedule)[i].stationStop[j + 1].arrTime.min);
					}
					else if ((*trainSchedule)[i].stationStop[j].arrTime.hour = 12) {
						printf("%02d:%02d PM     | ",
							((*trainSchedule)[i].stationStop[j + 1].arrTime.hour), // Convert to PM format
							(*trainSchedule)[i].stationStop[j + 1].arrTime.min);
					}
					else {
						printf("%02d:%02d AM    |\n",
							(*trainSchedule)[i].stationStop[j + 1].arrTime.hour,
							(*trainSchedule)[i].stationStop[j + 1].arrTime.min);
					}
				}
				printf("|-------------------|-----------------|----------------|--------------|\n");
			}
		}

		printf("\nDo you want to search for another Line Number? (Y/N): ");
		scanf(" %c", &choice);

	} while (choice == 'Y' || choice == 'y');

	system("cls");
	scheduleMenu();

	fclose(scheduleFile);

}
int insertSchedule(TrainInfo* trains, TrainLine(*trainLinePtr)[3]) {

	FILE* scheduleFile;
	scheduleFile = fopen("schedule6.bin", "ab");
	if (scheduleFile == NULL) {
		printf("Error opening the schedule file for writing.\n");
		return;
	}

	TrainInfo newSchedule;
	int validOrNo = 0;

	do {
		validOrNo = 1;

		printf("Enter Train ID (e.g., 101A): ");
		scanf("%s", newSchedule.trainID);

		if (!(strlen(newSchedule.trainID) == 4 && isdigit(newSchedule.trainID[0]) && isdigit(newSchedule.trainID[1]) && isdigit(newSchedule.trainID[2]) &&
			(newSchedule.trainID[3] == 'A' || newSchedule.trainID[3] == 'B'))) {
			printf("Invalid Train ID format. Please enter a 3-digit number followed by 'A' or 'B'.\n");
			validOrNo = 0;
		}

	} while (!validOrNo);

	printf("Enter Line Number: ");
	scanf("%d", &newSchedule.lineNo);


	int stationCount = 0;
	char addStation;
	do {
		printf("Enter Departure Station: ");
		scanf("%s", newSchedule.stationStop[stationCount].stationName);


		printf("Enter Arrival Station: ");
		scanf("%s", newSchedule.stationStop[stationCount + 1].stationName);

		printf("Enter Departure Time (HH MM): ");
		scanf("%d %d", &newSchedule.stationStop[stationCount].dpTime.hour, &newSchedule.stationStop[stationCount].dpTime.min);

		printf("Enter Arrival Time (HH MM): ");
		scanf("%d %d", &newSchedule.stationStop[stationCount + 1].arrTime.hour, &newSchedule.stationStop[stationCount + 1].arrTime.min);

		stationCount += 2; // Increment by 2 for departure and arrival stations

		printf("Do you want to add another station? (Y/N): ");
		scanf(" %c", &addStation);

	} while (addStation == 'Y' || addStation == 'y');


	fwrite(&newSchedule, sizeof(TrainInfo), 1, scheduleFile);
	fclose(scheduleFile);

	printf("New train schedule inserted:\n");
	printf("Train ID: %s\n", newSchedule.trainID);
	printf("Line Number: %d\n", newSchedule.lineNo);
	printf("Number of Stations: %d\n", stationCount);
	printf("Station Details:\n");
	for (int i = 0; i < stationCount / 2; i++) {
		printf("Station %d: %s\n", i + 1, newSchedule.stationStop[i * 2].stationName);
		printf("Departure Time: %02d:%02d\n", newSchedule.stationStop[i * 2].dpTime.hour, newSchedule.stationStop[i * 2].dpTime.min);
		printf("Arrival Time: %02d:%02d\n", newSchedule.stationStop[i * 2 + 1].arrTime.hour, newSchedule.stationStop[i * 2 + 1].arrTime.min);
	}


	char choice;
	printf("\nDo you want to insert another schedule? (Y/N): ");
	scanf(" %c", &choice);
	if (choice == 'Y' || choice == 'y') {
		insertSchedule(trains, trainLinePtr); // Recursively call insertSchedule if user wants to insert another schedule
	}
	else {
		char backToMenu;
		printf("Do you want to go back to the main menu? (Y/N): ");
		scanf(" %c", &backToMenu);
		if (backToMenu == 'Y' || backToMenu == 'y') {
			system("cls");
			scheduleMenu();
			printf("Returning to main menu...\n");
		}
		else {
			printf("Exiting the program...\n");
			exit(-1);
		}
	}

}
int updateSchedule(TrainInfo* trains, TrainLine(*trainLinePtr)[3]) {

	int numStations = 0;
	int searchLine;
	char updateChoice;
	char lineAB;

	FILE* scheduleFile;
	scheduleFile = fopen("schedule6.bin", "wb");
	if (scheduleFile == NULL) {
		printf("Error opening the schedule file for reading.\n");
		return 0;
	}

	do {
		printf("Enter the Line Number to edit : ");
		scanf("%d", &searchLine);
		rewind(stdin);
		printf("\nEnter Line A or B (A/B): ");
		scanf("%c", &lineAB);
		rewind(stdin);

		while (lineAB != 'A' && lineAB != 'B' && lineAB != 'a' && lineAB != 'b') {
			printf("Invalid input. Please enter Line A or B (A/B): ");
			scanf(" %c", &lineAB);
		}

		printf("\n");

		while (searchLine != 101 && searchLine != 102 &&
			searchLine != 103) {
			printf("Invalid Line Number. Please enter a valid Line Number (101, 102, 103): ");
			scanf("%d", &searchLine);
			printf("\n");
		}

		int updated = 0; // Flag to track if any updates were made

		for (int i = 0; i < 6; i++) {
			if (trains[i].lineNo == searchLine && trains[i].trainID[3] == lineAB) {
				printf("\nTrain ID: %s\n", trains[i].trainID);
				printf("Line Number: %d\n", trains[i].lineNo);
				printf("| Departure Station | Departure Time  | Arrival Station | Arrival Time |\n");
				printf("|-------------------|-----------------|-----------------|--------------|\n");

				// Calculate numStations based on train ID
				int numStations;
				if (i == 0 || i == 1) {
					numStations = 4;  // Other trains have 5 stations
				}
				else if (i == 4 || i == 5) {
					numStations = 3;
				}
				else {
					numStations = 3;  // Default for most trains
				}

				// Print the schedule for the current train
				for (int j = 0; j < numStations; j++) {
					int depHour = trains[i].stationStop[j].dpTime.hour;
					int arrHour = trains[i].stationStop[j + 1].arrTime.hour;

					if (depHour >= 12) {
						depHour -= 12;
						printf("| %-17s | %02d:%02d PM       | %-15s | ",
							trains[i].stationStop[j].stationName,
							(depHour == 0) ? 12 : depHour,
							trains[i].stationStop[j].dpTime.min,
							trains[i].stationStop[j + 1].stationName);
					}
					else {
						printf("| %-17s | %02d:%02d AM       | %-15s | ",
							trains[i].stationStop[j].stationName,
							(depHour == 0) ? 12 : depHour,
							trains[i].stationStop[j].dpTime.min,
							trains[i].stationStop[j + 1].stationName);
					}

					if (arrHour >= 12) {
						arrHour -= 12;
						printf("%02d:%02d PM     |\n",
							(arrHour == 0) ? 12 : arrHour,
							trains[i].stationStop[j + 1].arrTime.min);
						printf("|-------------------|----------------|-----------------|--------------|\n");
					}
					else {
						printf("%02d:%02d AM     |\n",
							(arrHour == 0) ? 12 : arrHour,
							trains[i].stationStop[j + 1].arrTime.min);
						printf("|-------------------|----------------|-----------------|--------------|\n");
					}
				}

				// Allow user to update train information
				printf("======================================\n");
				printf("Enter below to update\n");
				printf("Enter the new TrainID : ");
				scanf("%s", trains[i].trainID);

				printf("\nEnter the new Line number : ");
				scanf("%d", &trains[i].lineNo);

				for (int j = 0; j < numStations; j++) {
					printf("\nEnter the new Departure Station for %s : ", trains[i].stationStop[j].stationName);
					scanf("%s", trains[i].stationStop[j].stationName);
					rewind(stdin);

					printf("\nEnter the new Arrival Station for %s : ", trains[i].stationStop[j + 1].stationName);
					scanf("%s", trains[i].stationStop[j + 1].stationName);
					rewind(stdin);

					printf("\nEnter the new Departure Time for %s (HH MM): ", trains[i].stationStop[j].stationName);
					scanf("%d %d", &trains[i].stationStop[j].dpTime.hour, &trains[i].stationStop[j].dpTime.min);
					rewind(stdin);

					printf("\nEnter the new Arrival Time for %s (HH MM): ", trains[i].stationStop[j + 1].stationName);
					scanf("%d %d", &trains[i].stationStop[j + 1].arrTime.hour, &trains[i].stationStop[j + 1].arrTime.min);
					rewind(stdin);
				}

				printf("Train schedule updated.\n");
				updated = 1; // Update flag
			}
		}

		if (!updated) {
			printf("No train found for the specified Line Number and Line AB.\n");
		}

		printf("Do you want to update another train schedule? (Y/N): ");
		scanf(" %c", &updateChoice);

		if (updateChoice == 'N' || updateChoice == 'n') {
			char backToMenu;
			printf("Do you want to go back to the main menu? (Y/N): ");
			scanf(" %c", &backToMenu);

			if (backToMenu == 'Y' || backToMenu == 'y') {
				system("cls");
				scheduleMenu();
			}
			else {
				exit(-1);
			}
		}

	} while (updateChoice == 'Y' || updateChoice == 'y');

}
int deleteSchedule(TrainInfo* trains, TrainLine(*trainLinePtr)[3]) {
	int searchLineNo;
	char lineChoice;
	FILE* scheduleFile;
	char choice;
	scheduleFile = fopen("schedule6.bin", "rb+");
	if (scheduleFile == NULL) {
		printf("Error opening the schedule file for reading.\n");
		return;
	}

	fread((*trainLinePtr), sizeof(TrainLine), 3, scheduleFile);
	fread(trains, sizeof(TrainInfo), 6, scheduleFile);

	printf("\nDELETE SCHEDULE\n");
	printf("================\n");
	printf("Enter the TrainID : ");
	scanf("%d", &searchLineNo);
	rewind(stdin);

	int found = 0;
	for (int i = 0; i < 6; i++) {
		if (trains[i].lineNo == searchLineNo) {
			// Shift elements to delete the entry
			for (int j = i; j < 7; j++) {
				strcpy(trains[j].trainID, trains[j + 1].trainID);
				trains[j].lineNo = trains[j + 1].lineNo;
				for (int k = 0; k < 6; k++) {
					strcpy(trains[j].stationStop[k].stationName, trains[j + 1].stationStop[k].stationName);
					trains[j].stationStop[k].dpTime.hour = trains[j + 1].stationStop[k].dpTime.hour;
					trains[j].stationStop[k].dpTime.min = trains[j + 1].stationStop[k].dpTime.min;
					trains[j].stationStop[k].arrTime.hour = trains[j + 1].stationStop[k].arrTime.hour;
					trains[j].stationStop[k].arrTime.min = trains[j + 1].stationStop[k].arrTime.min;
				}
			}
			found = 1;
			printf("\nTrain schedule deleted.\n");
			break;
		}
	}

	if (found) {
		fclose(scheduleFile);
		scheduleFile = fopen("schedule6.bin", "wb+");
		if (scheduleFile == NULL) {
			printf("Error opening the schedule file for writing.\n");
			return;
		}
		fwrite((*trainLinePtr), sizeof(TrainLine), 3, scheduleFile);
		fwrite(trains, sizeof(TrainInfo), 6, scheduleFile);
		fclose(scheduleFile);

		printf("Data saved successfully.\n");
	}
	else {
		printf("Train schedule not found.\n");
		fclose(scheduleFile);
	}


	printf("Do you want to go back to the main menu? (y/n): ");
	scanf(" %c", &choice);

	if (choice == 'y' || choice == 'Y') {
		system("cls");
		scheduleMenu();
	}
	else {
		// Exit the program
		printf("Exiting the program...\n");
		exit(-1);
	}
}
int displaySchedule(TrainInfo(*trainSchedule)[6], TrainLine(*trainLinePtr)[3]) {

	int numStations;
	char userChoice;
	int depHour;
	int arrHour;

	printf("\n\n");

	FILE* scheduleFile;
	scheduleFile = fopen("schedule6.bin", "wb+");
	if (scheduleFile == NULL) {
		printf("Error opening the schedule file.\n");
		return -1;
	}
	else {
		fwrite(trainLinePtr, sizeof(TrainLine), 3, scheduleFile);
		fwrite((*trainSchedule), sizeof(TrainInfo), 6, scheduleFile);

		fclose(scheduleFile);
	}

	scheduleFile = fopen("schedule6.bin", "rb");
	if (scheduleFile == NULL) {
		printf("Error opening the schedule file for reading.\n");
		return;
	}

	while (fread(trainLinePtr, sizeof(TrainLine), 3, scheduleFile) &&
		fread((*trainSchedule), sizeof(TrainInfo), 6, scheduleFile)) {


		printf("\nLine Details:\n");
		printf("==============================================================================================================================\n");
		printf("| %-15s | %-10s| %-8s| %-80s|\n", "Train ID", "Line Number", "Line Price", "Line stops");
		printf("------------------------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < 3; i++) {
			printf("| %-15s | %-11d| %-9d | ", (*trainLinePtr)[i].lineName, (*trainLinePtr)[i].lineNo, (*trainLinePtr)[i].linePrice);
			for (int j = 0; j < 5; j++) {
				printf("%s, ", (*trainLinePtr)[i].stationName[j]);
			}
			printf("\n");
		}
		printf("------------------------------------------------------------------------------------------------------------------------------\n");

		for (int i = 0; i < 6; i++) {
			if (strcmp((*trainSchedule)[i].trainID, "") != 0) {
				printf("\nTrain ID: %s\n", (*trainSchedule)[i].trainID);
				printf("Line Number: %d\n", (*trainSchedule)[i].lineNo);
				printf("|-------------------|----------------|-----------------|--------------|\n");
				printf("| Departure Station | Departure Time | Arrival Station | Arrival Time |\n");
				printf("|-------------------|----------------|-----------------|--------------|\n");


				int numStations;

				if (i == 0 || i == 1) {
					numStations = 4;
				}
				else if (i == 4 || i == 5) {
					numStations = 3;
				}
				else {
					numStations = 3;
				}

				for (int j = 0; j < numStations; j++) {

					depHour = (*trainSchedule)[i].stationStop[j].dpTime.hour;
					arrHour = (*trainSchedule)[i].stationStop[j + 1].arrTime.hour;

					if (depHour >= 12) {
						depHour -= 12;
						printf("| %-17s | %02d:%02d PM       | %-15s | ",
							(*trainSchedule)[i].stationStop[j].stationName,
							(depHour == 0) ? 12 : depHour,
							(*trainSchedule)[i].stationStop[j].dpTime.min,
							(*trainSchedule)[i].stationStop[j + 1].stationName);

					}
					else {
						printf("| %-17s | %02d:%02d AM       | %-15s | ",
							(*trainSchedule)[i].stationStop[j].stationName,
							(depHour == 0) ? 12 : depHour,
							(*trainSchedule)[i].stationStop[j].dpTime.min,
							(*trainSchedule)[i].stationStop[j + 1].stationName);

					}

					if (arrHour >= 12) {
						arrHour -= 12;
						printf("%02d:%02d PM     |\n",
							(arrHour == 0) ? 12 : arrHour,
							(*trainSchedule)[i].stationStop[j + 1].arrTime.min);
						printf("|-------------------|----------------|-----------------|--------------|\n");
						;
					}
					else {
						printf("%02d:%02d AM     |\n",
							(arrHour == 0) ? 12 : arrHour,
							(*trainSchedule)[i].stationStop[j + 1].arrTime.min);
						printf("|-------------------|----------------|-----------------|--------------|\n");

					}

				}

			}
		}
		do {
			printf("\nBack to menu? (Y/N): ");
			scanf(" %c", &userChoice);

			if (userChoice == 'Y' || userChoice == 'y') {
				system("cls");
				scheduleMenu();
				break;
			}
			else exit(-1);
		} while (userChoice != 'Y' && userChoice != 'y');
	}
	fclose(scheduleFile);
}
void report(TrainInfo* trains, TrainLine* trainLines) {

	int numStations;
	printf("REPORT GENERATED\n");
	FILE* scheduleFile;
	FILE* report;
	scheduleFile = fopen("schedule6.bin", "rb");
	if (scheduleFile == NULL) {
		printf("Error opening the schedule file.\n");
		return -1;
	}

	report = fopen("scheduleReport.txt", "w");
	if (report == NULL) {
		printf("Error opening the report file.\n");
		return -1;
	}

	while (fread(trainLines, sizeof(TrainLine), 3, scheduleFile) &&
		fread(trains, sizeof(TrainInfo), 6, scheduleFile)) {


		fprintf(report, "\nLine Details:\n");
		fprintf(report, "==============================================================================================================================\n");
		fprintf(report, "| %-15s | %-10s| %-8s| %-80s|\n", "Train ID", "Line Number", "Line Price", "Line stops");
		fprintf(report, "------------------------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < 3; i++) {
			fprintf(report, "| %-15s | %-11d| %-9d | ", trainLines[i].lineName, trainLines[i].lineNo, trainLines[i].linePrice);
			for (int j = 0; j < 5; j++) {
				fprintf(report, "%s, ", trainLines[i].stationName[j]);
			}
			fprintf(report, "\n");
		}
		fprintf(report, "------------------------------------------------------------------------------------------------------------------------------\n");

		for (int i = 0; i < 6; i++) {
			if (strcmp(trains[i].trainID, "") != 0) {
				fprintf(report, "\nTrain ID: %s\n", trains[i].trainID);
				fprintf(report, "Line Number: %d\n", trains[i].lineNo);
				fprintf(report, "|-------------------|----------------|-----------------|--------------|\n");
				fprintf(report, "| Departure Station | Departure Time | Arrival Station | Arrival Time |\n");
				fprintf(report, "|-------------------|----------------|-----------------|--------------|\n");

				int numStations;

				if (i == 0 || i == 1) {
					numStations = 4;
				}
				else if (i == 4 || i == 5) {
					numStations = 3;
				}
				else {
					numStations = 3;
				}

				for (int j = 0; j < numStations; j++) {
					int depHour = trains[i].stationStop[j].dpTime.hour;
					int arrHour = trains[i].stationStop[j + 1].arrTime.hour;

					if (depHour >= 12) {
						depHour -= 12;
						fprintf(report, "| %-17s | %02d:%02d PM       | %-15s | ",
							trains[i].stationStop[j].stationName,
							(depHour == 0) ? 12 : depHour,
							trains[i].stationStop[j].dpTime.min,
							trains[i].stationStop[j + 1].stationName);
					}
					else {
						fprintf(report, "| %-17s | %02d:%02d AM       | %-15s | ",
							trains[i].stationStop[j].stationName,
							(depHour == 0) ? 12 : depHour,
							trains[i].stationStop[j].dpTime.min,
							trains[i].stationStop[j + 1].stationName);
					}

					if (arrHour >= 12) {
						arrHour -= 12;
						fprintf(report, "%02d:%02d PM     |\n",
							(arrHour == 0) ? 12 : arrHour,
							trains[i].stationStop[j + 1].arrTime.min);
						fprintf(report, "|-------------------|----------------|-----------------|--------------|\n");
					}
					else {
						fprintf(report, "%02d:%02d AM     |\n",
							(arrHour == 0) ? 12 : arrHour,
							trains[i].stationStop[j + 1].arrTime.min);
						fprintf(report, "|-------------------|----------------|-----------------|--------------|\n");
					}
				}

			}
			else {
				for (int j = 0; j < 3; j++) {
					fprintf(report, "");
					fprintf(report, "");
				}
			}
		}
	}
	fclose(report);
	fclose(scheduleFile);

}
int modifyScheduleMenu(TrainInfo* trains, TrainLine* trainLines) {

	int userChoice;

	printf("\n");
	printf("Train Scheduling System\n");
	printf("---------------------\n");
	printf("1. Insert new Train Schedule\n");
	printf("2. Update Train Schedule\n");
	printf("3. Delete Train Schedule\n");
	printf("4. Back\n");


	do {
		printf("Enter your choice : ");
		scanf("%d", &userChoice);

		switch (userChoice) {
		case 1:
			system("cls");
			insertSchedule(trains, trainLines);
			break;
		case 2:
			system("cls");
			updateSchedule(trains, trainLines);
			break;
		case 3:
			system("cls");
			deleteSchedule(trains, trainLines);
			break;
		case 4:
			system("cls");
			scheduleMenu();
			break;
		default:
			printf("Please enter again..\n\n");
		}

	} while (userChoice != 1 && userChoice != 2 && userChoice != 3 && userChoice != 4);


}
int scheduleMenu() {

	TrainLine trainLine[3] = {
		{"Liverpool", 101, 50, {"Fenchurch", "Victoria", "Liverpool", "Everton", "Cambridge"}},
		{"King's Cross", 102, 60,{"King's Cross", "Paddington", "Cambridge", "Marylebone"}},
		{"OxSord",  103, 70, {"Oxford", "Leicester", "Marylebone", "Everton", "Waterloo"}}
	};

	TrainInfo trains[6] = {
	   {"101A", 101, {{"Cambridge", {00,11}, {10, 11}}, {"Fenchurch", {40, 12}, {50 , 12}},{"Victoria", {10, 13}, {40 , 13}}, {"Liverpool", {00 , 15}, {20, 15}}, {"Everton", {50 , 17}, {10 , 17}}}},
	   {"101B", 101, {{"Everton", {20 , 9}, {40, 9} }, {"Liverpool", { 10, 11}, { 20, 11} }, {"Victoria", {30, 13},{00, 14} }, {"Fenchurch", {30, 14}, {40, 14} }, {"Cambridge", {50, 15}, {00, 16}}}},
	   {"102A", 102, {{"Cambridge", {20, 9}, {30, 9}}, {"Paddington", {40, 10}, {50, 10}}, {"King's Cross", {10, 12}, {40, 12}}, {"Marylebone", {30, 14}, {40, 14}}}},
	   {"102B", 102, {{"Marylebone", {20, 9}, {30, 9}}, {"King's Cross", {40, 10}, {50, 10}}, {"Paddington", {10, 12}, {40, 12}}, {"Cambridge", {30, 14}, {40, 14}}}},
	   {"103A", 103, {{"Oxford", {20, 9}, {30, 9}}, {"Leicester", {40, 9}, {50, 9}}, {"Marylebone", {10, 10}, {20, 10}}, {"Everton", {30, 10}, {40, 10}}}},
	   {"103B", 103, {{"Everton", {40, 9}, {50, 9}}, {"Marylebone", {10, 10}, {20, 10}}, {"Leicester", {30, 10}, {40, 10}}, {"Oxford", {50, 10}, {00, 11}}}},
	};
	int userChoice;
	system("cls");
	printf("\n");
	printf("Train Scheduling System\n");
	printf("---------------------\n");
	if (toupper(userType) == 'S') {
		printf("1. Modify the Train Schedule\n");
		printf("2. Back to Staff Menu\n");
		do {
			printf("Enter your choice : ");
			scanf("%d", &userChoice);
			rewind(stdin);
			switch (userChoice) {
			case 1:
				system("cls"); modifyScheduleMenu(&trains, &trainLine);
				break;
			case 2:
				system("cls");
				staffMain();
				break;

			default:
				printf("Please enter again..\n\n");
			}

		} while (userChoice != 1 && userChoice != 2 && userChoice != 3 && userChoice != 4 && userChoice != 5 && userChoice != 6);
	}
	else if (toupper(userType) == 'M'){
		printf("1. Display the Train Schedule\n");
		printf("2. Search the Train Schedule\n");
		printf("3. Check Seat Availability\n");
		printf("4. Generate Schedule Report\n");
		printf("5. Back to Main Menu\n");
		do {

			printf("Enter your choice : ");
			scanf("%d", &userChoice);
			rewind(stdin);
			switch (userChoice) {
			case 1:
				system("cls");
				displaySchedule(&trains, &trainLine);
				break;
			case 2:
				system("cls");
				searchSchedule(&trains, &trainLine);
				break;

			case 3:
				system("cls");
				seatAvailability(&trains, &trainLine);
				break;
			case 4:
				system("cls");
				report(trains, trainLine);
				break;
			case 5:
				system("cls");  staffMain(); break;
			default:
				printf("Please enter again..\n\n");
			}

		} while (userChoice != 1 && userChoice != 2 && userChoice != 3 && userChoice != 4 && userChoice != 5 && userChoice != 6);
	}
	

}