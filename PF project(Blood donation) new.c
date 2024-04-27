#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Donor Registration
void donorRegistration() {
  // Get donor's personal information
  char name[100];
  int age;
  char bloodGroup[10];
  int lastDonation;

  printf("Enter your name: ");
  scanf("%s", name);

  printf("Enter your age: ");
  scanf("%d", &age);

  printf("Enter your blood group: ");
  scanf("%s", bloodGroup);

  printf("Enter the date of your last blood donation (YYYYMMDD): ");
  scanf("%d", &lastDonation);

  // Store the donor's information in a database
  FILE *db = fopen("donors.db", "a");
  if (db == NULL) {
    printf("Error opening database.\n");
    return;
  }

  fprintf(db, "%s %d %s %d\n", name, age, bloodGroup, lastDonation);

  fclose(db);

  // Print a success message
  printf("Donor registration successful.\n");
}

// Eligibility Evaluation
int eligibilityEvaluation(int age, char *bloodGroup, int lastDonation) {
  // Check if the donor is old enough
  if (age < 16) {
    return 0;
  }

  // Check if the donor has a compatible blood group
  if (strcmp(bloodGroup, "A+") != 0 && strcmp(bloodGroup, "A-") != 0 &&
      strcmp(bloodGroup, "B+") != 0 && strcmp(bloodGroup, "B-") != 0 &&
      strcmp(bloodGroup, "AB+") != 0 && strcmp(bloodGroup, "AB-") != 0 &&
      strcmp(bloodGroup, "O+") != 0 && strcmp(bloodGroup, "O-") != 0) {
    return 0;
  }

  // Check if the donor has donated blood too recently
  if (lastDonation > (time(NULL) - 7 * 86400)) {
    return 0;
  }

  // The donor is eligible to donate blood
  return 1;
}

// Blood Availability and Requirement
void bloodAvailabilityAndRequirement() {
  // Get the current blood inventory
  FILE *db = fopen("Blood info.txt", "r");
  if (db == NULL) {
    printf("Error opening database.\n");
    return;
  }

  char bloodGroup[10];
  int quantity;

  while (fscanf(db, "%s %d", bloodGroup, &quantity) != EOF) {
    printf("%s: %d\n", bloodGroup, quantity);
  }

  fclose(db);

  

  // Print a message to inform users about the blood shortage
  if (quantity < 100) {
    printf("Blood shortage! Please donate blood today.\n");
  }
}


// Automated Reminder System
void automatedReminderSystem() {
  // Get the list of upcoming appointments
  FILE *db = fopen("Reminder info.txt", "r");
  if (db == NULL) {
    printf("Error opening database.\n");
    return;
  }

  char name[100];
  int date;

  while (fscanf(db, "%s %d", name, &date) != EOF) {
    // Send a reminder to the donor
    printf("Sending reminder to %s about their appointment on %d-%02d-%02d\n", name, date / 10000, (date / 100) % 100, date % 100);
}

fclose(db);
}

// Donor Rewards System
void donorRewardsSystem() {
// Get the list of donors who have donated blood in the past year
FILE *db = fopen("Donors info.txt", "r");
if (db == NULL) {
printf("Error opening database.\n");
return;
}

char name[100];
int age;
char bloodGroup[10];
int lastDonation;
int numberOfDonations;

while (fscanf(db, "%s %d %s %d %d", name, &age, bloodGroup, &lastDonation, &numberOfDonations) != EOF) {
// Check if the donor has donated blood in the past year
if (lastDonation > (time(NULL) - 365 * 86400)) {
// The donor is eligible for rewards
// Get the list of rewards that are available
FILE *rewardsDb = fopen("Rewards info.txt", "r");
if (rewardsDb == NULL) {
printf("Error opening rewards database.\n");
return;
}
  char rewardName[100];
  int rewardPoints;

  while (fscanf(rewardsDb, "%s %d", rewardName, &rewardPoints) != EOF) {
    // Check if the donor has enough points to redeem the reward
    if (numberOfDonations >= rewardPoints) {
      // The donor can redeem the reward
      printf("Donor %s has redeemed the %s reward.\n", name, rewardName);
    }
  }

  fclose(rewardsDb);
}
}

fclose(db);
}

void provideDonorEducation() {
    printf("Thank you for considering blood donation!\n");
    printf("Donating blood is a noble act that can save lives.\n");
    printf("Here are some important guidelines to follow:\n");
    printf("Ensure you are in good health and meet the eligibility criteria.\n");
    printf("Stay hydrated before and after donation.\n");
    printf("Follow post-donation instructions for a quick recovery.\n");
    printf("Remember, your donation can make a difference!\n");
    
    printf("Donor education provided successfully!\n");
}

// Main function
int main() {
// Start the program
printf("Welcome to the Blood Donation System!\n");

// Get the user's choice
int choice;
do {
printf("What would you like to do?\n");
printf("1. Donor Registration\n");
printf("2. Eligibility Evaluation\n");
printf("3. Blood Availability and Requirement\n");
printf("4. Automated Reminder System\n");
printf("5. Donor Rewards System\n");
printf("6. Donor Education\n");
printf("7. Exit\n");
scanf("%d", &choice);

switch (choice) {
  case 1:
    donorRegistration();
    break;
  case 2: {
    // Get donor's personal information
    char name[100];
    int age;
    char bloodGroup[10];
    int lastDonation;

    printf("Enter your name: ");
    scanf("%s", name);

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Enter your blood group: ");
    scanf("%s", bloodGroup);

    printf("Enter the date of your last blood donation (YYYYMMDD): ");
scanf("%d", &lastDonation);

    // Evaluate donor's eligibility
    int isEligible = eligibilityEvaluation(age, bloodGroup, lastDonation);

    // Print the eligibility status
    if (isEligible) {
      printf("You are eligible to donate blood.\n");
    } else {
      printf("You are not eligible to donate blood.\n");
    }
    break;
  }
  case 3:
    bloodAvailabilityAndRequirement();
    break;
  case 4:
    automatedReminderSystem();
    break;
  case 5:
    donorRewardsSystem();
    break;
  case 6:
    provideDonorEducation();
    break;
   case 7:
    printf("Thank you for using the Blood Donation System!\n");
    break;
  default:
    printf("Invalid choice.\n");
}

} while (choice != 7);

// End the program
return 0;
}

